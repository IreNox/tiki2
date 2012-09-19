////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_ENUMERATORBASE_HPP
#define CLODDY_CORE_COLLECTIONS_ENUMERATORBASE_HPP

#include "Cloddy/EnumeratorBase.h"

namespace Cloddy { namespace Core { namespace Collections {

// Use referenced namespaces.

using namespace CodeX;

// Use referenced classes.

using CodeX::System::Disposable;

// -------------------------------------------------------------------------------------------------
// Public / Attributes
// -------------------------------------------------------------------------------------------------
template<class T>
int32 EnumeratorBase<T>::GetIndex()
{
  return index;
}

// -------------------------------------------------------------------------------------------------
// Public / Methods
// -------------------------------------------------------------------------------------------------

template<class T>
bool EnumeratorBase<T>::Next()
{
  // Already reached end of enumeration?
  
  if (index == -2) return false;
  
  // Reaching end of enumeration?
  
  if (!DoNext()) 
  {
    this->Dispose();
    
    return false;
  }
  
  index++;
  
  return true;
}

// -------------------------------------------------------------------------------------------------
// Protected / Constructors
// -------------------------------------------------------------------------------------------------

/*!
 * @brief  Creates a new instance of EnumeratorBase.
 */
template<class T>
EnumeratorBase<T>::EnumeratorBase()
{
  // Initialize all primitive fields to default values.
  
  this->index = 0;
  
  try
  {
    index = -1;
  }
  catch (...)
  {
    this->Dispose();
    
    throw ;
  }
}

// -------------------------------------------------------------------------------------------------
// Protected / Methods
// -------------------------------------------------------------------------------------------------

template<class T>
void EnumeratorBase<T>::DisposeManaged()
{
  index = -2;
  
  Disposable::DisposeManaged();
}

} } } 

#endif
