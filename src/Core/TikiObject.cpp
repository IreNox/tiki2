
#include "Core/TikiObject.h"
#include "Core/TypeGlobals.h"

#if _DEBUG
#include <typeinfo.h>
#include <Windows.h>
#include <sstream>
#endif

#if _WIN64
TikiObject* wrongPtr = (TikiObject*)0xCDCDCDCDCDCDCDCD;
#else
TikiObject* wrongPtr = (TikiObject*)0xCDCDCDCD;
#endif

TikiObject::TikiObject()
	: refCount(1)
{	
}

TikiObject::~TikiObject()
{
#if _DEBUG
	if (refCount > 0)
	{
		OutputDebugString(L"Used object destroyed.");
		//throw "Used object destroyed.";
	}
#endif
}

UInt32 TikiObject::AddRef()
{	
#if _DEBUG
	 refCount++;

	if (this == wrongPtr)
	{
		throw "AddRef wrong Pointer.";
	}

	std::wostringstream s;
	s << L"AddRef: " << this << L" to " << refCount << L"\n";
	OutputDebugString(s.str().c_str());

	return refCount;
#else
	return ++refCount;
#endif
}

UInt32 TikiObject::Release()
{
	refCount--;

#if _DEBUG
	if (refCount == 0xfeeefeed)
	{
		throw "Release Released Object.";
	}

	if (this == wrongPtr)
	{
		throw "Release wrong Pointer.";
	}

	std::wostringstream s;
	s << L"Release: " << this << L" to " << refCount << L"\n";
	OutputDebugString(s.str().c_str());
#endif

	if (refCount == 0)
	{
		delete this;
		return 0;
	}

	return refCount;
}