////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_PROJECTION_MAPPROJECTION_EQUIRECTANGULAR_H
#define CLODDY_API_HEIGHTMAPS_PROJECTION_MAPPROJECTION_EQUIRECTANGULAR_H

#include "CodeX/System.h"

// Include referenced structures.

#include "Cloddy/Vec2D.h"
#include "Cloddy/Vec3D.h"

// Include referenced classes.

#include "Cloddy/MapProjection.h"

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Projection { class MapProjection; } } } }

// Declare class ::Cloddy::API::Heightmaps::Projection::MapProjection_Equirectangular.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Projection
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced structures.
  
  using Cloddy::Core::Math::Vectors::Vec2D;
  using Cloddy::Core::Math::Vectors::Vec3D;
  
  class MapProjection_Equirectangular : public MapProjection
  {
    // Declare friend classes.
    
    friend class MapProjection;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual Vec2D Project(float64 x, float64 y, float64 z);
    
    virtual Vec3D Unproject(float64 x, float64 y);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Center cubemap coordinate.
     */
    float64 center;
    
    /*!
     * @brief  Longitude offset.
     */
    float64 offsetX;
    
    /*!
     * @brief  Longitude scale.
     */
    float64 scaleX;
    
    /*!
     * @brief  Latitude scale.
     */
    float64 scaleY;
    
    /*!
     * @brief  Reciprocal longitude scale.
     */
    float64 scaleXInv;
    
    /*!
     * @brief  Reciprocal Latitude scale.
     */
    float64 scaleYInv;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of MapProjection_Equirectangular.
     * 
     * @param centerLongitude The lontigude to map to the map center,in degrees.
     * @param mapWidth The map width,in pixels.
     * @param mapHeight The map height,in pixels.
     * @param cubeSize The cubemap size.
     */
    MapProjection_Equirectangular(float64 centerLongitude, int32 mapWidth, int32 mapHeight, int32 cubeSize);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<MapProjection_Equirectangular> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x7AF62A27;
    
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
      if ((ptr = MapProjection::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } 

#endif
