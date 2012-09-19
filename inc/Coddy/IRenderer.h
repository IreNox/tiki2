////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_RENDERING_IRENDERER_H
#define CLODDY_API_RENDERING_IRENDERER_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/Primitive.h"

// Declare interface ::Cloddy::API::Rendering::IRenderer.

namespace Cloddy { namespace API { namespace Rendering
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  An IRenderer object submits rendering commands to the GPU.
   */
  class NO_VTABLE IRenderer : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Draws an indexed primitive.
     * 
     * The vertex indices of the primitive are stored in an IIndexBuffer object,the vertices are 
     * stored in an IVertexBuffer object.The application is responsible for setting the proper 
     * render states.
     * 
     * @param primitive The type of primitive to draw.
     * @param firstIndex <b>[>=0]</b>  First vertex index to draw.
     * @param indexCount <b>[>=0]</b>  The number of vertex indices to draw.
     * @param minimumIndex <b>[>=0]</b>  Minimum vertex index used by this draw call.
     * @param maximumIndex <b>[>=0]</b>  Maximum vertex index used by this draw call.
     */
    virtual void DrawIndexedPrimitive(Primitive primitive, int32 firstIndex, int32 indexCount, int32 minimumIndex, int32 maximumIndex) = 0;
    
    /*!
     * @brief  Draws a primitive.
     * 
     * The vertices are stored in an IVertexBuffer object.The application is responsible for 
     * setting the proper render states.
     * 
     * @param primitive The type of primitive to draw.
     * @param firstVertex <b>[>=0]</b>  First vertex to draw.
     * @param vertexCount <b>[>=0]</b>  The number of vertices to draw.
     */
    virtual void DrawPrimitive(Primitive primitive, int32 firstVertex, int32 vertexCount) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IRenderer> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x820B174A;
    
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
} } } 

#endif
