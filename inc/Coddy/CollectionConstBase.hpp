////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_COLLECTIONCONSTBASE_HPP
#define CLODDY_CORE_COLLECTIONS_COLLECTIONCONSTBASE_HPP

#include "Cloddy/CollectionConstBase.h"

// Include referenced interfaces.

#include "Cloddy/IEnumerable.h"
#include "Cloddy/IEnumerator.h"
#include "Cloddy/IList.h"

// Include referenced classes.

#include "Cloddy/EnumerableBase.hpp"
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
bool CollectionConstBase<T>::ContainsAll(IEnumerable<T>* elements)
{
#ifdef _DEBUG
  if (elements == null) throw InvalidArgumentException::NotNull(ZSTRING("CollectionConstBase.ContainsAll"), ZSTRING("elements"));
#endif
  
  for (Ptr<IEnumerator<T> > it = elements->GetEnumerator(); it->Next(); )
  {
    if (!Contains(it->GetCurrent())) return false;
  }
  
  return true;
}

template<class T>
bool CollectionConstBase<T>::ContainsNone(IEnumerable<T>* elements)
{
#ifdef _DEBUG
  if (elements == null) throw InvalidArgumentException::NotNull(ZSTRING("CollectionConstBase.ContainsNone"), ZSTRING("elements"));
#endif
  
  for (Ptr<IEnumerator<T> > it = elements->GetEnumerator(); it->Next(); )
  {
    if (Contains(it->GetCurrent())) return false;
  }
  
  return true;
}

template<class T>
bool CollectionConstBase<T>::ContainsSome(IEnumerable<T>* elements)
{
#ifdef _DEBUG
  if (elements == null) throw InvalidArgumentException::NotNull(ZSTRING("CollectionConstBase.ContainsSome"), ZSTRING("elements"));
#endif
  
  for (Ptr<IEnumerator<T> > it = elements->GetEnumerator(); it->Next(); )
  {
    if (Contains(it->GetCurrent())) return true;
  }
  
  return false;
}

template<class T>
Array<typename T::Out> CollectionConstBase<T>::ToArray()
{
  Array<typename T::Out> array;
  
  array = Array<typename T::Out>(GetCount());
  
  return ToArrayCopy(array, 0);
}

} } } 

#endif
