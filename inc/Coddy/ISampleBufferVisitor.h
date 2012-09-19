////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_SAMPLEBUFFERS_ISAMPLEBUFFERVISITOR_H
#define CLODDY_API_HEIGHTMAPS_SAMPLEBUFFERS_ISAMPLEBUFFERVISITOR_H

#include "CodeX/System.h"

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleBuffers { class ColorBuffer; } } } }
namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleBuffers { class DetailBuffer; } } } }
namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleBuffers { class DisplacementBuffer; } } } }
namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleBuffers { class ElevationBuffer; } } } }
namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleBuffers { class SlopeBuffer; } } } }

// Declare interface ::Cloddy::API::Heightmaps::SampleBuffers::ISampleBufferVisitor.

namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleBuffers
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Visitor interface for concrete ISampleBuffer implementations.
   */
  class NO_VTABLE ISampleBufferVisitor : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Visits the given ISampleBuffer object.
     * 
     * @param buffer The ISampleBuffer object.
     */
    virtual void Visit(ColorBuffer* buffer) = 0;
    
    /*!
     * @brief  Visits the given ISampleBuffer object.
     * 
     * @param buffer The ISampleBuffer object.
     */
    virtual void Visit(DetailBuffer* buffer) = 0;
    
    /*!
     * @brief  Visits the given ISampleBuffer object.
     * 
     * @param buffer The ISampleBuffer object.
     */
    virtual void Visit(DisplacementBuffer* buffer) = 0;
    
    /*!
     * @brief  Visits the given ISampleBuffer object.
     * 
     * @param buffer The ISampleBuffer object.
     */
    virtual void Visit(ElevationBuffer* buffer) = 0;
    
    /*!
     * @brief  Visits the given ISampleBuffer object.
     * 
     * @param buffer The ISampleBuffer object.
     */
    virtual void Visit(SlopeBuffer* buffer) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<ISampleBufferVisitor> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x3E799414;
    
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
