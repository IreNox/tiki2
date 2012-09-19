////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_KERNEL_COMMANDBUFFER_H
#define CLODDY_KERNEL_COMMANDBUFFER_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/InitialVertex.h"

// Include referenced interfaces.

#include "Cloddy/ICapacity.h"

// Include referenced classes.

#include "CodeX/Disposable.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Kernel { class IVertexHierarchyCallback; } }

// Forward declare referenced classes.

namespace Cloddy { namespace Kernel { class CloddyKernel; } }
namespace Cloddy { namespace Kernel { class ComputationThreadMain; } }
namespace Cloddy { namespace Kernel { class Mesh; } }
namespace Cloddy { namespace Kernel { class RefinementBufferDual; } }
namespace Cloddy { namespace Kernel { class RefinementBufferSingle; } }
namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::Kernel::CommandBuffer.

namespace Cloddy { namespace Kernel
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced classes.
  
  using CodeX::System::ByteBuffer;
  using CodeX::System::Disposable;
  
  /*!
   * @brief  Container for input data about vertices that need to be computed.
   * 
   * @see IVertexFactory
   */
  class CommandBuffer : public Disposable, public virtual ICapacity
  {
    // Declare friend classes.
    
    friend class ComputationThreadMain;
    friend class RefinementBufferDual;
    friend class RefinementBufferSingle;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constants
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The current vertex is an existing one that needs to be computed again in order to 
     *         correctly reflect changes in the heightmap.
     * 
     * @see #V
     * @see #L
     * @see #R
     * @see #G
     * @see #A
     */
    static const int32 ComputeAgain = 3;
    
    /*!
     * @brief  The current vertex is a regular one that has been added to the mesh.
     * 
     * @see #V
     * @see #L
     * @see #R
     * @see #G
     * @see #A
     */
    static const int32 ComputeNew = 1;
    
    /*!
     * @brief  The current vertex is an initial mesh vertex.
     * 
     * @see #V
     * @see #IV
     */
    static const int32 ComputeNewInitial = 0;
    
    /*!
     * @brief  There are no more vertices to compute.
     */
    static const int32 None = 4;
    
    /*!
     * @brief  The current vertex is an existing one that needs to be updated in order to correctly 
     *         reflect changes in the mesh structure (eg. normal/tangent vectors).
     * 
     * @see #V
     * @see #L
     * @see #R
     * @see #G
     * @see #A
     */
    static const int32 Recompute = 2;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Ancestor of #V.
     * 
     * @see #ComputeHeightmapCoordinatesRegular
     * @see #ComputeVertexData
     */
    int32 A;
    
    virtual int32 GetCapacity();
    
    /*!
     * @brief  Need to compute vertex data that is dependent on the adjacency of the current 
     *         vertex (ie. the neighbouring mesh vertices,#L,#R,#G and #A)?
     * 
     * Usually,vertex normal and tangent vectors are dependent on the mesh structure neighbourhood 
     * of the vertex.Each time a vertex is added to a CLOD mesh,the surrounding vertices need to be 
     * updated in order to reflect the changed surface structure.
     * 
     * The following fields contain information about the current vertex when #ComputeAdjacencyData 
     * is set to \c true :
     *   - #V
     *   - #L
     *   - #R
     *   - #G
     *   - #A
     */
    bool ComputeAdjacencyData;
    
    /*!
     * @brief  Need to compute heightmap coordinates for an initial vertex (ie. not a regular one)?
     * 
     * Heightmap coordinates for initial vertices must be deferred from the type of the initial 
     * vertex (#IV).
     * 
     * The following fields contain information about the current vertex 
     * when #ComputeHeightmapCoordinatesInitial is set to \c true :
     *   - #V
     *   - #IV
     */
    bool ComputeHeightmapCoordinatesInitial;
    
    /*!
     * @brief  Need to compute heightmap coordinates and refineability state for a regular vertex (
     *         ie. not an initial one)?
     * 
     * Vertices that have been added to the mesh do not have heightmap coordinates yet.These must 
     * be deferred from the vertex diamond (#L,#R,#G and #A).
     * 
     * The following fields contain information about the current vertex 
     * when #ComputeHeightmapCoordinatesRegular is set to \c true :
     *   - #V
     *   - #L
     *   - #R
     *   - #G
     *   - #A
     */
    bool ComputeHeightmapCoordinatesRegular;
    
    /*!
     * @brief  Need to access the heightmap and compute vertex data from the read heightmap sample?
     * 
     * This field is set to \c true  for vertices that have added to the mesh and for dirty 
     * vertices that need to be updated because the heightmap has been modified.
     * 
     * The following fields contain information about the current vertex when #ComputeVertexData is 
     * set to \c true :
     *   - #V
     *   - #L
     *   - #R
     *   - #G
     *   - #A
     */
    bool ComputeVertexData;
    
    /*!
     * @brief  Grand parent of #V.
     * 
     * @see #ComputeHeightmapCoordinatesRegular
     * @see #ComputeVertexData
     */
    int32 G;
    
    /*!
     * @brief  The kind of initial vertex to compute.
     * 
     * @see #ComputeHeightmapCoordinatesInitial
     */
    InitialVertex IV;
    
    /*!
     * @brief  Left parent of #V.
     * 
     * @see #ComputeHeightmapCoordinatesRegular
     * @see #ComputeVertexData
     */
    int32 L;
    
    /*!
     * @brief  Right parent of #V.
     * 
     * @see #ComputeHeightmapCoordinatesRegular
     * @see #ComputeVertexData
     */
    int32 R;
    
    /*!
     * @brief  The vertex to compute.
     * 
     * @see #ComputeHeightmapCoordinatesInitial
     * @see #ComputeHeightmapCoordinatesRegular
     * @see #ComputeVertexData
     * @see #ComputeAdjacencyData
     */
    int32 V;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Returns the next compute vertex command.
     * 
     * @return \c true  if there is at least one compute vertex command to process,\c false  if all 
     * commands have been processed.
     */
    bool Next();
    
    /*!
     * @brief  Resets this vertex factory input container by placing the vertex cursor before the 
     *         first vertex to compute.
     * 
     * @return <b>[not-null]</b>  this
     */
    Ptr<CommandBuffer> Reset();
    
    /*!
     * @brief  Performs an upward traversal in the vertex hierarchy,starting at #V.
     * 
     * @param callback <b>[not-null]</b>  The traversal callback.
     */
    void TraverseHierarchy(IVertexHierarchyCallback* callback);
    
    /*!
     * @brief  Returns the buffer for writing vertex data.
     * 
     * @param vertexSize <b>[>0]</b>  The size of a single vertex,in bytes.
     * 
     * @return <b>[not-null]</b>  The byte buffer.
     */
    Ptr<ByteBuffer> VertexData(int32 vertexSize);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
  protected:
    
    virtual void DisposeManaged();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constants
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Number of 32-bit integers used to buffer a single command.
     */
    static const int32 IntsPerCommand = 8;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Counts the number of computed vertices (ie. the number of necessary vertex updates).
     * 
     * @return <b>[>=0]</b>  The number of computed vertices.
     */
    int32 GetComputeCount();
    
    /*!
     * @brief  Maximum vertex index of all compute commands.
     * 
     * @return The maximum vertex index.
     */
    int32 GetMaxComputeVertexIndex();
    
    /*!
     * @brief  The current CLOD mesh.
     * 
     * @return The current CLOD mesh.
     */
    Ptr<Mesh> GetMesh();
    
    /*!
     * @brief  Minimum vertex index of all compute commands.
     * 
     * @return The minimum vertex index.
     */
    int32 GetMinComputeVertexIndex();
    
    /*!
     * @brief  Mesh structure array.
     */
    Array<int32> c;
    
    /*!
     * @brief  The capacity of this command buffer.
     */
    int32 capacity;
    
    /*!
     * @brief  The CloddyKernel object.
     */
    Ptr<CloddyKernel> cloddyKernel;
    
    /*!
     * @brief  The buffer for the vertex computations to perform.
     */
    Array<int32> computeCommands;
    
    /*!
     * @brief  Current read index into #computeCommands.
     */
    int32 computeCommandsReadIndex;
    
    /*!
     * @brief  Current write index into #computeCommands.
     */
    int32 computeCommandsWriteIndex;
    
    /*!
     * @brief  Counts the number of computed vertices (ie. the number of necessary vertex updates).
     */
    int32 computeCount;
    
    /*!
     * @brief  Vertex flags.
     */
    Array<int16> f;
    
    /*!
     * @brief  Left parent vertex indices.
     */
    Array<int32> l;
    
    /*!
     * @brief  Left anchor left branch child vertex indices.
     */
    Array<int32> ll;
    
    /*!
     * @brief  Left anchor right branch child vertex indices.
     */
    Array<int32> lr;
    
    /*!
     * @brief  Maximum vertex index of all compute commands.
     */
    int32 maxComputeVertexIndex;
    
    /*!
     * @brief  The current CLOD mesh.
     */
    Ptr<Mesh> mesh;
    
    /*!
     * @brief  Buffer for mesh update commands:Add Even,Add Odd,Delete Even,Delete Odd.
     */
    Array<int32> meshCommands;
    
    /*!
     * @brief  Current write index into #meshCommands.
     */
    int32 meshCommandsWriteIndex;
    
    /*!
     * @brief  Has this command buffers CLOD mesh been marked as initialized?
     */
    bool meshInitialized;
    
    /*!
     * @brief  Does this command buffer hold a concurrent lock on #mesh?
     */
    bool meshLocked;
    
    /*!
     * @brief  Minimum vertex index of all compute commands.
     */
    int32 minComputeVertexIndex;
    
    /*!
     * @brief  Right parent vertex indices.
     */
    Array<int32> r;
    
    /*!
     * @brief  The byte buffer that holds the output vertex data.
     */
    Ptr<ByteBuffer> vertexData;
    
    /*!
     * @brief  The vertex size,in bytes.
     */
    int32 vertexSize;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of CommandBuffer.
     * 
     * @param kernel The owning CloddyKernel object.
     */
    CommandBuffer(CloddyKernel* kernel);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Recursively deletes all child references,starting at the given root vertex.
     * 
     * @param vm The root vertex index,premultiplied with 4.
     */
    void Delete(int32 vm);
    
    /*!
     * @brief  Enqueues the following mesh structure update:add vertex (even,ie. LL-RR).
     * 
     * @param v The vertex to add.
     * @param l The left parent of \e v .
     * @param r The right parent of \e v .
     */
    void EnqueueAddEven(int32 v, int32 l, int32 r);
    
    /*!
     * @brief  Enqueues the following mesh structure update:add vertex (odd,ie. LR-RL).
     * 
     * @param v The vertex to add.
     * @param l The left parent of \e v .
     * @param r The right parent of \e v .
     */
    void EnqueueAddOdd(int32 v, int32 l, int32 r);
    
    /*!
     * @brief  Enqueues the computation of an existing mesh vertex.
     * 
     * @param v The vertex to compute.
     * @param l The left parent of \e v .
     * @param r The right parent of \e v .
     * @param g The grand parent of \e v .
     * @param a The ancestor of \e v .
     */
    void EnqueueComputeAgain(int32 v, int32 l, int32 r, int32 g, int32 a);
    
    /*!
     * @brief  Enqueues the computation of an initial mesh vertex.
     * 
     * @param v The vertex to compute.
     * @param initialVertex The kind of the initial vertex.
     */
    void EnqueueComputeInitial(int32 v, InitialVertex initialVertex);
    
    /*!
     * @brief  Enqueues the computation of a new mesh vertex.
     * 
     * @param v The vertex to compute.
     * @param l The left parent of \e v .
     * @param r The right parent of \e v .
     * @param g The grand parent of \e v .
     * @param a The ancestor of \e v .
     */
    void EnqueueComputeRegular(int32 v, int32 l, int32 r, int32 g, int32 a);
    
    /*!
     * @brief  Enqueues the following mesh structure update:delete vertex (recursive).
     * 
     * @param v The root vertex.
     */
    void EnqueueDelete(int32 v);
    
    /*!
     * @brief  Enqueues the following mesh structure update:delete vertex (even,ie. LL-RR).
     * 
     * @param l Left parent of the deleted vertex.
     * @param r Right parent of the deleted vertex.
     */
    void EnqueueDeleteEven(int32 l, int32 r);
    
    /*!
     * @brief  Enqueues the following mesh structure update:delete vertex (odd,ie. LR-RL).
     * 
     * @param l Left parent of the deleted vertex.
     * @param r Right parent of the deleted vertex.
     */
    void EnqueueDeleteOdd(int32 l, int32 r);
    
    /*!
     * @brief  Enqueues the recomputation of an existing vertex.
     * 
     * @param v The vertex to recompute.
     * @param nl The nearest vertex in direction of the left parent of \e v .
     * @param nr The nearest vertex in direction of the right parent of \e v .
     * @param ng The nearest vertex in direction of the grand parent of \e v .
     * @param na The nearest vertex in direction of the ancestor of \e v .
     */
    void EnqueueRecompute(int32 v, int32 nl, int32 nr, int32 ng, int32 na);
    
    /*!
     * @brief  Initializes this command buffer for the given CLOD mesh.
     * 
     * @param mesh The CLOD mesh.
     */
    void Initialize(Mesh* mesh);
    
    /*!
     * @brief  Marks the CLOD mesh of this command buffer as initialized.
     */
    void MeshInitialized();
    
    /*!
     * @brief  Updates the mesh structure.
     */
    void UpdateMeshStructure();
    
    /*!
     * @brief  Updates the given vertex buffer.
     * 
     * @param vertexBuffer The locked vertex buffer region.
     * @param vertexBufferPosition Position of first byte of first locked vertex.
     * @param min Index of first locked vertex.
     * @param vertexSize The vertex size,in bytes.
     */
    void UpdateVertexBuffer(ByteBuffer* vertexBuffer, int64 vertexBufferPosition, int32 min, int32 vertexSize);
    
    /*!
     * @brief  Processes pending vertex flags updates.
     */
    void UpdateVertexFlags();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<CommandBuffer> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x85453F8E;
    
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
      if ((ptr = ICapacity::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } 

#endif
