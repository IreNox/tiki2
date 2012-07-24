#pragma once

template <class T>
class IEnumerator
{
public:
	IEnumerator() { };
	virtual ~IEnumerator() { };

	virtual T Current() = 0;

	virtual void Reset() = 0;
	virtual bool MoveNext() = 0;
};
