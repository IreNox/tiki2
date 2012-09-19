////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_UTIL_COLORS_COLORRAMP_H
#define CLODDY_API_UTIL_COLORS_COLORRAMP_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/ColorRampBase.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Util { namespace Colors { class IColorRamp; } } } }

// Declare class ::Cloddy::API::Util::Colors::ColorRamp.

namespace Cloddy { namespace API { namespace Util { namespace Colors
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  This class represents a color ramp.
   * 
   * A color ramp consists of one or more color ramp slots;each slot holds an X-coordinate and a 
   * color value.
   */
  class ColorRamp : public ColorRampBase
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual int32 GetColorCount();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of ColorRamp.
     */
    ColorRamp();
    
    /*!
     * @brief  Creates a new instance of ColorRamp.
     * 
     * @param initialCapacity <b>[>=0]</b>  The initial capacity of the color ramp.
     */
    ColorRamp(int32 initialCapacity);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a color ramp with two colors.
     * 
     * The first color is placed at the X-coordinate <c>0.0</c>,the second one at <c>1.0</c> (
     * see #Set).
     * 
     * @param colorA The first color ramp color.
     * @param colorB The second color ramp color.
     * 
     * @return <b>[not-null]</b>  The created ColorRamp.
     */
    static Ptr<IColorRamp> ForDualColor(int32 colorA, int32 colorB);
    
    /*!
     * @brief  Creates a color ramp with a single color.
     * 
     * The color is placed at the X-coordinate <c>0.0</c>.
     * 
     * @param color The color ramp color.
     * 
     * @return <b>[not-null]</b>  The created ColorRamp.
     */
    static Ptr<IColorRamp> ForSingleColor(int32 color);
    
    /*!
     * @brief  Adds a color on this color ramp.
     * 
     * The color ramp slots must be set so that the following condition is met:
     * <pre>
     *       x[i] >= x[i-1]
     * </pre>
     * The X-coordinate of a color ramp slot must be greater than or equal to the X-coordinate of 
     * the preceding slot.
     * 
     * The index of the added color will be #GetColorCount.
     * 
     * @param x X-coordinate of color ramp slot.
     * @param y Color value of color ramp slot,as a 32-bit ARGB color value.
     * 
     * @return <b>[not-null]</b>  this
     */
    Ptr<ColorRamp> Add(float64 x, int32 y);
    
    virtual int32 Get(float64 x);
    
    /*!
     * @brief  Sets a color on this color ramp.
     * 
     * The color ramp slots must be set so that the following condition is met:
     * <pre>
     *     x[i] >= x[i-1]
     * </pre>
     * The X-coordinate of a color ramp slot must be greater than or equal to the X-coordinate of 
     * the preceding slot.
     * 
     * @param idx <b>[>=0]</b>  Index of color ramp slot.
     * @param x X-coordinate of color ramp slot.
     * @param y Color value of color ramp slot,as a 32-bit ARGB color value.
     * 
     * @return <b>[not-null]</b>  this
     */
    Ptr<ColorRamp> Set(int32 idx, float64 x, int32 y);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The number of color ramp slots.
     */
    int32 colorCount;
    
    /*!
     * @brief  The X-coordinate of each color ramp slot.
     */
    Array<float64> x;
    
    /*!
     * @brief  The 32-bit ARGB color value of each color ramp slot.
     */
    Array<int32> y;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    void GrowIfNecessary(int32 newCapacity);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<ColorRamp> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xDADEFEDB;
    
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
      if ((ptr = ColorRampBase::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } 

#endif
