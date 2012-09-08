#pragma once

#include "Core/TypeDef.h"
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

	List(T* data, UInt32 count, bool readOnly)
		: lengthData(count - 1), lengthArr(2)
	{
		this->IsReadOnly = readOnly;

		while (lengthArr < count)
		{
			lengthArr = getNextSize();
		}

		this->data = new T[lengthArr];

		for (int i = 0; i < count; i++)
		{
			this->data[i] = data[i];
		}
	}

	~List()
	{
		delete[](this->data);
	}
	#pragma endregion

	#pragma region Member
	UInt32 Count() const
	{
		return this->lengthData + 1;
	}

	int IndexOf(T item) const
	{
		for (int i = 0; i < this->lengthData + 1; i++)
		{
			if (this->data[i] == item) return i;
		}

		return -1;
	}

	void Clear()
	{
		this->lengthData = -1;
	}

	bool Contains(T item) const
	{
		return (this->IndexOf(item) != -1);
	}

	T* ToArray() const
	{
		UInt32 c = lengthData + 1; 
		T* arr = new T[c];

		UInt32 i = 0;
		while (i < c)
		{
			arr[i] = data[i];

			i++;
		}

		return arr;
	}
	#pragma endregion

	#pragma region Member - Add
	void Add(T item)
	{
		if (this->IsReadOnly) return;

		int index = getNewIndex(this->lengthData, true);

		this->data[index] = item;
	}

	void AddRange(T* src, Int32 offset, UInt32 length)
	{
		int index = getNewIndex(this->lengthData + (length - 2), true);

		UInt32 i = 0;
		while (i < length)
		{
			index = getNewIndex(this->lengthData, true);

			data[index] = src[i + offset];
			i++;
		}
	}

	void Insert(UInt32 index, T item)
	{
		if (this->IsReadOnly) return;

		for (UInt32 i = this->lengthArr; i > index; i--)
		{
			bool use = (i < this->Count() + 1);
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

	void RemoveAt(UInt32 index)
	{
		if (this->IsReadOnly) return;

		if ((Int32)index > this->lengthData)
		{
			return;
		}

		for (UInt32 i = index; i < this->Count(); i++)
		{
			bool use = (i < (UInt32)(this->lengthData + 1));
			int newIndex = getNewIndex(i - 1, use);

			if (use)
			{
				T value = this->data[i + 1];
			
				this->data[newIndex] = value;
			}
		}

		this->lengthData--;
	}  
	#pragma endregion

	#pragma region Member - Enumerator
	IEnumerator<T>* GetEnumerator() const
	{
		return new Enumerator<T>(this);
	}
	#pragma endregion

	#pragma region Indexer
	T Get(const int index) const
	{
		return this->data[index];
	}

	void Set(const int index, T value)
	{
		this->data[index] = value;
	}

	T operator[](const int index) const
	{
		return this->data[index];
	}  

	T& operator[](const int index)
	{
		return this->data[index];
	} 
	#pragma endregion

	#pragma region Class - Enumerator
	template <class T>
	class Enumerator : public IEnumerator<T>
	{
	public:
		Enumerator(const List<T>* list)
			: list(list), index(0)
		{
		}

		~Enumerator()
		{
		};

		T Current() const
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
		UInt32 index;
		const List<T>* list;
	};
	#pragma endregion

protected:

	T* data;
	UInt32 lengthArr;
	Int32 lengthData;

private:

	#pragma region Private Member
	int getNextSize()
	{
		return this->lengthArr * 2;
	}

	int getNewIndex(UInt32 in, bool used)
	{
		UInt32 index = in + 1;

		if (index > this->lengthArr - 1)
		{
			int size = getNextSize();
			T* newData = new T[size];

			for (int i = 0; i <= this->lengthData; i++)
			{
				newData[i] = this->data[i];
			}

			delete[](this->data);

			this->data = newData;
			this->lengthArr = size;
		}

		if ((Int32)index > this->lengthData && used) this->lengthData = index;

		return index;
	}
	#pragma endregion
};
