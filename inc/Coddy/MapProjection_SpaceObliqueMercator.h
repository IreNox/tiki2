////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_PROJECTION_MAPPROJECTION_SPACEOBLIQUEMERCATOR_H
#define CLODDY_API_HEIGHTMAPS_PROJECTION_MAPPROJECTION_SPACEOBLIQUEMERCATOR_H

#include "CodeX/System.h"

// Include referenced structures.

#include "Cloddy/Vec2D.h"
#include "Cloddy/Vec3D.h"

// Include referenced classes.

#include "Cloddy/MapProjection.h"

// Declare class ::Cloddy::API::Heightmaps::Projection::MapProjection_SpaceObliqueMercator.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Projection
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced structures.
  
  using Cloddy::Core::Math::Vectors::Vec2D;
  using Cloddy::Core::Math::Vectors::Vec3D;
  
  class MapProjection_SpaceObliqueMercator : public MapProjection
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual Vec2D Project(float64 x, float64 y, float64 z);
    
    virtual Vec3D Unproject(float64 x, float64 y);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
  private:
    
    MapProjection_SpaceObliqueMercator(int32 mapWidth, int32 mapHeight, int32 cubeSize);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<MapProjection_SpaceObliqueMercator> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xB5406E19;
    
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
