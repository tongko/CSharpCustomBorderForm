// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once
#pragma comment(lib, "dwmapi.lib") 
#pragma comment(lib, "UxTheme.lib") 

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <dwmapi.h>
#include <Uxtheme.h>
#include <vssym32.h>
#include <windowsx.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <strsafe.h>

// TODO: reference additional headers your program requires here
#include "Resource.h"
#include "NativeWnd.h"
//#include "SkinWindow.h"


#define		RECTWIDTH(x) (x.right - x.left)
#define		RECTHEIGHT(y) (y.bottom - y.top)

#define LEFTEXTENDWIDTH 8 
#define RIGHTEXTENDWIDTH 8 
#define TOPEXTENDWIDTH 27 
#define BOTTOMEXTENDWIDTH 20 