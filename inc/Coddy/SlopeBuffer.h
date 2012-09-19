////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_SAMPLEBUFFERS_SLOPEBUFFER_H
#define CLODDY_API_HEIGHTMAPS_SAMPLEBUFFERS_SLOPEBUFFER_H

#include "CodeX/System.h"

// Include referenced structures.

#include "Cloddy/SlopeInfo.h"

// Include referenced classes.

#include "Cloddy/SampleBuffer.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleBuffers { class ISampleBuffer; } } } }
namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleBuffers { class ISampleBufferVisitor; } } } }
namespace Cloddy { namespace API { namespace Imaging { class IImageReader; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleBuffers { class ElevationBuffer; } } } }
namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::API::Heightmaps::SampleBuffers::SlopeBuffer.

namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleBuffers
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Imaging::IImageReader;
  
  // Use referenced classes.
  
  using CodeX::System::ByteBuffer;
  
  class SlopeBuffer : public SampleBuffer
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The slope buffer.
     * 
     * The slope buffer stores the terrain slope per sample,given as an angle in degrees in the 
     * range <c>[0..90]</c>.
     * 
     * @return <b>[not-null]</b>  The buffer samples.
     */
    Array<float32> GetSamples();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of SlopeBuffer.
     * 
     * @param width <b>[>0]</b>  The buffer width,in samples.
     * @param height <b>[>0]</b>  The buffer height,in samples.
     * @param slopeInfo The slope info value to use for terrain slope computation.
     */
    SlopeBuffer(int32 width, int32 height, const SlopeInfo& slopeInfo);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void Accept(ISampleBufferVisitor* visitor);
    
    /*!
     * @brief  Computes the slope buffer samples from the given elevation buffer.
     * 
     * @param buffer <b>[not-null]</b>  The elevation buffer.
     */
    void ComputeSlope(ElevationBuffer* buffer);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
  protected:
    
    virtual void CopySamples(int32 sourceOffset, int32 targetOffset, int32 count);
    
    virtual Ptr<IImageReader> DoReadAsImage();
    
    virtual void DoReadFromImage(int32 y, ByteBuffer* scanline);
    
    virtual Ptr<ISampleBuffer> DoSubBuffer(int32 offset, int32 stride, int32 width, int32 height);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The slope buffer.
     */
    Array<float32> samples;
    
    /*!
     * @brief  The SlopeInfo value used for slope computation.
     */
    SlopeInfo slopeInfo;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of SlopeBuffer.
     * 
     * @param slopeInfo TODO
     * @param samples TODO
     * @param width TODO
     * @param height TODO
     * @param offset TODO
     * @param stride TODO
     */
    SlopeBuffer(const SlopeInfo& slopeInfo, Array<float32> samples, int32 width, int32 height, int32 offset, int32 stride);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<SlopeBuffer> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x18A22678;
    
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
