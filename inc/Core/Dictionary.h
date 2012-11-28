#pragma once

#include "Core/List.h"
#include "Core/KeyValuePair.h"

template <class TKey, class TValue>
class Dictionary
{
public:
	#pragma region Class
	Dictionary()
		: list(), optimized(false)
	{
	}

	~Dictionary()
	{
	}  
	#pragma endregion

	#pragma region Member
	void Clear()
	{
		list.Clear();
	}
	#pragma endregion

	#pragma region Member - Search
	inline void Optimize()
	{
		if (!optimized)
		{
			list.Sort();
			optimized = true;
		}
	}
	#pragma endregion
	
	#pragma region Member - Add/Remove
	inline void Add(KeyValuePair<TKey, TValue> kvp)
	{
		optimized = false;
		list.Add(kvp);
	}

	inline void Add(TKey key, TValue value)
	{
		optimized = false;
		list.Add(KeyValuePair<TKey, TValue>(key, value));
	}

	inline bool Remove(TKey key)
	{
		int index = _keyToIndex(key);

		if (index != -1) 
		{
			list.RemoveAt(index);
			return true;
		}

		return false;
	}

	inline bool Remove(KeyValuePair<TKey, TValue> kvp)
	{
		return list.Remove(kvp);
	}  
	#pragma endregion

	#pragma region Member - Contains/GetValue
	inline bool Contains(KeyValuePair<TKey, TValue> kvp) const
	{
		return list.Contains(kvp);
	}

	inline bool ContainsKey(const TKey& key) const
	{
		return _keyToIndex(key) != -1;
	}

	inline bool TryGetValue(const TKey& key, TValue* value) const
	{
		int index = _keyToIndex(key);

		if (index != -1)
		{
			*value = list[index].GetValue();

			return true;
		}

		return false;
	}  
	#pragma endregion

	#pragma region Member - Get Lists
	inline List<TKey>* GetKeys() const
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

	inline List<TValue>* GetValues() const
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
	inline UInt32 Count() const
	{
		return list.Count();
	}

	inline KeyValuePair<TKey, TValue> GetKVP(UInt32 index) const
	{
		return list.Get(index);
	}

	inline KeyValuePair<TKey, TValue>& GetKVPRef(UInt32 index)
	{
		return list.GetRef(index);
	}

	inline const KeyValuePair<TKey, TValue>& GetKVPCRef(UInt32 index) const
	{
		return list.GetCRef(index);
	}

	inline TValue Get(TKey key) const
	{
		int index = _keyToIndex(key);

		if (index == -1)
		{
			throw "Key not found.";
		}

		return list.Get(index).GetValue();
	}

	inline TValue& GetRef(TKey key)
	{
		int index = _keyToIndex(key);

		if (index == -1)
		{
			throw "Key not found.";
		}

		return list.GetRef(index).GetValueRef();
	}

	inline TValue operator[](TKey key) const
	{
		return this->Get(key);
	}

	inline TValue& operator[](TKey key)
	{
		return this->GetRef(key);
	}
	#pragma endregion

private:

	bool optimized;
	List<KeyValuePair<TKey, TValue>> list;

	#pragma region Private Member
	inline int _keyToIndex(const TKey& key) const
	{
		if (list.Count() == 0) return -1;

		if (optimized)
		{
			UInt32 mid = list.Count() / 2;
			UInt32 step = mid;

			while (true)
			{
				step /= 2;
				
				if (step == 0 && (mid == 0 || list[mid-1] < key) && list[mid+1] > key && list[mid].GetKey() != key)
				{
					break;
				}
				else if (step == 0)
				{
					step = 1;
				}
		
				if (list[mid] < key)
				{
					mid += step;
				}
				else if (list[mid] > key)
				{
					mid -= step;
				}
				else
				{
					return mid;
				}
			}
		}
		else
		{
			UInt32 i = 0;
			while (i < list.Count())
			{
				if (list.GetCRef(i).GetKey() == key) return i;
				i++;
			}
		}

		return -1;
	}
	#pragma endregion

};