
#include "Core/TikiObject.h"
#include "Core/TypeGlobals.h"

#if _DEBUG
#include <typeinfo.h>
#include <Windows.h>
#include <sstream>
#endif

TikiObject::TikiObject()
	: refCount(1)
{	
}

TikiObject::~TikiObject()
{
	if (refCount > 0)
	{
		OutputDebugString(L"Used object destroyed.");
		//throw "Used object destroyed.";
	}
}

UInt32 TikiObject::AddRef()
{	
#if _DEBUG
	 refCount++;

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
	std::wostringstream s;
	s << L"Release: " << this << L" to " << refCount << L"\n";
	OutputDebugString(s.str().c_str());
#endif

	if (refCount == 0)
	{
		delete this;
	}

	return refCount;
}