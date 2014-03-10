#pragma once

namespace Ivis { namespace Windows { namespace Forms {

	public enum class NcHitTestResults
	{
		Error = -2,		//On the screen background or on a dividing line between windows(same as HTNOWHERE, except that the DefWindowProc function produces a system beep to indicate an error).
		Transparent = -1, //In a window currently covered by another window in the same thread(the message will be sent to underlying windows in the same thread until one of them returns a code that is not HTTRANSPARENT).
		NoWhere = 0,		//On the screen background or on a dividing line between windows.
		Client = 1,		//In a client area.
		Caption = 2,		//In a title bar.
		SysMenu = 3,		//In a window menu or in a Close button in a child window.
		Size = 4,			//In a size box(same as HTGROWBOX).
		Menu = 5,			//In a menu.
		HScroll = 6,		//In a horizontal scroll bar.
		VScroll = 7,		//In the vertical scroll bar.
		MinButton = 8,	//In a Minimize button.
		MaxButton = 9,	//In a Maximize button.
		Left = 10,		//In the left border of a resizable window(the user can click the mouse to resize the window horizontally).
		Right = 11,		//In the right border of a resizable window(the user can click the mouse to resize the window horizontally).
		Top = 12,			//In the upper - horizontal border of a window.
		TopLeft = 13,		//In the upper - left corner of a window border.
		TopRight = 14,	//In the upper - right corner of a window border.
		Bottom = 15,		//In the lower - horizontal border of a resizable window(the user can click the mouse to resize the window vertically).
		BottomLeft = 16,	//In the lower - left corner of a border of a resizable window(the user can click the mouse to resize the window diagonally).
		BottomRight = 17,	//In the lower - right corner of a border of a resizable window(the user can click the mouse to resize the window diagonally).
		Border = 18,		//In the border of a window that does not have a sizing border.
		Close = 20,		//In a Close button.
		Help = 21,		//In a Help button.
	};

	public ref class NcHitTestEventArgs : EventArgs
	{
	public:
		NcHitTestEventArgs(Int32 x, Int32 y);

	public:
		property Int32 X { Int32 get(void); void set(Int32 value); }

		property Int32 Y { Int32 get(void); void set(Int32 value); }

		property NcHitTestResults Result { NcHitTestResults get(void); void set(NcHitTestResults value); }

		property bool IsHandled { bool get(void); void set(bool value); }

	private:
		Int32 m_x;
		Int32 m_y;
		NcHitTestResults m_result;
		bool m_handled;
	};

}}}