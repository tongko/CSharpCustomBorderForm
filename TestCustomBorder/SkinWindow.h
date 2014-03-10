//#pragma once
//
//
//typedef	struct tagCREATEPARAMS
//{
//	LPCTSTR		lpszCaption;
//	LPCTSTR		lpszClassName;
//	UINT		classStyle;
//	DWORD		dwExStyle;
//	DWORD		dwStyle;
//	int			nHeight;
//	int			nWidth;
//	int			x;
//	int			y;
//	HWND		hParent;
//	LPVOID		lpParam;
//} CREATEPARAMS, *LPCREATEPARAMS;
//
//class CSkinWindow
//{
//public:
//	CSkinWindow();
//	~CSkinWindow();
//
//public:		//	static method
//	static LRESULT CALLBACK		StaticWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
//
//protected:	//	Oparetion
//	VOID						InitWindow(VOID);
//	virtual LRESULT	__stdcall	WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
//
//	virtual VOID				OnCreate(VOID);
//
//private:	//	Operations
//	VOID						ThrowError(LPCTSTR lpszFunction);
//
//public:		//	Attributes
//	virtual LPCREATEPARAMS		GetCreateParams(VOID);
//};
//
