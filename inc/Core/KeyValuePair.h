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

	inline TKey GetKey() const
	{
		return key;
	}

	inline TValue GetValue() const
	{
		return value;
	}

	inline TValue& GetValueRef()
	{
		return value;
	}

	inline bool operator<(const TKey& rhs) const
	{
		return this->key < rhs;
	}

	inline bool operator>(const TKey& rhs) const
	{
		return this->key > rhs;
	}

	inline bool operator<(const KeyValuePair<TKey, TValue>& kvp) const
	{
		return this->key < kvp.key;
	}

	inline bool operator>(const KeyValuePair<TKey, TValue>& kvp) const
	{
		return this->key > kvp.key;
	}

	inline bool operator<=(const KeyValuePair<TKey, TValue>& kvp) const
	{
		return this->key <= kvp.key;
	}

	inline bool operator>=(const KeyValuePair<TKey, TValue>& kvp) const
	{
		return this->key >= kvp.key;
	}

	inline bool operator==(const KeyValuePair<TKey, TValue>& kvp) const
	{
		return this->key == kvp.key;
	}

	inline bool operator!=(const KeyValuePair<TKey, TValue>& kvp) const
	{
		return this->key != kvp.key;
	}

private:

	TKey key;
	TValue value;

};
