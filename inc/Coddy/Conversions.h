////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_UTIL_CONVERSIONS_H
#define CLODDY_API_UTIL_CONVERSIONS_H

#include "CodeX/System.h"

// Declare class ::Cloddy::API::Util::Conversions.

namespace Cloddy { namespace API { namespace Util
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Helper class that performs various number conversions.
   */
  class Conversions
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Constants
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Maximum value for 16-bit integers.
     */
    static const int32 Max16 = 65535;
    
    /*!
     * @brief  Maximum value for 24-bit integers.
     */
    static const int32 Max24 = 16777215;
    
    /*!
     * @brief  Maximum value for 30-bit integers.
     */
    static const int32 Max30 = 1073741823;
    
    /*!
     * @brief  Maximum value for 8-bit integers.
     */
    static const int32 Max8 = 255;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Clamps the given value to the range <c>[0..65535]</c>.
     * 
     * @param value The input value.
     * 
     * @return The output value.
     */
    static int32 Clamp16(int32 value);
    
    /*!
     * @brief  Clamps the given value to the range <c>[0..16777215]</c>.
     * 
     * @param value The input value.
     * 
     * @return The output value.
     */
    static int32 Clamp24(int32 value);
    
    /*!
     * @brief  Clamps the given value to the range <c>[0..1073741823]</c>.
     * 
     * @param value The input value.
     * 
     * @return The output value.
     */
    static int32 Clamp30(int32 value);
    
    /*!
     * @brief  Clamps the given value to the range <c>[0..255]</c>.
     * 
     * @param value The input value.
     * 
     * @return The output value.
     */
    static int32 Clamp8(int32 value);
    
    /*!
     * @brief  Converts the given 16-bit value of range <c>[0..65535]</c> to a 30-bit value of 
     *         range <c>[0..1073741823]</c>.
     * 
     * @param value The input value.
     * 
     * @return The output value.
     */
    static int32 Convert16BitTo30Bit(int32 value);
    
    /*!
     * @brief  Converts the given 16-bit value of range <c>[0..65535]</c> to a 16-bit value of 
     *         range <c>[0..255]</c>.
     * 
     * @param value The input value.
     * 
     * @return <b>[0..255]</b>  The output value.
     */
    static int32 Convert16BitTo8Bit(int32 value);
    
    /*!
     * @brief  Converts the given 24-bit value of range <c>[0..16777215]</c> to a 30-bit value of 
     *         range <c>[0..1073741823]</c>.
     * 
     * @param value The input value.
     * 
     * @return The output value.
     */
    static int32 Convert24BitTo30Bit(int32 value);
    
    /*!
     * @brief  Converts the given 30-bit value of range <c>[0..1073741823]</c> to a 16-bit value of 
     *         range <c>[0..65535]</c>.
     * 
     * @param value The input value.
     * 
     * @return The output value.
     */
    static int32 Convert30BitTo16Bit(int32 value);
    
    /*!
     * @brief  Converts the given 30-bit value of range <c>[0..1073741823]</c> to a 24-bit value of 
     *         range <c>[0..16777215]</c>.
     * 
     * @param value The input value.
     * 
     * @return The output value.
     */
    static int32 Convert30BitTo24Bit(int32 value);
    
    /*!
     * @brief  Converts the given 30-bit value of range <c>[0..1073741823]</c> to a 8-bit value of 
     *         range <c>[0..255]</c>.
     * 
     * @param value The input value.
     * 
     * @return The output value.
     */
    static int32 Convert30BitTo8Bit(int32 value);
    
    /*!
     * @brief  Converts the given 8-bit value of range <c>[0..255]</c> to a 16-bit value of range 
     *         <c>[0..65535]</c>.
     * 
     * @param value The input value.
     * 
     * @return <b>[0..65535]</b>  The output value.
     */
    static int32 Convert8BitTo16Bit(int32 value);
    
    /*!
     * @brief  Converts the given 8-bit value of range <c>[0..255]</c> to a 30-bit value of range 
     *         <c>[0..1073741823]</c>.
     * 
     * @param value The input value.
     * 
     * @return The output value.
     */
    static int32 Convert8BitTo30Bit(int32 value);
    
    /*!
     * @brief  Converts the given red,green and blue channel values to an 8-bit grayscale intensity 
     *         value.
     * 
     * @param r The red channel in range <c>[0..255]</c>.
     * @param g The green channel in range <c>[0..255]</c>.
     * @param b The blue channel in range <c>[0..255]</c>.
     * 
     * @return <b>[0..255]</b>  The output value.
     */
    static int32 ConvertRGB8ToI16(int32 r, int32 g, int32 b);
    
    /*!
     * @brief  Converts the given red,green and blue channel values to a 16-bit grayscale intensity 
     *         value.
     * 
     * @param r The red channel in range <c>[0..255]</c>.
     * @param g The green channel in range <c>[0..255]</c>.
     * @param b The blue channel in range <c>[0..255]</c>.
     * 
     * @return <b>[0..65535]</b>  The output value.
     */
    static int32 ConvertRGB8ToI8(int32 r, int32 g, int32 b);
    
    /*!
     * @brief  Rounds the given 30-bit value down to the given number of significant bits.
     * 
     * @param value The input value.
     * @param bits The number of significant bits.
     * 
     * @return The output value.
     */
    static int32 RoundDown30Bit(int32 value, int32 bits);
    
    /*!
     * @brief  Rounds the given 30-bit value down to the given number of significant bits.
     * 
     * @param value The input value.
     * @param bits The number of significant bits.
     * 
     * @return The output value.
     */
    static int32 RoundUp30Bit(int32 value, int32 bits);
  };
  
} } } 

#endif
