
#include "Core/Object.h"
#include "Core/TypeGlobals.h"

#if _DEBUG
#include <typeinfo.h>
#include <Windows.h>
#endif

Object::Object()
	: refCount(1)
{	
}

Object::~Object()
{
	if (refCount > 0)
	{
		OutputDebugString(L"Used object destroyed.");
		//throw "Used object destroyed.";
	}
}

UInt32 Object::AddRef()
{
#if _DEBUG
	wstring text = L"AddRef: " + StringAtoW(typeid(this).name()) + L"\n";
	OutputDebugString(text.c_str());
#endif

	return ++refCount;
}

UInt32 Object::Release()
{
#if _DEBUG
	wstring text = L"Release: " + StringAtoW(typeid(this).name()) + L"\n";
	OutputDebugString(text.c_str());
#endif

	refCount--;

	if (refCount == 0)
	{
		delete this;
	}

	return refCount;
}