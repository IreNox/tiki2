////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_HASHDICTIONARY_KEYS_HPP
#define CLODDY_CORE_COLLECTIONS_HASHDICTIONARY_KEYS_HPP

#include "Cloddy/HashDictionary_Keys.h"

// Include referenced enumerations.

#include "CodeX/DisposalPolicy.h"

// Include referenced interfaces.

#include "Cloddy/IEnumerator.h"
#include "Cloddy/IList.h"

// Include referenced classes.

#include "Cloddy/CollectionConstBase.hpp"
#include "CodeX/ErrorInfo.h"
#include "Cloddy/HashDictionary.hpp"
#include "Cloddy/HashDictionary_Keys_Enumerator.hpp"
#include "CodeX/InvalidArgumentException.h"

namespace Cloddy { namespace Core { namespace Collections {

// Use referenced namespaces.

using namespace CodeX;
using namespace CodeX::System;

// -------------------------------------------------------------------------------------------------
// Public / Attributes
// -------------------------------------------------------------------------------------------------

template<class TKey, class TValue>
int32 HashDictionary_Keys<TKey, TValue>::GetCount()
{
  return dictionary->GetCount();
}

template<class TKey, class TValue>
Ptr<IEnumerator<TKey> > HashDictionary_Keys<TKey, TValue>::GetEnumerator()
{
  return new HashDictionary_Keys_Enumerator<TKey>(dictionary->hashtable, dictionary->nodeKeys, dictionary->nodeNext);
}

// -------------------------------------------------------------------------------------------------
// Public / Methods
// -------------------------------------------------------------------------------------------------

template<class TKey, class TValue>
bool HashDictionary_Keys<TKey, TValue>::Contains(typename TKey::In element)
{
  return dictionary->Contains(element);
}

template<class TKey, class TValue>
Array<typename TKey::Out> HashDictionary_Keys<TKey, TValue>::ToArrayCopy(Array<typename TKey::Out> array, int32 offset)
{
#ifdef _DEBUG
  if (array == null) throw InvalidArgumentException::NotNull(ZSTRING("HashDictionary_Keys.ToArrayCopy"), ZSTRING("array"));
  if (offset < 0) throw InvalidArgumentException::GreaterEqual(ZSTRING("HashDictionary_Keys.ToArrayCopy"), ZSTRING("offset"), 0);
#endif
  
  for (int32 i = 0; i < dictionary->hashtable.Length(); i++)
  {
    int32 idx;
    
    idx = dictionary->hashtable[i];
    
    while (idx >= 0)
    {
      array[offset++] = dictionary->nodeKeys[idx];
      idx = dictionary->nodeNext[idx];
    }
  }
  
  return array;
}

// -------------------------------------------------------------------------------------------------
// Private / Constructors
// -------------------------------------------------------------------------------------------------

/*!
 * @brief  Creates a new instance of HashDictionary_Keys.
 * 
 * @param dictionary The owning dictionary.
 */
template<class TKey, class TValue>
HashDictionary_Keys<TKey, TValue>::HashDictionary_Keys(HashDictionary<TKey, TValue>* dictionary)
{
  this->dictionary = dictionary;
}

} } } 

#endif
