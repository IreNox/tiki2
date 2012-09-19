////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_HASHDICTIONARY_ENTRIES_ENUMERATOR_HPP
#define CLODDY_CORE_COLLECTIONS_HASHDICTIONARY_ENTRIES_ENUMERATOR_HPP

#include "Cloddy/HashDictionary_Entries_Enumerator.h"

// Include referenced structures.

#include "Cloddy/DictionaryEntry.hpp"

// Include referenced classes.

#include "Cloddy/EnumeratorBase.hpp"

namespace Cloddy { namespace Core { namespace Collections {

// Use referenced namespaces.

using namespace CodeX;

// -------------------------------------------------------------------------------------------------
// Public / Attributes
// -------------------------------------------------------------------------------------------------

template<class TKey, class TValue>
DictionaryEntry<TKey, TValue> HashDictionary_Entries_Enumerator<TKey, TValue>::GetCurrent()
{
  return DictionaryEntry<TKey, TValue>(keys[node], values[node]);
}

// -------------------------------------------------------------------------------------------------
// Protected / Methods
// -------------------------------------------------------------------------------------------------

template<class TKey, class TValue>
void HashDictionary_Entries_Enumerator<TKey, TValue>::DisposeManaged()
{
  hashtable = null;
  keys = null;
  values = null;
  next = null;
  
  EnumeratorBase<Val<DictionaryEntry<TKey, TValue> > >::DisposeManaged();
}

template<class TKey, class TValue>
bool HashDictionary_Entries_Enumerator<TKey, TValue>::DoNext()
{
  // Advance to next node?
  
  if (node >= 0) node = next[node];
  
  // Need to advance to next hashtable bucket?
  
  if (node == -1) 
  {
    do
    {
      // Reached last bucket?
      
      if (bucket == hashtable.Length()) 
      {
        this->Dispose();
        
        return false;
      }
      
      node = hashtable[bucket++];
    }
    while (node == -1);
  }
  
  return true;
}

// -------------------------------------------------------------------------------------------------
// Private / Constructors
// -------------------------------------------------------------------------------------------------

template<class TKey, class TValue>
HashDictionary_Entries_Enumerator<TKey, TValue>::HashDictionary_Entries_Enumerator(Array<int32> hashtable, Array<typename TKey::Out> keys, Array<typename TValue::Out> values, Array<int32> next)
{
  // Initialize all primitive fields to default values.
  
  this->bucket = 0;
  this->node = 0;
  
  try
  {
    this->hashtable = hashtable;
    this->keys = keys;
    this->values = values;
    this->next = next;
    bucket = 0;
    node = -1;
  }
  catch (...)
  {
    this->Dispose();
    
    throw ;
  }
}

} } } 

#endif
