#pragma once

#include "IEnumerable.h"

template <class T>
class ICollection : public IEnumerable<T>
{
public:
	bool IsReadOnly;

	ICollection()
		: IsReadOnly(false)
	{
	};
	virtual ~ICollection() { };

	virtual void Add(T item) = 0;
	virtual bool Remove(T item) = 0;

	virtual bool Contains(T item) const = 0;
	
	virtual UInt32 Count() const = 0;
};