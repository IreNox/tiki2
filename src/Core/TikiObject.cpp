
#include "Core/TikiObject.h"
#include "Core/TypeGlobals.h"

#if _DEBUG
#include <typeinfo.h>
#include <Windows.h>
#include <sstream>

#define TIKIOUT(str) OutputDebugStringA(str); \
	_CrtDbgBreak();
#else

#define TIKIOUT(str)

#endif

#if _WIN64
TikiObject* wrongPtr = (TikiObject*)0xCDCDCDCDCDCDCDCD;
#else
TikiObject* wrongPtr = (TikiObject*)0xCDCDCDCD;
#endif


TikiObject::TikiObject()
	: refCount(0)
{	
}

TikiObject::~TikiObject()
{
#if _DEBUG
	if (refCount > 0)
	{
		TIKIOUT("Used object destroyed.");
	}
#endif
}

Int32 TikiObject::AddRef()
{	
#if _DEBUG
	 refCount++;

	if (this == wrongPtr)
	{
		TIKIOUT("AddRef wrong Pointer.");
		return -1;
	}

	return refCount;
#else
	return ++refCount;
#endif
}

Int32 TikiObject::Release()
{
	refCount--;

#if _DEBUG
	if (refCount == 0xfeeefeed)
	{
		TIKIOUT("Release Released Object.");
		return -1;
	}

	if (this == wrongPtr)
	{
		TIKIOUT( "Release wrong Pointer.");
		return -1;
	}
#endif

	if (refCount < 1)
	{
		delete this;
		return 0;
	}

	return refCount;
}