#include "Stdafx.h"
#include "FlatForm.h"


namespace Ivis { namespace Windows { namespace Forms {

	FlatForm::FlatForm()
	{
	}

	FlatForm::~FlatForm()
	{
	}

	//
	//	PaintCustomCaption - Paint window caption text
	//
	void FlatForm::PaintCustomCaption(IntPtr handle, IntPtr handleDc)
	{
		HWND hWnd = intptr_cast<HWND>(handle);
		HDC hdc = intptr_cast<HDC>(handleDc);

		RECT rcClient;
		GetClientRect(hWnd, &rcClient);   
		
		HTHEME hTheme = OpenThemeData(NULL, L"CompositedWindow::Window");
		if (hTheme)
		{
			HDC hdcPaint = CreateCompatibleDC(hdc);
			if (hdcPaint)
			{
				int cx = RECTWIDTH(rcClient);
				int cy = RECTHEIGHT(rcClient);

				// Define the BITMAPINFO structure used to draw text.
				// Note that biHeight is negative. This is done because
				// DrawThemeTextEx() needs the bitmap to be in top-to-bottom
				// order.
				BITMAPINFO dib = { 0 };
				dib.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
				dib.bmiHeader.biWidth = cx;
				dib.bmiHeader.biHeight = -cy;
				dib.bmiHeader.biPlanes = 1;
				dib.bmiHeader.biBitCount = BIT_COUNT;
				dib.bmiHeader.biCompression = BI_RGB;

				HBITMAP hbm = CreateDIBSection(hdc, &dib, DIB_RGB_COLORS, NULL, NULL, 0);

				if (hbm)
				{
					HBITMAP hbmOld = (HBITMAP)SelectObject(hdcPaint, hbm);   // Setup the theme drawing options.
					DTTOPTS dttOpts = { sizeof(DTTOPTS) };
					dttOpts.dwFlags = DTT_COMPOSITED | DTT_GLOWSIZE;
					dttOpts.iGlowSize = 15;

					// Select a font.
					LOGFONT lgFont;
					HFONT hFont = NULL, hFontOld;
					if (SUCCEEDED(GetThemeSysFont(hTheme, TMT_CAPTIONFONT, &lgFont)))
					{
						hFont = CreateFontIndirect(&lgFont);
						if (hFont)
							hFontOld = (HFONT)SelectObject(hdcPaint, hFont);
					}                
					
					// Draw the title.
					RECT rcPaint = rcClient;
					rcPaint.top += 8;
					rcPaint.right -= 125;
					rcPaint.left += 8;
					rcPaint.bottom = 50;

					pin_ptr<const Char> lpszCaption = PtrToStringChars(Form::Text);
					DrawThemeTextEx(hTheme,
						hdcPaint,
						0, 0,
						lpszCaption,
						-1,
						DT_LEFT | DT_WORD_ELLIPSIS,
						&rcPaint,
						&dttOpts);

					// Blit text to the frame.
					BitBlt(hdc, 0, 0, cx, cy, hdcPaint, 0, 0, SRCCOPY);

					if (hFont)
					{
						SelectObject(hdcPaint, hFontOld);
						DeleteObject(hFont);
					}

					SelectObject(hdcPaint, hbmOld);
					DeleteObject(hbm);
				}

				DeleteDC(hdcPaint);
			}

			CloseThemeData(hTheme);
		}
	}


	//
	//	HitTestNCA - Test mouse location at given point
	//
	LRESULT FlatForm::HitTestNCA(HWND hWnd, WPARAM wParam, LPARAM lParam)
	{
		// Get the point coordinates for the hit test.
		POINT ptMouse = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };

		// Get the window rectangle.
		RECT rcWindow;
		GetWindowRect(hWnd, &rcWindow);

		// Get the frame rectangle, adjusted for the style without a caption.
		RECT rcFrame = { 0 };
		AdjustWindowRectEx(&rcFrame, WS_OVERLAPPEDWINDOW & ~WS_CAPTION, FALSE, NULL);

		// Determine if the hit test is for resizing. Default middle (1,1).
		USHORT uRow = 1;
		USHORT uCol = 1;
		bool fOnResizeBorder = false;

		// Determine if the point is at the top or bottom of the window.
		if (ptMouse.y >= rcWindow.top && ptMouse.y < rcWindow.top + TOPEXTENDWIDTH)
		{
			fOnResizeBorder = (ptMouse.y < (rcWindow.top - rcFrame.top));
			uRow = 0;
		}
		else if (ptMouse.y < rcWindow.bottom && ptMouse.y >= rcWindow.bottom - BOTTOMEXTENDWIDTH)
		{
			uRow = 2;
		}

		// Determine if the point is at the left or right of the window.
		if (ptMouse.x >= rcWindow.left && ptMouse.x < rcWindow.left + LEFTEXTENDWIDTH)
		{
			uCol = 0; // left side
		}
		else if (ptMouse.x < rcWindow.right && ptMouse.x >= rcWindow.right - RIGHTEXTENDWIDTH)
		{
			uCol = 2; // right side
		}

		// Hit test (HTTOPLEFT, ... HTBOTTOMRIGHT)
		LRESULT hitTests[3][3] =
		{
			{ HTTOPLEFT, fOnResizeBorder ? HTTOP : HTCAPTION, HTTOPRIGHT },
			{ HTLEFT, HTNOWHERE, HTRIGHT },
			{ HTBOTTOMLEFT, HTBOTTOM, HTBOTTOMRIGHT },
		};

		return hitTests[uRow][uCol];
	}


	//
	//	CustomCaptionProc - Message handler for handling the custom caption messages.
	//
	Boolean FlatForm::CustomCaptionProc(Message %m)
	{
		HWND hWnd = intptr_cast<HWND>(m.HWnd);
		UINT message = (UINT)m.Msg;
		WPARAM wParam = intptr_cast<WPARAM>(m.WParam);
		LPARAM lParam = intptr_cast<LPARAM>(m.LParam);

		LRESULT lRet = 0;
		HRESULT hr = S_OK;
		bool fCallDWP = true; // Pass on to DefWindowProc?

		fCallDWP = !DwmDefWindowProc(hWnd, message, wParam, lParam, &lRet);

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
			lRet = 0;
		}

		// Handle window activation.
		else if (message == WM_ACTIVATE)
		{
			// Extend the frame into the client area.
			MARGINS margins;

			margins.cxLeftWidth = LEFTEXTENDWIDTH;      // 8
			margins.cxRightWidth = RIGHTEXTENDWIDTH;    // 8
			margins.cyBottomHeight = BOTTOMEXTENDWIDTH; // 20
			margins.cyTopHeight = TOPEXTENDWIDTH;       // 27

			hr = DwmExtendFrameIntoClientArea(hWnd, &margins);

			if (!SUCCEEDED(hr))
			{
				// Handle error.
				System::Windows::Forms::MessageBox::Show(this, "Error extending windows frame.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				Application::Exit();
			}

			fCallDWP = true;
			lRet = 0;
		}

		else if (message == WM_PAINT)
		{
			RECT rc = { 0 };
			if (GetUpdateRect(hWnd, &rc, false) == 0)
				return true;

			PAINTSTRUCT ps = { 0 };
			HDC hdc = BeginPaint(hWnd, &ps);

			Graphics^ g = Graphics::FromHdc(IntPtr(hdc));
			System::Drawing::Rectangle rect = System::Drawing::Rectangle::FromLTRB(rc.left, rc.top, rc.right, rc.bottom);
			PaintEventArgs^ pe = gcnew PaintEventArgs(g, rect);
			OnPaint(pe);

			HBRUSH hb = CreateSolidBrush(RGB(210, 210, 207));
			HBRUSH oldB = (HBRUSH)SelectObject(hdc, hb);
			FillRect(hdc, &rc, hb);
			SelectObject(hdc, oldB);
			DeleteBrush(hb);

			IntPtr handle = IntPtr(hWnd);
			IntPtr handleDc = IntPtr(hdc);
			PaintCustomCaption(handle, handleDc);

			EndPaint(hWnd, &ps);

			fCallDWP = true;
			lRet = 0;
		}

		// Handle the non-client size message.
		else if ((message == WM_NCCALCSIZE) && (wParam == TRUE))
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
		else if ((message == WM_NCHITTEST) && (lRet == 0))
		{
			lRet = HitTestNCA(hWnd, wParam, lParam);

			if (lRet != HTNOWHERE)
			{
				fCallDWP = false;
			}
		}

		m.Result = IntPtr(lRet);

		return fCallDWP;
	}

	//
	//	AppWndProc - Message handler for the application.
	//
	void FlatForm::AppWndProc(Message %m)
	{
		HWND hWnd = intptr_cast<HWND>(m.HWnd);
		UINT message = (UINT)m.Msg;
		WPARAM wParam = intptr_cast<WPARAM>(m.WParam);
		LPARAM lParam = intptr_cast<LPARAM>(m.LParam);

		if (message == WM_CREATE)
		{
			return;
		}
		else if (message == WM_PAINT)
		{
			RECT rc = { 0 };
			if (GetUpdateRect(hWnd, &rc, false) == 0)
				return;

			PAINTSTRUCT ps = { 0 };
			HDC hdc = BeginPaint(hWnd, &ps);

			Graphics^ g = Graphics::FromHdc(IntPtr(hdc));
			System::Drawing::Rectangle rect = System::Drawing::Rectangle::FromLTRB(rc.left, rc.top, rc.right, rc.bottom);
			PaintEventArgs^ pe = gcnew PaintEventArgs(g, rect);
			OnPaint(pe);

			HBRUSH hb = CreateSolidBrush(RGB(210, 210, 207));
			HBRUSH oldB = (HBRUSH)SelectObject(hdc, hb);
			FillRect(hdc, &rc, hb);
			SelectObject(hdc, oldB);
			DeleteBrush(hb);

			IntPtr handle = IntPtr(hWnd);
			IntPtr handleDc = IntPtr(hdc);
			PaintCustomCaption(handle, handleDc);

			EndPaint(hWnd, &ps);

			m.Result = IntPtr::Zero;
		}
		else
		{
			Form::WndProc(m);
		}
	}

	//
	//	WndProc - Override Form::WndProc
	//
	void FlatForm::WndProc(Message %m)
	{
		HRESULT hr = S_OK;
		BOOL fDwmEnabled = FALSE;
		bool callDWP = true;

		// Winproc worker for custom frame issues.
		hr = DwmIsCompositionEnabled(&fDwmEnabled); //DWM_EC_DISABLECOMPOSITION);
		if (SUCCEEDED(hr))
			callDWP = CustomCaptionProc(m);

		if (callDWP)
			AppWndProc(m);
	}
}}}