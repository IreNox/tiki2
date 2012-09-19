////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_KERNEL_MESH_H
#define CLODDY_KERNEL_MESH_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/BaseGeometry.h"
#include "Cloddy/MeshFace.h"
#include "Cloddy/RefinementStatus.h"

// Include referenced interfaces.

#include "Cloddy/IMesh.h"

// Include referenced classes.

#include "CodeX/Disposable.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Kernel { class IMeshVisitor; } }
namespace Cloddy { namespace Kernel { class IProvider; } }
namespace Cloddy { namespace Kernel { class IRefinementBuffer; } }
namespace Cloddy { namespace Kernel { class IRefinementCallback; } }
namespace Cloddy { namespace Kernel { class IVertexFactory; } }
namespace Cloddy { namespace Kernel { class IVisibilityCriterion; } }

// Forward declare referenced classes.

namespace Cloddy { namespace Kernel { class CloddyKernel; } }
namespace Cloddy { namespace Kernel { class CommandBuffer; } }
namespace Cloddy { namespace Kernel { class ComputationThreadMain; } }
namespace Cloddy { namespace Kernel { class Mesh_Sphere; } }
namespace Cloddy { namespace Kernel { class Mesh_Square; } }
namespace Cloddy { namespace Kernel { class Mesh_Terrain; } }
namespace Cloddy { namespace Kernel { class Mesh_Volume; } }
namespace Cloddy { namespace Kernel { class MeshList; } }
namespace Cloddy { namespace Kernel { class RefinementBufferDual; } }
namespace Cloddy { namespace Kernel { class RefinementBufferSingle; } }
namespace Cloddy { namespace Kernel { class RefinementProgress; } }
namespace Cloddy { namespace Kernel { class RefinementProgressValues; } }
namespace Cloddy { namespace Kernel { class Traversal_Terrain; } }

// Declare class ::Cloddy::Kernel::Mesh.

namespace Cloddy { namespace Kernel
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced classes.
  
  using CodeX::System::Disposable;
  
  /*!
   * @brief  Abstract base class for IMesh implementations.
   */
  class Mesh : public Disposable, public virtual IMesh
  {
    // Declare friend classes.
    
    friend class CloddyKernel;
    friend class CommandBuffer;
    friend class ComputationThreadMain;
    friend class Mesh_Sphere;
    friend class Mesh_Square;
    friend class Mesh_Terrain;
    friend class Mesh_Volume;
    friend class MeshList;
    friend class RefinementBufferDual;
    friend class RefinementBufferSingle;
    friend class Traversal_Terrain;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual BaseGeometry GetBaseGeometry() = 0;
    
    virtual Ptr<CloddyKernel> GetKernel();
    
    virtual bool GetPauseOnFinished();
    
    virtual void SetPauseOnFinished(bool value);
    
    virtual int32 GetPendingVerticesCount();
    
    virtual int32 GetProgressInPercent();
    
    virtual Ptr<IProvider> GetProvider();
    
    virtual RefinementStatus GetStatus();
    
    virtual int32 GetTestedVerticesCount();
    
    virtual int32 GetToggledVerticesCount();
    
    virtual void* GetUserData();
    
    virtual void SetUserData(void* value);
    
    virtual Ptr<IVertexFactory> GetVertexFactory();
    
    virtual Ptr<IVisibilityCriterion> GetVisibilityCriterion();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void AddRefinementCallback(IRefinementCallback* callback);
    
    virtual void RemoveRefinementCallback(IRefinementCallback* callback);
    
    virtual void ResumeRefinement();
    
    virtual void TraverseSectors(MeshFace meshFace, IMeshVisitor* visitor, int32 userData) = 0;
    
    virtual void Triangulate(MeshFace meshFace) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Attributes
    // ---------------------------------------------------------------------------------------------
  protected:
    
    Ptr<IRefinementBuffer> refinementBuffer;
    
    /*!
     * @brief  The number of refinement levels this CLOD mesh has.
     * 
     * For a map of size <c>2^n+1</c>,the number of refinement levels is <c>n - 1</c>.
     */
    int32 refinementLevels;
    
    /*!
     * @brief  Counts the number of vertices that have been enqueued for computation.
     */
    int32 runningPendingVerticesCount;
    
    /*!
     * @brief  Counts the number of vertices visited during refinement.
     */
    int32 runningTestedVerticesCount;
    
    /*!
     * @brief  Counts the number of vertices activated/deactivated during refinement.
     */
    int32 runningToggledVerticesCount;
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void DisposeManaged();
    
    virtual void RefineVertices() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Number of concurrent locks on this CLOD mesh.
     */
    int32 concurrentLockCount;
    
    /*!
     * @brief  Shortcut to CloddyKernel::f.
     */
    Array<int16> f;
    
    /*!
     * @brief  Has refinement for this CLOD mesh been finished?
     */
    bool isFinished;
    
    /*!
     * @brief  Has refinement for this CLOD mesh been paused?
     */
    bool isPaused;
    
    /*!
     * @brief  Is this mesh ready for traversal /triangulation?
     */
    bool isReady;
    
    /*!
     * @brief  The Cloddy Kernel instance.
     */
    Ptr<CloddyKernel> kernel;
    
    /*!
     * @brief  Does this CLOD mesh need to be initialized?
     */
    bool needInitialize;
    
    /*!
     * @brief  Does this CLOD mesh need to be recycled?
     */
    bool needRecycle;
    
    /*!
     * @brief  Points to the next CLOD mesh in its linked list.
     */
    Ptr<Mesh> next;
    
    /*!
     * @brief  The IProvider that provides mesh specific components.
     */
    Ptr<IProvider> provider;
    
    /*!
     * @brief  The aggregated RefinementProgress object 
     */
    Ptr<RefinementProgress> refinementProgress;
    
    /*!
     * @brief  The progress values of the most recent refinement cycle.
     */
    Ptr<RefinementProgressValues> refinementProgressValues;
    
    /*!
     * @brief  Have the values in #refinementProgressValues been updated by background refinement 
     *         since the last call to #UpdateRefinementProgress?
     */
    bool refinementProgressValuesUpdated;
    
    /*!
     * @brief  Shall refinement be paused when finished?
     */
    bool shallPause;
    
    /*!
     * @brief  The current user data object.
     */
    void* userData;
    
    /*!
     * @brief  The vertex factory.
     */
    Ptr<IVertexFactory> vertexFactory;
    
    /*!
     * @brief  The visibility criterion used for refinement.
     */
    Ptr<IVisibilityCriterion> visibilityCriterion;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of Mesh.
     * 
     * @param kernel The Cloddy Kernel instance.
     * @param refinementLevels The number of refinement levels.
     * @param provider The IProvider object of the mesh.
     * @param vertexFactory The vertex factory for this mesh.
     * @param visibilityCriterion The visibility criterion for this mesh.
     */
    Mesh(CloddyKernel* kernel, int32 refinementLevels, IProvider* provider, IVertexFactory* vertexFactory, IVisibilityCriterion* visibilityCriterion);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    bool BeginRefine();
    
    /*!
     * @brief  Places a concurrent lock on this CLOD mesh.
     * 
     * Concurrent locks are used to track the lifetime of CLOD meshes.Locks are held during the 
     * following occasions:
     *   - The mesh is enqueued in on of the kernels internal list.
     *   - The mesh is used as the target of a CommandBuffer.
     */
    void ConcurrentLock();
    
    /*!
     * @brief  Removes a concurrent lock from this CLOD mesh.
     * 
     * @see #ConcurrentLock
     */
    void ConcurrentUnlock();
    
    void FinishRefine();
    
    /*!
     * @brief  Is this CLOD mesh locked?
     * 
     * @return <c>true if this CLOD mesh is locked,\c false  if not.</c>
     */
    bool HasConcurrentLock();
    
    /*!
     * @brief  Initializes the CLOD mesh.
     * 
     * @param refinementBuffer The refinement buffer to use.
     */
    virtual void Initialize(IRefinementBuffer* refinementBuffer) = 0;
    
    /*!
     * @brief  Recycles this mesh.
     */
    virtual void Recycle() = 0;
    
    /*!
     * @brief  Performs mesh refinement.
     * 
     * @param refinementBuffer The refinement buffer to use.
     */
    void Refine(IRefinementBuffer* refinementBuffer);
    
    /*!
     * @brief  Unpauses background refinement.
     */
    void Unpause();
    
    /*!
     * @brief  Updates the refinement progress values as returned via the 
     *         implemented IRefinementProgress interface.
     */
    void UpdateRefinementProgress();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<Mesh> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xAC630FA;
    
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
      if ((ptr = IMesh::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } 

#endif
