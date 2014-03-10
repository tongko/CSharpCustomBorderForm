#include "Stdafx.h"
#include "NcHitTestEventArgs.h"


namespace Ivis { namespace Windows { namespace Forms {

	NcHitTestEventArgs::NcHitTestEventArgs(Int32 x, Int32 y) :
		m_result(NcHitTestResults::NoWhere),
		m_handled(false),
		m_x(x),
		m_y(y)
	{
	}

	Int32 NcHitTestEventArgs::X::get(void)  {
		return m_x;
	}

	void NcHitTestEventArgs::X::set(Int32 value) {
		m_x = value;
	}

	Int32 NcHitTestEventArgs::Y::get(void) {
		return m_y;
	}

	void NcHitTestEventArgs::Y::set(Int32 value) {
		m_y = value;
	}

	NcHitTestResults NcHitTestEventArgs::Result::get(void) {
		return m_result;
	}

	void NcHitTestEventArgs::Result::set(NcHitTestResults value) {
		m_result = value;
	}

	bool NcHitTestEventArgs::IsHandled::get(void) {
		return m_handled;
	}
	void NcHitTestEventArgs::IsHandled::set(bool value) {
		m_handled = value;
	}

}}}