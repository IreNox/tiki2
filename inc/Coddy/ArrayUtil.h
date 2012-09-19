////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_SYSTEM_ARRAYUTIL_H
#define CLODDY_CORE_SYSTEM_ARRAYUTIL_H

#include "CodeX/System.h"

// Declare class ::Cloddy::Core::System::ArrayUtil.

namespace Cloddy { namespace Core { namespace System
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Helper class for dealing with arrays.
   */
  class ArrayUtil
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Runs a binary search for \e value  in the given array.
     * 
     * @param value The value to search.
     * @param array <b>[not-null]</b>  The array (must be sorted in ascending order).
     * 
     * @return Index of the array element that equals \e value .If the value has not been found in 
     * the array,\c -idx-1  is returned,where \c idx  is the insertion index of \e value .
     */
    static int32 BinarySearch(int32 value, Array<int32> array);
    
    /*!
     * @brief  Runs a binary search for \e value  in the given array.
     * 
     * @param value The value to search.
     * @param array <b>[not-null]</b>  The array (must be sorted in ascending order).
     * @param offset <b>[>=0]</b>  Index of first array element to search.
     * @param count <b>[>=0]</b>  Length of array range to search.
     * 
     * @return Index of the array element that equals \e value .If the value has not been found in 
     * the array,\c -idx-1  is returned,where \c idx  is the insertion index of \e value .
     */
    static int32 BinarySearch(int32 value, Array<int32> array, int32 offset, int32 count);
    
    /*!
     * @brief  Runs a binary search for \e value  in the given array.
     * 
     * @param value The value to search.
     * @param array <b>[not-null]</b>  The array (must be sorted in ascending order).
     * 
     * @return Index of the array element that equals \e value .If the value has not been found in 
     * the array,\c -idx-1  is returned,where \c idx  is the insertion index of \e value .
     */
    static int32 BinarySearch(int64 value, Array<int64> array);
    
    /*!
     * @brief  Runs a binary search for \e value  in the given array.
     * 
     * @param value The value to search.
     * @param array <b>[not-null]</b>  The array (must be sorted in ascending order).
     * @param offset <b>[>=0]</b>  Index of first array element to search.
     * @param count <b>[>=0]</b>  Length of array range to search.
     * 
     * @return Index of the array element that equals \e value .If the value has not been found in 
     * the array,\c -idx-1  is returned,where \c idx  is the insertion index of \e value .
     */
    static int32 BinarySearch(int64 value, Array<int64> array, int32 offset, int32 count);
    
    /*!
     * @brief  Sorts the given array range.
     * 
     * @param array <b>[not-null]</b>  The array that holds the range to sort.
     * 
     * @return <b>[not-null]</b>  The sorted input \e array .
     */
    static Array<int64> Sort(Array<int64> array);
    
    /*!
     * @brief  Sorts the given array range.
     * 
     * @param array <b>[not-null]</b>  The array that holds the range to sort.
     * @param offset <b>[>=0]</b>  Offset into \e array  to first element in range.
     * @param count <b>[>=0]</b>  Total number of elements in range.
     * 
     * @return <b>[not-null]</b>  The sorted input \e array .
     */
    static Array<int64> Sort(Array<int64> array, int32 offset, int32 count);
    
    /*!
     * @brief  Sorts the given array range.
     * 
     * @param array <b>[not-null]</b>  The array that holds the range to sort.
     * 
     * @return <b>[not-null]</b>  The sorted input \e array .
     */
    static Array<int32> Sort(Array<int32> array);
    
    /*!
     * @brief  Sorts the given array range.
     * 
     * @param array <b>[not-null]</b>  The array that holds the range to sort.
     * @param offset <b>[>=0]</b>  Offset into \e array  to first element in range.
     * @param count <b>[>=0]</b>  Total number of elements in range.
     * 
     * @return <b>[not-null]</b>  The sorted input \e array .
     */
    static Array<int32> Sort(Array<int32> array, int32 offset, int32 count);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Sorts the given array range.
     * 
     * @param array The array to sort.
     * @param from Start index of range to sort,inclusive.
     * @param to End index of range to sort,inclusive.
     */
    static void SortRange(Array<int32> array, int32 from, int32 to);
    
    /*!
     * @brief  Sorts the given array range.
     * 
     * @param array The array to sort.
     * @param from Start index of range to sort,inclusive.
     * @param to End index of range to sort,inclusive.
     */
    static void SortRange(Array<int64> array, int32 from, int32 to);
  };
  
} } } 

#endif
