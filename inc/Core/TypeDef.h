#pragma once

#ifdef _WIN64
typedef __int64 IntPtr;
#else
typedef __int32 IntPtr;
#endif

typedef __int32 IntSize;

typedef unsigned char Byte;

typedef __int16 Int16;
typedef __int32 Int32;
typedef __int64 Int64;

typedef unsigned __int16 UInt16;
typedef unsigned __int32 UInt32;
typedef unsigned __int64 UInt64;

typedef float  Single;
typedef double Double;

typedef bool Boolean;

typedef const char* cstring;
typedef const wchar_t* wcstring;

#define MATH_PI 3.1415926535f