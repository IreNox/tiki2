////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_DEQUE_ENUMERATOR_HPP
#define CLODDY_CORE_COLLECTIONS_DEQUE_ENUMERATOR_HPP

#include "Cloddy/Deque_Enumerator.h"

// Include referenced interfaces.

#include "Cloddy/IDeque.h"

// Include referenced classes.

#include "Cloddy/EnumeratorBase.hpp"

namespace Cloddy { namespace Core { namespace Collections {

// Use referenced namespaces.

using namespace CodeX;

// -------------------------------------------------------------------------------------------------
// Public / Attributes
// -------------------------------------------------------------------------------------------------

template<class T>
typename T::Out Deque_Enumerator<T>::GetCurrent()
{
  return current;
}

// -------------------------------------------------------------------------------------------------
// Protected / Methods
// -------------------------------------------------------------------------------------------------

template<class T>
void Deque_Enumerator<T>::DisposeManaged()
{
  deque = null;
  current = T::Default();
  
  EnumeratorBase<T>::DisposeManaged();
}

template<class T>
bool Deque_Enumerator<T>::DoNext()
{
  if (deque->GetCount() == 0) return false;
  
  current = deque->PopFirst();
  
  return true;
}

// -------------------------------------------------------------------------------------------------
// Private / Constructors
// -------------------------------------------------------------------------------------------------

template<class T>
Deque_Enumerator<T>::Deque_Enumerator(IDeque<T>* deque)
{
  try
  {
    this->deque = deque;
  }
  catch (...)
  {
    this->Dispose();
    
    throw ;
  }
}

} } } 

#endif
