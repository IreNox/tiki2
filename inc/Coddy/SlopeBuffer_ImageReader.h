////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_SAMPLEBUFFERS_SLOPEBUFFER_IMAGEREADER_H
#define CLODDY_API_HEIGHTMAPS_SAMPLEBUFFERS_SLOPEBUFFER_IMAGEREADER_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/ImageReaderBase.h"

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleBuffers { class SlopeBuffer; } } } }
namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::API::Heightmaps::SampleBuffers::SlopeBuffer_ImageReader.

namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleBuffers
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced classes.
  
  using Cloddy::API::Imaging::ImageReaderBase;
  using CodeX::System::ByteBuffer;
  
  /*!
   * @brief  An implementation of the IImageReader interface that reads the slope samples of a 
   *         slope buffer as a 16-bit greyscale image.
   * 
   * A slope value of 0 degrees will be represented by a pixel value of \c 0 ,a slope value of 90 
   * degress will be represented by a pixel value of \c 65535 .
   */
  class SlopeBuffer_ImageReader : public ImageReaderBase
  {
    // Declare friend classes.
    
    friend class SlopeBuffer;
    
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
     * @brief  Offset to top-left buffer sample in #samples.
     */
    int32 offset;
    
    /*!
     * @brief  The slope buffer samples.
     */
    Array<float32> samples;
    
    /*!
     * @brief  The slope buffer stride.
     */
    int32 stride;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of SlopeBuffer_ImageReader.
     * 
     * @param width The image width.
     * @param height The image height.
     * @param samples The slope buffer samples.
     * @param offset The slope buffer offset.
     * @param stride The slope buffer stride.
     */
    SlopeBuffer_ImageReader(int32 width, int32 height, Array<float32> samples, int32 offset, int32 stride);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<SlopeBuffer_ImageReader> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x53172607;
    
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
      if ((ptr = ImageReaderBase::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } 

#endif
