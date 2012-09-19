////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_ENUMERATOR_SELECT_HPP
#define CLODDY_CORE_COLLECTIONS_ENUMERATOR_SELECT_HPP

#include "Cloddy/Enumerator_Select.h"

// Include referenced interfaces.

#include "Cloddy/IEnumerator.h"
#include "Cloddy/IPredicate.h"

// Include referenced classes.

#include "Cloddy/EnumeratorBase.hpp"

namespace Cloddy { namespace Core { namespace Collections {

// Use referenced namespaces.

using namespace CodeX;

// -------------------------------------------------------------------------------------------------
// Public / Attributes
// -------------------------------------------------------------------------------------------------

template<class T>
typename T::Out Enumerator_Select<T>::GetCurrent()
{
  return enumerator->GetCurrent();
}

// -------------------------------------------------------------------------------------------------
// Protected / Methods
// -------------------------------------------------------------------------------------------------

template<class T>
void Enumerator_Select<T>::DisposeManaged()
{
  if (enumerator != null) 
  {
    enumerator->Dispose();
    
    enumerator = null;
  }
  
  predicate = null;
  
  EnumeratorBase<T>::DisposeManaged();
}

template<class T>
bool Enumerator_Select<T>::DoNext()
{
  while (true)
  {
    if (enumerator == null) return false;
    if (!enumerator->Next()) 
    {
      enumerator->Dispose();
      
      enumerator = null;
      
      return false;
    }
    if (predicate->Evaluate(enumerator->GetCurrent())) return true;
  }
}

// -------------------------------------------------------------------------------------------------
// Private / Constructors
// -------------------------------------------------------------------------------------------------

template<class T>
Enumerator_Select<T>::Enumerator_Select(IEnumerator<T>* enumerator, IPredicate<T>* predicate)
{
  try
  {
    this->enumerator = enumerator;
    this->predicate = predicate;
  }
  catch (...)
  {
    this->Dispose();
    
    throw ;
  }
}

} } } 

#endif
