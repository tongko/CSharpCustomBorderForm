#pragma once

#include "StdAfx.h"

template<bool Predicate> class STATIC_ASSERT_FAILURE;
template <> class STATIC_ASSERT_FAILURE<true> { };
template <class T> T intptr_cast(System::IntPtr intPtr)
{
	STATIC_ASSERT_FAILURE<sizeof(T) == sizeof(void *)>();

	return reinterpret_cast<T>(intPtr.ToPointer());
};

#define		RECTWIDTH(x) (x.right - x.left)
#define		RECTHEIGHT(y) (y.bottom - y.top)
#define		BIT_COUNT		32
#define		TMT_CAPTIONFONT 5