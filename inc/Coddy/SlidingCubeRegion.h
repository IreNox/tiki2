////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_UTIL_SPATIAL_SLIDINGCUBEREGION_H
#define CLODDY_API_UTIL_SPATIAL_SLIDINGCUBEREGION_H

#include "CodeX/System.h"

// Include referenced structures.

#include "Cloddy/Vec3D.h"

// Include referenced classes.

#include "Cloddy/TerrainSpaceRegion.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Util { namespace Spatial { class ITerrainSpaceRegionVisitor; } } } }

// Declare class ::Cloddy::API::Util::Spatial::SlidingCubeRegion.

namespace Cloddy { namespace API { namespace Util { namespace Spatial
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced structures.
  
  using Cloddy::Core::Math::Vectors::Vec3D;
  
  /*!
   * @brief  The SlidingCubeRegion class divides terrain-space into 3D grid of equally sized cubes;
   *         only the cubes that surround the region origin are contained in the terrain space 
   *         region.
   * 
   * The following figures illustrates how terrain-space is divided into a cube grid and which 
   * cubes belong to the terrain space region:
   * <pre>
   *     +---+---+---+---+---+
   *     | 2 | 2 | 2 | 2 | 2 |
   *     +---+---+---+---+---+
   *     | 2 | 1 | 1 | 1 | 2 |
   *     +---+---+---+---+---+
   *     | 2 | 1 | O | 1 | 2 |
   *     +---+---+---+---+---+
   *     | 2 | 1 | 1 | 1 | 2 |
   *     +---+---+---+---+---+
   *     | 2 | 2 | 2 | 2 | 2 |
   *     +---+---+---+---+---+
   *     O := terrain space origin
   *     1 := direct neighbours
   *     2 := indirect neighbours
   * </pre>
   * The grid cube that contains the current region origin and all direct neighbours always belong 
   * to the terrain space region.When the region origin is moved,cube are added to resp. removed 
   * from the region according to the following rules:
   *   - A grid cube is \b added  if it has become a new direct neighbour.
   *   - A grid cube is \b removed  if it is no longer an indirect neighbour.
   * These rules are used in order to avoid that grid cubes are added and removed repeatedly when 
   * the region origin is moving back and forth over the same grid cell border.
   */
  class SlidingCubeRegion : public TerrainSpaceRegion
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual Vec3D GetOrigin();
    
    virtual void SetOrigin(const Vec3D& value);
    
    /*!
     * @brief  The size of the sliding cube.
     * 
     * @return <b>[>0]</b>  The cube size.
     */
    float32 GetSize();
    
    /*!
     * @brief  The size of the sliding cube.
     * 
     * @param value <b>[>0]</b>  The cube size.
     */
    void SetSize(float32 value);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of SlidingCubeRegion.
     */
    SlidingCubeRegion();
    
    /*!
     * @brief  Creates a new instance of SlidingCubeRegion.
     * 
     * @param size <b>[>0]</b>  The size of the sliding cube.
     */
    SlidingCubeRegion(float32 size);
    
    /*!
     * @brief  Creates a new instance of SlidingCubeRegion.
     * 
     * @param originX X-coordinate of origin,in terrain-space.
     * @param originY Y-coordinate of origin,in terrain-space.
     * @param originZ Z-coordinate of origin,in terrain-space.
     * @param size <b>[>0]</b>  The size of the sliding cube.
     */
    SlidingCubeRegion(float32 originX, float32 originY, float32 originZ, float32 size);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void Accept(ITerrainSpaceRegionVisitor* visitor, Object* userData);
    
    virtual bool IntersectsSphere(float64 x, float64 y, float64 z, float64 r);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Cell grid X-coordinate of grid cell that contains the region origin.
     */
    int32 centerX;
    
    /*!
     * @brief  Cell grid Y-coordinate of grid cell that contains the region origin.
     */
    int32 centerY;
    
    /*!
     * @brief  Cell grid Z-coordinate of grid cell that contains the region origin.
     */
    int32 centerZ;
    
    /*!
     * @brief  Current maximum cell grid X-coordinate.
     */
    int32 maxX;
    
    /*!
     * @brief  Current maximum cell grid Y-coordinate.
     */
    int32 maxY;
    
    /*!
     * @brief  Current maximum cell grid Z-coordinate.
     */
    int32 maxZ;
    
    /*!
     * @brief  Current minimum cell grid X-coordinate.
     */
    int32 minX;
    
    /*!
     * @brief  Current minimum cell grid Y-coordinate.
     */
    int32 minY;
    
    /*!
     * @brief  Current minimum cell grid Z-coordinate.
     */
    int32 minZ;
    
    /*!
     * @brief  Reciprocal value of #size.
     */
    float32 rSize;
    
    /*!
     * @brief  Size of the sliding cube.
     */
    float32 size;
    
    /*!
     * @brief  X-coordinate of minimum corner of bounding box of current cell grid,in terrain-space.
     */
    float32 x1;
    
    /*!
     * @brief  X-coordinate of maximum corner of bounding box of current cell grid,in terrain-space.
     */
    float32 x2;
    
    /*!
     * @brief  Y-coordinate of minimum corner of bounding box of current cell grid,in terrain-space.
     */
    float32 y1;
    
    /*!
     * @brief  Y-coordinate of maximum corner of bounding box of current cell grid,in terrain-space.
     */
    float32 y2;
    
    /*!
     * @brief  Z-coordinate of minimum corner of bounding box of current cell grid,in terrain-space.
     */
    float32 z1;
    
    /*!
     * @brief  Z-coordinate of maximum corner of bounding box of current cell grid,in terrain-space.
     */
    float32 z2;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Computes the extend in terrain-space of the current sliding cube.
     */
    void ComputeCellGridExtend();
    
    /*!
     * @brief  Computes the cell grid coordinate for the given terrain-space coordinate.
     * 
     * @param v The terrain-space coordinate.
     * 
     * @return The cell grid coordinate.
     */
    int32 ToGrid(float64 v);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<SlidingCubeRegion> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xD019DD73;
    
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
      if ((ptr = TerrainSpaceRegion::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } 

#endif
