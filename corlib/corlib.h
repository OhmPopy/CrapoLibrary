// Perch Lake Computer System

#pragma once
#pragma warning(disable:4514)
#pragma warning(disable:4365)
#pragma warning(disable:4668)
#pragma warning(disable:4710)
#pragma warning(disable:4711)
#pragma warning(disable:4820)

typedef unsigned char byte;
typedef char sbyte;
typedef unsigned long ulong;
typedef const wchar_t* cstring;
typedef wchar_t* wstring;

typedef __int8             int8;
typedef unsigned __int8   uint8;
typedef __int16           int16;
typedef unsigned __int16 uint16;
typedef __int32           int32;
typedef unsigned __int32 uint32;
typedef __int64           int64;
typedef unsigned __int64 uint64;

#ifdef _WIN64
typedef uint64 sizet;
typedef int64  intptr;
typedef uint64 uintptr;
#else
typedef uint32 sizet;
typedef int32  intptr;
typedef uint32 uintptr;
#endif

#define _WINSOCKAPI_
#include <windows.h>
#include <commctrl.h>

#include <cassert>

#ifdef CRAPOCOREDLL_ENABLED
#ifdef CRAPOCOREDLL_EXPORTS
#define CRAPOCOREDLL_API __declspec(dllexport) 
#else
#define CRAPOCOREDLL_API __declspec(dllimport) 
#endif
#else
#define CRAPOCOREDLL_API
#endif


// Global
#include "Application.h"
#include "AutoPtr.h"
#include "Global.Memory.h"

// System namespace
#include "System.h"

// System.Globalization namespace
#include "System.Globalization.CultureInfo.h"
#include "System.Globalization.NumberFormatInfo.h"

#include "System.Collections.h"
#include "System.Collections.Generic.h"

// System.IO namespace
#include "System.IO.h"

#include "System.Runtime.InteropServices.DllImport.h"
#include "System.Runtime.InteropServices.UseCom.h"

#include "System.Text.ASCIIEncoding.h"
//#include "System.Text.DecoderFallback.h"
//#include "systext.decoder_fallback_buffer.h"
#include "System.Text.EncoderFallback.h"
#include "System.Text.EncoderFallbackBuffer.h"
#include "System.Text.Encoding.h"
#include "System.Text.StringBuilder.h"
#include "System.Text.UTF8Encoding.h"
#include "System.Text.Unicode.h"

// System.Threading
#include "System.Threading.h"

#include "Microsoft.Win32.h"

#include "win32.security_attribute.h"
