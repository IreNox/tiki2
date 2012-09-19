////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_UTIL_SPATIAL_ITERRAINSPACEREGION_H
#define CLODDY_API_UTIL_SPATIAL_ITERRAINSPACEREGION_H

#include "CodeX/System.h"

// Include referenced structures.

#include "Cloddy/Vec3D.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Util { namespace Spatial { class ITerrainSpaceRegionVisitor; } } } }

// Declare interface ::Cloddy::API::Util::Spatial::ITerrainSpaceRegion.

namespace Cloddy { namespace API { namespace Util { namespace Spatial
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced structures.
  
  using Cloddy::Core::Math::Vectors::Vec3D;
  
  /*!
   * @brief  Base interface for classes that represent regions in terrain-space.
   */
  class NO_VTABLE ITerrainSpaceRegion : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The origin of this terrain space region.
     * 
     * @return Coordinates of origin.
     */
    virtual Vec3D GetOrigin() = 0;
    
    /*!
     * @brief  The origin of this terrain space region.
     * 
     * @param value Coordinates of origin.
     */
    virtual void SetOrigin(const Vec3D& value) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Accepts the given visitor object.
     * 
     * @param visitor <b>[not-null]</b>  The visitor object.
     * @param userData Optional user data.
     */
    virtual void Accept(ITerrainSpaceRegionVisitor* visitor, Object* userData) = 0;
    
    /*!
     * @brief  Returns \c true  if this terrain space region has been modified.
     * 
     * The modified flag will be cleared by this method,so all following calls will return 
     * \c false  until another modification is made.
     * 
     * When a new terrain space region is instantiated,the modified flag will initially be set to 
     * \c true .
     * 
     * @return \c true  if this region has been modified,\c false  if not.
     */
    virtual bool HasChanged() = 0;
    
    /*!
     * @brief  Checks if this terrain-space region intersects with the given sphere.
     * 
     * @param x X-coordinate of sphere center,in terrain-space.
     * @param y Y-coordinate of sphere center,in terrain-space.
     * @param z Z-coordinate of sphere center,in terrain-space.
     * @param r Radius of sphere,in terrain-space.
     * 
     * @return \c true  if this region intersects with the sphere,\c false  if not.
     */
    virtual bool IntersectsSphere(float64 x, float64 y, float64 z, float64 r) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<ITerrainSpaceRegion> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x11F1616;
    
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
