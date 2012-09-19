////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_FRACTAL_FRACTALLAYER_ELELVATION_H
#define CLODDY_API_HEIGHTMAPS_FRACTAL_FRACTALLAYER_ELELVATION_H

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

// Declare class ::Cloddy::API::Heightmaps::Fractal::FractalLayer_Elelvation.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Fractal
{
  // Use referenced namespaces.
  
  using namespace Cloddy::API::Heightmaps;
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Procedural::INoiseFunction;
  
  class FractalLayer_Elelvation : public FractalLayer
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
    
    Ptr<INoiseFunction> function;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of FractalLayer_Elelvation.
     * 
     * @param function The noise function that computes normalized elevation values.
     */
    FractalLayer_Elelvation(INoiseFunction* function);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<FractalLayer_Elelvation> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xF67AFCA5;
    
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
