////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_SAMPLEBUFFERS_ISAMPLEBUFFER_H
#define CLODDY_API_HEIGHTMAPS_SAMPLEBUFFERS_ISAMPLEBUFFER_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/PixelFormat.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleBuffers { class ISampleBufferVisitor; } } } }
namespace Cloddy { namespace API { namespace Imaging { class IImageReader; } } }

// Declare interface ::Cloddy::API::Heightmaps::SampleBuffers::ISampleBuffer.

namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleBuffers
{
  // Use referenced namespaces.
  
  using namespace Cloddy::API::Imaging;
  using namespace CodeX;
  
  /*!
   * @brief  Base interface for classes that represent buffers for heightmap sample values.
   * 
   * Subclasses provide an array that stores the buffer samples.This array can be accessed as 
   * follows:
   * <pre>
   *     Samples[y * Stride + x] := value
   * </pre>
   * where \c x  and \c y  are the coordinates of the buffer sample.Alternatively,the #GetRowOffset 
   * and #GetSampleOffset methods can be used.
   */
  class NO_VTABLE ISampleBuffer : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The height of the buffer,in samples.
     * 
     * @return <b>[>0]</b>  The height of the buffer,in samples.
     */
    virtual int32 GetHeight() = 0;
    
    /*!
     * @brief  Index of top-left sample in the buffer.
     * 
     * @return <b>[>=0]</b>  The buffer offset.
     */
    virtual int32 GetOffset() = 0;
    
    /*!
     * @brief  Distance between two consecutive rows in the buffer.
     * 
     * @return <b>[>0]</b>  The buffer stride,in samples.
     */
    virtual int32 GetStride() = 0;
    
    /*!
     * @brief  The width of the buffer,in samples.
     * 
     * @return <b>[>0]</b>  The width of the buffer,in samples.
     */
    virtual int32 GetWidth() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Accepts the given ISampleBufferVisitor object.
     * 
     * @param visitor <b>[not-null]</b>  The ISampleBufferVisitor object.
     */
    virtual void Accept(ISampleBufferVisitor* visitor) = 0;
    
    /*!
     * @brief  Computes the buffer index for the given heightmap sample.
     * 
     * The returned buffer index may only be used to access the heightmap samples in the specified 
     * row (see \e y ).
     * 
     * @param y <b>[0..#GetHeight-1]</b>  Y-coordinate of the row.
     * 
     * @return <b>[>=0]</b>  Buffer index of the heightmap sample.
     */
    virtual int32 GetRowOffset(int32 y) = 0;
    
    /*!
     * @brief  Computes the buffer indes for the given heightmap sample.
     * 
     * @param x <b>[0..#GetWidth-1]</b>  X-coordinate of sample.
     * @param y <b>[0..#GetHeight-1]</b>  Y-coordinate of sample.
     * 
     * @return <b>[>=0]</b>  Buffer index of the heightmap sample.
     */
    virtual int32 GetSampleOffset(int32 x, int32 y) = 0;
    
    /*!
     * @brief  Reads the samples in this sample buffer as an image.
     * 
     * @param pixelFormat The pixel format of the image to read.
     * 
     * @return <b>[not-null]</b>  The IImageReader object.
     */
    virtual Ptr<IImageReader> ReadAsImage(PixelFormat pixelFormat) = 0;
    
    /*!
     * @brief  Replaces the values in this sample buffer with the pixels read from the given source 
     *         image.
     * 
     * Both IImageReader::GetWidth and IImageReader::GetHeight of \e image  must be equal to the 
     * width and height of this ISampleBuffer object.
     * 
     * @param image <b>[not-null]</b>  The source image.
     */
    virtual void ReadFromImage(IImageReader* image) = 0;
    
    /*!
     * @brief  Shifts the heightmap samples in this buffer by the given amount.
     * 
     * This method allows sample buffers to be used in a toroidal manner (ie. as a two-dimensional 
     * ringbuffer).
     * 
     * Specifying a positive value for \e x  will create space for new samples at the left buffer 
     * border,a negative value for \e x  will create space at the right border.
     * 
     * Specifying a positive value for \e y  will create space for new samples at the top buffer 
     * border,a negative value for \e y  will create space at the bottom border.
     * 
     * The contents of the heightmap samples in the additional space at the buffer border is 
     * unspecified and must be set by the application (eg. using #SubBuffer).
     * 
     * @param x Horizontal shift amount.
     * @param y Vertical shift amount.
     */
    virtual void Shift(int32 x, int32 y) = 0;
    
    /*!
     * @brief  Represents an ISampleBuffer object that represents a rectangular subregion of this 
     *         sample buffer.
     * 
     * Modifications made to this sample buffer will be visible to the returned buffer and vice 
     * versa.
     * 
     * @param x <b>[0..#GetWidth-width]</b>  X-coordinate of top-left sample of subregion.
     * @param y <b>[0..#GetHeight-height]</b>  Y-coordinate of top-left sample of subregion.
     * @param width <b>[1..#GetWidth]</b>  Width of subregion.
     * @param height <b>[1..#GetHeight]</b>  Height of subregion.
     * 
     * @return <b>[not-null]</b>  The subregion of this sample buffer.
     */
    virtual Ptr<ISampleBuffer> SubBuffer(int32 x, int32 y, int32 width, int32 height) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<ISampleBuffer> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x2FF25F12;
    
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
      return (void*) 0;
    }
  };
} } } } 

#endif
