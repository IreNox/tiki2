#pragma once

#include "ICollection.h"

template <class T>
class IList : public ICollection<T>
{
public:
	IList(void) { };
	virtual ~IList(void) { };

	virtual void AddRange(T* data, Int32 offset, UInt32 length) = 0;

	virtual void Clear() = 0;

	virtual void Insert(UInt32 index, T item) = 0;
	virtual void RemoveAt(UInt32 index) = 0;

	virtual Int32 IndexOf(T item) const = 0;

	virtual T* ToArray() const = 0;
};