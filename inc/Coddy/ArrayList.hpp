////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_ARRAYLIST_HPP
#define CLODDY_CORE_COLLECTIONS_ARRAYLIST_HPP

#include "Cloddy/ArrayList.h"

// Include referenced enumerations.

#include "CodeX/DisposalPolicy.h"

// Include referenced interfaces.

#include "Cloddy/IEnumerable.h"
#include "Cloddy/IEnumerator.h"
#include "Cloddy/IList.h"

// Include referenced classes.

#include "Cloddy/ArrayList_Enumerator.hpp"
#include "Cloddy/ArrayUtilGeneric.hpp"
#include "CodeX/ErrorInfo.h"
#include "CodeX/InvalidArgumentException.h"
#include "Cloddy/ListBase.hpp"

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
int32 ArrayList<T>::GetCount()
{
  return count;
}

template<class T>
Ptr<IEnumerator<T> > ArrayList<T>::GetEnumerator()
{
  return new ArrayList_Enumerator<T>(elements, count);
}

// -------------------------------------------------------------------------------------------------
// Public / Constructors
// -------------------------------------------------------------------------------------------------

/*!
 * @brief  Creates a new instance of ArrayList.
 */
template<class T>
ArrayList<T>::ArrayList()
{
  // Initialize all primitive fields to default values.
  
  this->capacity = 0;
  this->count = 0;
  
  capacity = 12;
  elements = Array<typename T::Out>(capacity);
}

/*!
 * @brief  Creates a new instance of ArrayList.
 * 
 * @param capacity <b>[>=0]</b>  The initial capacity.
 */
template<class T>
ArrayList<T>::ArrayList(int32 capacity)
{
  // Initialize all primitive fields to default values.
  
  this->capacity = 0;
  this->count = 0;
  
#ifdef _DEBUG
  if (capacity < 0) throw InvalidArgumentException::GreaterEqual(ZSTRING("ArrayList.ArrayList"), ZSTRING("capacity"), 0);
#endif
  
  this->capacity = capacity;
  
  if (capacity > 0) elements = Array<typename T::Out>(capacity);
}

// -------------------------------------------------------------------------------------------------
// Public / Methods
// -------------------------------------------------------------------------------------------------

template<class T>
bool ArrayList<T>::Add(typename T::In element)
{
  // Need to grow internal array?
  
  if (count + 1 > capacity) 
  {
    elements = ArrayUtilGeneric<T>::GrowUntil(elements, count, capacity + 16);
    capacity = elements.Length();
  }
  
  // Append element to list.
  
  elements[count++] = element;
  
  return true;
}

template<class T>
void ArrayList<T>::Clear()
{
  // Remove all list elements.
  
  for (int32 i = 0; i < count; i++)
    elements[i] = T::Default();
  
  count = 0;
}

template<class T>
typename T::Out ArrayList<T>::GetAt(int32 index)
{
#ifdef _DEBUG
  if (index < 0 || index > GetCount() - 1) throw InvalidArgumentException::WithinInterval(ZSTRING("ArrayList.GetAt"), ZSTRING("index"), 0, GetCount() - 1);
#endif
  
  return elements[index];
}

template<class T>
int32 ArrayList<T>::IndexOf(typename T::In element)
{
  for (int32 i = 0; i < count; i++)
  {
    if (T::Equals(elements[i], element)) return i;
  }
  
  return -1;
}

template<class T>
void ArrayList<T>::InsertAt(int32 index, typename T::In element)
{
#ifdef _DEBUG
  if (index < 0 || index > GetCount()) throw InvalidArgumentException::WithinInterval(ZSTRING("ArrayList.InsertAt"), ZSTRING("index"), 0, GetCount());
#endif
  
  // Need to grow internal array?
  
  if (count + 1 > capacity) 
  {
    elements = ArrayUtilGeneric<T>::GrowUntil(elements, count, capacity + 16);
    capacity = elements.Length();
  }
  
  ArrayUtilGeneric<T>::ArrayCopy(elements, index, elements, index + 1, count - index);
  
  elements[index] = element;
  
  count++;
}

template<class T>
bool ArrayList<T>::Remove(typename T::In element)
{
  for (int32 i = 0; i < count; i++)
  {
    if (!T::Equals(elements[i], element)) continue;
    
    ArrayUtilGeneric<T>::ArrayCopy(elements, i + 1, elements, i, count - i - 1);
    
    elements[--count] = T::Default();
    
    return true;
  }
  
  return false;
}

template<class T>
typename T::Out ArrayList<T>::RemoveAt(int32 index)
{
#ifdef _DEBUG
  if (index < 0 || index > GetCount() - 1) throw InvalidArgumentException::WithinInterval(ZSTRING("ArrayList.RemoveAt"), ZSTRING("index"), 0, GetCount() - 1);
#endif
  
  typename T::Out result;
  
  result = elements[index];
  
  ArrayUtilGeneric<T>::ArrayCopy(elements, index + 1, elements, index, count - index - 1);
  
  elements[--count] = T::Default();
  
  return result;
}

template<class T>
void ArrayList<T>::RemoveRange(int32 index, int32 count)
{
#ifdef _DEBUG
  if (index < 0 || index > GetCount()) throw InvalidArgumentException::WithinInterval(ZSTRING("ArrayList.RemoveRange"), ZSTRING("index"), 0, GetCount());
  if (count < 0 || count > GetCount() - index) throw InvalidArgumentException::WithinInterval(ZSTRING("ArrayList.RemoveRange"), ZSTRING("count"), 0, GetCount() - index);
#endif
  
  if (count == 0) return;
  
  ArrayUtilGeneric<T>::ArrayCopy(elements, index + count, elements, index, this->count - index - count);
  
  for (int32 i = this->count - count; i < this->count; i++)
    elements[i] = T::Default();
  
  this->count -= count;
}

template<class T>
typename T::Out ArrayList<T>::SetAt(int32 index, typename T::In element)
{
#ifdef _DEBUG
  if (index < 0 || index > GetCount() - 1) throw InvalidArgumentException::WithinInterval(ZSTRING("ArrayList.SetAt"), ZSTRING("index"), 0, GetCount() - 1);
#endif
  
  typename T::Out previous;
  
  previous = elements[index];
  elements[index] = element;
  
  return previous;
}

template<class T>
Array<typename T::Out> ArrayList<T>::ToArrayCopy(Array<typename T::Out> array, int32 offset)
{
#ifdef _DEBUG
  if (array == null) throw InvalidArgumentException::NotNull(ZSTRING("ArrayList.ToArrayCopy"), ZSTRING("array"));
  if (offset < 0) throw InvalidArgumentException::GreaterEqual(ZSTRING("ArrayList.ToArrayCopy"), ZSTRING("offset"), 0);
#endif
  
  if (elements != null) ArrayUtilGeneric<T>::ArrayCopy(elements, 0, array, offset, count);
  
  return array;
}

} } } 

#endif
