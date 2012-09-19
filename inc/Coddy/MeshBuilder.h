////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_RENDERING_MESHBUILDER_H
#define CLODDY_API_RENDERING_MESHBUILDER_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/ITriangulationCallback.h"

// Include referenced classes.

#include "CodeX/Disposable.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Rendering { class IIndexBuffer; } } }
namespace Cloddy { namespace API { namespace VertexFactories { namespace VertexFormats { class IVertexFormat; } } } }
namespace Cloddy { namespace Kernel { class IVertexBuffer; } }

// Forward declare referenced classes.

namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::API::Rendering::MeshBuilder.

namespace Cloddy { namespace API { namespace Rendering
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::VertexFactories::VertexFormats::IVertexFormat;
  using Cloddy::Kernel::ITriangulationCallback;
  using Cloddy::Kernel::IVertexBuffer;
  
  // Use referenced classes.
  
  using CodeX::System::ByteBuffer;
  using CodeX::System::Disposable;
  
  /*!
   * @brief  The MeshBuilder class can be used to export triangle mesh data from a CLOD mesh.
   * 
   * Exporting a triangle mesh from a CLOD mesh involves the following steps:
   *   -# Create a MeshBuilder object.
   *   -# Perform a triangulation of a CLOD mesh or a part of it using the MeshBuilder object as 
   *   the ITriangulationCallback.Be sure to use 
   *   the TriangleStitching::TriangleStitching_Concatenate stitching mode.
   *   -# Use the #GetVertexCount,#GetIndexCount and #GetTriangleCount properties for providing 
   *   application buffers for mesh vertices and indices.
   *   -# Use the <c>Write*()</c> methods to write the vertex and index data of the exported 
   *   triangle mesh to the application buffers.
   */
  class MeshBuilder : public Disposable, public virtual ITriangulationCallback
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Returns the number of vertex indices in the exported triangle mesh.
     * 
     * @return <b>[>=0]</b>  The number of vertex indices.
     * 
     * @see #WriteIndices(IIndexBuffer*,int32)
     * @see #WriteIndices(ByteBuffer*)
     */
    int32 GetIndexCount();
    
    /*!
     * @brief  Returns the number of triangles in the exported triangle mesh.
     * 
     * @return <b>[>=0]</b>  The number of triangles.
     * 
     * @see #WriteTriangles(IIndexBuffer*,int32)
     * @see #WriteTriangles(ByteBuffer*)
     */
    int32 GetTriangleCount();
    
    /*!
     * @brief  Returns the number of vertices in the exported triangle mesh.
     * 
     * @return <b>[>=0]</b>  The number of vertices.
     * 
     * @see #WriteVertices(IVertexFormat*,IVertexBuffer*,void*,int32)
     * @see #WriteVertices(IVertexFormat*,ByteBuffer*)
     */
    int32 GetVertexCount();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of MeshBuilder.
     * 
     * The MeshBuilder class uses internal buffers for storing exported triangle mesh data during 
     * triangulation.These buffers will be grown if necessary.Initial values for vertex and index 
     * count can be provided in order to reduce the number of reallocations during runtime.
     * 
     * @param kernelCapacity <b>[>0]</b>  Capacity of the CloddyKernel object that manages the 
     * source CLOD meshes.
     * @param initialVertexCount <b>[>0]</b>  Initial vertex count of exported triangle mesh.
     * @param initialIndexCount <b>[>0]</b>  Initial index count of exported triangle mesh.
     */
    MeshBuilder(int32 kernelCapacity, int32 initialVertexCount, int32 initialIndexCount);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void BeginTriangulation(void* userData);
    
    virtual void EndTriangulation();
    
    virtual void TriangleStripChunk(Array<int32> indices, int32 count, int32 min, int32 max);
    
    /*!
     * @brief  Writes the indices of the exported triangle mesh to the given buffer (as a triangle 
     *         strip).
     * 
     * @param buffer <b>[not-null]</b>  The index buffer.
     * @param offset <b>[>=0]</b>  Offset into index buffer where to start writing,in indices.
     * 
     * @see #GetIndexCount
     */
    void WriteIndices(IIndexBuffer* buffer, int32 offset);
    
    /*!
     * @brief  Writes the indices of the exported triangle mesh to the given buffer (as a triangle 
     *         strip).
     * 
     * @param buffer <b>[not-null]</b>  The index buffer.
     * 
     * @see #GetIndexCount
     */
    void WriteIndices(ByteBuffer* buffer);
    
    /*!
     * @brief  Writes the indices of the exported triangle mesh to the given buffer (as a triangle 
     *         list).
     * 
     * @param buffer <b>[not-null]</b>  The index buffer.
     * @param offset <b>[>=0]</b>  Offset into index buffer where to start writing,in indices.
     * 
     * @see #GetTriangleCount
     */
    void WriteTriangles(IIndexBuffer* buffer, int32 offset);
    
    /*!
     * @brief  Writes the indices of the exported triangle mesh to the given buffer (as a triangle 
     *         list).
     * 
     * @param buffer <b>[not-null]</b>  The index buffer.
     * 
     * @see #GetTriangleCount
     */
    void WriteTriangles(ByteBuffer* buffer);
    
    /*!
     * @brief  Writes the vertices of the exported triangle mesh to the given buffer.
     * 
     * @param vertexFormat <b>[not-null]</b>  The vertex layout to use.
     * @param buffer <b>[not-null]</b>  The vertex buffer.
     * @param bufferUserObject Optional user object to pass to IVertexBuffer::LockBuffer.
     * @param offset <b>[>=0]</b>  Offset into vertex buffer where to start writing,in vertices.
     * 
     * @return \c true  if the vertices have been written to the vertex buffer,\c false  if the 
     * vertex buffer cannot be locked (see BufferLock for details).
     */
    bool WriteVertices(IVertexFormat* vertexFormat, IVertexBuffer* buffer, void* bufferUserObject, int32 offset);
    
    /*!
     * @brief  Writes the vertices of the exported triangle mesh to the given buffer.
     * 
     * @param vertexFormat <b>[not-null]</b>  The vertex layout to use.
     * @param buffer <b>[not-null]</b>  The vertex buffer.
     * 
     * @return \c true  if the vertices have been written to the vertex buffer,\c false  if the 
     * vertex buffer cannot be locked (see BufferLock for details).
     */
    void WriteVertices(IVertexFormat* vertexFormat, ByteBuffer* buffer);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
  protected:
    
    virtual void DisposeManaged();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Mapping from CLOD mesh vertex indices to exported triangle mesh vertex indices.
     */
    Array<int32> clodToMesh;
    
    /*!
     * @brief  The number of vertex indices in the exported triangle mesh.
     */
    int32 indexCount;
    
    /*!
     * @brief  The vertex indices of the exported triangle mesh.
     */
    Array<int32> meshIndices;
    
    /*!
     * @brief  Mapping from exported triangle mesh vertex indices to CLOD mesh vertex indices.
     */
    Array<int32> meshToClod;
    
    /*!
     * @brief  The number of triangles in the exported triangle mesh.
     */
    int32 triangleCount;
    
    /*!
     * @brief  The number of vertices in the exported triangle mesh.
     */
    int32 vertexCount;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<MeshBuilder> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xA3192DA;
    
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
