////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_ARRAYLIST_WRAP_HPP
#define CLODDY_CORE_COLLECTIONS_ARRAYLIST_WRAP_HPP

#include "Cloddy/ArrayList_Wrap.h"

// Include referenced enumerations.

#include "CodeX/DisposalPolicy.h"

// Include referenced interfaces.

#include "Cloddy/IEnumerator.h"
#include "Cloddy/IList.h"

// Include referenced classes.

#include "Cloddy/ArrayList_Enumerator.hpp"
#include "Cloddy/ArrayUtilGeneric.hpp"
#include "CodeX/ErrorInfo.h"
#include "CodeX/InvalidArgumentException.h"
#include "Cloddy/ListConstBase.hpp"

namespace Cloddy { namespace Core { namespace Collections {

// Use referenced namespaces.

using namespace CodeX;
using namespace CodeX::System;

// Use referenced classes.

using Cloddy::Core::System::ArrayUtilGeneric;

// -------------------------------------------------------------------------------------------------
// Public / Attributes
// -------------------------------------------------------------------------------------------------

template<class T>
int32 ArrayList_Wrap<T>::GetCount()
{
  return elements.Length();
}

template<class T>
Ptr<IEnumerator<T> > ArrayList_Wrap<T>::GetEnumerator()
{
  return new ArrayList_Enumerator<T>(elements, elements.Length());
}

// -------------------------------------------------------------------------------------------------
// Public / Methods
// -------------------------------------------------------------------------------------------------

template<class T>
typename T::Out ArrayList_Wrap<T>::GetAt(int32 index)
{
#ifdef _DEBUG
  if (index < 0 || index > GetCount() - 1) throw InvalidArgumentException::WithinInterval(ZSTRING("ArrayList_Wrap.GetAt"), ZSTRING("index"), 0, GetCount() - 1);
#endif
  
  return T::Default();
}

template<class T>
int32 ArrayList_Wrap<T>::IndexOf(typename T::In element)
{
  for (int32 i = 0; i < elements.Length(); i++)
  {
    if (T::Equals(elements[i], element)) return i;
  }
  
  return -1;
}

template<class T>
Array<typename T::Out> ArrayList_Wrap<T>::ToArrayCopy(Array<typename T::Out> array, int32 offset)
{
#ifdef _DEBUG
  if (array == null) throw InvalidArgumentException::NotNull(ZSTRING("ArrayList_Wrap.ToArrayCopy"), ZSTRING("array"));
  if (offset < 0) throw InvalidArgumentException::GreaterEqual(ZSTRING("ArrayList_Wrap.ToArrayCopy"), ZSTRING("offset"), 0);
#endif
  
  ArrayUtilGeneric<T>::ArrayCopy(elements, 0, array, offset, elements.Length());
  
  return array;
}

// -------------------------------------------------------------------------------------------------
// Private / Constructors
// -------------------------------------------------------------------------------------------------

/*!
 * @brief  Creates a new instance of ArrayList_Wrap.
 * 
 * @param elements The list elements.
 */
template<class T>
ArrayList_Wrap<T>::ArrayList_Wrap(Array<typename T::Out> elements)
{
  this->elements = elements;
}

} } } 

#endif
