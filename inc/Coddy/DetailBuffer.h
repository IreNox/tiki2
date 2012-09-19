////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_SAMPLEBUFFERS_DETAILBUFFER_H
#define CLODDY_API_HEIGHTMAPS_SAMPLEBUFFERS_DETAILBUFFER_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/SampleBuffer.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleBuffers { class ISampleBuffer; } } } }
namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleBuffers { class ISampleBufferVisitor; } } } }
namespace Cloddy { namespace API { namespace Imaging { class IImageReader; } } }

// Forward declare referenced classes.

namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::API::Heightmaps::SampleBuffers::DetailBuffer.

namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleBuffers
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Imaging::IImageReader;
  
  // Use referenced classes.
  
  using CodeX::System::ByteBuffer;
  
  class DetailBuffer : public SampleBuffer
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The current detail channel for filling this detail buffer with data.
     * 
     * The current channel has no effect when the detail buffer is used by a detail brush,in this 
     * case,all detail channels will be processed.
     * 
     * @return <b>[0..15]</b>  The current detail channel.
     * 
     * @see ISampleBuffer::ReadAsImage
     * @see ISampleBuffer::ReadFromImage
     * @see #FillSamples(int32)
     * @see #FillSamples(int32,int32,int32)
     */
    int32 GetCurrentChannel();
    
    /*!
     * @brief  The current detail channel for filling this detail buffer with data.
     * 
     * The current channel has no effect when the detail buffer is used by a detail brush,in this 
     * case,all detail channels will be processed.
     * 
     * @param value <b>[0..15]</b>  The current detail channel.
     * 
     * @see ISampleBuffer::ReadAsImage
     * @see ISampleBuffer::ReadFromImage
     * @see #FillSamples(int32)
     * @see #FillSamples(int32,int32,int32)
     */
    void SetCurrentChannel(int32 value);
    
    /*!
     * @brief  The samples of this detail buffer.
     * 
     * The detail buffer stores the detail channel values per sample in row-major order.
     * The returned array can be indexed as follows:
     * <pre>
     *     Samples[rowOffset + x * 4 + 0] := Detail channel values 0 to 3.
     *     Samples[rowOffset + x * 4 + 1] := Detail channel values 4 to 7.
     *     Samples[rowOffset + x * 4 + 2] := Detail channel values 8 to 11.
     *     Samples[rowOffset + x * 4 + 3] := Detail channel values 12 to 15.
     * </pre>
     * where \c rowOffset  is the row offset value returned by the SampleBuffer::GetRowOffset 
     * method and \c x  is the buffer X-coordinate of the sample to access.
     * 
     * @return <b>[not-null]</b>  The displacement values.
     */
    Array<int32> GetSamples();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of DetailBuffer.
     * 
     * @param width <b>[>0]</b>  Width of the detail buffer,in samples.
     * @param height <b>[>0]</b>  Height of the detail buffer,in samples.
     */
    DetailBuffer(int32 width, int32 height);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void Accept(ISampleBufferVisitor* visitor);
    
    /*!
     * @brief  Sets all values in the given detail channels to a uniform value.
     * 
     * @param firstChannel <b>[0..15]</b>  Index of first detail channel to set.
     * @param lastChannel <b>[0..15]</b>  Index of last detail channel to set.
     * @param value <b>[0..255]</b>  The uniform detail channel value.
     * 
     * @return <b>[not-null]</b>  this
     */
    Ptr<DetailBuffer> FillSamples(int32 firstChannel, int32 lastChannel, int32 value);
    
    /*!
     * @brief  Sets all values in the current detail channel to a uniform value.
     * 
     * @param value <b>[0..255]</b>  The uniform detail channel value.
     * 
     * @return <b>[not-null]</b>  this
     * 
     * @see #GetCurrentChannel
     */
    Ptr<DetailBuffer> FillSamples(int32 value);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
  protected:
    
    virtual void CopySamples(int32 sourceOffset, int32 targetOffset, int32 count);
    
    virtual Ptr<IImageReader> DoReadAsImage();
    
    virtual Ptr<IImageReader> DoReadFromImage(IImageReader* image);
    
    virtual void DoReadFromImage(int32 y, ByteBuffer* scanline);
    
    virtual Ptr<ISampleBuffer> DoSubBuffer(int32 offset, int32 stride, int32 width, int32 height);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The current detail channel.
     */
    int32 currentChannel;
    
    /*!
     * @brief  The samples of this detail buffer.
     */
    Array<int32> samples;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of DetailBuffer.
     * 
     * @param samples The detail channel values.
     * @param width Width of this sample buffer.
     * @param height Height of this sample buffer.
     * @param offset Offset of top-left sample of this sample buffer in buffer array.
     * @param stride The stride of this sample buffer.
     */
    DetailBuffer(Array<int32> samples, int32 width, int32 height, int32 offset, int32 stride);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<DetailBuffer> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x4CBB1C9C;
    
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
      if ((ptr = SampleBuffer::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } 

#endif
