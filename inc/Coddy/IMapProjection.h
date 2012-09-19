////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_PROJECTION_IMAPPROJECTION_H
#define CLODDY_API_HEIGHTMAPS_PROJECTION_IMAPPROJECTION_H

#include "CodeX/System.h"

// Include referenced structures.

#include "Cloddy/Vec2D.h"
#include "Cloddy/Vec2I.h"
#include "Cloddy/Vec3D.h"

// Forward declare referenced structures.

namespace Cloddy { namespace Core { namespace Math { namespace Vectors { struct Vec3I; } } } }

// Declare interface ::Cloddy::API::Heightmaps::Projection::IMapProjection.

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
   * @brief  Base interface for classes that provide a projection from cubemap space to a 
   *         rectangular map space.
   * 
   * The pixels of a rectangular map are interpreted as points.
   */
  class NO_VTABLE IMapProjection : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Size of the cubemap.
     * 
     * @return <b>[pow2+1]</b>  The cubemap size.
     */
    virtual int32 GetCubeSize() = 0;
    
    /*!
     * @brief  Size of the rectangular map.
     * 
     * @return The map size.
     */
    virtual Vec2I GetMapSize() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Projects the given cubemap coordinates to rectangular map coordinates.
     * 
     * @param coords The cubemap coordinates.
     * 
     * @return The projected rectangular map coordinates.
     */
    virtual Vec2D Project(const Vec3I& coords) = 0;
    
    /*!
     * @brief  Projects the given cubemap coordinates to rectangular map coordinates.
     * 
     * @param x Cubemap X-coordinate.
     * @param y Cubemap Y-coordinate.
     * @param z Cubemap Z-coordinate.
     * 
     * @return The projected rectangular map coordinates.
     */
    virtual Vec2D Project(int32 x, int32 y, int32 z) = 0;
    
    /*!
     * @brief  Projects the given cubemap coordinates to rectangular map coordinates.
     * 
     * @param coords The cubemap coordinates.
     * 
     * @return The projected rectangular map coordinates.
     */
    virtual Vec2D Project(const Vec3D& coords) = 0;
    
    /*!
     * @brief  Projects the given cubemap coordinates to rectangular map coordinates.
     * 
     * @param x Cubemap X-coordinate.
     * @param y Cubemap Y-coordinate.
     * @param z Cubemap Z-coordinate.
     * 
     * @return The projected rectangular map coordinates.
     */
    virtual Vec2D Project(float64 x, float64 y, float64 z) = 0;
    
    /*!
     * @brief  Unprojects the given rectangular map coordinates to cubemap coordinates.
     * 
     * @param coords The rectangular map coordinate.
     * 
     * @return The cubemap coordinates.
     */
    virtual Vec3D Unproject(const Vec2I& coords) = 0;
    
    /*!
     * @brief  Unprojects the given rectangular map coordinates to cubemap coordinates.
     * 
     * @param x Rectangular map X-coordinate.
     * @param y Rectangular map X-coordinate.
     * 
     * @return The cubemap coordinates.
     */
    virtual Vec3D Unproject(int32 x, int32 y) = 0;
    
    /*!
     * @brief  Unprojects the given rectangular map coordinates to cubemap coordinates.
     * 
     * @param coords The rectangular map coordinate.
     * 
     * @return The cubemap coordinates.
     */
    virtual Vec3D Unproject(const Vec2D& coords) = 0;
    
    /*!
     * @brief  Unprojects the given rectangular map coordinates to cubemap coordinates.
     * 
     * @param x Rectangular map X-coordinate.
     * @param y Rectangular map X-coordinate.
     * 
     * @return The cubemap coordinates.
     */
    virtual Vec3D Unproject(float64 x, float64 y) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IMapProjection> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xACE1201F;
    
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
      return (void*) 0;
    }
  };
} } } } 

#endif
