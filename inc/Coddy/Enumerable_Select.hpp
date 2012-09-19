////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_ENUMERABLE_SELECT_HPP
#define CLODDY_CORE_COLLECTIONS_ENUMERABLE_SELECT_HPP

#include "Cloddy/Enumerable_Select.h"

// Include referenced enumerations.

#include "CodeX/DisposalPolicy.h"

// Include referenced interfaces.

#include "Cloddy/IEnumerable.h"
#include "Cloddy/IEnumerator.h"
#include "Cloddy/IList.h"
#include "Cloddy/IPredicate.h"

// Include referenced classes.

#include "Cloddy/EnumerableBase.hpp"
#include "Cloddy/Enumerator_Select.hpp"
#include "CodeX/ErrorInfo.h"
#include "CodeX/InvalidArgumentException.h"

namespace Cloddy { namespace Core { namespace Collections {

// Use referenced namespaces.

using namespace CodeX;
using namespace CodeX::System;

// -------------------------------------------------------------------------------------------------
// Public / Attributes
// -------------------------------------------------------------------------------------------------

template<class T>
Ptr<IEnumerator<T> > Enumerable_Select<T>::GetEnumerator()
{
  return new Enumerator_Select<T>(enumerable->GetEnumerator(), predicate);
}

// -------------------------------------------------------------------------------------------------
// Private / Constructors
// -------------------------------------------------------------------------------------------------

template<class T>
Enumerable_Select<T>::Enumerable_Select(IEnumerable<T>* enumerable, IPredicate<T>* predicate)
{
  this->enumerable = enumerable;
  this->predicate = predicate;
}

} } } 

#endif
