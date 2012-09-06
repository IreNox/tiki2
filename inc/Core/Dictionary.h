#pragma once

#include "List.h"
#include "IDictionary.h"

template <class TKey, class TValue>
class Dictionary : public IDictionary<TKey, TValue>
{
public:
	#pragma region Class
	Dictionary()
		: list()
	{
	}

	~Dictionary()
	{
	}  
	#pragma endregion
	
	#pragma region Member - Add/Remove
	void Add(KeyValuePair<TKey, TValue> kvp)
	{
		list.Add(kvp);
	}

	void Add(TKey key, TValue value)
	{
		list.Add(KeyValuePair<TKey, TValue>(key, value));
	}

	bool Remove(TKey key)
	{
		int index = _keyToIndex(key);

		if (index != -1) 
		{
			list.RemoveAt(index);
			return true;
		}

		return false;
	}

	bool Remove(KeyValuePair<TKey, TValue> kvp)
	{
		return list.Remove(kvp);
	}  
	#pragma endregion

	#pragma region Member - Contains/GetValue
	bool Contains(KeyValuePair<TKey, TValue> kvp) const
	{
		return list.Contains(kvp);
	}

	bool ContainsKey(TKey key) const
	{
		for (UInt32 i = 0; i < this->Count(); i++)
		{
			if (list.Get(i).GetKey() == key) return true;
		}

		return false;
	}

	bool TryGetValue(TKey key, TValue* value) const
	{
		int index = _keyToIndex(key);

		if (index != -1)
		{
			*value = list.Get(index).GetValue();

			return true;
		}

		return false;
	}  
	#pragma endregion

	#pragma region Member - Get Lists
	List<TKey>* GetKeys() const
	{
		List<TKey>* list = new List<TKey>();

		for (UInt32 i = 0; i < this->Count(); i++)
		{
			list->Add(
				this->list.Get(i).GetKey()
			);
		}

		list->IsReadOnly = true;
		return list;
	}

	List<TValue>* GetValues() const
	{
		List<TValue>* list = new List<TValue>();

		for (UInt32 i = 0; i < this->Count(); i++)
		{
			list->Add(
				this->list.Get(i).GetValue()
			);
		}

		list->IsReadOnly = true;
		return list;
	}  
	#pragma endregion

	#pragma region Member - Data
	UInt32 Count() const
	{
		return list.Count();
	}

	IEnumerator<KeyValuePair<TKey, TValue>>* GetEnumerator() const
	{
		return list.GetEnumerator();
	} 

	KeyValuePair<TKey, TValue> Get(UInt32 index) const
	{
		return list.Get(index);
	}

	TValue Get(TKey key) const
	{
		int index = _keyToIndex(key);

		if (index == -1)
		{
			throw "Key not found.";
		}

		return list.Get(index).GetValue();
	}

	TValue operator[](TKey key) const
	{
		return this->Get(key);
	}
	#pragma endregion

private:

	List<KeyValuePair<TKey, TValue>> list;

	#pragma region Private Member
	int _keyToIndex(TKey key) const
	{
		for (UInt32 i = 0; i < this->Count(); i++)
		{
			if (list.Get(i).GetKey() == key) return i;
		}

		return -1;
	}  
	#pragma endregion

};