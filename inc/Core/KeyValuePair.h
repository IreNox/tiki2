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

	TKey GetKey() const
	{
		return key;
	}

	TValue GetValue() const
	{
		return value;
	}

	bool operator==(const KeyValuePair<TKey, TValue>& kvp) const
	{
		return this->GetKey() == kvp.GetKey();
	}

	bool operator!=(const KeyValuePair<TKey, TValue>& kvp) const
	{
		return !(this->GetKey() == kvp.GetKey());
	}

private:

	TKey key;
	TValue value;
};
