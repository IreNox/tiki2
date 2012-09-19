////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_RENDERING_BUFFEREDMESH_H
#define CLODDY_API_RENDERING_BUFFEREDMESH_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/ITriangulationCallback.h"

// Include referenced classes.

#include "CodeX/Disposable.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Rendering { class IIndexBuffer; } } }
namespace Cloddy { namespace API { namespace Rendering { class IRenderer; } } }

// Declare class ::Cloddy::API::Rendering::BufferedMesh.

namespace Cloddy { namespace API { namespace Rendering
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Kernel::ITriangulationCallback;
  
  // Use referenced classes.
  
  using CodeX::System::Disposable;
  
  /*!
   * @brief  The BufferedMesh class can be used to improve performance in multi pass rendering 
   *         scenarios by buffering the result of the triangulation of CLOD meshes.
   * 
   * The usual process of rendering CLOD meshes is as follows:
   *   -# Create a CLOD mesh.
   *   -# Update vertex data (ie. fill the vertex buffer with data).
   *   -# Perform CLOD mesh triangulation (ie. fill the index buffer with data).This includes two 
   *   steps:First,CLOD mesh sectors are chosen (eg. via view frustum culling).Then,the chosen 
   *   sectors are triangulated (ie. converted into triangle strips).choosing
   *   -# Submit rendering commands to the GPU using the data stored in the vertex and index 
   *   buffers.
   * When rendering in a single pass,the steps <i>3.</i> and <i>4.</i> are typically merged into 
   * one,ie. rendering commands are issued while CLOD mesh triangulation is performed.When doing 
   * multi pass rendering,this is inadvisable because the workload for mesh triangulation is 
   * duplicated.
   * 
   * The BufferedMesh class consumes the results of CLOD mesh triangulation via 
   * the ITriangulationCallback interface.The buffered triangulation result can then be rendered as 
   * a whole by submitting only few render commands to the GPU.Since both vertex data and vertex 
   * indices reside in GPU memory,rendering is performed with high triangle throughput.
   */
  class BufferedMesh : public Disposable, public virtual ITriangulationCallback
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The GPU index buffer.
     * 
     * @return <b>[not-null]</b>  The index buffer.
     */
    Ptr<IIndexBuffer> GetIndexBuffer();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of BufferedMesh.
     * 
     * @param indexBuffer <b>[not-null]</b>  The index buffer to use for storing vertex indices.
     * @param triangleStripChunkSize <b>[>0]</b>  The triangle strip chunk size.
     */
    BufferedMesh(IIndexBuffer* indexBuffer, int32 triangleStripChunkSize);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void BeginTriangulation(void* userData);
    
    virtual void EndTriangulation();
    
    /*!
     * @brief  Renders the buffered mesh.
     * 
     * @param renderer <b>[not-null]</b>  The renderer to use.
     */
    void Render(IRenderer* renderer);
    
    virtual void TriangleStripChunk(Array<int32> indices, int32 count, int32 min, int32 max);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
  protected:
    
    virtual void DisposeManaged();
    
    virtual void DisposeManagedChildren();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Number of triangle strip chunks that can be stored in #indexBuffer.
     */
    int32 chunkCount;
    
    /*!
     * @brief  The length of each triangle strip chunk.
     */
    Array<int32> chunkLength;
    
    /*!
     * @brief  The maximum vertex index of each triangle strip chunk.
     */
    Array<int32> chunkMax;
    
    /*!
     * @brief  The minimum vertex index of each triangle strip chunk.
     */
    Array<int32> chunkMin;
    
    /*!
     * @brief  The GPU index buffer.
     */
    Ptr<IIndexBuffer> indexBuffer;
    
    /*!
     * @brief  The number of triangle strip chunks that can be rendered.
     */
    int32 renderChunkCount;
    
    /*!
     * @brief  Index of the chunk that will be rendered first.
     */
    int32 renderChunkIdx;
    
    /*!
     * @brief  The size of a triangle strip chunk,in vertex indices.
     */
    int32 triangleStripChunkSize;
    
    /*!
     * @brief  Counts the number of updated triangle strip chunks.
     */
    int32 updateChunkCount;
    
    /*!
     * @brief  Index of the chunk that will be update next.
     */
    int32 updateChunkIdx;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<BufferedMesh> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x8512A324;
    
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
      if ((ptr = Disposable::TryCast(typeId)) != 0) return ptr;
      if ((ptr = ITriangulationCallback::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
