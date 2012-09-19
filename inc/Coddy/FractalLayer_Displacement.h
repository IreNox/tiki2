////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_FRACTAL_FRACTALLAYER_DISPLACEMENT_H
#define CLODDY_API_HEIGHTMAPS_FRACTAL_FRACTALLAYER_DISPLACEMENT_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/HeightmapLayer.h"

// Include referenced classes.

#include "Cloddy/FractalLayer.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Procedural { class INoiseFunction; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Fractal { class FractalLayer; } } } }
namespace Cloddy { namespace API { namespace Heightmaps { class HeightmapSample; } } }

// Declare class ::Cloddy::API::Heightmaps::Fractal::FractalLayer_Displacement.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Fractal
{
  // Use referenced namespaces.
  
  using namespace Cloddy::API::Heightmaps;
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Procedural::INoiseFunction;
  
  class FractalLayer_Displacement : public FractalLayer
  {
    // Declare friend classes.
    
    friend class FractalLayer;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual HeightmapLayer GetLayerMask();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void ComputeHeightmapSample(float64 x, float64 y, float64 z, HeightmapSample* sample);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Noise function for X-axis displacement.
     */
    Ptr<INoiseFunction> displacementX;
    
    /*!
     * @brief  Noise function for Y-axis displacement.
     */
    Ptr<INoiseFunction> displacementY;
    
    /*!
     * @brief  Noise function for Z-axis displacement.
     */
    Ptr<INoiseFunction> displacementZ;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of FractalLayer_Displacement.
     * 
     * @param displacementX Noise function for X-axis displacement.
     * @param displacementY Noise function for Y-axis displacement.
     * @param displacementZ Noise function for Z-axis displacement.
     */
    FractalLayer_Displacement(INoiseFunction* displacementX, INoiseFunction* displacementY, INoiseFunction* displacementZ);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<FractalLayer_Displacement> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x1DAEDE95;
    
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
      if ((ptr = FractalLayer::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } 

#endif
