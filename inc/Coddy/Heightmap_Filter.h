////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_HEIGHTMAP_FILTER_H
#define CLODDY_API_HEIGHTMAPS_HEIGHTMAP_FILTER_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/HeightmapLayer.h"

// Include referenced classes.

#include "Cloddy/CompositeHeightmapOne.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Heightmaps { class IHeightmap; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Heightmaps { class Heightmap; } } }
namespace Cloddy { namespace API { namespace Heightmaps { class HeightmapSample; } } }

// Declare class ::Cloddy::API::Heightmaps::Heightmap_Filter.

namespace Cloddy { namespace API { namespace Heightmaps
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  class Heightmap_Filter : public CompositeHeightmapOne
  {
    // Declare friend classes.
    
    friend class Heightmap;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual void Get(int32 x, int32 y, HeightmapSample* sample);
    
    virtual void Get(int32 x, int32 y, int32 z, HeightmapSample* sample);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
  protected:
    
    virtual void DisposeManaged();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Update HeightmapLayer::HeightmapLayer_Detail0?
     */
    bool detail0;
    
    /*!
     * @brief  Update HeightmapLayer::HeightmapLayer_Detail1?
     */
    bool detail1;
    
    /*!
     * @brief  Update HeightmapLayer::HeightmapLayer_Detail2?
     */
    bool detail2;
    
    /*!
     * @brief  Update HeightmapLayer::HeightmapLayer_Detail3?
     */
    bool detail3;
    
    /*!
     * @brief  Update HeightmapLayer::HeightmapLayer_Diffuse?
     */
    bool diffuse;
    
    /*!
     * @brief  Update HeightmapLayer::HeightmapLayer_Displacement?
     */
    bool displacement;
    
    /*!
     * @brief  Update HeightmapLayer::HeightmapLayer_Elevation?
     */
    bool elevation;
    
    /*!
     * @brief  The helper heightmap sample object.
     */
    Ptr<HeightmapSample> sample;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of Heightmap_Filter.
     * 
     * @param heightmap The heightmap to filter.
     * @param layers The heightmap layers.
     */
    Heightmap_Filter(IHeightmap* heightmap, HeightmapLayer layers);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<Heightmap_Filter> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x38A45F70;
    
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
      if ((ptr = CompositeHeightmapOne::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
