////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_UTIL_COLORS_ICOLORRAMP_H
#define CLODDY_API_UTIL_COLORS_ICOLORRAMP_H

#include "CodeX/System.h"

// Declare interface ::Cloddy::API::Util::Colors::IColorRamp.

namespace Cloddy { namespace API { namespace Util { namespace Colors
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Base interface for classes that provide a color ramp.
   * 
   * A color ramp consists of one or more color ramp slots;each slot holds an X-coordinate and a 
   * color value.
   */
  class NO_VTABLE IColorRamp : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The number of color ramp slots.
     * 
     * @return <b>[>=0]</b>  The number of slots in this color ramp.
     */
    virtual int32 GetColorCount() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Returns a color on this color ramp.
     * 
     * @param x X-coordinate of color to return.
     * 
     * @return The interpolated color,as a 32-bit ARGB color value.
     */
    virtual int32 Get(float64 x) = 0;
    
    /*!
     * @brief  Converts this color ramp into a color palette.
     * 
     * @param x1 X-coordinate of first palette color.
     * @param x2 Y-coordinate of last palette color.
     * @param n <b>[>0]</b>  The number of palette colors.
     * 
     * @return <b>[not-null]</b>  The created color palette.
     */
    virtual Array<int32> ToColorPalette(float64 x1, float64 x2, int32 n) = 0;
    
    /*!
     * @brief  Returns an IColorRamp instance that uses the same colors as this color ramp,but 
     *         transforms the input X-coordinate.
     * 
     * Input X-coordinates are transformed as follows:
     * <pre>
     *     xOut = xIn * scale + offset
     * </pre>
     * 
     * @param scale Scale factor to apply to input X-coordinates.
     * @param offset Offset value to add to scaled input X-coordinates.
     * 
     * @return <b>[not-null]</b>  The transformed color ramp.
     */
    virtual Ptr<IColorRamp> Transform(float64 scale, float64 offset) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IColorRamp> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x18BA67FA;
    
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
