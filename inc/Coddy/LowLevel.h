////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_SYSTEM_LOWLEVEL_H
#define CLODDY_CORE_SYSTEM_LOWLEVEL_H

#include "CodeX/System_Native.h"

// Declare class ::Cloddy::Core::System::LowLevel.

namespace Cloddy { namespace Core { namespace System
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  This class provides methods for accessing low level native functions.
   */
  class LowLevel
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Returns the human-readable name of the underlying platform.
     * 
     * @return <b>[not-null]</b>  The platform name.
     */
    static String GetPlatformName();
    
    /*!
     * @brief  Returns the number of processor on the system.
     * 
     * @return <b>[>=1]</b>  The number of processors.
     */
    static int32 GetProcessorCount();
    
    /*!
     * @brief  Returns the human-readable name of the underlying programming language.
     * 
     * @return <b>[not-null]</b>  The programming language name.
     */
    static String GetProgrammingLanguageName();
    
    /*!
     * @brief  Returns the system tick count.
     * 
     * @return The current system tick,in milliseconds.
     */
    static int32 GetTickCount();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Interprets the given 64-bit floating point value as a 64-bit integer value.
     * 
     * @param value The floating point value.
     * 
     * @return The integer value.
     */
    static int64 DoubleToLong(float64 value);
    
    /*!
     * @brief  Interprets the given 64-bit floating point value as a 64-bit integer value.
     * 
     * @param value The floating point value.
     * 
     * @return The integer value.
     */
    static int32 FloatToInt(float32 value);
    
    /*!
     * @brief  Converts the given 64-bit integer to a pointer.
     * 
     * @param pointer The integer value.
     * 
     * @return The pointer value.
     */
    static void* FromRawPointer(int64 pointer);
    
    /*!
     * @brief  Applies a randomization function to the given 32-bit input value,procuding a 32-bit 
     *         hash value.
     * 
     * @param value The input value.
     * 
     * @return The hash value.
     */
    static int32 Hash32(int32 value);
    
    /*!
     * @brief  Applies a randomization function to the given 64-bit input value,procuding a 32-bit 
     *         hash value.
     * 
     * @param value The input value.
     * 
     * @return The hash value.
     */
    static int32 Hash64(int64 value);
    
    /*!
     * @brief  Interprets the given 32-bit integer as a 32-bit floating point value.
     * 
     * @param value The integer value.
     * 
     * @return The floating point value.
     */
    static float32 IntToFloat(int32 value);
    
    /*!
     * @brief  Interprets the given 64-bit integer as a 64-bit floating point value.
     * 
     * @param value The integer value.
     * 
     * @return The floating point value.
     */
    static float64 LongToDouble(int64 value);
    
    /*!
     * @brief  Swaps the bytes of the given multibyte value.
     * 
     * @param value The multibyte value.
     * 
     * @return The swapped value.
     */
    static int16 SwapBytes(int16 value);
    
    /*!
     * @brief  Swaps the bytes of the given multibyte value.
     * 
     * @param value The multibyte value.
     * 
     * @return The swapped value.
     */
    static int32 SwapBytes(int32 value);
    
    /*!
     * @brief  Swaps the bytes of the given multibyte value.
     * 
     * @param value The multibyte value.
     * 
     * @return The swapped value.
     */
    static int64 SwapBytes(int64 value);
    
    /*!
     * @brief  Converts the given pointer to a 64-bit integer.
     * 
     * @param pointer The pointer value.
     * 
     * @return The integer value.
     */
    static int64 ToRawPointer(void* pointer);
    
    // ---------------------------------------------------------------------------------------------
    // Native code
    // ---------------------------------------------------------------------------------------------
    
    NATIVE_BLOCK_BEGIN ("6BE312B3-9D61-4174-A306-DBB5C1098E57")
    
    // Nothing to do here.
    
    NATIVE_BLOCK_END   ("6BE312B3-9D61-4174-A306-DBB5C1098E57")
  };
  
} } } 

#endif
