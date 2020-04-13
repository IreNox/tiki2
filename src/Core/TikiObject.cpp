
#include "Core/TikiObject.h"
#include "Core/TypeGlobals.h"

#if _DEBUG
#include <Windows.h>
#include <sstream>
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
		TIKI_DEBUG_OUTPUT("Used object destroyed.");
	}
#endif
}

Int32 TikiObject::AddRef()
{	
#if _DEBUG
	 refCount++;

	if (this == wrongPtr)
	{
		TIKI_DEBUG_OUTPUT("AddRef wrong Pointer.");
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
		TIKI_DEBUG_OUTPUT("Release Released Object.");
		return -1;
	}

	if (this == wrongPtr)
	{
		TIKI_DEBUG_OUTPUT( "Release wrong Pointer.");
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