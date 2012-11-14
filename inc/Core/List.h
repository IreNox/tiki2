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

	List(const List<T>& copy)
		: IsReadOnly(copy.IsReadOnly), lengthArr(copy.lengthArr), lengthData(copy.lengthData), data(new T[copy.lengthArr])
	{
		memcpy(
			data,
			copy.data,
			sizeof(T) * lengthArr
		);
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
		int i = 0;
		while (i < lengthData + 1)
		{
			if (this->data[i] == item) return i;
			i++;
		}

		return -1;
	}

	void Sort()
	{
		sortQuickSort(0, lengthData);	
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

	inline void Insert(const UInt32& index, T item)
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

	inline void RemoveAt(const UInt32& index)
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
	inline T Get(const UInt32& index) const
	{
		return this->data[index];
	}

	inline T& GetRef(const UInt32& index)
	{
		return this->data[index];
	}

	inline void Set(const UInt32& index, T value)
	{
		this->data[index] = value;
	}

	inline T operator[](const UInt32& index) const
	{
		return this->data[index];
	}  

	inline T& operator[](const UInt32& index)
	{
		return this->data[index];
	} 
	#pragma endregion

	#pragma region Operators
	inline void operator=(const List<T>& copy)
	{
		delete[](data);

		this->IsReadOnly = copy.IsReadOnly;
		this->lengthArr = copy.lengthArr;
		this->lengthData = copy.lengthData;
		
		this->data = new T[copy.lengthArr];
		memcpy(this->data, copy.data, sizeof(T) * copy.lengthArr);
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

	inline int getNewIndex(const UInt32& in, bool used)
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

	#pragma region Private Member - Sort
	void sortQuickSort(int left, int right)
	{
		int iLeft = left;
		int iRight = right;

		while (right > left)
		{
			UInt32 i = sortQuickSeperate(left, right, iLeft, iRight);

			if (iRight > iLeft)
			{
				sortQuickSort(left, i - 1);
				left = i + 1;
			}
			else
			{
				sortQuickSort(i + 1, right);
				right = i - 1;
			}
		}
	}

	UInt32 sortQuickSeperate(int start, int end, int& i, int& j)
	{
		i = start;
		j = end - 1;
		int p = end;
		T pValue = data[p];

		do
		{
			while (data[i] < pValue && i < end)
			{
				i++;
			}

			while (data[j] >= pValue && j > start)
			{
				j--;
			}

			if (i < j)
			{
				T valueTemp = data[i];
				data[i] = data[j];
				data[j] = valueTemp;
			}
		} while (i < j);

		if (data[i] > pValue)
		{
			T valueTemp = data[i];
			data[i] = data[end];
			data[end] = valueTemp;
		}

		return i;
	}
	#pragma endregion
};
