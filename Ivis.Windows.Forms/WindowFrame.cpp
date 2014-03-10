#include "stdafx.h"
#include "WindowFrame.h"

namespace Ivis { namespace Windows { namespace Forms {

	void WindowFrame::Render(IntPtr hrgnClip)
	{
		if (m_form == nullptr)
			throw gcnew InvalidOperationException(_T("Target form not set."));

		HRGN hrgn = intptr_cast<HRGN>(hrgnClip);
		HDC hdc = GetDCEx(m_form->m_hWnd, (HRGN)hrgn, DCX_WINDOW | DCX_INTERSECTRGN);

		//	Do Paint window frame.

		ReleaseDC(m_form->m_hWnd, hdc);
	}

}}}