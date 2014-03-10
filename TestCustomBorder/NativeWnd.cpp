#include "stdafx.h"
#include "NativeWnd.h"
#include <crtdbg.h>

namespace windows {

	CNativeWnd::CNativeWnd()
	{
	}


	CNativeWnd::~CNativeWnd()
	{
	}

	//
	//	Register window class, create window.
	//
	BOOL CNativeWnd::InitializeWindow(VOID)
	{
		HINSTANCE g_hInst = NULL;
		LPCREATEPARAMS lpcp = GetCreateParams();
		LPWNDCLASSEX lpwcex = new WNDCLASSEX();
		lpwcex->cbSize = sizeof(WNDCLASSEX);
		lpwcex->style = lpcp->classStyle;
		lpwcex->lpfnWndProc = StaticWndProc01;
		lpwcex->cbClsExtra = 0;
		lpwcex->cbWndExtra = sizeof(CNativeWnd *);	//	Need to store class pointer in per-window data.
		lpwcex->hInstance = g_hInst;
		lpwcex->hIcon = LoadIcon(g_hInst, MAKEINTRESOURCE(IDI_TESTCUSTOMBORDER));
		lpwcex->hCursor = LoadCursor(g_hInst, MAKEINTRESOURCE(IDC_ARROW));
		lpwcex->hbrBackground = (HBRUSH)(COLOR_APPWORKSPACE + 1);
		lpwcex->lpszMenuName = NULL;
		lpwcex->lpszClassName = lpcp->lpszClassName;
		lpwcex->hIconSm = LoadIcon(g_hInst, MAKEINTRESOURCE(IDI_SMALL));

		m_atom = RegisterClassEx(lpwcex);
		delete lpwcex;

		return m_atom == 0 ? FALSE : TRUE;
	}

	//
	//	Get window creation parameter
	//
	LPCREATEPARAMS CNativeWnd::GetCreateParams(VOID)
	{
		CREATEPARAMS cp = {
			_T("Native Window"),
			_T("CNativeWnd"),
			CS_HREDRAW | CS_VREDRAW,
			WS_EX_APPWINDOW | WS_EX_LEFT | WS_EX_LTRREADING,
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			NULL,
			this
		};

		return &cp;
	}

	//
	//	Satic Window Procedure 01
	//
	LRESULT CALLBACK	CNativeWnd::StaticWndProc01(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
	{
		if (msg == WM_GETMINMAXINFO)
		{
			LPCREATESTRUCT lpcs = (LPCREATESTRUCT)lp;
			// Set associated this pointer
			SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG)lpcs->lpCreateParams);
			// Reset the window message handler
			SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG)StaticWndProc02);
			// Dispatch WM_NCCREATE to the member message handler
			return StaticWndProc02(hwnd, msg, wp, lp);
		}
		else
			return DefWindowProc(hwnd, msg, wp, lp);
	}

	//
	//	Satic Window Procedure 02
	//
	LRESULT CALLBACK	CNativeWnd::StaticWndProc02(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
	{
		CNativeWnd *w = (CNativeWnd *)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		_ASSERT(w);

		LPMESSAGE lpMsg = new MESSAGE();
		*lpMsg = { hwnd, msg, wp, lp, 0 };

		w->WndProc(lpMsg);

		return lpMsg->lResult;
	}

	VOID	CNativeWnd::WndProc(LPMESSAGE lpMsg)
	{

	}
}