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

	}

	void FlatForm::OnHandleCreated(EventArgs ^ e)
	{
		m_hWnd = intptr_cast<HWND>(Handle);
		Form::OnHandleCreated(e);
	}

	void FlatForm::OnNcHitTest(NcHitTestEventArgs ^% e)
	{
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
			if (ptMouse.x >= m_ncParams.FirstTitleBarControl.Left && ptMouse.x <= m_ncParams.LastTitleBarControl.Right)
			{
				if (m_ncParams.LastTitleBarControl.Contains(ptMouse.x, ptMouse.y))
					topRightResult = NcHitTestResults::Close;
				else if (m_ncParams.FirstTitleBarControl.Contains(ptMouse.x, ptMouse.y))
					topRightResult = NcHitTestResults::MinButton;
				else
					topRightResult = NcHitTestResults::MaxButton;
			}
			uCol = 2; // right side
		}

		// Hit test (HTTOPLEFT, ... HTBOTTOMRIGHT)
		NcHitTestResults hitTests[3][3] =
		{
			{ NcHitTestResults::TopLeft, fOnResizeBorder ? NcHitTestResults::Top : NcHitTestResults::Caption, topRightResult },
			{ NcHitTestResults::Left, NcHitTestResults::NoWhere, NcHitTestResults::Right},
			{ NcHitTestResults::BottomLeft, NcHitTestResults::Bottom, NcHitTestResults::BottomRight },
		};

		e->Result = hitTests[uRow][uCol];
	}

}}}