////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_PREDICATE_OR_HPP
#define CLODDY_CORE_COLLECTIONS_PREDICATE_OR_HPP

#include "Cloddy/Predicate_Or.h"

// Include referenced interfaces.

#include "Cloddy/IPredicate.h"

// Include referenced classes.

#include "CodeX/ErrorInfo.h"
#include "CodeX/InvalidArgumentException.h"
#include "Cloddy/PredicateBase.hpp"

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
bool Predicate_Or<T>::Evaluate(typename T::In element)
{
  return first->Evaluate(element) || second->Evaluate(element);
}

// -------------------------------------------------------------------------------------------------
// Private / Constructors
// -------------------------------------------------------------------------------------------------

template<class T>
Predicate_Or<T>::Predicate_Or(IPredicate<T>* first, IPredicate<T>* second)
{
  this->first = first;
  this->second = second;
}

} } } 

#endif
