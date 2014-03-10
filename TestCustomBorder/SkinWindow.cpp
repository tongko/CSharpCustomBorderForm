//#include "stdafx.h"
//#include "SkinWindow.h"
//
//
//CSkinWindow::CSkinWindow()
//{
//	InitWindow();
//}
//
//
//CSkinWindow::~CSkinWindow()
//{
//}
//
//VOID	CSkinWindow::ThrowError(LPCTSTR lpszFunction)
//{
//	// Retrieve the system error message for the last-error code
//
//	LPVOID lpMsgBuf;
//	LPVOID lpDisplayBuf;
//	DWORD dw = GetLastError();
//
//	FormatMessage(
//		FORMAT_MESSAGE_ALLOCATE_BUFFER |
//		FORMAT_MESSAGE_FROM_SYSTEM |
//		FORMAT_MESSAGE_IGNORE_INSERTS,
//		NULL,
//		dw,
//		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
//		(LPTSTR)&lpMsgBuf,
//		0, NULL);
//
//	// Display the error message and exit the process
//
//	lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
//		(lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR));
//	StringCchPrintf((LPTSTR)lpDisplayBuf,
//		LocalSize(lpDisplayBuf) / sizeof(TCHAR),
//		TEXT("%s failed with error %d: %s"),
//		lpszFunction, dw, lpMsgBuf);
//	MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);
//
//	LocalFree(lpMsgBuf);
//	LocalFree(lpDisplayBuf);
//	ExitProcess(dw);
//}
//
//VOID	CSkinWindow::InitWindow(VOID)
//{
//	LPCREATEPARAMS lpcp = GetCreateParams();
//
//	LPWNDCLASSEX lpwcex = new WNDCLASSEX();
//	lpwcex->cbSize = sizeof(WNDCLASSEX);
//	lpwcex->style = lpcp->classStyle;
//	lpwcex->lpfnWndProc = StaticWndProc;
//	lpwcex->cbClsExtra = 0;
//	lpwcex->cbWndExtra = 0;
//	lpwcex->hInstance = g_hInstance;
//	lpwcex->hIcon = LoadIcon(g_hInstance, MAKEINTRESOURCE(IDI_TESTCUSTOMBORDER));
//	lpwcex->hCursor = LoadCursor(NULL, IDC_ARROW);
//	lpwcex->hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
//	lpwcex->lpszMenuName = NULL;
//	lpwcex->lpszClassName = lpcp->lpszClassName;
//	lpwcex->hIconSm = LoadIcon(g_hInstance, MAKEINTRESOURCE(IDI_SMALL));
//
//	ATOM atom = RegisterClassEx(lpwcex);
//	if (atom == NULL)
//	{
//		ThrowError(_T("InitWindow"));
//	}
//
//	HWND hwnd = CreateWindowEx(
//		lpcp->dwExStyle,
//		MAKEINTATOM(atom),
//		lpcp->lpszCaption,
//		lpcp->dwStyle,
//		lpcp->x,
//		lpcp->y,
//		lpcp->nWidth,
//		lpcp->nHeight,
//		lpcp->hParent,
//		NULL,
//		g_hInstance,
//		lpcp->lpParam);
//	
//	if (hwnd == NULL)
//	{
//		ThrowError(_T("InitWindow"));
//	}
//
//	SetWindowLongPtr(hwnd, GWLP_USERDATA, WndProc);
//}
//
//LRESULT CALLBACK CSkinWindow::StaticWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
//{
//	LONG_PTR ptr = GetWindowLongPtr(hwnd, GWLP_USERDATA);
//	if (ptr == NULL) return DefWindowProc(hwnd, msg, wParam, lParam);
//
//	WNDPROC wp = (WNDPROC)ptr;
//
//	return wp(hwnd, msg, wParam, lParam);
//}