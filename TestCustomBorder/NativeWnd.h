#pragma once


namespace windows {

	typedef	struct tagCREATEPARAMS
	{
		LPCTSTR		lpszCaption;
		LPCTSTR		lpszClassName;
		UINT		classStyle;
		DWORD		dwExStyle;
		DWORD		dwStyle;
		int			nHeight;
		int			nWidth;
		int			x;
		int			y;
		HWND		hParent;
		LPVOID		lpParam;
	} CREATEPARAMS, far *LPCREATEPARAMS;

	typedef	struct tagMESSAGE
	{
		HWND		hWnd;
		UINT		msg;
		WPARAM		wParam;
		LPARAM		lParam;
		LRESULT		lResult;
	} MESSAGE, far *LPMESSAGE;

	class CNativeWnd
	{
	public:
		CNativeWnd();
		~CNativeWnd();

	public:		//	Static Operations
		static LRESULT CALLBACK		StaticWndProc01(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
		static LRESULT CALLBACK		StaticWndProc02(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

	public:		//	Operations

	protected:	//	Operations
		virtual VOID WINAPI			WndProc(LPMESSAGE lpMsg);
		virtual LPCREATEPARAMS		GetCreateParams(VOID);
		BOOL						InitializeWindow(VOID);

	private:	//	Fields
		ATOM						m_atom;
		HWND						m_hwnd;
		LPTSTR						m_caption;
		POINT						m_location;
		SIZE						m_size;
	};

}