////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_SYSTEM_ARRAYUTILGENERIC_HPP
#define CLODDY_CORE_SYSTEM_ARRAYUTILGENERIC_HPP

#include "Cloddy/ArrayUtilGeneric.h"

// Include referenced classes.

#include "CodeX/ErrorInfo.h"
#include "CodeX/InvalidArgumentException.h"

namespace Cloddy { namespace Core { namespace System {

// Use referenced namespaces.

using namespace CodeX;

// Use referenced classes.

using CodeX::System::ErrorInfo;
using CodeX::System::InvalidArgumentException;

// -------------------------------------------------------------------------------------------------
// Public / Methods
// -------------------------------------------------------------------------------------------------

/*!
 * @brief  Appends the given element to the specified array.
 * 
 * @param array The input array (can be \c null ).
 * @param element The element to append.
 * 
 * @return <b>[not-null]</b>  The resulting array.
 */
template<class T>
Array<typename T::Out> ArrayUtilGeneric<T>::Append(Array<typename T::Out> array, typename T::In element)
{
  Array<typename T::Out> result;
  int32 n;
  
  n = array == null ? 0 : array.Length();
  result = Array<typename T::Out>(n + 1);
  
  if (n > 0) ArrayCopy(array, 0, result, 0, n);
  
  result[n] = element;
  
  return result;
}

/*!
 * @brief  Copies elements from one array to another.
 * 
 * @param source <b>[not-null]</b>  The source array.
 * @param sourceIdx <b>[>=0]</b>  Index of first element in \e source  to copy.
 * @param target <b>[not-null]</b>  The target array.
 * @param targetIdx <b>[>=0]</b>  Index of first element in \e target  to write.
 * @param count <b>[>=0]</b>  Total number of array elements to copy.
 */
template<class T>
void ArrayUtilGeneric<T>::ArrayCopy(Array<typename T::Out> source, int32 sourceIdx, Array<typename T::Out> target, int32 targetIdx, int32 count)
{
#ifdef _DEBUG
  if (source == null) throw InvalidArgumentException::NotNull(ZSTRING("ArrayUtilGeneric.ArrayCopy"), ZSTRING("source"));
  if (sourceIdx < 0) throw InvalidArgumentException::GreaterEqual(ZSTRING("ArrayUtilGeneric.ArrayCopy"), ZSTRING("sourceIdx"), 0);
  if (target == null) throw InvalidArgumentException::NotNull(ZSTRING("ArrayUtilGeneric.ArrayCopy"), ZSTRING("target"));
  if (targetIdx < 0) throw InvalidArgumentException::GreaterEqual(ZSTRING("ArrayUtilGeneric.ArrayCopy"), ZSTRING("targetIdx"), 0);
  if (count < 0) throw InvalidArgumentException::GreaterEqual(ZSTRING("ArrayUtilGeneric.ArrayCopy"), ZSTRING("count"), 0);
#endif
  
  // Perform array copy.
  
  if (targetIdx <= sourceIdx) 
  {
    while (count-- > 0)
    {
      target[targetIdx++] = source[sourceIdx++];
    }
  }
  else 
  {
    targetIdx += count;
    sourceIdx += count;
    
    while (count-- > 0)
    {
      target[--targetIdx] = source[--sourceIdx];
    }
  }
}

/*!
 * @brief  Returns an array that represents the concatenation of the given input array.
 * 
 * @param first First input array (can be \c null ).
 * @param second Second input array (can be \c null ).
 * 
 * @return The output array (will be \c null  iff \e first  and \e second  are \c null ).
 */
template<class T>
Array<typename T::Out> ArrayUtilGeneric<T>::Concat(Array<typename T::Out> first, Array<typename T::Out> second)
{
  if (first == null && second == null) return null;
  if (first != null && second != null) 
  {
    Array<typename T::Out> result;
    
    result = Array<typename T::Out>(first.Length() + second.Length());
    
    ArrayCopy(first, 0, result, 0, first.Length());
    ArrayCopy(second, 0, result, first.Length(), second.Length());
    
    return result;
  }
  if (first == null) return second;
  
  return first;
}

/*!
 * @brief  Grows the given array to the specified length.
 * 
 * @param array The array to grow.
 * @param count <b>[>=0]</b>  Number of valid elements in \e array .
 * @param length <b>[>=0]</b>  New array length.
 * 
 * @return <b>[not-null]</b>  The grown array.
 */
template<class T>
Array<typename T::Out> ArrayUtilGeneric<T>::GrowTo(Array<typename T::Out> array, int32 count, int32 length)
{
#ifdef _DEBUG
  if (count < 0) throw InvalidArgumentException::GreaterEqual(ZSTRING("ArrayUtilGeneric.GrowTo"), ZSTRING("count"), 0);
  if (length < 0) throw InvalidArgumentException::GreaterEqual(ZSTRING("ArrayUtilGeneric.GrowTo"), ZSTRING("length"), 0);
#endif
  
  Array<typename T::Out> newArray;
  
  // Create new array.
  
  newArray = Array<typename T::Out>(length);
  
  // Copy old array elements (if necessary).
  
  if (count > 0) ArrayCopy(array, 0, newArray, 0, count);
  
  // Return new array.
  
  return newArray;
}

/*!
 * @brief  Proportionally grows the given array until its length is equal to or greater than the 
 *         specified length.
 * 
 * The new array length is computed as follows:
 * <pre>
 *       newLength := max(length, currentLength * 3 / 2)
 * </pre>
 * where \c newLength  is the length of the returned array,\c length  is the value of 
 * the \e length  parameter and \c currentLength  is the length of the given \e array .
 * 
 * If \e count  is greater than zero,all array elements in the range <c>[0..count-1]</c> are copied 
 * from the given \e array  to the newly allocated one.
 * 
 * @param array The array to grow.
 * @param count <b>[>=0]</b>  Number of valid elements in \e array .
 * @param length <b>[>=0]</b>  New array length (minimum).
 * 
 * @return <b>[not-null]</b>  The grown array.
 */
template<class T>
Array<typename T::Out> ArrayUtilGeneric<T>::GrowUntil(Array<typename T::Out> array, int32 count, int32 length)
{
#ifdef _DEBUG
  if (count < 0) throw InvalidArgumentException::GreaterEqual(ZSTRING("ArrayUtilGeneric.GrowUntil"), ZSTRING("count"), 0);
  if (length < 0) throw InvalidArgumentException::GreaterEqual(ZSTRING("ArrayUtilGeneric.GrowUntil"), ZSTRING("length"), 0);
#endif
  
  int32 newLength;
  
  newLength = array == null ? 0 : array.Length() * 3 / 2;
  
  if (newLength < length) newLength = length;
  
  return GrowTo(array, count, newLength);
}

} } } 

#endif
