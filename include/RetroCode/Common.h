#pragma once

#include <afxwin.h>
#include <afxtempl.h>
#include <afxmt.h>

#include <atlbase.h>

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif
#include <math.h>

#ifdef _DEBUG
	#define RETRO_MODULE_EXT _T("d")
#else
	#define RETRO_MODULE_EXT
#endif

#define RETRO_NULL_WHILE_LOOP_CONDITION (-1 == __LINE__)

#ifndef UNREFERENCED_PARAMETER
	#define UNREFERENCED_PARAMETER(P) (P)
#endif