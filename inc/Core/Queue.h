
#include "List.h"

template <class T>
class Queue : public List<T>
{
public:
	Queue()
	{
	}

	~Queue()
	{
	}
	
	// Get first
	T Peek()
	{
		if (this->Count() == 0)
		{
			throw "Queue is empty";
		}

		return this->Get(0);
	}

	// Get first and delete
	T Dequeue()
	{
		if (this->Count() == 0)
		{
			throw "Queue is empty";
		}

		T value = this->Get(0);

		this->RemoveAt(0);

		return value;
	}

	// Add
	void Enqueue(T item)
	{
		this->Add(item);
	}
};
