// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once


#pragma		comment(lib, "user32.lib")
#pragma		comment(lib, "gdi32.lib")
#pragma		comment(lib, "dwmapi.lib")
#pragma		comment(lib, "UxTheme.lib")
#include	<windows.h>
#include	<windowsx.h>
#include	<dwmapi.h>
#include	<UxTheme.h>
#include	<strsafe.h>
#include	<afxres.h>
#include	<vcclr.h>


//	Users defines
#define		LEFTEXTENDWIDTH			8 
#define		RIGHTEXTENDWIDTH		8 
#define		TOPEXTENDWIDTH			27 
#define		BOTTOMEXTENDWIDTH		20 


//	Users include
#include	"Ivis.Platforms.h"
#include	"FlatForm.h"