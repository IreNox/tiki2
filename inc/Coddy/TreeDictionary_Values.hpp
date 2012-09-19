////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_TREEDICTIONARY_VALUES_HPP
#define CLODDY_CORE_COLLECTIONS_TREEDICTIONARY_VALUES_HPP

#include "Cloddy/TreeDictionary_Values.h"

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
int32 TreeDictionary_Values<TKey, TValue>::GetCount()
{
  return dictionary->GetCount();
}

template<class TKey, class TValue>
Ptr<IEnumerator<TValue> > TreeDictionary_Values<TKey, TValue>::GetEnumerator()
{
  return new Tree_Enumerator<TValue>(dictionary->root, dictionary->left, dictionary->right, dictionary->values);
}

// -------------------------------------------------------------------------------------------------
// Public / Methods
// -------------------------------------------------------------------------------------------------

template<class TKey, class TValue>
bool TreeDictionary_Values<TKey, TValue>::Contains(typename TValue::In element)
{
  return dictionary->FindValue(dictionary->root, element);
}

template<class TKey, class TValue>
Array<typename TValue::Out> TreeDictionary_Values<TKey, TValue>::ToArrayCopy(Array<typename TValue::Out> array, int32 offset)
{
#ifdef _DEBUG
  if (array == null) throw InvalidArgumentException::NotNull(ZSTRING("TreeDictionary_Values.ToArrayCopy"), ZSTRING("array"));
  if (offset < 0) throw InvalidArgumentException::GreaterEqual(ZSTRING("TreeDictionary_Values.ToArrayCopy"), ZSTRING("offset"), 0);
#endif
  
  dictionary->ToValuesArray(array, dictionary->root, offset);
  
  return array;
}

// -------------------------------------------------------------------------------------------------
// Private / Constructors
// -------------------------------------------------------------------------------------------------

template<class TKey, class TValue>
TreeDictionary_Values<TKey, TValue>::TreeDictionary_Values(TreeDictionary<TKey, TValue>* dictionary)
{
  this->dictionary = dictionary;
}

} } } 

#endif
