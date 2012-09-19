////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_UTIL_CURVES_CURVESAMPLE_H
#define CLODDY_API_UTIL_CURVES_CURVESAMPLE_H

#include "CodeX/System.h"

// Declare class ::Cloddy::API::Util::Curves::CurveSample.

namespace Cloddy { namespace API { namespace Util { namespace Curves
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Data container for an interpolated point on a ICurve.
   */
  class CurveSample : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The control point index of this curve sample.
     */
    float64 ControlPointIndex;
    
    /*!
     * @brief  W-coordinate of the interpolated point.
     */
    float64 PositionW;
    
    /*!
     * @brief  X-coordinate of the interpolated point.
     */
    float64 PositionX;
    
    /*!
     * @brief  Y-coordinate of the interpolated point.
     */
    float64 PositionY;
    
    /*!
     * @brief  Z-coordinate of the interpolated point.
     */
    float64 PositionZ;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    CurveSample();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<CurveSample> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x7FA8437;
    
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
