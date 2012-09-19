////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_UTIL_SPATIAL_SPHEREREGION_H
#define CLODDY_API_UTIL_SPATIAL_SPHEREREGION_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/TerrainSpaceRegion.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Util { namespace Spatial { class ITerrainSpaceRegionVisitor; } } } }

// Declare class ::Cloddy::API::Util::Spatial::SphereRegion.

namespace Cloddy { namespace API { namespace Util { namespace Spatial
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  A terrain-space region specified by a bounding sphere.
   */
  class SphereRegion : public TerrainSpaceRegion
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Radius of sphere,in terrain-space.
     * 
     * @return <b>[>=0]</b>  Radius of sphere,in terrain-space.
     */
    float32 GetRadius();
    
    /*!
     * @brief  Radius of sphere,in terrain-space.
     * 
     * @param value <b>[>=0]</b>  Radius of sphere,in terrain-space.
     */
    void SetRadius(float32 value);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of SphereRegion.
     * 
     * The origin of the sphere will be set to <c>(0,0,0)</c> and the radius will be \c 0 .
     */
    SphereRegion();
    
    /*!
     * @brief  Creates a new instance of SphereRegion.
     * 
     * The origin of the sphere will be set to <c>(0,0,0)</c>.
     * 
     * @param radius <b>[>=0]</b>  Radius of sphere,in terrain-space.
     */
    SphereRegion(float32 radius);
    
    /*!
     * @brief  Creates a new instance of SphereRegion.
     * 
     * @param originX X-coordinate of sphere center,in terrain-space.
     * @param originY Y-coordinate of sphere center,in terrain-space.
     * @param originZ Z-coordinate of sphere center,in terrain-space.
     * @param radius <b>[>=0]</b>  Radius of sphere,in terrain-space.
     */
    SphereRegion(float32 originX, float32 originY, float32 originZ, float32 radius);
    
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
     * @brief  Radius of sphere,in terrain-space.
     */
    float32 radius;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<SphereRegion> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x46F24001;
    
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
