////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_FRACTAL_FRACTALDIFFUSECOMBINER_RAMP_H
#define CLODDY_API_HEIGHTMAPS_FRACTAL_FRACTALDIFFUSECOMBINER_RAMP_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/FractalDiffuseCombiner.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Util { namespace Colors { class IColorRamp; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Fractal { class FractalDiffuseCombiner; } } } }

// Declare class ::Cloddy::API::Heightmaps::Fractal::FractalDiffuseCombiner_Ramp.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Fractal
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Util::Colors::IColorRamp;
  
  class FractalDiffuseCombiner_Ramp : public FractalDiffuseCombiner
  {
    // Declare friend classes.
    
    friend class FractalDiffuseCombiner;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual int32 MakeDiffuseColor(float64 a, float64 b, float64 c, float64 d);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    Ptr<IColorRamp> ramp;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    FractalDiffuseCombiner_Ramp(IColorRamp* ramp);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<FractalDiffuseCombiner_Ramp> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x696C4DD4;
    
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
      if ((ptr = FractalDiffuseCombiner::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } 

#endif
