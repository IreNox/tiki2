////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_FRACTAL_IFRACTALLAYER_H
#define CLODDY_API_HEIGHTMAPS_FRACTAL_IFRACTALLAYER_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/HeightmapLayer.h"

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Heightmaps { class HeightmapSample; } } }

// Declare interface ::Cloddy::API::Heightmaps::Fractal::IFractalLayer.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Fractal
{
  // Use referenced namespaces.
  
  using namespace Cloddy::API::Heightmaps;
  using namespace CodeX;
  
  /*!
   * @brief  Base interface for fractal heightmap layers.
   * 
   * @see Heightmap::FractalRect
   * @see Heightmap::FractalCube
   */
  class NO_VTABLE IFractalLayer : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The heightmap layers that are filled by this fractal layer.
     * 
     * @return The layer mask.
     */
    virtual HeightmapLayer GetLayerMask() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Returns a fractal heightmap layer that is a combination of this layer and the given 
     *         one.
     * 
     * @param layer <b>[not-null]</b>  The second layer.
     * 
     * @return <b>[not-null]</b>  The resulting fractal layer.
     */
    virtual Ptr<IFractalLayer> Append(IFractalLayer* layer) = 0;
    
    /*!
     * @brief  Computes 
     * 
     * @param x The input X-coordinate,in noise space..
     * @param y The input Y-coordinate,in noise space..
     * @param z The input Z-coordinate,in noise space..
     * @param sample The output heightmap sample.
     */
    virtual void ComputeHeightmapSample(float64 x, float64 y, float64 z, HeightmapSample* sample) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IFractalLayer> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xEFA5E624;
    
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
