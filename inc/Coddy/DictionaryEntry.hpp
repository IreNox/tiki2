////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_DICTIONARYENTRY_HPP
#define CLODDY_CORE_COLLECTIONS_DICTIONARYENTRY_HPP

#include "Cloddy/DictionaryEntry.h"

namespace Cloddy { namespace Core { namespace Collections {

// Use referenced namespaces.

using namespace CodeX;

// -------------------------------------------------------------------------------------------------
// Public / Constructors
// -------------------------------------------------------------------------------------------------

/*!
 * @brief  Creates a new instance of DictionaryEntry.
 * 
 * @param key The entry key.
 * @param value The entry value.
 */
template<class TKey, class TValue>
DictionaryEntry<TKey, TValue>::DictionaryEntry(typename TKey::In key, typename TValue::In value)
{
  Key = key;
  Value = value;
}

template<class TKey, class TValue>
DictionaryEntry<TKey, TValue>::DictionaryEntry()
{
}

// -------------------------------------------------------------------------------------------------
//  Copy constructor and copy assignment operator
// -------------------------------------------------------------------------------------------------

template<class TKey, class TValue>
DictionaryEntry<TKey, TValue>::DictionaryEntry(const DictionaryEntry<TKey, TValue>& other)
{
  *this = other;
}

template<class TKey, class TValue>
DictionaryEntry<TKey, TValue>& DictionaryEntry<TKey, TValue>::operator=(const DictionaryEntry<TKey, TValue>& other)
{
  Key = other.Key;
  Value = other.Value;
  
  return *this;
}

} } } 

#endif
