#pragma once

#include "Core/TypeDef.h"

template <class T>
class List
{
public:

	bool IsReadOnly;

	#pragma region Class
	List()
		: IsReadOnly(false), lengthArr(0), lengthData(0), data(0)
	{
	}

	List(const List<T>& copy)
		: IsReadOnly(copy.IsReadOnly), lengthArr(copy.lengthArr), lengthData(copy.lengthData), data(TIKI_NEW T[copy.lengthArr])
	{
		UInt32 i = 0;
		while (i < lengthData)
		{
			this->data[i] = copy.data[i];
			i++;
		}
	}

	List(T* data, UInt32 count, bool readOnly)
		: IsReadOnly(readOnly), lengthData(count), lengthArr(2)
	{
		lengthArr = getNextSize(count);

		this->data = TIKI_NEW T[lengthArr];

		UInt32 i = 0;
		while (i < lengthData)
		{
			this->data[i] = data[i];
			i++;
		}
	}

	~List()
	{
		delete[](this->data);
	}
	#pragma endregion

	#pragma region Member
	inline UInt32 Count() const
	{
		return lengthData;
	}

	inline int IndexOf(T item) const
	{
		UInt32 i = 0;
		while (i < lengthData)
		{
			if (this->data[i] == item) return i;
			i++;
		}

		return -1;
	}

	inline void Sort()
	{
		sortQuickSort(0, lengthData - 1);	
	}

	inline void Clear()
	{
		this->lengthData = 0;
	}

	inline bool Contains(T item) const
	{
		return (this->IndexOf(item) != -1);
	}

	inline T* ToArray() const
	{
		UInt32 c = lengthData; 
		T* arr = TIKI_NEW T[c];

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

		UInt32 index = lengthData;
		checkArraySize(lengthData + 1);

		this->data[index] = item;
	}

	inline void AddRange(const List<T>& list)
	{
		this->AddRange(list.data, 0, list.lengthData);
	}

	inline void AddRange(const T* src, Int32 offset, UInt32 length)
	{
		if(length == 0)	return;

		UInt32 index = lengthData;
		checkArraySize(lengthData + length);

		UInt32 i = 0;
		while (i < length)
		{
			data[index + i] = src[i];
			i++;
		}
	}

	inline void Insert(const UInt32& index, T item)
	{
		if (this->IsReadOnly) return;

		UInt32 i = lengthData;
		checkArraySize(lengthData + 1);

		while (i > index)
		{
			T value = data[i - 1];
			this->data[i] = value;

			i--;
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
		if (index >= lengthData) return;

		UInt32 i = index;
		while (i < lengthData - 1)
		{
			T value = data[i + 1];
			data[i] = value;

			i++;
		}

		lengthData--;
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

	inline const T& GetCRef(const UInt32& index) const
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

		this->data = TIKI_NEW T[copy.lengthArr];
		UInt32 i = 0;
		while (i < lengthData)
		{
			this->data[i] = copy.data[i];
			i++;
		}
		
	}
	#pragma endregion

protected:

	T* data;
	UInt32 lengthArr;
	UInt32 lengthData;

private:

	#pragma region Private Member
	inline UInt32 getNextSize(UInt32 targetSize)
	{
		if (lengthArr == 0) lengthArr = 2;

		while (lengthArr <= targetSize)
		{
			lengthArr *= 2;
		}

		return lengthArr;
	}

	inline void checkArraySize(UInt32 neddedSize)
	{
		if (lengthArr < neddedSize)
		{
			lengthArr = getNextSize(neddedSize);
			T* TIKI_NEWData = TIKI_NEW T[lengthArr];

			UInt32 i = 0;
			while (i < lengthData)
			{
				TIKI_NEWData[i] = data[i];
				i++;
			}

			if (data != 0) delete[](data);
			data = TIKI_NEWData;
		}

		lengthData = neddedSize;
	}
	#pragma endregion

	#pragma region Private Member - Sort
	inline void sortQuickSort(int left, int right)
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

	inline UInt32 sortQuickSeperate(int start, int end, int& i, int& j)
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
