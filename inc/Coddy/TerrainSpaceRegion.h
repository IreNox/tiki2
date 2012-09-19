////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_UTIL_SPATIAL_TERRAINSPACEREGION_H
#define CLODDY_API_UTIL_SPATIAL_TERRAINSPACEREGION_H

#include "CodeX/System.h"

// Include referenced structures.

#include "Cloddy/Vec3D.h"

// Include referenced interfaces.

#include "Cloddy/ITerrainSpaceRegion.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Util { namespace Spatial { class ITerrainSpaceRegionVisitor; } } } }

// Declare class ::Cloddy::API::Util::Spatial::TerrainSpaceRegion.

namespace Cloddy { namespace API { namespace Util { namespace Spatial
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced structures.
  
  using Cloddy::Core::Math::Vectors::Vec3D;
  
  /*!
   * @brief  Abstract base class for ITerrainSpaceRegion implementations.
   */
  class TerrainSpaceRegion : public virtual ITerrainSpaceRegion
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual Vec3D GetOrigin();
    
    virtual void SetOrigin(const Vec3D& value);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void Accept(ITerrainSpaceRegionVisitor* visitor, Object* userData) = 0;
    
    virtual bool HasChanged();
    
    virtual bool IntersectsSphere(float64 x, float64 y, float64 z, float64 r) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Attributes
    // ---------------------------------------------------------------------------------------------
  protected:
    
    /*!
     * @brief  The terrain space origin.
     */
    Vec3D origin;
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of TerrainSpaceRegion.
     * 
     * The origin of the region will be at <c>(0,0,0)</c>.
     */
    TerrainSpaceRegion();
    
    /*!
     * @brief  Creates a new instance of TerrainSpaceRegion.
     * 
     * @param originX X-coordinate of origin,in terrain-space.
     * @param originY Y-coordinate of origin,in terrain-space.
     * @param originZ Z-coordinate of origin,in terrain-space.
     */
    TerrainSpaceRegion(float64 originX, float64 originY, float64 originZ);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Subclasses can call this method to set the modified flag.
     * 
     * @see #HasChanged
     */
    void Changed();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Has this terrain space region been modified?
     */
    bool hasChanged;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<TerrainSpaceRegion> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x23123E7B;
    
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
      if ((ptr = ITerrainSpaceRegion::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } 

#endif
