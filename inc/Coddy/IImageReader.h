////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_IMAGING_IIMAGEREADER_H
#define CLODDY_API_IMAGING_IIMAGEREADER_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/PixelFormat.h"

// Include referenced interfaces.

#include "CodeX/IDisposable.h"
#include "Cloddy/IImageOp.h"
#include "Cloddy/IUserData.h"

// Forward declare referenced classes.

namespace CodeX { namespace System { class ByteBuffer; } }

// Declare interface ::Cloddy::API::Imaging::IImageReader.

namespace Cloddy { namespace API { namespace Imaging
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Kernel::IUserData;
  using CodeX::System::IDisposable;
  
  // Use referenced classes.
  
  using CodeX::System::ByteBuffer;
  
  /*!
   * @brief  Base interface for classes that read images scanline after scanline.
   */
  class NO_VTABLE IImageReader : public virtual IImageOp<Ref<IImageReader> >, public virtual IDisposable, public virtual IUserData
  {
    // ---------------------------------------------------------------------------------------------
    // Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Number of bytes per pixel.
     * 
     * @return <b>[>0]</b>  The number of bytes per pixel.
     */
    virtual int32 GetBytesPerPixel() = 0;
    
    /*!
     * @brief  Has the image reader finished (ie. the whole image has been read)?
     * 
     * @return \c true  if the whole image has been read,\c false  if not.
     */
    virtual bool HasFinished() = 0;
    
    /*!
     * @brief  Height of the processed image,in pixels.
     * 
     * @return <b>[>0]</b>  The image height,in pixels.
     */
    virtual int32 GetHeight() = 0;
    
    /*!
     * @brief  The pixel format of the processed image.
     * 
     * @return The PixelFormat.
     */
    virtual PixelFormat GetPixelFormat() = 0;
    
    /*!
     * @brief  The length of a single scanline,in bytes.
     * 
     * @return <b>[>0]</b>  The scanline length,in bytes.
     */
    virtual int32 GetScanlineLength() = 0;
    
    /*!
     * @brief  The Y-coordinate that will be read upon the next call to #ReadScanline.
     * 
     * @return <b>[0..#GetHeight]</b>  The scanline Y-coordinate.
     */
    virtual int32 GetScanlineY() = 0;
    
    /*!
     * @brief  Width of the processed image,in pixels.
     * 
     * @return <b>[>0]</b>  The image width,in pixels.
     */
    virtual int32 GetWidth() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Reads the next scanline.
     * 
     * The given output buffer must contain at least #GetScanlineLength remaining bytes.
     * 
     * The format of the read scanline depends on the PixelFormat:
     *   - PixelFormat::PixelFormat_Grayscale8:
     *   Each byte in the scanline represents a grayscale pixel;\c 0x00  is black and \c 0xFF  is 
     *   white.
     *   <pre>
     *             +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
     *             | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | A | B | C | D | E | F | Byte offset
     *             +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
     *             | G | G | G | G | G | G | G | G | G | G | G | G | G | G | G | G | Scanline pixel
     *             +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
     *   </pre>
     *   - PixelFormat::PixelFormat_Grayscale16:
     *   Two consecutive bytes in the scanline represent a grayscale pixel;\c 0x0000  is black and 
     *   \c 0xFFFF  is white.The high byte (MSB)is stored at the lower byte offset,the low byte (
     *   LSB)at the higher byte offset (ie. big-endian).
     *   <pre>
     *             +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
     *             | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | A | B | C | D | E | F | Byte offset
     *             +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
     *             | H   L | H   L | H   L | H   L | H   L | H   L | H   L | H   L | Scanline pixel
     *             +-------+-------+-------+-------+-------+-------+-------+-------+
     *   </pre>
     *   - PixelFormat::PixelFormat_Truecolor24:
     *   Three consecutive bytes in the scanline represent a truecolor pixel;the first byte 
     *   represents the red channel,the second byte represents the green channel and the third byte 
     *   represents the blue channel.A channel value of \c 0x00  represents black and \c 0xFF  
     *   represents maximum intensity.
     *   <pre>
     *             +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
     *             | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | A | B | C | D | E | F | Byte offset
     *             +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
     *             | R   G   B | R   G   B | R   G   B | R   G   B | R   G   B | ..  Scanline pixel
     *             +-----------+-----------+-----------+-----------+-----------+---+
     *   </pre>
     *   - PixelFormat::PixelFormat_Truecolor32:
     *   Four consecutive bytes in the scanline represent a truecolor pixel;the first byte 
     *   represents the red channel,the second byte represents the green channel,the third byte 
     *   represents the blue channel and the fourth byte represents the alpha channel.A channel 
     *   value of \c 0x00  represents black resp. fully transparent and \c 0xFF  represents maximum 
     *   intensity resp. fully opaque.
     *   <pre>
     *             +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
     *             | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | A | B | C | D | E | F | Byte offset
     *             +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
     *             | R   G   B   A | R   G   B   A | R   G   B   A | R   G   B   A | Scanline pixel
     *             +---------------+---------------+---------------+---------------+
     *   </pre>
     * 
     * @param scanline <b>[not-null]</b>  The output buffer for the read scanline bytes.
     * 
     * @return Y-coordinate of processed scanline.
     */
    virtual int32 ReadScanline(ByteBuffer* scanline) = 0;
    
    /*!
     * @brief  Skips the given number of scanlines.
     * 
     * @param count <b>[>=0]</b>  The number of scanlines to skip.
     */
    virtual void SkipScanlines(int32 count) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IImageReader> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x84DCA921;
    
    /*!
     * @brief Tries to cast this object to the given type.
     *
     * @param typeId The ID of the type to cast to.
     *
     * @return The result of the type cast. Can be \c 0 if the requested cast is an invalid 
     *         downcast.
     */
    protected: virtual void* TryCast(int typeId)
    {
      if (typeId == TypeId) return (void*) this;
      void* ptr;
      if ((ptr = IImageOp<Ref<IImageReader> >::TryCast(typeId)) != 0) return ptr;
      if ((ptr = IDisposable::TryCast(typeId)) != 0) return ptr;
      if ((ptr = IUserData::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
} } } 

#endif
