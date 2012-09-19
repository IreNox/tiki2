////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_ARRAYLIST_ENUMERATOR_HPP
#define CLODDY_CORE_COLLECTIONS_ARRAYLIST_ENUMERATOR_HPP

#include "Cloddy/ArrayList_Enumerator.h"

// Include referenced classes.

#include "Cloddy/EnumeratorBase.hpp"

namespace Cloddy { namespace Core { namespace Collections {

// Use referenced namespaces.

using namespace CodeX;

// -------------------------------------------------------------------------------------------------
// Public / Attributes
// -------------------------------------------------------------------------------------------------

template<class T>
typename T::Out ArrayList_Enumerator<T>::GetCurrent()
{
  return elements[current];
}

// -------------------------------------------------------------------------------------------------
// Protected / Methods
// -------------------------------------------------------------------------------------------------

template<class T>
void ArrayList_Enumerator<T>::DisposeManaged()
{
  elements = null;
  
  EnumeratorBase<T>::DisposeManaged();
}

template<class T>
bool ArrayList_Enumerator<T>::DoNext()
{
  if (current == last) 
  {
    this->Dispose();
    
    return false;
  }
  
  current++;
  
  return true;
}

// -------------------------------------------------------------------------------------------------
// Private / Constructors
// -------------------------------------------------------------------------------------------------

/*!
 * @brief  Creates a new instance of ArrayList_Enumerator.
 * 
 * @param elements Total number of elements.
 * @param count Total number of elements.
 */
template<class T>
ArrayList_Enumerator<T>::ArrayList_Enumerator(Array<typename T::Out> elements, int32 count)
{
  // Initialize all primitive fields to default values.
  
  this->current = 0;
  this->last = 0;
  
  try
  {
    this->elements = elements;
    last = count - 1;
    current = -1;
  }
  catch (...)
  {
    this->Dispose();
    
    throw ;
  }
}

} } } 

#endif
