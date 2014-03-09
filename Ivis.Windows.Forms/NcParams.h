#pragma once


using namespace System;
using namespace System::Collections::Generic;
using namespace System::Drawing;
using Rectangle = System::Drawing::Rectangle;
using IListRc = System::Collections::Generic::IList<Rectangle>;

namespace Ivis { namespace Windows { namespace Forms {

	public value class NcParams	{
	public:
		Int32 TitleBarHeight;
		Int32 MenuBarHeight;
		Int32 BorderWidth;
		Int32 BorderHeight;
		Rectangle HScrollBar;
		Rectangle VScrollBar;

	public:
		property IListRc^ TitleBarControls {
			IListRc^ get(void) {
				return m_tbControls;
			};
			public protected: void set(IListRc^ value) {
				m_tbControls = gcnew List<Rectangle>(value);
			}
		}

		property Rectangle FirstTitleBarControl {
			Rectangle get(void) {
				return m_tbControls[0];
			}
		}

		property Rectangle LastTitleBarControl {
			Rectangle get(void) {
				return m_tbControls[m_tbControls->Count - 1];
			}
		}

	private:
		List<Rectangle>^ m_tbControls;
	};



}}}