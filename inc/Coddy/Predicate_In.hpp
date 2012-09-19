////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_PREDICATE_IN_HPP
#define CLODDY_CORE_COLLECTIONS_PREDICATE_IN_HPP

#include "Cloddy/Predicate_In.h"

// Include referenced interfaces.

#include "Cloddy/ICollectionConst.h"

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
bool Predicate_In<T>::Evaluate(typename T::In element)
{
  return collection->Contains(element);
}

// -------------------------------------------------------------------------------------------------
// Private / Constructors
// -------------------------------------------------------------------------------------------------

template<class T>
Predicate_In<T>::Predicate_In(ICollectionConst<T>* collection)
{
  this->collection = collection;
}

} } } 

#endif
