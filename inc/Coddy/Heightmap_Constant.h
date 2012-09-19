////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_HEIGHTMAP_CONSTANT_H
#define CLODDY_API_HEIGHTMAPS_HEIGHTMAP_CONSTANT_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/HeightmapLayer.h"
#include "Cloddy/MapType.h"

// Include referenced classes.

#include "Cloddy/Heightmap.h"

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Heightmaps { class Heightmap; } } }
namespace Cloddy { namespace API { namespace Heightmaps { class HeightmapSample; } } }

// Declare class ::Cloddy::API::Heightmaps::Heightmap_Constant.

namespace Cloddy { namespace API { namespace Heightmaps
{
  // Use referenced namespaces.
  
  using namespace Cloddy::API::Util;
  using namespace CodeX;
  
  /*!
   * @brief  Abstract base class for constant heightmaps (ie. heightmaps that return constant 
   *         elevation and color values).
   */
  class Heightmap_Constant : public Heightmap
  {
    // Declare friend classes.
    
    friend class Heightmap;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual HeightmapLayer GetLayerMask();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void Get(int32 x, int32 y, HeightmapSample* sample);
    
    virtual void Get(int32 x, int32 y, int32 z, HeightmapSample* sample);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    int32 detail0;
    
    int32 detail1;
    
    int32 detail2;
    
    int32 detail3;
    
    /*!
     * @brief  The constant diffuse color value.
     */
    int32 diffuse;
    
    int32 displacementX;
    
    int32 displacementY;
    
    int32 displacementZ;
    
    /*!
     * @brief  The constant elevation value.
     */
    int32 elevation;
    
    HeightmapLayer layers;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    Heightmap_Constant(int32 width, int32 height, MapType mapType, HeightmapSample* sample, HeightmapLayer layers);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<Heightmap_Constant> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x21CF0ED6;
    
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
      if ((ptr = Heightmap::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
