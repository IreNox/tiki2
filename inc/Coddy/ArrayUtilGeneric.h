////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_SYSTEM_ARRAYUTILGENERIC_H
#define CLODDY_CORE_SYSTEM_ARRAYUTILGENERIC_H

#include "CodeX/System.h"

// Declare class ::Cloddy::Core::System::ArrayUtilGeneric.

namespace Cloddy { namespace Core { namespace System
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Helper class for generic array operations.
   */
  template<class T>
  class ArrayUtilGeneric
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Appends the given element to the specified array.
     * 
     * @param array The input array (can be \c null ).
     * @param element The element to append.
     * 
     * @return <b>[not-null]</b>  The resulting array.
     */
    static Array<typename T::Out> Append(Array<typename T::Out> array, typename T::In element);
    
    /*!
     * @brief  Copies elements from one array to another.
     * 
     * @param source <b>[not-null]</b>  The source array.
     * @param sourceIdx <b>[>=0]</b>  Index of first element in \e source  to copy.
     * @param target <b>[not-null]</b>  The target array.
     * @param targetIdx <b>[>=0]</b>  Index of first element in \e target  to write.
     * @param count <b>[>=0]</b>  Total number of array elements to copy.
     */
    static void ArrayCopy(Array<typename T::Out> source, int32 sourceIdx, Array<typename T::Out> target, int32 targetIdx, int32 count);
    
    /*!
     * @brief  Returns an array that represents the concatenation of the given input array.
     * 
     * @param first First input array (can be \c null ).
     * @param second Second input array (can be \c null ).
     * 
     * @return The output array (will be \c null  iff \e first  and \e second  are \c null ).
     */
    static Array<typename T::Out> Concat(Array<typename T::Out> first, Array<typename T::Out> second);
    
    /*!
     * @brief  Grows the given array to the specified length.
     * 
     * @param array The array to grow.
     * @param count <b>[>=0]</b>  Number of valid elements in \e array .
     * @param length <b>[>=0]</b>  New array length.
     * 
     * @return <b>[not-null]</b>  The grown array.
     */
    static Array<typename T::Out> GrowTo(Array<typename T::Out> array, int32 count, int32 length);
    
    /*!
     * @brief  Proportionally grows the given array until its length is equal to or greater than 
     *         the specified length.
     * 
     * The new array length is computed as follows:
     * <pre>
     *       newLength := max(length, currentLength * 3 / 2)
     * </pre>
     * where \c newLength  is the length of the returned array,\c length  is the value of 
     * the \e length  parameter and \c currentLength  is the length of the given \e array .
     * 
     * If \e count  is greater than zero,all array elements in the range <c>[0..count-1]</c> are 
     * copied from the given \e array  to the newly allocated one.
     * 
     * @param array The array to grow.
     * @param count <b>[>=0]</b>  Number of valid elements in \e array .
     * @param length <b>[>=0]</b>  New array length (minimum).
     * 
     * @return <b>[not-null]</b>  The grown array.
     */
    static Array<typename T::Out> GrowUntil(Array<typename T::Out> array, int32 count, int32 length);
  };
  
} } } 

#endif
