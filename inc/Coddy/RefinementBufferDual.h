////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_KERNEL_REFINEMENTBUFFERDUAL_H
#define CLODDY_KERNEL_REFINEMENTBUFFERDUAL_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/InitialVertex.h"

// Include referenced interfaces.

#include "Cloddy/IRefinementBuffer.h"

// Include referenced classes.

#include "Cloddy/ThreadMainBase.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Threading { class IThreadContext; } } }
namespace Cloddy { namespace Kernel { class IVertexBufferCollection; } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace Threading { class Thread; } } }
namespace Cloddy { namespace Kernel { class BufferLock; } }
namespace Cloddy { namespace Kernel { class CloddyKernel; } }
namespace Cloddy { namespace Kernel { class CommandBuffer; } }
namespace Cloddy { namespace Kernel { class ComputationThreadMain; } }
namespace Cloddy { namespace Kernel { class Mesh; } }
namespace CodeX { namespace System { class Monitor; } }

// Declare class ::Cloddy::Kernel::RefinementBufferDual.

namespace Cloddy { namespace Kernel
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::Threading::IThreadContext;
  
  // Use referenced classes.
  
  using Cloddy::Core::Threading::Thread;
  using Cloddy::Core::Threading::ThreadMainBase;
  using CodeX::System::Monitor;
  
  /*!
   * @brief  This class is an implementation of the IRefinementBuffer for single-threaded mode (
   *         see Threadedness::Threadedness_Single.
   */
  class RefinementBufferDual : public ThreadMainBase, public virtual IRefinementBuffer
  {
    // Declare friend classes.
    
    friend class CloddyKernel;
    friend class ComputationThreadMain;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual void AddEven(int32 v, int32 l, int32 r);
    
    virtual void AddOdd(int32 v, int32 l, int32 r);
    
    virtual void BeginMesh(Mesh* mesh);
    
    virtual void Cancel();
    
    virtual void ComputeAgain(int32 v, int32 l, int32 r, int32 g, int32 a);
    
    virtual void ComputeNew(int32 v, int32 l, int32 r, int32 g, int32 a);
    
    virtual void ComputeNew(int32 v, InitialVertex initialVertex);
    
    virtual void Delete(int32 v);
    
    virtual void DeleteEven(int32 l, int32 r);
    
    virtual void DeleteOdd(int32 l, int32 r);
    
    virtual void EndMesh();
    
    virtual void MeshInitialized();
    
    virtual void Recompute(int32 v, int32 nl, int32 nr, int32 ng, int32 na);
    
    virtual void Run(IThreadContext* argument);
    
    virtual bool Update(void* userData);
    
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
     * @brief  The BufferLock object used for locking the vertex buffer.
     */
    Array<Ptr<BufferLock> > bufferLocks;
    
    /*!
     * @brief  Holds the command buffers.
     */
    Array<Ptr<CommandBuffer> > commandBuffers;
    
    Ptr<Thread> computationThread;
    
    /*!
     * @brief  Number of command buffers in state \e computed .
     */
    int32 computedCount;
    
    /*!
     * @brief  Index of first command buffer in state \e computed .
     */
    int32 computedIndex;
    
    /*!
     * @brief  Number of command buffers in state \e finished .
     */
    int32 finishedCount;
    
    /*!
     * @brief  Index of first command buffer in state \e finished .
     */
    int32 finishedIndex;
    
    /*!
     * @brief  Number of command buffers in the #commandBuffers array that are free and can be used 
     *         for buffering new refinement commands.
     */
    int32 freeCount;
    
    /*!
     * @brief  Index of the first free command buffer in the #commandBuffers array.
     * 
     * @see #freeCount
     */
    int32 freeIndex;
    
    /*!
     * @brief  The CLOD mesh that is currently being refined.
     */
    Ptr<Mesh> mesh;
    
    /*!
     * @brief  Monitor object used for command buffer synchronization.
     */
    Ptr<Monitor> monitor;
    
    /*!
     * @brief  The CommandBuffer object that is currently being filled by the refinement process.
     */
    Ptr<CommandBuffer> refineCommandBuffer;
    
    /*!
     * @brief  Counts the CommandBuffer objects in the #commandBuffers array that have been filled 
     *         with commands by the refinement process and are ready for being processed by the 
     *         vertex factory.
     */
    int32 refinedCount;
    
    /*!
     * @brief  Index of the first ready command buffer in the #commandBuffers array.
     */
    int32 refinedIndex;
    
    /*!
     * @brief  Number of compute commands that can still be added to #refineCommandBuffer.
     */
    int32 remainingComputeCommands;
    
    /*!
     * @brief  Number of mesh commands that can still be added to #refineCommandBuffer.
     */
    int32 remainingMeshCommands;
    
    /*!
     * @brief  The vertex buffer.
     */
    Ptr<IVertexBufferCollection> vertexBuffers;
    
    /*!
     * @brief  The vertex granularity,in vertices.
     */
    int32 vertexGranularity;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of RefinementBufferDual.
     * 
     * @param kernel The owning CloddyKernel instance.
     */
    RefinementBufferDual(CloddyKernel* kernel);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Finishes the command buffer that is currently being filled by the refinement process.
     * 
     * The calling thread must have a lock on #monitor.
     */
    void FlushRefineCommandBuffer();
    
    /*!
     * @brief  Enqueues the current refine command buffer for computation and fetches a new command 
     *         buffer.
     * 
     * @return \c true  if a new command buffer is ready,\c false  if not (this only happens during 
     * shutdown.
     */
    bool NextRefineCommandBuffer();
    
    /*!
     * @brief  Processes all vertex flag update commands.
     * 
     * The calling thread must have a lock on #monitor.
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
    public: typedef Ptr<RefinementBufferDual> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x3934E6FE;
    
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
      if ((ptr = ThreadMainBase::TryCast(typeId)) != 0) return ptr;
      if ((ptr = IRefinementBuffer::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } 

#endif
