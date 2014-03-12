#include "stdafx.h"
#include "FlatForm.h"

namespace Ivis { namespace Windows { namespace Forms {

	FlatForm::FlatForm(void)
	{
		InitializeComponent();
		//
		//TODO: Add the constructor code here
		//
	}

	FlatForm::~FlatForm(void)
	{
		if (components)
		{
			delete components;
		}
	}

	void FlatForm::WndProc(Message % m)
	{
		bool fCallDWP = true;
		BOOL fDwmEnabled = FALSE;
		LRESULT lRet = 0;
		HRESULT hr = S_OK;

		// Chk Aero is on.
		hr = DwmIsCompositionEnabled(&fDwmEnabled);
		if (SUCCEEDED(hr))
			fCallDWP = NcWndProc(m);

		// Winproc worker for the rest of the application.
		if (fCallDWP)
			//AppWndProc(m);
			Form::DefWndProc(m);
	}

	void FlatForm::AppWndProc(Message % m)
	{
		//HWND hwnd = intptr_cast<HWND>(m.HWnd);
		//UINT message = m.Msg;
		//WPARAM wParam = intptr_cast<WPARAM>(m.WParam);
		//LPARAM lParam = intptr_cast<LPARAM>(m.LParam);
	}

	bool FlatForm::NcWndProc(Message % m)
	{
		HWND hWnd = intptr_cast<HWND>(m.HWnd);
		UINT message = m.Msg;
		WPARAM wParam = intptr_cast<WPARAM>(m.WParam);
		LPARAM lParam = intptr_cast<LPARAM>(m.LParam);

		LRESULT lRet = 0;
		HRESULT hr = S_OK;
		bool fCallDWP = true;

		fCallDWP = !DwmDefWindowProc(hWnd, message, wParam, lParam, &lRet);
		m.Result = IntPtr((int)lRet);

		// Handle window creation.
		if (message == WM_CREATE)
		{
			RECT rcClient;
			GetWindowRect(hWnd, &rcClient);

			// Inform application of the frame change.
			SetWindowPos(hWnd,
				NULL,
				rcClient.left, rcClient.top,
				RECTWIDTH(rcClient), RECTHEIGHT(rcClient),
				SWP_FRAMECHANGED);

			fCallDWP = true;
			m.Result = IntPtr::Zero;
		}

		// Handle window activation.
		else if (message == WM_ACTIVATE)
		{
			// Extend the frame into the client area.
			MARGINS margins;

			margins.cxLeftWidth = m_ncParams.BorderWidth;
			margins.cxRightWidth = m_ncParams.BorderWidth;
			margins.cyBottomHeight = m_ncParams.BorderHeight;
			margins.cyTopHeight = m_ncParams.BorderHeight + m_ncParams.TitleBarHeight;

			hr = DwmExtendFrameIntoClientArea(hWnd, &margins);

			if (!SUCCEEDED(hr))
				Marshal::ThrowExceptionForHR(hr);

			fCallDWP = true;
			m.Result = IntPtr::Zero;
		}

		//	Handle the non-client area painting
		else if (message == WM_NCPAINT)
		{
			HDC hdc = GetDCEx(hWnd, (HRGN)wParam, DCX_WINDOW | DCX_INTERSECTRGN | 0x10000);

			//	Do paint code.
			PaintFrame(hdc);

			ReleaseDC(hWnd, hdc);
		}

		//if (message == WM_PAINT)
		//{
		//	HDC hdc;
		//	{
		//		hdc = BeginPaint(hWnd, &ps);
		//		PaintCustomCaption(hWnd, hdc);
		//		EndPaint(hWnd, &ps);
		//	}

		//	fCallDWP = true;
		//	lRet = 0;
		//}

		// Handle the non-client size message.
		if ((message == WM_NCCALCSIZE) && (wParam == TRUE))
		{
			// Calculate new NCCALCSIZE_PARAMS based on custom NCA inset.
			NCCALCSIZE_PARAMS *pncsp = reinterpret_cast<NCCALCSIZE_PARAMS*>(lParam);

			pncsp->rgrc[0].left = pncsp->rgrc[0].left + 0;
			pncsp->rgrc[0].top = pncsp->rgrc[0].top + 0;
			pncsp->rgrc[0].right = pncsp->rgrc[0].right - 0;
			pncsp->rgrc[0].bottom = pncsp->rgrc[0].bottom - 0;

			lRet = 0;

			// No need to pass the message on to the DefWindowProc.
			fCallDWP = false;
		}

		// Handle hit testing in the NCA if not handled by DwmDefWindowProc.
		if ((message == WM_NCHITTEST) && (lRet == 0))
		{
			int x = GET_X_LPARAM(lParam);
			int y = GET_Y_LPARAM(lParam);

			NcHitTestEventArgs ^ e = gcnew NcHitTestEventArgs(x, y);
			OnNcHitTest(e);

			if (e->Result != NcHitTestResults::NoWhere)
				fCallDWP = false;
		}

		return fCallDWP;
	}


	void FlatForm::OnHandleCreated(EventArgs ^ e)
	{
		m_hWnd = intptr_cast<HWND>(Handle);
		Form::OnHandleCreated(e);
	}


	void FlatForm::OnNcHitTest(NcHitTestEventArgs ^% e)
	{
		NcHitTest(this, e);
		if (e->IsHandled)
			return;

		// Get the point coordinates for the hit test.
		POINT ptMouse = { e->X, e->Y };

		// Get the window rectangle.
		RECT rcWindow;
		GetWindowRect(m_hWnd, &rcWindow);

		// Get the frame rectangle, adjusted for the style without a caption.
		RECT rcFrame;
		SecureZeroMemory(&rcFrame, sizeof(RECT));
		AdjustWindowRectEx(&rcFrame, WS_OVERLAPPEDWINDOW & ~WS_CAPTION, FALSE, NULL);

		// Determine if the hit test is for resizing. Default middle (1,1).
		USHORT uRow = 1;
		USHORT uCol = 1;
		bool fOnResizeBorder = false;
		bool fOnSysMenu = false;
		NcHitTestResults topRightResult = NcHitTestResults::TopRight;

		// Determine if the point is at the top or bottom of the window.
		if (ptMouse.y >= rcWindow.top && ptMouse.y < rcWindow.top + m_ncParams.TitleBarHeight + m_ncParams.BorderHeight)
		{
			fOnResizeBorder = (ptMouse.y < (rcWindow.top - rcFrame.top));
			uRow = 0;
		}
		else if (ptMouse.y < rcWindow.bottom && ptMouse.y >= rcWindow.bottom - m_ncParams.BorderHeight)
		{
			uRow = 2;
		}

		// Determine if the point is at the left or right of the window.
		if (ptMouse.x >= rcWindow.left && ptMouse.x < rcWindow.left + m_ncParams.BorderWidth)
		{
			uCol = 0; // left side
		}
		else if (ptMouse.x < rcWindow.right && ptMouse.x >= rcWindow.right - m_ncParams.BorderWidth)
		{
			uCol = 2; // right side
		}
		else 
		{
			if (uRow == 0 && !fOnResizeBorder)	// On Caption
			{
				if (m_ncParams.SysIcon.Contains(Point(ptMouse.x, ptMouse.y)))
				{
					fOnSysMenu = true;
					uCol = 0;
				}
				else if (ptMouse.x >= m_ncParams.FirstTitleBarControl.Left && ptMouse.x <= m_ncParams.LastTitleBarControl.Right)
				{
					if (m_ncParams.LastTitleBarControl.Contains(ptMouse.x, ptMouse.y))
						topRightResult = NcHitTestResults::Close;
					else if (m_ncParams.FirstTitleBarControl.Contains(ptMouse.x, ptMouse.y))
						topRightResult = NcHitTestResults::MinButton;
					else
						topRightResult = NcHitTestResults::MaxButton;
					uCol = 2;
				}				
			}
		}

		// Hit test (HTTOPLEFT, ... HTBOTTOMRIGHT)
		NcHitTestResults hitTests[3][3] =
		{
			{ fOnSysMenu ? NcHitTestResults::SysMenu : NcHitTestResults::TopLeft, fOnResizeBorder ? NcHitTestResults::Top : NcHitTestResults::Caption, topRightResult },
			{ NcHitTestResults::Left, NcHitTestResults::NoWhere, NcHitTestResults::Right},
			{ NcHitTestResults::BottomLeft, NcHitTestResults::Bottom, NcHitTestResults::BottomRight },
		};

		e->Result = hitTests[uRow][uCol];
	}

}}}