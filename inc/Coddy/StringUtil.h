////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_SYSTEM_STRINGUTIL_H
#define CLODDY_CORE_SYSTEM_STRINGUTIL_H

#include "CodeX/System_Native.h"

// Forward declare referenced classes.

namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::Core::System::StringUtil.

namespace Cloddy { namespace Core { namespace System
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced classes.
  
  using CodeX::System::ByteBuffer;
  
  /*!
   * @brief  Helper class for dealing with Strings.
   */
  class StringUtil
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Returns the given default value if \e value  is \c null  orhas a length of \c 0 .
     * 
     * @param value The string value.
     * @param defaultValue The default value.
     * 
     * @return The resulting value.
     */
    static String DefaultIfEmpty(String value, String defaultValue);
    
    /*!
     * @brief  Returns the given default value if \e value  is \c null ,has a length of \c 0  or 
     *         contains only whitespace characters.
     * 
     * @param value The string value.
     * @param defaultValue The default value.
     * 
     * @return The resulting value.
     */
    static String DefaultIfEmptyOrWhitespace(String value, String defaultValue);
    
    /*!
     * @brief  Returns the given default value if \e value  is \c null .
     * 
     * @param value The string value.
     * @param defaultValue The default value.
     * 
     * @return The resulting value.
     */
    static String DefaultIfNull(String value, String defaultValue);
    
    /*!
     * @brief  Checks if the given string is empty.
     * 
     * A string is considered empty if it is \c null  or has a length or \c 0 .
     * 
     * @param value The string.
     * 
     * @return \c true  if \e value  is empty,\c false  if not.
     */
    static bool IsEmpty(String value);
    
    /*!
     * @brief  Checks if the given string is empty or whitespace.
     * 
     * A string is considered empty or whitespace.if it is \c null ,has a length or \c 0  or 
     * contains only whitespace characters.
     * 
     * @param value The string.
     * 
     * @return \c true  if \e value  is empty or whitespace.,\c false  if not.
     */
    static bool IsEmptyOrWhitespace(String value);
    
    /*!
     * @brief  Repeatedly prepends the given character to the specified string until the desired 
     *         total length has been reached.
     * 
     * @param str <b>[not-null]</b>  The string to pad.
     * @param length <b>[>=0]</b>  The desired total string length.
     * @param c The pad character.
     * 
     * @return <b>[not-null]</b>  The resulting string.
     */
    static String PadLeft(String str, int32 length, wchar_t c);
    
    /*!
     * @brief  Repeatedly appends the given character to the specified string until the desired 
     *         total length has been reached.
     * 
     * @param str <b>[not-null]</b>  The string to pad.
     * @param length <b>[>=0]</b>  The desired total string length.
     * @param c The pad character.
     * 
     * @return <b>[not-null]</b>  The resulting string.
     */
    static String PadRight(String str, int32 length, wchar_t c);
    
    /*!
     * @brief  Returns a hexadecimal number string for the given 8-bit integer value.
     * 
     * @param value The value.
     * 
     * @return The hexadecimal number string.
     */
    static String ToHexB(int8 value);
    
    /*!
     * @brief  Returns a hexadecimal number string for the given 32-bit integer value.
     * 
     * @param value The value.
     * 
     * @return The hexadecimal number string.
     */
    static String ToHexI(int32 value);
    
    /*!
     * @brief  Returns a hexadecimal number string for the given 64-bit integer value.
     * 
     * @param value The value.
     * 
     * @return The hexadecimal number string.
     */
    static String ToHexL(int64 value);
    
    /*!
     * @brief  Returns a hexadecimal number string for the given 16-bit integer value.
     * 
     * @param value The value.
     * 
     * @return The hexadecimal number string.
     */
    static String ToHexS(int16 value);
    
    /*!
     * @brief  Returns a string from the given character sequence.
     * 
     * @param array <b>[not-null]</b>  The input character array.
     * @param offset <b>[>=0]</b>  Offset into \e array .
     * @param length <b>[>=0]</b>  Number of input tokens to convert.
     * 
     * @return <b>[not-null]</b>  The string.
     */
    static String ToString(Array<wchar_t> array, int32 offset, int32 length);
    
    /*!
     * @brief  Returns an ASCII string from the given byte sequence.
     * 
     * @param buffer <b>[not-null]</b>  The buffer holding the byte sequence.
     * 
     * @return <b>[not-null]</b>  The ASCII string.
     */
    static String ToString(ByteBuffer* buffer);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Array of hexadecimal digits.
     */
    static const Array<String> Digits;
  };
  
} } } 

#endif
