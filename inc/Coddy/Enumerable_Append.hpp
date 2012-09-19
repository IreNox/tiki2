////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_ENUMERABLE_APPEND_HPP
#define CLODDY_CORE_COLLECTIONS_ENUMERABLE_APPEND_HPP

#include "Cloddy/Enumerable_Append.h"

// Include referenced enumerations.

#include "CodeX/DisposalPolicy.h"

// Include referenced interfaces.

#include "Cloddy/IEnumerable.h"
#include "Cloddy/IEnumerator.h"
#include "Cloddy/IList.h"

// Include referenced classes.

#include "Cloddy/EnumerableBase.hpp"
#include "Cloddy/Enumerator_Append.hpp"
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
Ptr<IEnumerator<T> > Enumerable_Append<T>::GetEnumerator()
{
  return new Enumerator_Append<T>(first, second);
}

// -------------------------------------------------------------------------------------------------
// Private / Constructors
// -------------------------------------------------------------------------------------------------

template<class T>
Enumerable_Append<T>::Enumerable_Append(IEnumerable<T>* first, IEnumerable<T>* second)
{
  this->first = first;
  this->second = second;
}

} } } 

#endif
