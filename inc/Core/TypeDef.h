#pragma once

#pragma region TypeDef
#ifdef _WIN64
typedef __int64 PInt;
typedef unsigned __int64 UPInt;
#else
typedef __int32 PInt;
typedef unsigned __int32 UPInt;
#endif

typedef unsigned char Byte;
typedef unsigned __int32 Boolean;

typedef __int16 Int16;
typedef __int32 Int32;
typedef __int64 Int64;

typedef unsigned __int16 UInt16;
typedef unsigned __int32 UInt32;
typedef unsigned __int64 UInt64;

typedef float  Single;
typedef double Double;

typedef const char* cstring;
typedef const wchar_t* wcstring;
#pragma endregion

#pragma region Define
#define MATH_PIOVER4	0.785398163
#define MATH_PIOVER2	1.570796327
#define MATH_PI			3.141592654
#define MATH_TWOPI		6.283185307

#ifndef TIKI_EDITOR 
#define TIKI_ENGINE 1
#endif

#define TIKI_CULLING 1
#define TIKI_USE_SCENEGRAPH 0

#if _DEBUG
#include <crtdbg.h>

#define _CRTDBG_MAP_ALLOC
#define TIKI_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#else
#define TIKI_NEW new
#endif
#pragma endregion

#pragma region Macros
#define FOREACH(list, code) UInt32 i = 0; while (i < list.Count()) { code;  i++; }

#define FOREACH_CALL(list, code) UInt32 i = 0; while (i < list.Count()) { list[i].code;  i++; }
#define FOREACH_PTR_CALL(list, code) UInt32 i = 0; while (i < list.Count()) { list[i]->code;  i++; }

#if _DEBUG
#define TIKI_LOG(msg) engine->HLog.Write(msg)
#else
#define TIKI_LOG(msg) 
#endif

#define TIKI_MIN(a, b) (a < b ? a : b);
#define TIKI_MAX(a, b) (a > b ? a : b);
#pragma endregion

