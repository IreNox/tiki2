////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_FRACTAL_FRACTALDIFFUSECOMBINER_H
#define CLODDY_API_HEIGHTMAPS_FRACTAL_FRACTALDIFFUSECOMBINER_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IFractalDiffuseCombiner.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Util { namespace Colors { class IColorRamp; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Fractal { class FractalDiffuseCombiner_HSV; } } } }
namespace Cloddy { namespace API { namespace Heightmaps { namespace Fractal { class FractalDiffuseCombiner_RGB; } } } }

// Declare class ::Cloddy::API::Heightmaps::Fractal::FractalDiffuseCombiner.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Fractal
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Util::Colors::IColorRamp;
  
  class FractalDiffuseCombiner : public virtual IFractalDiffuseCombiner
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  A fractal diffuse color combiner that maps the argument values into HSV color space.
     * 
     * The combiner arguments are interpreted as follows:
     *   - <b>a:</b> Hue angle in the range <b>[0..360]</b>.
     *   - <b>b:</b> Saturation value in the range <b>[0..1]</b>.
     *   - <b>c:</b> Brightness value in the range <b>[0..1]</b>.
     *   - <b>d:</b> Alpha channel in the range <b>[0..1]</b>.
     */
    static const StaticPtr<IFractalDiffuseCombiner> HueSaturationBrightness;
    
    /*!
     * @brief  A fractal diffuse color combiner that maps the argument values into RGB color space.
     * 
     * The combiner arguments are interpreted as follows:
     *   - <b>a:</b> Red channel in the range <b>[0..1]</b>.
     *   - <b>b:</b> Blue channel in the range <b>[0..1]</b>.
     *   - <b>c:</b> Green channel in the range <b>[0..1]</b>.
     *   - <b>d:</b> Alpha channel in the range <b>[0..1]</b>.
     */
    static const StaticPtr<IFractalDiffuseCombiner> RedGreenBlue;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Returns a IFractalDiffuseCombiner object that maps the first combiner argument into 
     *         the given color ramp.
     * 
     * The combiner arguments are interpreted as follows:
     *   - <b>a:</b> Input coordinate for color ramp lookup (IColorRamp::Get).
     *   - <b>b:</b> not used
     *   - <b>c:</b> not used
     *   - <b>d:</b> not used
     * 
     * @param colorRamp <b>[not-null]</b>  The color ramp.
     * 
     * @return <b>[not-null]</b>  The combiner.
     */
    static Ptr<IFractalDiffuseCombiner> ColorRamp(IColorRamp* colorRamp);
    
    virtual int32 MakeDiffuseColor(float64 a, float64 b, float64 c, float64 d) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Static Initializer Functions
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief Static initializer function for field HueSaturationBrightness.
     */
    static Object* StaticInitializer_HueSaturationBrightness();
    
    /*!
     * @brief Static initializer function for field RedGreenBlue.
     */
    static Object* StaticInitializer_RedGreenBlue();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<FractalDiffuseCombiner> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xA8775BF7;
    
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
      if ((ptr = IFractalDiffuseCombiner::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } 

#endif
