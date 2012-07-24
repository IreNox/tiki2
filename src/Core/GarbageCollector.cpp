
#include "Core/GarbageCollector.h"
#include "Core/Object.h"

List<Object*> GC::deleteObjects = List<Object*>();

void GC::Destroy(Object* obj)
{
	deleteObjects.Add(obj);
}

void GC::Collect()
{
	int c = deleteObjects.Count();

	if (c > 0)
	{
		int i = -1;

		while (++i < c)
		{
			delete(deleteObjects[i]);
		}

		deleteObjects.Clear();
	}
}