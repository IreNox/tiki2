////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_ENUMERATOR_APPEND_HPP
#define CLODDY_CORE_COLLECTIONS_ENUMERATOR_APPEND_HPP

#include "Cloddy/Enumerator_Append.h"

// Include referenced interfaces.

#include "Cloddy/IEnumerable.h"
#include "Cloddy/IEnumerator.h"

// Include referenced classes.

#include "Cloddy/EnumeratorBase.hpp"

namespace Cloddy { namespace Core { namespace Collections {

// Use referenced namespaces.

using namespace CodeX;

// -------------------------------------------------------------------------------------------------
// Public / Attributes
// -------------------------------------------------------------------------------------------------

template<class T>
typename T::Out Enumerator_Append<T>::GetCurrent()
{
  return enumerator->GetCurrent();
}

// -------------------------------------------------------------------------------------------------
// Protected / Methods
// -------------------------------------------------------------------------------------------------

template<class T>
void Enumerator_Append<T>::DisposeManaged()
{
  if (enumerator != null) 
  {
    enumerator->Dispose();
    
    enumerator = null;
  }
  
  first = null;
  second = null;
  
  EnumeratorBase<T>::DisposeManaged();
}

template<class T>
bool Enumerator_Append<T>::DoNext()
{
  while (true)
  {
    // Is there an enumerator object available?
    
    if (enumerator != null) 
    {
      // No more elements in current enumerator object?
      
      if (!enumerator->Next()) 
      {
        enumerator = null;
        
        continue;
      }
      
      // Next element is ready.
      
      return true;
    }
    
    // Create enumerator object if possible.
    
    if (first != null) 
    {
      enumerator = first->GetEnumerator();
      first = null;
      
      continue;
    }
    if (second != null) 
    {
      enumerator = second->GetEnumerator();
      second = null;
      
      continue;
    }
    
    return false;
  }
}

// -------------------------------------------------------------------------------------------------
// Private / Constructors
// -------------------------------------------------------------------------------------------------

/*!
 * @brief  Creates a new instance of Enumerator_Append.
 * 
 * @param first The first enumerable object.
 * @param second The second enumerable object.
 */
template<class T>
Enumerator_Append<T>::Enumerator_Append(IEnumerable<T>* first, IEnumerable<T>* second)
{
  try
  {
    this->first = first;
    this->second = second;
  }
  catch (...)
  {
    this->Dispose();
    
    throw ;
  }
}

} } } 

#endif
