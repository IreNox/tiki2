////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_UTIL_SPATIAL_COMPOSITEREGION_H
#define CLODDY_API_UTIL_SPATIAL_COMPOSITEREGION_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/TerrainSpaceRegion.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Util { namespace Spatial { class ITerrainSpaceRegion; } } } }
namespace Cloddy { namespace API { namespace Util { namespace Spatial { class ITerrainSpaceRegionVisitor; } } } }

// Declare class ::Cloddy::API::Util::Spatial::CompositeRegion.

namespace Cloddy { namespace API { namespace Util { namespace Spatial
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  A terrain space region that aggregates and combines multiple child regions.
   * 
   * A composite regions represents the space defined by the union of its child regions.The origin 
   * vector of each child region is interpreted relative to the origin of the composite region.
   */
  class CompositeRegion : public TerrainSpaceRegion
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The number of terrain space regions this CompositeRegion currently contains.
     * 
     * @return <b>[>=0]</b>  The number of aggregated regions.
     */
    int32 GetRegionCount();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of CompositeRegion.
     */
    CompositeRegion();
    
    /*!
     * @brief  Creates a new instance of CompositeRegion.
     * 
     * @param initialCapacity <b>[>0]</b>  The initial capacity,in regions.
     */
    CompositeRegion(int32 initialCapacity);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void Accept(ITerrainSpaceRegionVisitor* visitor, Object* userData);
    
    /*!
     * @brief  Adds the given region to this composite region.
     * 
     * @param region <b>[not-null]</b>  The region to add.
     */
    void AddRegion(ITerrainSpaceRegion* region);
    
    /*!
     * @brief  Returns an aggregated region.
     * 
     * @param index <b>[0..#GetRegionCount-1]</b>  Index of the region to return.
     * 
     * @return <b>[not-null]</b>  The aggregated ITerrainSpaceRegion object.
     */
    Ptr<ITerrainSpaceRegion> GetRegion(int32 index);
    
    virtual bool HasChanged();
    
    virtual bool IntersectsSphere(float64 x, float64 y, float64 z, float64 r);
    
    /*!
     * @brief  Removes the given region from this composite region.
     * 
     * @param region <b>[not-null]</b>  The region to remove.
     */
    void RemoveRegion(ITerrainSpaceRegion* region);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Number of terrain space regions currently stored in the #regions array.
     */
    int32 regionCount;
    
    /*!
     * @brief  This array holds the aggregated terrain space regions.
     */
    Array<Ptr<ITerrainSpaceRegion> > regions;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<CompositeRegion> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xF4E01C3D;
    
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
