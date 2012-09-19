////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_GAL_IGRAPHICSCONTEXT_H
#define CLODDY_GAL_IGRAPHICSCONTEXT_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/BufferUsage.h"

// Include referenced interfaces.

#include "CodeX/IDisposable.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Rendering { class IIndexBuffer; } } }
namespace Cloddy { namespace Kernel { class ITriangulationCallback; } }
namespace Cloddy { namespace Kernel { class IVertexBuffer; } }

// Declare interface ::Cloddy::GAL::IGraphicsContext.

namespace Cloddy { namespace GAL
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Rendering::IIndexBuffer;
  using Cloddy::Kernel::ITriangulationCallback;
  using Cloddy::Kernel::IVertexBuffer;
  using CodeX::System::IDisposable;
  
  /*!
   * @brief  Base interface for classes that provide a graphics context for the CloddyPlugin.
   */
  class NO_VTABLE IGraphicsContext : public virtual IDisposable
  {
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Creates an IIndexBuffer object.
     * 
     * @param capacity <b>[>0]</b>  The capacity of the index buffer,in vertex indices.
     * @param usage The index buffer usage.
     * 
     * @return <b>[not-null]</b>  The IIndexBuffer object.
     */
    virtual Ptr<IIndexBuffer> CreateIndexBuffer(int32 capacity, BufferUsage usage) = 0;
    
    /*!
     * @brief  Creates an ITriangulationCallback object that can be used to render geometry.
     * 
     * @param triangleStripChunkSize <b>[>0]</b>  The triangle strip chunk length.
     * 
     * @return <b>[not-null]</b>  The ITriangulationCallback object.
     */
    virtual Ptr<ITriangulationCallback> CreateTriangulationCallback(int32 triangleStripChunkSize) = 0;
    
    /*!
     * @brief  Creates an IVertexBuffer object.
     * 
     * @param capacity <b>[>0]</b>  The capacity of the vertex buffer,in vertices.
     * @param vertexSize <b>[>0]</b>  The vertex size,in bytes.
     * @param usage The vertex buffer usage.
     * 
     * @return <b>[not-null]</b>  The IVertexBuffer object.
     */
    virtual Ptr<IVertexBuffer> CreateVertexBuffer(int32 capacity, int32 vertexSize, BufferUsage usage) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IGraphicsContext> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xC412A96B;
    
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
      if ((ptr = IDisposable::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
} } 

#endif
