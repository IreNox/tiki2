////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_HASHDICTIONARY_KEYS_ENUMERATOR_HPP
#define CLODDY_CORE_COLLECTIONS_HASHDICTIONARY_KEYS_ENUMERATOR_HPP

#include "Cloddy/HashDictionary_Keys_Enumerator.h"

// Include referenced classes.

#include "Cloddy/EnumeratorBase.hpp"

namespace Cloddy { namespace Core { namespace Collections {

// Use referenced namespaces.

using namespace CodeX;

// -------------------------------------------------------------------------------------------------
// Public / Attributes
// -------------------------------------------------------------------------------------------------

template<class TKey>
typename TKey::Out HashDictionary_Keys_Enumerator<TKey>::GetCurrent()
{
  return keys[node];
}

// -------------------------------------------------------------------------------------------------
// Protected / Methods
// -------------------------------------------------------------------------------------------------

template<class TKey>
void HashDictionary_Keys_Enumerator<TKey>::DisposeManaged()
{
  hashtable = null;
  keys = null;
  next = null;
  
  EnumeratorBase<TKey>::DisposeManaged();
}

template<class TKey>
bool HashDictionary_Keys_Enumerator<TKey>::DoNext()
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

template<class TKey>
HashDictionary_Keys_Enumerator<TKey>::HashDictionary_Keys_Enumerator(Array<int32> hashtable, Array<typename TKey::Out> keys, Array<int32> next)
{
  // Initialize all primitive fields to default values.
  
  this->bucket = 0;
  this->node = 0;
  
  try
  {
    this->hashtable = hashtable;
    this->keys = keys;
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
