////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_PREDICATEBASE_HPP
#define CLODDY_CORE_COLLECTIONS_PREDICATEBASE_HPP

#include "Cloddy/PredicateBase.h"

// Include referenced interfaces.

#include "Cloddy/IPredicate.h"

// Include referenced classes.

#include "CodeX/ErrorInfo.h"
#include "CodeX/InvalidArgumentException.h"
#include "Cloddy/Predicate_And.hpp"
#include "Cloddy/Predicate_Not.hpp"
#include "Cloddy/Predicate_Or.hpp"
#include "Cloddy/Predicate_XOr.hpp"

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
Ptr<IPredicate<T> > PredicateBase<T>::And(IPredicate<T>* other)
{
#ifdef _DEBUG
  if (other == null) throw InvalidArgumentException::NotNull(ZSTRING("PredicateBase.And"), ZSTRING("other"));
#endif
  
  return new Predicate_And<T>(this, other);
}

template<class T>
Ptr<IPredicate<T> > PredicateBase<T>::Not()
{
  return new Predicate_Not<T>(this);
}

template<class T>
Ptr<IPredicate<T> > PredicateBase<T>::Or(IPredicate<T>* other)
{
#ifdef _DEBUG
  if (other == null) throw InvalidArgumentException::NotNull(ZSTRING("PredicateBase.Or"), ZSTRING("other"));
#endif
  
  return new Predicate_Or<T>(this, other);
}

template<class T>
Ptr<IPredicate<T> > PredicateBase<T>::XOr(IPredicate<T>* other)
{
#ifdef _DEBUG
  if (other == null) throw InvalidArgumentException::NotNull(ZSTRING("PredicateBase.XOr"), ZSTRING("other"));
#endif
  
  return new Predicate_XOr<T>(this, other);
}

} } } 

#endif
