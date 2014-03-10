// TestCustomBorder.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "TestCustomBorder.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc01(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_TESTCUSTOMBORDER, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TESTCUSTOMBORDER));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DROPSHADOW;
	wcex.lpfnWndProc = WndProc01;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TESTCUSTOMBORDER));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_TESTCUSTOMBORDER);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // Store instance handle in our global variable

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//void PaintCustomCaption(HWND hWnd, HDC hdc)
//{
//	RECT rcClient;
//	GetClientRect(hWnd, &rcClient);
//	
//	HTHEME hTheme = OpenThemeData(NULL, L"CompositedWindow::Window");
//	if (hTheme)
//	{
//		HDC hdcPaint = CreateCompatibleDC(hdc);
//		if (hdcPaint)
//		{
//			int cx = RECTWIDTH(rcClient);
//			int cy = RECTHEIGHT(rcClient);            
//			
//			// Define the BITMAPINFO structure used to draw text.
//			// Note that biHeight is negative. This is done because
//			// DrawThemeTextEx() needs the bitmap to be in top-to-bottom
//			// order.
//			BITMAPINFO dib = { 0 };
//			dib.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
//			dib.bmiHeader.biWidth = cx;
//			dib.bmiHeader.biHeight = -cy;
//			dib.bmiHeader.biPlanes = 1;
//			dib.bmiHeader.biBitCount = 32;
//			dib.bmiHeader.biCompression = BI_RGB;
//
//			HBITMAP hbm = CreateDIBSection(hdc, &dib, DIB_RGB_COLORS, NULL, NULL, 0);
//
//			if (hbm)
//			{
//				HBITMAP hbmOld = (HBITMAP)SelectObject(hdcPaint, hbm);   // Setup the theme drawing options.
//				DTTOPTS DttOpts = { sizeof(DTTOPTS) };
//				DttOpts.dwFlags = DTT_COMPOSITED | DTT_GLOWSIZE;
//				DttOpts.iGlowSize = 15;
//				// Select a font.
//				LOGFONT lgFont;
//				HFONT hFont = NULL, hFontOld = NULL;
//				if (SUCCEEDED(GetThemeSysFont(hTheme, TMT_CAPTIONFONT, &lgFont)))
//				{
//					hFont = CreateFontIndirect(&lgFont);
//					if (hFont)
//						hFontOld = (HFONT)SelectObject(hdcPaint, hFont);
//				}
//				
//				// Draw the title.
//				RECT rcPaint = rcClient;
//				rcPaint.top += 8;
//				rcPaint.right -= 125;
//				rcPaint.left += 8;
//				rcPaint.bottom = 50;
//
//				DrawThemeTextEx(hTheme,
//					hdcPaint,
//					0, 0,
//					TEXT("Test Frame Window"),
//					-1,
//					DT_LEFT | DT_WORD_ELLIPSIS,
//					&rcPaint,
//					&DttOpts);
//				
//				// Blit text to the frame.
//				BitBlt(hdc, rcPaint.left, rcPaint.top, 
//					RECTWIDTH(rcPaint),
//					RECTHEIGHT(rcPaint),
//					hdcPaint, rcPaint.left, rcPaint.top, SRCCOPY);
//
//				if (hFontOld)
//					SelectObject(hdcPaint, hFontOld);
//				if (hFont)
//					DeleteObject(hFont);
//
//				SelectObject(hdcPaint, hbmOld);
//				DeleteObject(hbm);
//			}
//
//			DeleteDC(hdcPaint);
//		}
//
//		CloseThemeData(hTheme);
//	}
//}

// Hit test the frame for resizing and moving.
LRESULT HitTestNCA(HWND hWnd, WPARAM wParam, LPARAM lParam)
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

LRESULT CustomCaptionProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, bool* pfCallDWP)
{
	LRESULT lRet = 0;
	HRESULT hr = S_OK;
	bool fCallDWP = true; // Pass on to DefWindowProc?

	//fCallDWP = !DwmDefWindowProc(hWnd, message, wParam, lParam, &lRet);

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
	if (message == WM_ACTIVATE)
	{
		// Extend the frame into the client area.
		MARGINS margins;

		margins.cxLeftWidth = 8;      // 8
		margins.cxRightWidth = 8;    // 8
		margins.cyBottomHeight = 20; // 20
		margins.cyTopHeight = 27;       // 27

		hr = DwmExtendFrameIntoClientArea(hWnd, &margins);

		if (FAILED(hr))
		{
			// Handle error.
			MessageBox(hWnd, _T("Error extend."), _T("Error"), MB_ICONERROR | MB_OK);
			PostQuitMessage(-1);
		}

		fCallDWP = true;
		lRet = 0;
	}

	if (message == WM_PAINT)
	{
		{
			HDC hdc;
			PAINTSTRUCT ps;
			hdc = BeginPaint(hWnd, &ps);
			HPEN hpn = NULL, hpnOld = NULL;
			hpn = CreatePen(PS_SOLID, 8, RGB(255, 0, 0));
			if (hpn)
			{
				RECT rc = { 0 };
				GetClientRect(hWnd, &rc);

				hpnOld = (HPEN)SelectObject(hdc, hpn);
				Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
				SelectObject(hdc, hpnOld);
				DeleteObject(hpn);
			}
			//PaintCustomCaption(hWnd, hdc);
			EndPaint(hWnd, &ps);
		}

		fCallDWP = true;
		lRet = 0;
	}

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
		lRet = HitTestNCA(hWnd, wParam, lParam);

		if (lRet != HTNOWHERE)
		{
			fCallDWP = false;
		}
	}

	*pfCallDWP = fCallDWP;

	return lRet;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	////	The message is sent to a window when its frame must be painted. We should paint the window here.
	//case WM_NCPAINT:
	//	break;
	////	The message is sent when the size and position of a window's client area must be calculated. By 
	////	processing this message, an application can control the content of the window's client area when
	////	the size or position of the window changes.
	//case WM_NCCALCSIZE:

	//	break;
	////	The message is sent to a window when its non-client area needs to be changed to indicate an active
	////	or inactive state.
	//case WM_NCACTIVATE:
	//	break;
	////	The message is sent to a window when the cursor moves or when a mouse button is pressed or 
	////	released. If the mouse is not captured, the message is sent to the window beneath the
	////	cursor. Otherwise, the message is sent to the window that has captured the mouse.
	//case WM_NCHITTEST:
	//	break;
	////	The message is posted when the user releases the left mouse button while the cursor is within the
	////	non-client area of the window. This message is posted to the window that
	////	contains the cursor. If a window has captured the mouse, this message is not posted.
	//case WM_NCLBUTTONUP:
	//case WM_NCLBUTTONDOWN:
	//case WM_NCLBUTTONDBLCLK:
	//case WM_NCRBUTTONUP:
	//case WM_NCRBUTTONDOWN:
	//case WM_NCMOUSEMOVE:
	//	break;
	////	The message is sent to a window when the size or position of the window is about to change. An
	////	application can use this message to override the window's default maximized size
	////	and position, or its default minimum or maximum tracking size.
	//case WM_GETMINMAXINFO:
	//	break;
	////	The message is sent to both the window being activated and the window being deactivated. If the
	////	windows use the same input queue, the message is sent synchronously. First it is
	////	sent to the window procedure of the top-level window being deactivated and then it is sent to the
	////	window procedure of the top-level window being activated. If the windows use 
	////	different input queues, the message is sent asynchronously, so the window is activated immediately.
	//case WM_ACTIVATE:
	//	break;

	case WM_CREATE:
		break;
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		{
			hdc = BeginPaint(hWnd, &ps);

			HPEN hpn = NULL, hpnOld = NULL;
			hpn = CreatePen(PS_SOLID, 8, RGB(255, 0, 0));
			if (hpn)
			{
				RECT rc = { 0 };
				GetClientRect(hWnd, &rc);

				hpnOld = (HPEN)SelectObject(hdc, hpn);
				Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
				SelectObject(hdc, hpnOld);
				DeleteObject(hpn);
			}
			//PaintCustomCaption(hWnd, hdc);
			EndPaint(hWnd, &ps);
		}

		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

LRESULT CALLBACK WndProc01(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	bool fCallDWP = true;
	BOOL fDwmEnabled = FALSE;
	LRESULT lRet = 0;
	HRESULT hr = S_OK;

	// Winproc worker for custom frame issues.
	hr = DwmIsCompositionEnabled(&fDwmEnabled);
	if (SUCCEEDED(hr))
	{
		lRet = CustomCaptionProc(hWnd, message, wParam, lParam, &fCallDWP);
	}

	// Winproc worker for the rest of the application.
	if (fCallDWP)
	{
		lRet = WndProc(hWnd, message, wParam, lParam);
	}
	return lRet;
}



// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
