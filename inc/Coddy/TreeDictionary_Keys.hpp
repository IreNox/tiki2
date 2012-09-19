////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_TREEDICTIONARY_KEYS_HPP
#define CLODDY_CORE_COLLECTIONS_TREEDICTIONARY_KEYS_HPP

#include "Cloddy/TreeDictionary_Keys.h"

// Include referenced enumerations.

#include "CodeX/DisposalPolicy.h"

// Include referenced interfaces.

#include "Cloddy/IDeque.h"
#include "Cloddy/IEnumerator.h"
#include "Cloddy/IList.h"

// Include referenced classes.

#include "Cloddy/CollectionConstBase.hpp"
#include "CodeX/ErrorInfo.h"
#include "CodeX/InvalidArgumentException.h"
#include "Cloddy/Tree_Enumerator.hpp"
#include "Cloddy/TreeDictionary.hpp"

namespace Cloddy { namespace Core { namespace Collections {

// Use referenced namespaces.

using namespace CodeX;
using namespace CodeX::System;

// -------------------------------------------------------------------------------------------------
// Public / Attributes
// -------------------------------------------------------------------------------------------------

template<class TKey, class TValue>
int32 TreeDictionary_Keys<TKey, TValue>::GetCount()
{
  return dictionary->GetCount();
}

template<class TKey, class TValue>
Ptr<IEnumerator<TKey> > TreeDictionary_Keys<TKey, TValue>::GetEnumerator()
{
  return new Tree_Enumerator<TKey>(dictionary->root, dictionary->left, dictionary->right, dictionary->keys);
}

// -------------------------------------------------------------------------------------------------
// Public / Methods
// -------------------------------------------------------------------------------------------------

template<class TKey, class TValue>
bool TreeDictionary_Keys<TKey, TValue>::Contains(typename TKey::In element)
{
  return dictionary->Contains(element);
}

template<class TKey, class TValue>
Array<typename TKey::Out> TreeDictionary_Keys<TKey, TValue>::ToArrayCopy(Array<typename TKey::Out> array, int32 offset)
{
#ifdef _DEBUG
  if (array == null) throw InvalidArgumentException::NotNull(ZSTRING("TreeDictionary_Keys.ToArrayCopy"), ZSTRING("array"));
  if (offset < 0) throw InvalidArgumentException::GreaterEqual(ZSTRING("TreeDictionary_Keys.ToArrayCopy"), ZSTRING("offset"), 0);
#endif
  
  dictionary->ToKeysArray(array, dictionary->root, offset);
  
  return array;
}

// -------------------------------------------------------------------------------------------------
// Private / Constructors
// -------------------------------------------------------------------------------------------------

template<class TKey, class TValue>
TreeDictionary_Keys<TKey, TValue>::TreeDictionary_Keys(TreeDictionary<TKey, TValue>* dictionary)
{
  this->dictionary = dictionary;
}

} } } 

#endif
