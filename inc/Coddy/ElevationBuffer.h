////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_SAMPLEBUFFERS_ELEVATIONBUFFER_H
#define CLODDY_API_HEIGHTMAPS_SAMPLEBUFFERS_ELEVATIONBUFFER_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/SampleBuffer.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleBuffers { class ISampleBuffer; } } } }
namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleBuffers { class ISampleBufferVisitor; } } } }
namespace Cloddy { namespace API { namespace Imaging { class IImageReader; } } }

// Forward declare referenced classes.

namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::API::Heightmaps::SampleBuffers::ElevationBuffer.

namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleBuffers
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Imaging::IImageReader;
  
  // Use referenced classes.
  
  using CodeX::System::ByteBuffer;
  
  /*!
   * @brief  An implementation of the ISampleBuffer interface that stores elevation values.
   */
  class ElevationBuffer : public SampleBuffer
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The elevation values.
     * 
     * The elevation buffer stores the elevation values per sample in row-major order.
     * The returned array can be indexed as follows:
     * <pre>
     *     Samples[rowOffset + x] := normalized elevation value.
     * </pre>
     * where \c rowOffset  is the row offset value returned by the SampleBuffer::GetRowOffset 
     * method and \c x  is the buffer X-coordinate of the sample to access.
     * 
     * @return <b>[not-null]</b>  The elevation values.
     */
    Array<int32> GetSamples();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of ElevationBuffer.
     * 
     * @param width <b>[>0]</b>  Width of the elevation buffer.
     * @param height <b>[>0]</b>  Height of the elevation buffer.
     */
    ElevationBuffer(int32 width, int32 height);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of ColorBuffer.
     * 
     * @param imageReader <b>[not-null]</b>  The source image.
     * 
     * @return <b>[not-null]</b>  The created ColorBuffer.
     */
    static Ptr<ElevationBuffer> FromImage(IImageReader* imageReader);
    
    virtual void Accept(ISampleBufferVisitor* visitor);
    
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
     * @brief  The elevation values.
     */
    Array<int32> samples;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of ElevationBuffer.
     * 
     * @param samples The elevation values.
     * @param offset Offset of top-left sample of this sample buffer in buffer array.
     * @param stride The stride of this sample buffer.
     * @param width Width of this sample buffer.
     * @param height Height of this sample buffer.
     */
    ElevationBuffer(Array<int32> samples, int32 offset, int32 stride, int32 width, int32 height);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<ElevationBuffer> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xB98BFE38;
    
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
