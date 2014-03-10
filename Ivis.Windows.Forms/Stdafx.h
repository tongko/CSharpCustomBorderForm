// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once
#pragma	comment(lib, "user32.lib")
#pragma comment(lib, "uxtheme.lib")

#define		WIN32_LEAN_MEAN
#define		VCEXTRALEAN

#include	<windows.h>
#include	<windowsx.h>
#include	<uxtheme.h>
#include	<vssym32.h>
#include	<dwmapi.h>
#include	<tchar.h>
#include	<strsafe.h>


#include	"NcHitTestEventArgs.h"
#include	"NcCalcSizeEventArgs.h"
#include	"NcParams.h"
#include	"WindowFrame.h"
#include	"FlatForm.h"



template<bool Predicate> class STATIC_ASSERT_FAILURE;
template <> class STATIC_ASSERT_FAILURE<true> { };

template <class T> T intptr_cast(System::IntPtr intPtr)
{
	STATIC_ASSERT_FAILURE<sizeof(T) == sizeof(void *)>();

	return reinterpret_cast<T>(intPtr.ToPointer());
};


#define		RECTWIDTH(x) (x.right - x.left)
#define		RECTHEIGHT(y) (y.bottom - y.top)

#define		XINRECT(x, rc) (x >= rc.left && x <= rc.right)
#define		YINRECT(y, rc) (y >= rc.top && y <= rc.bottom)