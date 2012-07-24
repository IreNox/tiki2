#pragma once

#include "IList.h"

template <class T>
class List : public IList<T>
{
public:
	#pragma region Class
	List()
		: lengthArr(2), lengthData(-1), data(new T[2])
	{
	}

	List(T* data, int count, bool readOnly)
		: lengthArr(count)
	{
		this->IsReadOnly = readOnly;

		lengthData = 2;
		while (lengthData < count)
		{
			lengthData = getNextSize();
		}

		this->data = new T[lengthData];

		for (int i = 0; i < count; i++)
		{
			this->data[i] = data[i];
		}
	}

	~List()
	{
		//delete(this->data);
	}
	#pragma endregion

	#pragma region Member
	int Count()
	{
		return this->lengthData + 1;
	}

	int IndexOf(T item)
	{
		for (int i = 0; i < this->lengthData; i++)
		{
			if (this->data[i] == item) return i;
		}

		return -1;
	}

	void Clear()
	{
		this->lengthData = -1;
	}

	bool Contains(T item)
	{
		return (this->IndexOf(item) != -1);
	}
	#pragma endregion

	#pragma region Member - Add
	void Add(T item)
	{
		if (this->IsReadOnly) return;

		int index = getNewIndex(this->lengthData, true);

		this->data[index] = item;
	}

	void Insert(int index, T item)
	{
		if (this->IsReadOnly) return;

		for (int i = this->lengthArr; i > index; i--)
		{
			bool use = (i < this->lengthData + 2);
			int newIndex = getNewIndex(i - 1, use);

			if (use)
			{
				T value = this->data[i - 1];
			
				this->data[newIndex] = value;
			}
		}

		this->data[index] = item;
	}
	#pragma endregion

	#pragma region Member - Remove
	bool Remove(T item)
	{
		if (this->IsReadOnly) return false;

		int index = this->IndexOf(item);

		if (index != -1)
		{
			this->RemoveAt(index);
			return true;
		}

		return false;
	}

	void RemoveAt(int index)
	{
		if (this->IsReadOnly) return;

		if (index > this->lengthData)
		{
			return;
		}

		this->lengthData--;

		for (int i = index; i < this->lengthArr; i++)
		{
			bool use = (i < this->lengthData + 1);
			int newIndex = getNewIndex(i - 1, use);

			if (use)
			{
				T value = this->data[i + 1];
			
				this->data[newIndex] = value;
			}
		}
	}  
	#pragma endregion

	#pragma region Member - Enumerator
	IEnumerator<T>* GetEnumerator()
	{
		return new Enumerator<T>(this);
	}
	#pragma endregion

	#pragma region Indexer
	T Get(int index)
	{
		return this->data[index];
	}

	T operator[](int index)
	{
		return this->data[index];
	}  
	#pragma endregion

	#pragma region Class - Enumerator
	template <class T>
	class Enumerator : public IEnumerator<T>
	{
	public:
		Enumerator(List<T>* list)
			: list(list), index(0)
		{
		}

		~Enumerator()
		{
		};

		T Current()
		{
			return list->Get(index);
		}

		bool MoveNext()
		{
			if (index < list->Count() - 1)
			{
				index++;
				return true;
			}

			return false;
		}

		void Reset()
		{
			index = 0;
		}

	private:
		int index;
		List<T>* list;
	};
	#pragma endregion

private:
	#pragma region Vars
	T* data;
	int lengthArr;
	int lengthData;  
	#pragma endregion

	#pragma region Private Member
	int getNextSize()
	{
		return this->lengthArr * 2;
	}

	int getNewIndex(int in, bool used)
	{
		int index = in + 1;

		if (index > this->lengthArr - 1)
		{
			int size = getNextSize();
			T* newData = new T[size];

			for (int i = 0; i <= this->lengthData; i++)
			{
				newData[i] = this->data[i];
			}

			delete(this->data);

			this->data = newData;
			this->lengthArr = size;
		}

		if (index > this->lengthData && used) this->lengthData = index;

		return index;
	}
	#pragma endregion
};
