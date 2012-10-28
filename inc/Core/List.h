#pragma once

#include "Core/TypeDef.h"

template <class T>
class List
{
public:
	bool IsReadOnly;

	#pragma region Class
	List()
		: IsReadOnly(false), lengthArr(2), lengthData(-1), data(new T[2])
	{
	}

	List(T* data, UInt32 count, bool readOnly)
		: IsReadOnly(readOnly), lengthData(count - 1), lengthArr(2)
	{
		while (lengthArr < count)
		{
			lengthArr = getNextSize();
		}

		this->data = new T[lengthArr];

		for (UInt32 i = 0; i < count; i++)
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
	inline UInt32 FirstIndex() const
	{
		return 0;
	}

	inline UInt32 Count() const
	{
		return this->lengthData + 1;
	}

	inline int IndexOf(T item) const
	{
		for (int i = 0; i < this->lengthData + 1; i++)
		{
			if (this->data[i] == item) return i;
		}

		return -1;
	}

	inline void Clear()
	{
		this->lengthData = -1;
	}

	inline bool Contains(T item) const
	{
		return (this->IndexOf(item) != -1);
	}

	inline T* ToArray() const
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
	inline void Add(T item)
	{
		if (this->IsReadOnly) return;

		int index = getNewIndex(this->lengthData, true);

		this->data[index] = item;
	}

	inline void AddRange(const T* src, Int32 offset, UInt32 length)
	{
		Int32 badFix = lengthData;
		int index = getNewIndex(this->lengthData + (length - 2), true);
		lengthData = badFix;

		UInt32 i = 0;
		while (i < length)
		{
			index = getNewIndex(this->lengthData, true);

			data[index] = src[i + offset];
			i++;
		}
	}

	inline void Insert(UInt32 index, T item)
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

	inline const T* GetInternalData() const
	{
		return data;
	}
	#pragma endregion

	#pragma region Member - Remove
	inline bool Remove(T item)
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

	inline void RemoveAt(UInt32 index)
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

	#pragma region Indexer
	inline T Get(const int index) const
	{
		return this->data[index];
	}

	inline void Set(const int index, T value)
	{
		this->data[index] = value;
	}

	inline T operator[](const int index) const
	{
		return this->data[index];
	}  

	inline T& operator[](const int index)
	{
		return this->data[index];
	} 
	#pragma endregion
		
protected:

	T* data;
	UInt32 lengthArr;
	Int32 lengthData;

private:

	#pragma region Private Member
	inline int getNextSize()
	{
		return this->lengthArr * 2;
	}

	inline int getNewIndex(UInt32 in, bool used)
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
