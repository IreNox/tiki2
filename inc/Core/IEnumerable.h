#pragma once

#include "IEnumerator.h"

template<class T>
class IEnumerable
{
public:
	IEnumerable() { };
	virtual ~IEnumerable() { };

	virtual IEnumerator<T>* GetEnumerator() const = 0;
};