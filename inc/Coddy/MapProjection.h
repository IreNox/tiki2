////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_PROJECTION_MAPPROJECTION_H
#define CLODDY_API_HEIGHTMAPS_PROJECTION_MAPPROJECTION_H

#include "CodeX/System.h"

// Include referenced structures.

#include "Cloddy/Vec2D.h"
#include "Cloddy/Vec2I.h"
#include "Cloddy/Vec3D.h"

// Include referenced interfaces.

#include "Cloddy/IMapProjection.h"

// Forward declare referenced structures.

namespace Cloddy { namespace Core { namespace Math { namespace Vectors { struct Vec3I; } } } }

// Declare class ::Cloddy::API::Heightmaps::Projection::MapProjection.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Projection
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced structures.
  
  using Cloddy::Core::Math::Vectors::Vec2D;
  using Cloddy::Core::Math::Vectors::Vec2I;
  using Cloddy::Core::Math::Vectors::Vec3D;
  using Cloddy::Core::Math::Vectors::Vec3I;
  
  /*!
   * @brief  Base class for map projections.
   */
  class MapProjection : public virtual IMapProjection
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual int32 GetCubeSize();
    
    virtual Vec2I GetMapSize();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new equirectangular map projection.
     * 
     * @param centerLongitude The lontigude to map to the map center,in degrees.
     * @param mapWidth <b>[>0]</b>  The map width,in pixels.
     * @param mapHeight <b>[>0]</b>  The map height,in pixels.
     * @param cubeSize <b>[pow2+1]</b>  The cubemap size.
     * 
     * @return <b>[not-null]</b>  The created IMapProjection object.
     */
    static Ptr<IMapProjection> Equirectangular(float64 centerLongitude, int32 mapWidth, int32 mapHeight, int32 cubeSize);
    
    /*!
     * @brief  Creates a new equirectangular map projection.
     * 
     * @param centerLongitude The lontigude to map to the map center,in degrees.
     * @param mapWidth <b>[>0]</b>  The map width,in pixels.
     * @param mapHeight <b>[>0]</b>  The map height,in pixels.
     * @param cubeSize <b>[pow2+1]</b>  The cubemap size.
     * 
     * @return <b>[not-null]</b>  The created IMapProjection object.
     */
    static Ptr<IMapProjection> Mercator(float64 centerLongitude, int32 mapWidth, int32 mapHeight, int32 cubeSize);
    
    /*!
     * @brief  Creates a new plate caree map projection.
     * 
     * @param mapWidth <b>[>0]</b>  The map width,in pixels.
     * @param mapHeight <b>[>0]</b>  The map height,in pixels.
     * @param cubeSize <b>[pow2+1]</b>  The cubemap size.
     * 
     * @return <b>[not-null]</b>  The created IMapProjection object.
     */
    static Ptr<IMapProjection> PlateCaree(int32 mapWidth, int32 mapHeight, int32 cubeSize);
    
    virtual Vec2D Project(const Vec3I& coords);
    
    virtual Vec2D Project(int32 x, int32 y, int32 z);
    
    virtual Vec2D Project(const Vec3D& coords);
    
    virtual Vec2D Project(float64 x, float64 y, float64 z) = 0;
    
    virtual Vec3D Unproject(const Vec2I& coords);
    
    virtual Vec3D Unproject(int32 x, int32 y);
    
    virtual Vec3D Unproject(const Vec2D& coords);
    
    virtual Vec3D Unproject(float64 x, float64 y) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Attributes
    // ---------------------------------------------------------------------------------------------
  protected:
    
    /*!
     * @brief  Size of the cubemap.
     */
    int32 cubeSize;
    
    /*!
     * @brief  Size of the cubemap,minus one.
     */
    int32 cubeSizeMinusOne;
    
    /*!
     * @brief  Size of the rectangular map.
     */
    Vec2I mapSize;
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of MapProjection.
     * 
     * @param mapWidth <b>[>0]</b>  The map width,in pixels.
     * @param mapHeight <b>[>0]</b>  The map height,in pixels.
     * @param cubeSize <b>[pow2+1]</b>  The cubemap size.
     */
    MapProjection(int32 mapWidth, int32 mapHeight, int32 cubeSize);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<MapProjection> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x493F9AB6;
    
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
      if ((ptr = IMapProjection::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } 

#endif
