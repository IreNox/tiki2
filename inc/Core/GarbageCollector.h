#pragma once

#include "Core/List.h"

class Object;

class GC
{
public:

	static void Destroy(Object* obj);

	static void Collect();

private:

	GC() { }
	~GC() { }

	static List<Object*> deleteObjects;
};