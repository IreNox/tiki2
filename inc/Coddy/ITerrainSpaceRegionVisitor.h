////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_UTIL_SPATIAL_ITERRAINSPACEREGIONVISITOR_H
#define CLODDY_API_UTIL_SPATIAL_ITERRAINSPACEREGIONVISITOR_H

#include "CodeX/System.h"

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Util { namespace Spatial { class AxisAlignedBoxRegion; } } } }
namespace Cloddy { namespace API { namespace Util { namespace Spatial { class CompositeRegion; } } } }
namespace Cloddy { namespace API { namespace Util { namespace Spatial { class SlidingCubeRegion; } } } }
namespace Cloddy { namespace API { namespace Util { namespace Spatial { class SphereRegion; } } } }

// Declare interface ::Cloddy::API::Util::Spatial::ITerrainSpaceRegionVisitor.

namespace Cloddy { namespace API { namespace Util { namespace Spatial
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Visitor interface for ITerrainSpaceRegion implementations.
   */
  class NO_VTABLE ITerrainSpaceRegionVisitor : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Visits the given terrain space region.
     * 
     * @param region <b>[not-null]</b>  The terrain space region object to visit.
     * @param userData Optional user object to pass on to \e region .
     */
    virtual void Visit(AxisAlignedBoxRegion* region, Object* userData) = 0;
    
    /*!
     * @brief  Visits the given terrain space region.
     * 
     * @param region <b>[not-null]</b>  The terrain space region object to visit.
     * @param userData Optional user object to pass on to \e region .
     */
    virtual void Visit(CompositeRegion* region, Object* userData) = 0;
    
    /*!
     * @brief  Visits the given terrain space region.
     * 
     * @param region <b>[not-null]</b>  The terrain space region object to visit.
     * @param userData Optional user object to pass on to \e region .
     */
    virtual void Visit(SlidingCubeRegion* region, Object* userData) = 0;
    
    /*!
     * @brief  Visits the given terrain space region.
     * 
     * @param region <b>[not-null]</b>  The terrain space region object to visit.
     * @param userData Optional user object to pass on to \e region .
     */
    virtual void Visit(SphereRegion* region, Object* userData) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<ITerrainSpaceRegionVisitor> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x9FCB9D60;
    
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
