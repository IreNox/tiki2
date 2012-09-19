////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_DEQUEBASE_HPP
#define CLODDY_CORE_COLLECTIONS_DEQUEBASE_HPP

#include "Cloddy/DequeBase.h"

// Include referenced enumerations.

#include "CodeX/DisposalPolicy.h"

// Include referenced interfaces.

#include "Cloddy/IDeque.h"
#include "Cloddy/IEnumerator.h"
#include "Cloddy/IList.h"

// Include referenced classes.

#include "Cloddy/Deque_Enumerator.hpp"
#include "Cloddy/EnumerableBase.hpp"
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
Ptr<IEnumerator<T> > DequeBase<T>::GetEnumerator()
{
  return new Deque_Enumerator<T>(this);
}

} } } 

#endif
