////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_SAMPLEBUFFERS_SAMPLEBUFFER_H
#define CLODDY_API_HEIGHTMAPS_SAMPLEBUFFERS_SAMPLEBUFFER_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/PixelFormat.h"

// Include referenced interfaces.

#include "Cloddy/ISampleBuffer.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleBuffers { class ISampleBufferVisitor; } } } }
namespace Cloddy { namespace API { namespace Imaging { class IImageReader; } } }

// Forward declare referenced classes.

namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::API::Heightmaps::SampleBuffers::SampleBuffer.

namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleBuffers
{
  // Use referenced namespaces.
  
  using namespace Cloddy::API::Imaging;
  using namespace CodeX;
  
  // Use referenced classes.
  
  using CodeX::System::ByteBuffer;
  
  /*!
   * @brief  Abstract base class for ISampleBuffer implementations.
   */
  class SampleBuffer : public virtual ISampleBuffer
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual int32 GetHeight();
    
    virtual int32 GetOffset();
    
    virtual int32 GetStride();
    
    virtual int32 GetWidth();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void Accept(ISampleBufferVisitor* visitor) = 0;
    
    virtual int32 GetRowOffset(int32 y);
    
    virtual int32 GetSampleOffset(int32 x, int32 y);
    
    virtual Ptr<IImageReader> ReadAsImage(PixelFormat pixelFormat);
    
    virtual void ReadFromImage(IImageReader* image);
    
    virtual void Shift(int32 x, int32 y);
    
    virtual Ptr<ISampleBuffer> SubBuffer(int32 x, int32 y, int32 width, int32 height);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Attributes
    // ---------------------------------------------------------------------------------------------
  protected:
    
    /*!
     * @brief  Height of this sample buffer.
     */
    int32 height;
    
    /*!
     * @brief  Offset of top-left sample of this sample buffer in buffer array.
     */
    int32 offset;
    
    /*!
     * @brief  The stride of this sample buffer.
     */
    int32 stride;
    
    /*!
     * @brief  Width of this sample buffer.
     */
    int32 width;
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of SampleBuffer.
     * 
     * @param width <b>[>0]</b>  Width of this sample buffer.
     * @param height <b>[>0]</b>  Height of this sample buffer.
     * @param offset <b>[>=0]</b>  Offset of top-left sample of this sample buffer in buffer array.
     * @param stride <b>[>0]</b>  The stride of this sample buffer.
     */
    SampleBuffer(int32 width, int32 height, int32 offset, int32 stride);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Copies the samples in this sample buffer (source and target region may overlap).
     * 
     * @param sourceOffset Offset of first source sample.
     * @param targetOffset Offset of first target sample.
     * @param count The number of samples to copy.
     */
    virtual void CopySamples(int32 sourceOffset, int32 targetOffset, int32 count) = 0;
    
    /*!
     * @brief  Reads the samples in this buffer as an image.
     * 
     * @return <b>[not-null]</b>  The IImageReader object.
     */
    virtual Ptr<IImageReader> DoReadAsImage() = 0;
    
    /*!
     * @brief  This method is called when the #ReadFromImage is invoked in order to perform 
     *         optional conversions on the provided IImageReader.
     * 
     * The default implementation simply returns \e image .
     * 
     * @param image The IImageReader object that has been passed to ISampleBuffer::ReadFromImage.
     * 
     * @return The IImageReader to use.
     * 
     * @see #DoReadFromImage(int32,ByteBuffer*)
     */
    virtual Ptr<IImageReader> DoReadFromImage(IImageReader* image);
    
    /*!
     * @brief  This method is called from within #ReadFromImage for each scanline of the source 
     *         image.
     * 
     * The scanline layout corresponds to the PixelFormat of the IImageReader object that 
     * the #DoReadFromImage(IImageReader*) method has returned.
     * 
     * @param y Y-coordinate of current scanline.
     * @param scanline The byte buffer that holds the scanline pixels.
     * 
     * @see #DoReadFromImage(IImageReader*)
     */
    virtual void DoReadFromImage(int32 y, ByteBuffer* scanline) = 0;
    
    /*!
     * @brief  Creates a new sample buffer that shares a subregion of this sample buffer.
     * 
     * @param offset Offset of top-left sample of sub buffer.
     * @param stride Stride of this sample buffer.
     * @param width Width of the sub buffer.
     * @param height Height of the sub buffer.
     * 
     * @return <b>[not-null]</b>  The ISampleBuffer object.
     */
    virtual Ptr<ISampleBuffer> DoSubBuffer(int32 offset, int32 stride, int32 width, int32 height) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<SampleBuffer> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x77FA3605;
    
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
      if ((ptr = ISampleBuffer::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } 

#endif
