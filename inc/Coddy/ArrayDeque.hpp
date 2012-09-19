////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_ARRAYDEQUE_HPP
#define CLODDY_CORE_COLLECTIONS_ARRAYDEQUE_HPP

#include "Cloddy/ArrayDeque.h"

// Include referenced interfaces.

#include "Cloddy/IList.h"

// Include referenced classes.

#include "Cloddy/ArrayUtilGeneric.hpp"
#include "Cloddy/DequeBase.hpp"
#include "CodeX/ErrorInfo.h"
#include "CodeX/InvalidArgumentException.h"
#include "Cloddy/Maths.h"

namespace Cloddy { namespace Core { namespace Collections {

// Use referenced namespaces.

using namespace CodeX;

// Use referenced classes.

using Cloddy::Core::Math::Maths;
using Cloddy::Core::System::ArrayUtilGeneric;
using CodeX::System::ErrorInfo;
using CodeX::System::InvalidArgumentException;

// -------------------------------------------------------------------------------------------------
// Public / Attributes
// -------------------------------------------------------------------------------------------------

template<class T>
int32 ArrayDeque<T>::GetCount()
{
  return count;
}

// -------------------------------------------------------------------------------------------------
// Public / Constructors
// -------------------------------------------------------------------------------------------------

/*!
 * @brief  Creates a new instance of ArrayDeque.
 */
template<class T>
ArrayDeque<T>::ArrayDeque()
{
  // Initialize all primitive fields to default values.
  
  this->capacity = 0;
  this->count = 0;
  this->headIdx = 0;
  this->tailIdx = 0;
  
  capacity = 12;
  elements = Array<typename T::Out>(capacity);
}

/*!
 * @brief  Creates a new instance of ArrayDeque.
 * 
 * @param initialCapacity <b>[>=0]</b>  The initial capacity of the deque,in elements.
 */
template<class T>
ArrayDeque<T>::ArrayDeque(int32 initialCapacity)
{
  // Initialize all primitive fields to default values.
  
  this->capacity = 0;
  this->count = 0;
  this->headIdx = 0;
  this->tailIdx = 0;
  
#ifdef _DEBUG
  if (initialCapacity < 0) throw InvalidArgumentException::GreaterEqual(ZSTRING("ArrayDeque.ArrayDeque"), ZSTRING("initialCapacity"), 0);
#endif
  
  capacity = initialCapacity;
  
  if (initialCapacity > 0) elements = Array<typename T::Out>(initialCapacity);
}

// -------------------------------------------------------------------------------------------------
// Public / Methods
// -------------------------------------------------------------------------------------------------

template<class T>
typename T::Out ArrayDeque<T>::PeekFirst()
{
  return count == 0 ? T::Default() : elements[headIdx];
}

template<class T>
typename T::Out ArrayDeque<T>::PeekLast()
{
  return count == 0 ? T::Default() : elements[(tailIdx - 1 + capacity) % capacity];
}

template<class T>
typename T::Out ArrayDeque<T>::PopFirst()
{
  typename T::Out element;
  
  if (count == 0) return T::Default();
  
  element = elements[headIdx];
  elements[headIdx] = T::Default();
  headIdx = (headIdx + 1) % capacity;
  
  count--;
  
  return element;
}

template<class T>
typename T::Out ArrayDeque<T>::PopLast()
{
  typename T::Out element;
  
  if (count == 0) return T::Default();
  
  tailIdx = (tailIdx - 1 + capacity) % capacity;
  element = elements[tailIdx];
  elements[tailIdx] = T::Default();
  
  count--;
  
  return element;
}

template<class T>
void ArrayDeque<T>::PushFirst(typename T::In element)
{
  // Need to grow internal array?
  
  if (count + 1 > capacity) Grow();
  
  // Insert element.
  
  headIdx = (headIdx - 1 + capacity) % capacity;
  elements[headIdx] = element;
  
  count++;
}

template<class T>
void ArrayDeque<T>::PushLast(typename T::In element)
{
  // Need to grow internal array?
  
  if (count + 1 > capacity) Grow();
  
  // Insert element.
  
  elements[tailIdx] = element;
  tailIdx = (tailIdx + 1) % capacity;
  
  count++;
}

// -------------------------------------------------------------------------------------------------
// Private / Methods
// -------------------------------------------------------------------------------------------------

/*!
 * @brief  Grows the internal array.
 */
template<class T>
void ArrayDeque<T>::Grow()
{
  Array<typename T::Out> newElements;
  
  newElements = Array<typename T::Out>(Maths::MaxI(capacity + 16, capacity * 3 / 2));
  
  if (count > 0) 
  {
    if (headIdx >= tailIdx) 
    {
      int32 n;
      
      n = capacity - headIdx;
      
      ArrayUtilGeneric<T>::ArrayCopy(elements, headIdx, newElements, 0, n);
      ArrayUtilGeneric<T>::ArrayCopy(elements, 0, newElements, n, tailIdx);
    }
    else if (headIdx < tailIdx) ArrayUtilGeneric<T>::ArrayCopy(elements, headIdx, newElements, 0, count);
  }
  
  headIdx = 0;
  tailIdx = count;
  elements = newElements;
  capacity = elements.Length();
}

} } } 

#endif
