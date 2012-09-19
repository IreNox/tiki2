////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_HASHDICTIONARY_ENTRIES_HPP
#define CLODDY_CORE_COLLECTIONS_HASHDICTIONARY_ENTRIES_HPP

#include "Cloddy/HashDictionary_Entries.h"

// Include referenced enumerations.

#include "CodeX/DisposalPolicy.h"

// Include referenced structures.

#include "Cloddy/DictionaryEntry.hpp"

// Include referenced interfaces.

#include "Cloddy/IEnumerator.h"
#include "Cloddy/IList.h"

// Include referenced classes.

#include "Cloddy/CollectionConstBase.hpp"
#include "CodeX/ErrorInfo.h"
#include "Cloddy/HashDictionary.hpp"
#include "Cloddy/HashDictionary_Entries_Enumerator.hpp"
#include "CodeX/InvalidArgumentException.h"

namespace Cloddy { namespace Core { namespace Collections {

// Use referenced namespaces.

using namespace CodeX;
using namespace CodeX::System;

// -------------------------------------------------------------------------------------------------
// Public / Attributes
// -------------------------------------------------------------------------------------------------

template<class TKey, class TValue>
int32 HashDictionary_Entries<TKey, TValue>::GetCount()
{
  return dictionary->GetCount();
}

template<class TKey, class TValue>
Ptr<IEnumerator<Val<DictionaryEntry<TKey, TValue> > > > HashDictionary_Entries<TKey, TValue>::GetEnumerator()
{
  return new HashDictionary_Entries_Enumerator<TKey, TValue>(dictionary->hashtable, dictionary->nodeKeys, dictionary->nodeValues, dictionary->nodeNext);
}

// -------------------------------------------------------------------------------------------------
// Public / Methods
// -------------------------------------------------------------------------------------------------

template<class TKey, class TValue>
bool HashDictionary_Entries<TKey, TValue>::Contains(const DictionaryEntry<TKey, TValue>& element)
{
  return dictionary->Contains(element.Key) && TValue::Equals(element.Value, dictionary->Get(element.Key, TValue::Default()));
}

template<class TKey, class TValue>
Array<DictionaryEntry<TKey, TValue> > HashDictionary_Entries<TKey, TValue>::ToArrayCopy(Array<DictionaryEntry<TKey, TValue> > array, int32 offset)
{
#ifdef _DEBUG
  if (array == null) throw InvalidArgumentException::NotNull(ZSTRING("HashDictionary_Entries.ToArrayCopy"), ZSTRING("array"));
  if (offset < 0) throw InvalidArgumentException::GreaterEqual(ZSTRING("HashDictionary_Entries.ToArrayCopy"), ZSTRING("offset"), 0);
#endif
  
  for (int32 i = 0; i < dictionary->hashtable.Length(); i++)
  {
    int32 idx;
    
    idx = dictionary->hashtable[i];
    
    while (idx >= 0)
    {
      array[offset++] = DictionaryEntry<TKey, TValue>(dictionary->nodeKeys[idx], dictionary->nodeValues[idx]);
      idx = dictionary->nodeNext[idx];
    }
  }
  
  return array;
}

// -------------------------------------------------------------------------------------------------
// Private / Constructors
// -------------------------------------------------------------------------------------------------

/*!
 * @brief  Creates a new instance of HashDictionary_Entries.
 * 
 * @param dictionary The owning dictionary.
 */
template<class TKey, class TValue>
HashDictionary_Entries<TKey, TValue>::HashDictionary_Entries(HashDictionary<TKey, TValue>* dictionary)
{
  this->dictionary = dictionary;
}

} } } 

#endif
