////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_KERNEL_IVERTEXFACTORY_H
#define CLODDY_KERNEL_IVERTEXFACTORY_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IMeshCallback.h"

// Forward declare referenced classes.

namespace Cloddy { namespace Kernel { class CommandBuffer; } }

// Declare interface ::Cloddy::Kernel::IVertexFactory.

namespace Cloddy { namespace Kernel
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  An IVertexFactory object provides vertex data during mesh refinement.
   * 
   * Vertex data is provided in two ways:full and update.Full vertex data contains all vertex 
   * attributes needed for rendering;update vertex data contains only those vertex attributes that 
   * are dependent on the vertex normal vector.Vertex data is computed once when a new vertex is 
   * added to a CLOD mesh;vertex data is updated for a vertex when the surrounding mesh structure 
   * has changed so that its normal vector is affected.
   * 
   * Each time a CLOD mesh is created via CloddyKernel::CreateMesh,the passed IProvider object must 
   * contain an IVertexFactory object (see ComponentIdsKernel::Req_VertexFactory).
   */
  class NO_VTABLE IVertexFactory : public virtual IMeshCallback
  {
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Begin a new vertex computation cycle.
     * 
     * The vertex factory can use the provided command buffer to determine how it will process the 
     * requested vertex computations.It may,for example,compute a sequence in which to compute the 
     * vertices that provides an optimal match to the layout of an underlying dataset.Another 
     * typical task is to transmit the set of requested vertices to a geodata server using a 
     * sliding window in order to reduce the overhead that is inherent to network communication.
     * 
     * All calls to #BeginCompute and #EndCompute for a Mesh_Terrain are made within calls 
     * to IMeshCallback::BeginMeshAction and IMeshCallback::EndMeshAction.
     * 
     * @param commandBuffer The input buffer for vertex computation.
     * 
     * @return \c true  if the #BeginCompute method can be called at least once more 
     * before #EndCompute is called,\c false  if not.
     */
    virtual bool BeginCompute(CommandBuffer* commandBuffer) = 0;
    
    /*!
     * @brief  Ends a pending vertex computation cycle (cycles are ended in the same order as they 
     *         have been begun,ie. FIFO).
     * 
     * @param commandBuffer The output buffer for vertex computation.
     */
    virtual void EndCompute(CommandBuffer* commandBuffer) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IVertexFactory> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xC713F7FA;
    
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
      if ((ptr = IMeshCallback::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
} } 

#endif
