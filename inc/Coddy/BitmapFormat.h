////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_BROWSING_BITMAPFORMAT_H
#define CLODDY_API_BROWSING_BITMAPFORMAT_H

#include "CodeX/System.h"

// Declare enumeration ::Cloddy::API::Browsing::BitmapFormat.

namespace Cloddy { namespace API { namespace Browsing
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Enumeration of bitmap formats.
   */
  enum BitmapFormat
  {
    /*!
     * @brief  Truecolor without alpha.
     * 
     * Each pixel is a 16-bit value with the following color channel layout:
     * <pre>
     *     bits #15 .. #11 : red   [0..31]
     *     bits #10 .. #5  : green [0..63]
     *     bits #4  .. #0  : blue  [0..31]
     * </pre>
     */
    BitmapFormat_RGB_565 = 0,
    
    /*!
     * @brief  Truecolor without alpha.
     * 
     * Each pixel is a 24-bit value with the following color channel layout:
     * <pre>
     *     bits #23 .. #16 : red   [0..255]
     *     bits #15 .. #8  : green [0..255]
     *     bits #7  .. #0  : blue  [0..255]
     * </pre>
     */
    BitmapFormat_RGB_888 = 1,
    
    /*!
     * @brief  Truecolor with alpha.
     * 
     * Each pixel is a 16-bit value with the following color channel layout:
     * <pre>
     *     bits #15 .. #15 : alpha [0..1]
     *     bits #14 .. #10 : red   [0..31]
     *     bits #9  .. #5  : green [0..31]
     *     bits #4  .. #0  : blue  [0..31]
     * </pre>
     */
    BitmapFormat_ARGB_1555 = 1,
    
    /*!
     * @brief  Truecolor with alpha.
     * 
     * Each pixel is a 32-bit value with the following color channel layout:
     * <pre>
     *     bits #31 .. #24 : alpha [0..255]
     *     bits #23 .. #16 : red   [0..255]
     *     bits #15 .. #8  : green [0..255]
     *     bits #7  .. #0  : blue  [0..255]
     * </pre>
     */
    BitmapFormat_ARGB_888 = 1
  };
  
} } } 

#endif
