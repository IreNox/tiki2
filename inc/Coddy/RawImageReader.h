////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_IMAGING_RAWIMAGEREADER_H
#define CLODDY_API_IMAGING_RAWIMAGEREADER_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/PixelFormat.h"
#include "Cloddy/RawSampleFormat.h"

// Include referenced classes.

#include "Cloddy/NormalizeImageReader.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace IO { namespace Streams { class IDataStream; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Imaging { class RawImage; } } }
namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::API::Imaging::RawImageReader.

namespace Cloddy { namespace API { namespace Imaging
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::IO::Streams::IDataStream;
  
  // Use referenced classes.
  
  using CodeX::System::ByteBuffer;
  
  /*!
   * @brief  An IImageReader that reads raw image data.
   */
  class RawImageReader : public NormalizeImageReader
  {
    // Declare friend classes.
    
    friend class RawImage;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Returns the PixelFormat for raw image data of the given layout.
     * 
     * @param samplesPerPixel <b>[>=1]</b>  Number of samples per pixel.
     * @param sampleFormat The binary sample format.
     * 
     * @return The pixel format.
     */
    static PixelFormat GetPixelFormatForRawImageData(int32 samplesPerPixel, RawSampleFormat sampleFormat);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
  protected:
    
    virtual void DisposeManaged();
    
    virtual void DoReadScanline(int32 scanlineY, ByteBuffer* scanline);
    
    virtual void DoSkipScanlines(int32 count);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Number of bytes to skip after each pixel.
     */
    int32 pixelSkipCount;
    
    /*!
     * @brief  Number of bytes to skip after each scanline.
     */
    int32 scanlineSkipCount;
    
    /*!
     * @brief  The raw image data stream.
     */
    Ptr<IDataStream> stream;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of RawImageReader.
     * 
     * When \e scanlineStride  is set to \c 0 ,the stride will be computed as follows:
     * <pre>
     *     stride := pixelsPerColumn * samplesPerPixel * bitsPerSample / 8
     * </pre>
     * 
     * @param stream The data stream that contains the raw image data.
     * @param width Number of pixels per column.
     * @param height Number of pixels per row.
     * @param samplesPerPixel Number of samples per pixel.
     * @param sampleFormat Binary format of pixel samples.
     * @param scanlineStride Distance between corresponding pixels in adjacent scanlines,in bytes.
     */
    RawImageReader(IDataStream* stream, int32 width, int32 height, int32 samplesPerPixel, RawSampleFormat sampleFormat, int32 scanlineStride);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<RawImageReader> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xB2F51F74;
    
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
      if ((ptr = NormalizeImageReader::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
