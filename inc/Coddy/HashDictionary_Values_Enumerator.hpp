////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_HASHDICTIONARY_VALUES_ENUMERATOR_HPP
#define CLODDY_CORE_COLLECTIONS_HASHDICTIONARY_VALUES_ENUMERATOR_HPP

#include "Cloddy/HashDictionary_Values_Enumerator.h"

// Include referenced classes.

#include "Cloddy/EnumeratorBase.hpp"

namespace Cloddy { namespace Core { namespace Collections {

// Use referenced namespaces.

using namespace CodeX;

// -------------------------------------------------------------------------------------------------
// Public / Attributes
// -------------------------------------------------------------------------------------------------

template<class TValue>
typename TValue::Out HashDictionary_Values_Enumerator<TValue>::GetCurrent()
{
  return values[node];
}

// -------------------------------------------------------------------------------------------------
// Protected / Methods
// -------------------------------------------------------------------------------------------------

template<class TValue>
void HashDictionary_Values_Enumerator<TValue>::DisposeManaged()
{
  hashtable = null;
  values = null;
  next = null;
  
  EnumeratorBase<TValue>::DisposeManaged();
}

template<class TValue>
bool HashDictionary_Values_Enumerator<TValue>::DoNext()
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

template<class TValue>
HashDictionary_Values_Enumerator<TValue>::HashDictionary_Values_Enumerator(Array<int32> hashtable, Array<typename TValue::Out> values, Array<int32> next)
{
  // Initialize all primitive fields to default values.
  
  this->bucket = 0;
  this->node = 0;
  
  try
  {
    this->hashtable = hashtable;
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
