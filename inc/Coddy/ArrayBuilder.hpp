////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_ARRAYBUILDER_HPP
#define CLODDY_CORE_COLLECTIONS_ARRAYBUILDER_HPP

#include "Cloddy/ArrayBuilder.h"

// Include referenced interfaces.

#include "Cloddy/IEnumerable.h"
#include "Cloddy/IEnumerator.h"
#include "Cloddy/IList.h"
#include "Cloddy/ISet.h"

// Include referenced classes.

#include "Cloddy/ArrayList.hpp"
#include "CodeX/ErrorInfo.h"
#include "CodeX/InvalidArgumentException.h"

namespace Cloddy { namespace Core { namespace Collections {

// Use referenced namespaces.

using namespace CodeX;

// Use referenced classes.

using CodeX::System::ErrorInfo;
using CodeX::System::InvalidArgumentException;

// -------------------------------------------------------------------------------------------------
// Public / Methods
// -------------------------------------------------------------------------------------------------

/*!
 * @brief  Creates a new instance of ArrayBuilder.
 * 
 * @return <b>[not-null]</b>  The creates ArrayBuilder object.
 */
template<class T>
Ptr<ArrayBuilder<T> > ArrayBuilder<T>::New()
{
  return new ArrayBuilder<T>(12);
}

/*!
 * @brief  Creates a new instance of ArrayBuilder.
 * 
 * @param initialCapacity <b>[>=0]</b>  The initial capacity to assume.
 * 
 * @return <b>[not-null]</b>  The creates ArrayBuilder object.
 */
template<class T>
Ptr<ArrayBuilder<T> > ArrayBuilder<T>::New(int32 initialCapacity)
{
#ifdef _DEBUG
  if (initialCapacity < 0) throw InvalidArgumentException::GreaterEqual(ZSTRING("ArrayBuilder.New"), ZSTRING("initialCapacity"), 0);
#endif
  
  return new ArrayBuilder<T>(initialCapacity);
}

/*!
 * @brief  Appends a new element to the array being built.
 * 
 * @param element The element to append.
 * 
 * @return <b>[not-null]</b>  this
 */
template<class T>
Ptr<ArrayBuilder<T> > ArrayBuilder<T>::Add(typename T::In element)
{
  if (list == null) list = new ArrayList<T>(initialCapacity);
  
  list->Add(element);
  
  return this;
}

/*!
 * @brief  Returns the built array.
 * 
 * @return <b>[not-null]</b>  The array.
 */
template<class T>
Array<typename T::Out> ArrayBuilder<T>::Get()
{
  Array<typename T::Out> result;
  
  if (list == null) result = Array<typename T::Out>(0);
  else result = list->ToArray();
  
  list = null;
  
  return result;
}

// -------------------------------------------------------------------------------------------------
// Protected / Constructors
// -------------------------------------------------------------------------------------------------

/*!
 * @brief  Creates a new instance of ArrayBuilder.
 * 
 * @param initialCapacity <b>[>=0]</b>  The initial capacity
 */
template<class T>
ArrayBuilder<T>::ArrayBuilder(int32 initialCapacity)
{
  // Initialize all primitive fields to default values.
  
  this->initialCapacity = 0;
  
#ifdef _DEBUG
  if (initialCapacity < 0) throw InvalidArgumentException::GreaterEqual(ZSTRING("ArrayBuilder.ArrayBuilder"), ZSTRING("initialCapacity"), 0);
#endif
  
  this->initialCapacity = initialCapacity;
}

} } } 

#endif
