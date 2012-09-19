////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_COLLECTIONBASE_HPP
#define CLODDY_CORE_COLLECTIONS_COLLECTIONBASE_HPP

#include "Cloddy/CollectionBase.h"

// Include referenced interfaces.

#include "Cloddy/IEnumerable.h"
#include "Cloddy/IEnumerator.h"
#include "Cloddy/IList.h"
#include "Cloddy/IPredicate.h"

// Include referenced classes.

#include "Cloddy/CollectionConstBase.hpp"
#include "CodeX/ErrorInfo.h"
#include "CodeX/InvalidArgumentException.h"

namespace Cloddy { namespace Core { namespace Collections {

// Use referenced namespaces.

using namespace CodeX;

// Use referenced classes.

using CodeX::System::ErrorInfo;
using CodeX::System::InvalidArgumentException;

// -------------------------------------------------------------------------------------------------
// Public / Methods
// -------------------------------------------------------------------------------------------------
template<class T>
bool CollectionBase<T>::AddAll(IEnumerable<T>* elements)
{
#ifdef _DEBUG
  if (elements == null) throw InvalidArgumentException::NotNull(ZSTRING("CollectionBase.AddAll"), ZSTRING("elements"));
#endif
  
  bool result;
  
  result = false;
  
  for (Ptr<IEnumerator<T> > it = elements->GetEnumerator(); it->Next(); )
    result |= Add(it->GetCurrent());
  
  return result;
}

template<class T>
bool CollectionBase<T>::RemoveAll(IPredicate<T>* predicate)
{
#ifdef _DEBUG
  if (predicate == null) throw InvalidArgumentException::NotNull(ZSTRING("CollectionBase.RemoveAll"), ZSTRING("predicate"));
#endif
  
  return RemoveAll(this->Select(predicate)->ToList());
}

template<class T>
bool CollectionBase<T>::RemoveAll(IEnumerable<T>* elements)
{
#ifdef _DEBUG
  if (elements == null) throw InvalidArgumentException::NotNull(ZSTRING("CollectionBase.RemoveAll"), ZSTRING("elements"));
#endif
  
  bool result;
  
  result = false;
  
  for (Ptr<IEnumerator<T> > it = elements->GetEnumerator(); it->Next(); )
    result |= Remove(it->GetCurrent());
  
  return result;
}

} } } 

#endif
