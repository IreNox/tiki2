////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_DIRTYREGIONCUBE_H
#define CLODDY_API_HEIGHTMAPS_DIRTYREGIONCUBE_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/MeshFace.h"

// Include referenced structures.

#include "Cloddy/Box3I.h"

// Include referenced interfaces.

#include "Cloddy/IMeshVisitor.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Kernel { class IMesh; } }
namespace Cloddy { namespace Kernel { class IProvider; } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Heightmaps { class MeshDirtyRegionCallback; } } }
namespace Cloddy { namespace API { namespace VertexData { class Int3; } } }
namespace Cloddy { namespace Kernel { class CloddyKernel; } }
namespace Cloddy { namespace Kernel { class Traversal; } }

// Declare class ::Cloddy::API::Heightmaps::DirtyRegionCube.

namespace Cloddy { namespace API { namespace Heightmaps
{
  // Use referenced namespaces.
  
  using namespace Cloddy::Kernel;
  using namespace CodeX;
  
  // Use referenced structures.
  
  using Cloddy::API::Util::Box3I;
  
  // Use referenced classes.
  
  using Cloddy::API::VertexData::Int3;
  
  /*!
   * @brief  The DirtyRegionCube class can be used to mark a rectangular region of a cubemap 
   *         heightmap (see IMap::GetMapType)as dirty.
   * 
   * CLOD mesh vertices inside the dirty region will be recomputed in order to match recent 
   * modifications made to the heightmap samples.
   */
  class DirtyRegionCube : public virtual IMeshVisitor
  {
    // Declare friend classes.
    
    friend class MeshDirtyRegionCallback;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Vertex data container for heightmap coordinates.
     * 
     * @return <b>[not-null]</b>  The data container for heightmap coordinates.
     */
    Ptr<Int3> GetHeightmapCoords();
    
    /*!
     * @brief  Specifies the minimum sector size,in heightmap samples.
     * 
     * CLOD mesh sectors are marked as dirty if they lie completely inside the dirty region.If the 
     * intersect the dirty region and reach the given minimum sector size,they are marked as dirty 
     * as well.
     * 
     * @return <b>[>=0]</b>  The minimum sector size.
     */
    int32 GetMinSectorSize();
    
    /*!
     * @brief  Specifies the minimum sector size,in heightmap samples.
     * 
     * CLOD mesh sectors are marked as dirty if they lie completely inside the dirty region.If the 
     * intersect the dirty region and reach the given minimum sector size,they are marked as dirty 
     * as well.
     * 
     * @param value <b>[>=0]</b>  The minimum sector size.
     */
    void SetMinSectorSize(int32 value);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void BeginFace(MeshFace face);
    
    virtual void BeginMeshAction(IProvider* provider);
    
    virtual void EndFace();
    
    virtual void EndMeshAction();
    
    /*!
     * @brief  Marks the given heightmap region as dirty.
     * 
     * @param mesh <b>[not-null]</b>  The IMesh object.
     * @param x1 X-coordinate of top-left-front corner of dirty region box (inclusive).
     * @param y1 Y-coordinate of top-left-front corner of dirty region box (inclusive).
     * @param z1 Z-coordinate of top-left-front corner of dirty region box (inclusive).
     * @param x2 X-coordinate of bottom-right-back corner of dirty region box (inclusive).
     * @param y2 Y-coordinate of bottom-right-back corner of dirty region box (inclusive).
     * @param z2 Z-coordinate of bottom-right-back corner of dirty region box (inclusive).
     */
    void MarkAsDirty(IMesh* mesh, int32 x1, int32 y1, int32 z1, int32 x2, int32 y2, int32 z2);
    
    virtual void VisitSector(Traversal* traversal, int32 userData);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The bounding box that represents the current mesh sector.
     */
    Box3I current;
    
    /*!
     * @brief  The bounding box that represents the dirty region.
     */
    Box3I dirtyRegion;
    
    /*!
     * @brief  Internal buffer for sending dirty vertices via CloddyKernel::MarkAsDirty.
     */
    Array<int32> dirtyVertices;
    
    /*!
     * @brief  Number of valid entries in #dirtyVertices.
     */
    int32 dirtyVerticesCount;
    
    /*!
     * @brief  Vertex data container for heightmap coordinates.
     */
    Ptr<Int3> heightmapCoords;
    
    /*!
     * @brief  The CloddyKernel instance.
     */
    Ptr<CloddyKernel> kernel;
    
    /*!
     * @brief  The minimum sector size.
     */
    int32 minSectorSize;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of DirtyRegionRect.
     * 
     * @param heightmapCoords Vertex data container for heightmap coordinates.
     */
    DirtyRegionCube(Int3* heightmapCoords);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Adds the given vertex to the list of dirty vertices.
     * 
     * @param v The vertex to push.
     */
    void Push(int32 v);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<DirtyRegionCube> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xF5F775FB;
    
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
      if ((ptr = IMeshVisitor::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
