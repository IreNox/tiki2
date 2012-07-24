#pragma once

#include "ICollection.h"
#include "KeyValuePair.h"

template <class TKey, class TValue>
class IDictionary : public ICollection<KeyValuePair<TKey, TValue>>
{
public:

	IDictionary(void) { };
	virtual ~IDictionary(void) { };

	virtual void Add(TKey key, TValue value) = 0;
	virtual bool Remove(TKey key) = 0;

	virtual bool ContainsKey(TKey key) = 0;

	virtual bool TryGetValue(TKey key, TValue* value) = 0;

	virtual List<TKey> GetKeys() = 0;
	virtual List<TValue> GetValues() = 0;

	//virtual TValue operator[](TKey key) = 0;
};