#pragma once

#include "ICollection.h"

template <class T>
class IList : public ICollection<T>
{
public:
	IList(void) { };
	virtual ~IList(void) { };

	virtual void Clear() = 0;

	virtual void Insert(int index, T item) = 0;
	virtual void RemoveAt(int index) = 0;

	virtual int IndexOf(T item) = 0;

	virtual T* ToArray() = 0;

	virtual T operator[](int index) = 0;
};