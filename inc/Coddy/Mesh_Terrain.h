////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_KERNEL_MESH_TERRAIN_H
#define CLODDY_KERNEL_MESH_TERRAIN_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/MeshFace.h"

// Include referenced interfaces.

#include "Cloddy/IMeshTerrain.h"

// Include referenced classes.

#include "Cloddy/Mesh.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Kernel { class IMeshVisitor; } }
namespace Cloddy { namespace Kernel { class IProvider; } }
namespace Cloddy { namespace Kernel { class IVertexFactory; } }
namespace Cloddy { namespace Kernel { class IVisibilityCriterion; } }

// Forward declare referenced classes.

namespace Cloddy { namespace Kernel { class CloddyKernel; } }
namespace Cloddy { namespace Kernel { class Mesh_Sphere; } }
namespace Cloddy { namespace Kernel { class Mesh_Square; } }
namespace Cloddy { namespace Kernel { class Traversal_Terrain; } }

// Declare class ::Cloddy::Kernel::Mesh_Terrain.

namespace Cloddy { namespace Kernel
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Abstract base class for IMeshTerrain implementations.
   */
  class Mesh_Terrain : public Mesh, public virtual IMeshTerrain
  {
    // Declare friend classes.
    
    friend class Mesh_Sphere;
    friend class Mesh_Square;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual void TraverseSectors(MeshFace meshFace, IMeshVisitor* visitor, int32 userData);
    
    virtual void Triangulate(MeshFace meshFace);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
  protected:
    
    /*!
     * @brief  Translates the given vertex index value.
     * 
     * @param vertices The vertex index mapping table.
     * @param index Index in to \e vertices .
     * 
     * @return The translated vertex index value.
     */
    static int32 Translate(Array<int32> vertices, int32 index);
    
    virtual void DisposeManaged();
    
    /*!
     * @brief  Performs refinement on the given mesh diamond,visiting the LL and RL child vertices.
     * 
     * The diamond center vertex \e v  must be refineable.
     * 
     * The child vertices of \e v  that lie on the mesh border are depicted by \e borderState .
     * 
     * @param n The number of remaining refinement levels.
     * @param v Index of diamond center vertex.
     * @param l Index of left parent of \e v .
     * @param r Index of right parent of \e v .
     * @param g Index of grand parent of \e v .
     * @param a Index of ancestor of \e v .
     * @param borderState The current border state.
     */
    void RefineEvenBorder(int32 n, int32 v, int32 l, int32 r, int32 g, int32 a, int32 borderState);
    
    /*!
     * @brief  Performs refinement on the given mesh diamond,visiting the LL and LR child vertices.
     * 
     * The diamond center vertex \e v  must be refineable.
     * 
     * @param n The number of remaining refinement levels.
     * @param v Index of diamond center vertex.
     * @param l Index of left parent of \e v .
     * @param r Index of right parent of \e v .
     * @param g Index of grand parent of \e v .
     * @param a Index of ancestor of \e v .
     */
    void RefineOdd(int32 n, int32 v, int32 l, int32 r, int32 g, int32 a);
    
    /*!
     * @brief  Performs refinement,starting at the given root vertex.
     * 
     * @param v The root vertex.
     * @param l The left parent of \e v .
     * @param r The right parent of \e v .
     * @param g The grand parent of \e v .
     * @param a The ancestor of \e v .
     */
    virtual void RefineRootVertex(int32 v, int32 l, int32 r, int32 g, int32 a) = 0;
    
    virtual void RefineVertices();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Border state transition matrix used for refinement of square meshes.
     */
    static const Array<int32> BorderStateTransitions;
    
    /*!
     * @brief  Shortcut to CloddyKernel::linkAncestor.
     */
    Array<int32> a;
    
    /*!
     * @brief  The base vertices of the mesh.
     * 
     * The set of base vertices contains the center vertices of the mesh faces and all ancestors.
     */
    Array<int32> baseVertices;
    
    /*!
     * @brief  Shortcut to CloddyKernel::linkParent0.
     */
    Array<int32> l;
    
    /*!
     * @brief  Shortcut to CloddyKernel::linkChildRed.
     */
    Array<int32> ll;
    
    /*!
     * @brief  Shortcut to CloddyKernel::linkChildBlue.
     */
    Array<int32> lr;
    
    /*!
     * @brief  This array stores the mesh vertices which make up the six mesh faces.
     * 
     * The array is indexed as follows:
     * <pre>
     *       meshFaces[face * 5 + n] := Index of a vertex.
     *       where
     *       face := Index of the mesh face:
     *       0 => MeshFace.Front
     *       1 => MeshFace.Right
     *       2 => MeshFace.Back
     *       3 => MeshFace.Left
     *       4 => MeshFace.Top
     *       5 => MeshFace.Bottom
     *       n    := Index of face vertex:
     *       0 => Center vertex of sector
     *       1 => Left parent of center vertex of sector
     *       2 => Right parent of center vertex of sector
     *       3 => Grand parent of center vertex of sector
     *       4 => Ancestor of center vertex of sector 
     * </pre>
     */
    Array<int32> meshFaces;
    
    /*!
     * @brief  Shortcut to CloddyKernel::linkParent1.
     */
    Array<int32> r;
    
    /*!
     * @brief  Shortcut to CloddyKernel::linkChildYellow.
     */
    Array<int32> rl;
    
    /*!
     * @brief  The root vertices used for refinement.
     * 
     * Each root vertex meets the following criteria:
     *   - It is refineable.
     *   - It is always active.
     */
    Array<int32> rootVertices;
    
    /*!
     * @brief  Shortcut to CloddyKernel::linkChildGreen.
     */
    Array<int32> rr;
    
    /*!
     * @brief  The Traversal_Terrain is used for performing CLOD mesh traversal.
     */
    Ptr<Traversal_Terrain> traversal;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new CLOD mesh.
     * 
     * @param kernel The Cloddy Kernel instance.
     * @param refinementLevels The number of refinement levels.
     * @param provider The IProvider object of the mesh.
     * @param vertexFactory The vertex factory for this mesh.
     * @param visibilityCriterion The visibility criterion for this mesh.
     */
    Mesh_Terrain(CloddyKernel* kernel, int32 refinementLevels, IProvider* provider, IVertexFactory* vertexFactory, IVisibilityCriterion* visibilityCriterion);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Initializes the vertex references for a mesh face.
     * 
     * @param faceIdx The mesh face index (#meshFaces).
     * @param v Index of center vertex of mesh face sector.
     */
    void InitMeshFace(int32 faceIdx, int32 v);
    
    virtual void Recycle();
    
    /*!
     * @brief  Performs refinement on the given mesh diamond,visiting the LL and RL child vertices.
     * 
     * The diamond center vertex \e v  must be refineable.
     * 
     * No child vertex of \e v  lies on the mesh border.
     * 
     * @param n The number of remaining refinement levels.
     * @param v Index of diamond center vertex.
     * @param l Index of left parent of \e v .
     * @param r Index of right parent of \e v .
     * @param g Index of grand parent of \e v .
     * @param a Index of ancestor of \e v .
     */
    void RefineEven(int32 n, int32 v, int32 l, int32 r, int32 g, int32 a);
    
    /*!
     * @brief  Performs refinement on the given mesh diamond,visiting the LL and LR child vertices.
     * 
     * The diamond center vertex \e v  must be refineable.
     * 
     * @param n The number of remaining refinement levels.
     * @param v Index of diamond center vertex.
     * @param l Index of left parent of \e v .
     * @param r Index of right parent of \e v .
     * @param g Index of grand parent of \e v .
     * @param a Index of ancestor of \e v .
     * @param borderState The current border state.
     */
    void RefineOddBorder_S0_S3(int32 n, int32 v, int32 l, int32 r, int32 g, int32 a, int32 borderState);
    
    /*!
     * @brief  Performs refinement on the given mesh diamond,visiting the LL and LR child vertices.
     * 
     * The diamond center vertex \e v  must be refineable.
     * 
     * @param n The number of remaining refinement levels.
     * @param v Index of diamond center vertex.
     * @param l Index of left parent of \e v .
     * @param r Index of right parent of \e v .
     * @param g Index of grand parent of \e v .
     * @param a Index of ancestor of \e v .
     * @param borderState The current border state.
     */
    void RefineOddBorder_S2_S1(int32 n, int32 v, int32 l, int32 r, int32 g, int32 a, int32 borderState);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<Mesh_Terrain> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xAF4CBA48;
    
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
      if ((ptr = Mesh::TryCast(typeId)) != 0) return ptr;
      if ((ptr = IMeshTerrain::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } 

#endif
