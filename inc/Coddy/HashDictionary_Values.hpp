////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_HASHDICTIONARY_VALUES_HPP
#define CLODDY_CORE_COLLECTIONS_HASHDICTIONARY_VALUES_HPP

#include "Cloddy/HashDictionary_Values.h"

// Include referenced enumerations.

#include "CodeX/DisposalPolicy.h"

// Include referenced interfaces.

#include "Cloddy/IEnumerator.h"
#include "Cloddy/IList.h"

// Include referenced classes.

#include "Cloddy/CollectionConstBase.hpp"
#include "CodeX/ErrorInfo.h"
#include "Cloddy/HashDictionary.hpp"
#include "Cloddy/HashDictionary_Values_Enumerator.hpp"
#include "CodeX/InvalidArgumentException.h"

namespace Cloddy { namespace Core { namespace Collections {

// Use referenced namespaces.

using namespace CodeX;
using namespace CodeX::System;

// -------------------------------------------------------------------------------------------------
// Public / Attributes
// -------------------------------------------------------------------------------------------------

template<class TKey, class TValue>
int32 HashDictionary_Values<TKey, TValue>::GetCount()
{
  return dictionary->GetCount();
}

template<class TKey, class TValue>
Ptr<IEnumerator<TValue> > HashDictionary_Values<TKey, TValue>::GetEnumerator()
{
  return new HashDictionary_Values_Enumerator<TValue>(dictionary->hashtable, dictionary->nodeValues, dictionary->nodeNext);
}

// -------------------------------------------------------------------------------------------------
// Public / Methods
// -------------------------------------------------------------------------------------------------

template<class TKey, class TValue>
bool HashDictionary_Values<TKey, TValue>::Contains(typename TValue::In element)
{
  for (int32 i = 0; i < dictionary->hashtable.Length(); i++)
  {
    int32 idx;
    
    idx = dictionary->hashtable[i];
    
    while (idx >= 0)
    {
      if (TValue::Equals(element, dictionary->nodeValues[idx])) return true;
      
      idx = dictionary->nodeNext[idx];
    }
  }
  
  return false;
}

template<class TKey, class TValue>
Array<typename TValue::Out> HashDictionary_Values<TKey, TValue>::ToArrayCopy(Array<typename TValue::Out> array, int32 offset)
{
#ifdef _DEBUG
  if (array == null) throw InvalidArgumentException::NotNull(ZSTRING("HashDictionary_Values.ToArrayCopy"), ZSTRING("array"));
  if (offset < 0) throw InvalidArgumentException::GreaterEqual(ZSTRING("HashDictionary_Values.ToArrayCopy"), ZSTRING("offset"), 0);
#endif
  
  for (int32 i = 0; i < dictionary->hashtable.Length(); i++)
  {
    int32 idx;
    
    idx = dictionary->hashtable[i];
    
    while (idx >= 0)
    {
      array[offset++] = dictionary->nodeValues[idx];
      idx = dictionary->nodeNext[idx];
    }
  }
  
  return array;
}

// -------------------------------------------------------------------------------------------------
// Private / Constructors
// -------------------------------------------------------------------------------------------------

/*!
 * @brief  Creates a new instance of HashDictionary_Values.
 * 
 * @param dictionary The owning dictionary.
 */
template<class TKey, class TValue>
HashDictionary_Values<TKey, TValue>::HashDictionary_Values(HashDictionary<TKey, TValue>* dictionary)
{
  this->dictionary = dictionary;
}

} } } 

#endif
