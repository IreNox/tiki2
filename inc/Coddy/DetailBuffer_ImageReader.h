////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_SAMPLEBUFFERS_DETAILBUFFER_IMAGEREADER_H
#define CLODDY_API_HEIGHTMAPS_SAMPLEBUFFERS_DETAILBUFFER_IMAGEREADER_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/ImageReaderBase.h"

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleBuffers { class DetailBuffer; } } } }
namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::API::Heightmaps::SampleBuffers::DetailBuffer_ImageReader.

namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleBuffers
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced classes.
  
  using Cloddy::API::Imaging::ImageReaderBase;
  using CodeX::System::ByteBuffer;
  
  /*!
   * @brief  An IImageReader implementation that reads the detail channel values of an DetailBuffer 
   *         object as an 8-bit grayscale image.
   */
  class DetailBuffer_ImageReader : public ImageReaderBase
  {
    // Declare friend classes.
    
    friend class DetailBuffer;
    
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
     * @brief  The detail buffer.
     */
    Ptr<DetailBuffer> buffer;
    
    /*!
     * @brief  Sample offset to detail channel.
     */
    int32 offset;
    
    /*!
     * @brief  The detail channel values of the detail buffer.
     */
    Array<int32> samples;
    
    /*!
     * @brief  Bit offset to detail channel.
     */
    int32 shift;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of ElevationBuffer_ImageReader.
     * 
     * @param detailBuffer The #buffer object.
     * @param channel The detail channel to read.
     */
    DetailBuffer_ImageReader(DetailBuffer* detailBuffer, int32 channel);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<DetailBuffer_ImageReader> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x744F66F7;
    
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
