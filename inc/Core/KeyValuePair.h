#pragma once

template <class TKey, class TValue>
class KeyValuePair
{
public:
	KeyValuePair()
	{
	}

	KeyValuePair(TKey key, TValue value)
		: key(key), value(value)
	{
	}

	~KeyValuePair()
	{
	}

	TKey GetKey()
	{
		return key;
	}

	TValue GetValue()
	{
		return value;
	}

	bool operator==(KeyValuePair<TKey, TValue>& kvp)
	{
		return this->GetKey() == kvp.GetKey();
	}

	bool operator!=(KeyValuePair<TKey, TValue>& kvp)
	{
		return !(this->GetKey() == kvp.GetKey());
	}

private:
	TKey key;
	TValue value;
};
