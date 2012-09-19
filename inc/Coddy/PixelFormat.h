////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_IMAGING_PIXELFORMAT_H
#define CLODDY_API_IMAGING_PIXELFORMAT_H

#include "CodeX/System.h"

// Declare enumeration ::Cloddy::API::Imaging::PixelFormat.

namespace Cloddy { namespace API { namespace Imaging
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Enumeration of supported pixel formats.
   */
  enum PixelFormat
  {
    /*!
     * @brief  Unknown pixel format.
     */
    PixelFormat_UnknownPixelFormat = 0,
    
    /*!
     * @brief  8-bit grayscale pixel values.
     * 
     * Each byte in the scanline represents a grayscale pixel;\c 0x00  is black and \c 0xFF  is 
     * white.
     * <pre>
     *     +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
     *     | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | A | B | C | D | E | F | Byte offset
     *     +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
     *     | G | G | G | G | G | G | G | G | G | G | G | G | G | G | G | G | Scanline pixel
     *     +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
     * </pre>
     */
    PixelFormat_Grayscale8 = 1,
    
    /*!
     * @brief  16-bit grayscale pixel values.
     * 
     * Two consecutive bytes in the scanline represent a grayscale pixel;\c 0x0000  is black and 
     * \c 0xFFFF  is white.The high byte (MSB)is stored at the lower byte offset,the low byte (LSB)
     * at the higher byte offset (ie. big-endian).
     * <pre>
     *     +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
     *     | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | A | B | C | D | E | F | Byte offset
     *     +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
     *     | H   L | H   L | H   L | H   L | H   L | H   L | H   L | H   L | Scanline pixel
     *     +-------+-------+-------+-------+-------+-------+-------+-------+
     * </pre>
     */
    PixelFormat_Grayscale16 = 2,
    
    /*!
     * @brief  24-bit RGB truecolor pixel values.
     * 
     * Three consecutive bytes in the scanline represent a truecolor pixel;the first byte 
     * represents the red channel,the second byte represents the green channel and the third byte 
     * represents the blue channel.A channel value of \c 0x00  represents black and \c 0xFF  
     * represents maximum intensity.
     * <pre>
     *     +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
     *     | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | A | B | C | D | E | F | Byte offset
     *     +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
     *     | R   G   B | R   G   B | R   G   B | R   G   B | R   G   B | ..  Scanline pixel
     *     +-----------+-----------+-----------+-----------+-----------+---+
     * </pre>
     */
    PixelFormat_Truecolor24 = 3,
    
    /*!
     * @brief  32-bit ARGB truecolor pixel values.
     * 
     * Four consecutive bytes in the scanline represent a truecolor pixel;the first byte represents 
     * the red channel,the second byte represents the green channel,the third byte represents the 
     * blue channel and the fourth byte represents the alpha channel.A channel value of \c 0x00  
     * represents black resp. fully transparent and \c 0xFF  represents maximum intensity resp. 
     * fully opaque.
     * <pre>
     *     +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
     *     | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | A | B | C | D | E | F | Byte offset
     *     +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
     *     | R   G   B   A | R   G   B   A | R   G   B   A | R   G   B   A | Scanline pixel
     *     +---------------|---------------|---------------+---------------+
     * </pre>
     */
    PixelFormat_Truecolor32 = 4
  };
  
} } } 

#endif
