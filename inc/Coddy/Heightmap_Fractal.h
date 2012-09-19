////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_HEIGHTMAP_FRACTAL_H
#define CLODDY_API_HEIGHTMAPS_HEIGHTMAP_FRACTAL_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/HeightmapLayer.h"
#include "Cloddy/MapType.h"

// Include referenced structures.

#include "Cloddy/Vec3D.h"

// Include referenced classes.

#include "Cloddy/Heightmap.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Fractal { class IFractalLayer; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Heightmaps { class Heightmap; } } }
namespace Cloddy { namespace API { namespace Heightmaps { class HeightmapSample; } } }

// Declare class ::Cloddy::API::Heightmaps::Heightmap_Fractal.

namespace Cloddy { namespace API { namespace Heightmaps
{
  // Use referenced namespaces.
  
  using namespace Cloddy::API::Util;
  using namespace CodeX;
  
  // Use referenced structures.
  
  using Cloddy::Core::Math::Vectors::Vec3D;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Heightmaps::Fractal::IFractalLayer;
  
  /*!
   * @brief  An IHeightmap implementation that computes elevation,diffuse color and displacement 
   *         vectors from a given set of INoiseFunction objects.
   */
  class Heightmap_Fractal : public Heightmap
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
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
  protected:
    
    virtual void DisposeManaged();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Coordinates of center of heightmap space.
     */
    Vec3D center;
    
    /*!
     * @brief  The fractal heightmap layer.
     */
    Ptr<IFractalLayer> layer;
    
    /*!
     * @brief  Scale factor from heightmap space to noise space.
     */
    float64 scale;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of Heightmap_Fractal.
     * 
     * @param width The map width.
     * @param height The map height.
     * @param mapType The map type.
     * @param scale Scale factor for heightmap coordinates.
     * @param center Center heightmap coordinate.
     * @param layer The fractal layers.
     */
    Heightmap_Fractal(int32 width, int32 height, MapType mapType, float64 scale, const Vec3D& center, IFractalLayer* layer);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<Heightmap_Fractal> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xB5EB46CB;
    
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
