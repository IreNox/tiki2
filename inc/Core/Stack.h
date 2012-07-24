
#include "List.h"

template <class T>
class Stack : public List<T>
{
public:
	Stack()
		: List()
	{
	}
	~Stack()
	{
	}

	// Get last and delete
	T Pop()
	{
		T value = this->Peek();

		this->RemoveAt(this->Count() - 1);

		return value;
	}

	// Get last
    T Peek()
	{
		if (this->Count() == 0)
		{
			throw "Stack is empty";
		}

		return this->Get(this->Count() - 1);
	}

	// Push new
	void Push(T item)
	{
		this->Add(item);
	}
};