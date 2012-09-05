#pragma once

#include "List.h"
#include "IDictionary.h"

template <class TKey, class TValue>
class Dictionary : public IDictionary<TKey, TValue>, private List<KeyValuePair<TKey, TValue>>
{
public:
	#pragma region Class
	Dictionary()
		: List()
	{
	}

	~Dictionary()
	{
	}  
	#pragma endregion
	
	#pragma region Member - Add/Remove
	void Add(KeyValuePair<TKey, TValue> kvp)
	{
		List::Add(kvp);
	}

	void Add(TKey key, TValue value)
	{
		List::Add(KeyValuePair<TKey, TValue>(key, value));
	}

	bool Remove(TKey key)
	{
		int index = _keyToIndex(key);

		if (index != -1) 
		{
			this->RemoveAt(index);

			return true;
		}

		return false;
	}

	bool Remove(KeyValuePair<TKey, TValue> kvp)
	{
		return List::Remove(kvp);
	}  
	#pragma endregion

	#pragma region Member - Contains/GetValue
	bool Contains(KeyValuePair<TKey, TValue> kvp)
	{
		return List::Contains(kvp);
	}

	bool ContainsKey(TKey key)
	{
		for (UInt32 i = 0; i < this->Count(); i++)
		{
			if (List::Get(i).GetKey() == key) return true;
		}

		return false;
	}

	bool TryGetValue(TKey key, TValue* value)
	{
		int index = _keyToIndex(key);

		if (index != -1)
		{
			*value = List::Get(index).GetValue();

			return true;
		}

		return false;
	}  
	#pragma endregion

	#pragma region Member - Get Lists
	List<TKey>* GetKeys()
	{
		List<TKey>* list = new List<TKey>();

		for (UInt32 i = 0; i < this->Count(); i++)
		{
			list->Add(
				data[i].GetKey()
			);
		}

		list->IsReadOnly = true;

		return list;
	}

	List<TValue>* GetValues()
	{
		List<TValue>* list = new List<TValue>();

		for (UInt32 i = 0; i < this->Count(); i++)
		{
			list->Add(
				data[i].GetValue()
			);
		}

		list->IsReadOnly = true;

		return list;
	}  
	#pragma endregion

	#pragma region Member - Data
	UInt32 Count()
	{
		return List::Count();
	}

	IEnumerator<KeyValuePair<TKey, TValue>>* GetEnumerator()
	{
		return List::GetEnumerator();
	} 

	KeyValuePair<TKey, TValue> Get(UInt32 index)
	{
		return List::Get(index);
	}

	TValue Get(TKey key)
	{
		int index = _keyToIndex(key);

		if (index == -1)
		{
			throw "Key not found.";
		}

		return List::Get(index).GetValue();
	}

	//TValue operator[](TKey key)
	//{
	//	return this->Get(key);
	//}
	#pragma endregion

private:
	#pragma region Private Member
	int _keyToIndex(TKey key)
	{
		for (UInt32 i = 0; i < this->Count(); i++)
		{
			if (List::Get(i).GetKey() == key) return i;
		}

		return -1;
	}  
	#pragma endregion
};