////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_TREEDICTIONARY_ENTRIES_HPP
#define CLODDY_CORE_COLLECTIONS_TREEDICTIONARY_ENTRIES_HPP

#include "Cloddy/TreeDictionary_Entries.h"

// Include referenced enumerations.

#include "CodeX/DisposalPolicy.h"

// Include referenced structures.

#include "Cloddy/DictionaryEntry.hpp"

// Include referenced interfaces.

#include "Cloddy/IDeque.h"
#include "Cloddy/IEnumerator.h"
#include "Cloddy/IList.h"

// Include referenced classes.

#include "Cloddy/CollectionConstBase.hpp"
#include "CodeX/ErrorInfo.h"
#include "CodeX/InvalidArgumentException.h"
#include "Cloddy/TreeDictionary.hpp"
#include "Cloddy/TreeDictionary_Entries_Enumerator.hpp"

namespace Cloddy { namespace Core { namespace Collections {

// Use referenced namespaces.

using namespace CodeX;
using namespace CodeX::System;

// -------------------------------------------------------------------------------------------------
// Public / Attributes
// -------------------------------------------------------------------------------------------------

template<class TKey, class TValue>
int32 TreeDictionary_Entries<TKey, TValue>::GetCount()
{
  return dictionary->GetCount();
}

template<class TKey, class TValue>
Ptr<IEnumerator<Val<DictionaryEntry<TKey, TValue> > > > TreeDictionary_Entries<TKey, TValue>::GetEnumerator()
{
  return new TreeDictionary_Entries_Enumerator<TKey, TValue>(dictionary->root, dictionary->left, dictionary->right, dictionary->keys, dictionary->values);
}

// -------------------------------------------------------------------------------------------------
// Public / Methods
// -------------------------------------------------------------------------------------------------

template<class TKey, class TValue>
bool TreeDictionary_Entries<TKey, TValue>::Contains(const DictionaryEntry<TKey, TValue>& element)
{
  return dictionary->Contains(element.Key) && TValue::Equals(element.Value, dictionary->Get(element.Key, TValue::Default()));
}

template<class TKey, class TValue>
Array<DictionaryEntry<TKey, TValue> > TreeDictionary_Entries<TKey, TValue>::ToArrayCopy(Array<DictionaryEntry<TKey, TValue> > array, int32 offset)
{
#ifdef _DEBUG
  if (array == null) throw InvalidArgumentException::NotNull(ZSTRING("TreeDictionary_Entries.ToArrayCopy"), ZSTRING("array"));
  if (offset < 0) throw InvalidArgumentException::GreaterEqual(ZSTRING("TreeDictionary_Entries.ToArrayCopy"), ZSTRING("offset"), 0);
#endif
  
  dictionary->ToEntriesArray(array, dictionary->root, offset);
  
  return array;
}

// -------------------------------------------------------------------------------------------------
// Private / Constructors
// -------------------------------------------------------------------------------------------------

template<class TKey, class TValue>
TreeDictionary_Entries<TKey, TValue>::TreeDictionary_Entries(TreeDictionary<TKey, TValue>* dictionary)
{
  this->dictionary = dictionary;
}

} } } 

#endif
