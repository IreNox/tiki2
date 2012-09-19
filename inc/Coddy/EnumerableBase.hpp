////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_ENUMERABLEBASE_HPP
#define CLODDY_CORE_COLLECTIONS_ENUMERABLEBASE_HPP

#include "Cloddy/EnumerableBase.h"

// Include referenced interfaces.

#include "Cloddy/IEnumerable.h"
#include "Cloddy/IEnumerator.h"
#include "Cloddy/IList.h"
#include "Cloddy/IPredicate.h"
#include "Cloddy/ISet.h"

// Include referenced classes.

#include "Cloddy/Enumerable_Append.hpp"
#include "Cloddy/Enumerable_Select.hpp"
#include "CodeX/ErrorInfo.h"
#include "Cloddy/HashSet.hpp"
#include "CodeX/InvalidArgumentException.h"
#include "Cloddy/ListUtilGeneric.hpp"

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
Ptr<IEnumerable<T> > EnumerableBase<T>::Concatenate(IEnumerable<T>* elements)
{
#ifdef _DEBUG
  if (elements == null) throw InvalidArgumentException::NotNull(ZSTRING("EnumerableBase.Concatenate"), ZSTRING("elements"));
#endif
  
  return new Enumerable_Append<T>(this, elements);
}

template<class T>
Ptr<IEnumerable<T> > EnumerableBase<T>::Select(IPredicate<T>* predicate)
{
#ifdef _DEBUG
  if (predicate == null) throw InvalidArgumentException::NotNull(ZSTRING("EnumerableBase.Select"), ZSTRING("predicate"));
#endif
  
  return new Enumerable_Select<T>(this, predicate);
}

template<class T>
Array<typename T::Out> EnumerableBase<T>::ToArray()
{
  return ListUtilGeneric<T>::ToArray(this);
}

template<class T>
Ptr<IList<T> > EnumerableBase<T>::ToList()
{
  return ListUtilGeneric<T>::ToList(this);
}

template<class T>
Ptr<ISet<T> > EnumerableBase<T>::ToSet()
{
  Ptr<ISet<T> > result;
  
  result = new HashSet<T>(12);
  
  result->AddAll(this);
  
  return result;
}

} } } 

#endif
