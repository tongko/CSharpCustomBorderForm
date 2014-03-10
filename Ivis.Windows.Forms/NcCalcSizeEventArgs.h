#pragma once


namespace Ivis { namespace Windows { namespace Forms {

	using namespace System;
	using namespace System::Drawing;
	using Rectangle = System::Drawing::Rectangle;


	public value struct WindowPosition {
		IntPtr hwnd;
		IntPtr hwndInsertAfter;
		int  x;
		int  y;
		int  cx;
		int  cy;
		int flags;
	};

	public ref class NcCalcSizeEventArgs : EventArgs
	{
	public:
		NcCalcSizeEventArgs(Rectangle proposed, Rectangle original, Rectangle client, WindowPosition windowPos);
	internal:
		NcCalcSizeEventArgs(LPNCCALCSIZE_PARAMS lpParams);

	private:
		WindowPosition		FromWINDOWPOS(LPWINDOWPOS lppos);

	public:
		property Rectangle	Proposed { Rectangle get(void); void set(Rectangle value); }
		property Rectangle	Original { Rectangle get(void); void set(Rectangle value); }
		property Rectangle	ClientRectangle { Rectangle get(void); void set(Rectangle value); }
		property WindowPosition WindowPos { WindowPosition get(void); void set(WindowPosition value); }

	private:
		Rectangle			m_new;
		Rectangle			m_now;
		Rectangle			m_client;
		WindowPosition		m_lppos;
	};

}}}
