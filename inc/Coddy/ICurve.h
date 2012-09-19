////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_UTIL_CURVES_ICURVE_H
#define CLODDY_API_UTIL_CURVES_ICURVE_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/Continuity.h"

// Include referenced interfaces.

#include "Cloddy/ISerializable.h"

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Util { namespace Curves { class CurveSample; } } } }

// Declare interface ::Cloddy::API::Util::Curves::ICurve.

namespace Cloddy { namespace API { namespace Util { namespace Curves
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::IO::Serialization::ISerializable;
  
  /*!
   * @brief  Base interface for classes that represent a curve that interpolates through a sequence 
   *         of control points.
   */
  class NO_VTABLE ICurve : public virtual ISerializable
  {
    // ---------------------------------------------------------------------------------------------
    // Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The continuity type of this curve.
     * 
     * @return The continuity of this curve.
     */
    virtual Continuity GetContinuity() = 0;
    
    /*!
     * @brief  The number of control points.
     * 
     * @return <b>[>=0]</b>  The number of control points.
     */
    virtual int32 GetControlPointCount() = 0;
    
    /*!
     * @brief  The maximum control point index that can be computed without interpolation errors 
     *         assuming additional control points are added to the curve.
     * 
     * @return The maximum control point index.A value of \c -1  indicates that no points may be 
     * computed.
     */
    virtual int32 GetMaxControlPointIndex() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Adds a 1D control point to this curve.
     * 
     * The Y,Z and W coordinates are set to zero.
     * 
     * @param x X-coordinate of the control point.
     * 
     * @return this
     */
    virtual Ptr<ICurve> AddControlPoint(float64 x) = 0;
    
    /*!
     * @brief  Adds a 2D control point to this curve.
     * 
     * The Z and W coordinates are set to zero.
     * 
     * @param x X-coordinate of the control point.
     * @param y Y-coordinate of the control point.
     * 
     * @return this
     */
    virtual Ptr<ICurve> AddControlPoint(float64 x, float64 y) = 0;
    
    /*!
     * @brief  Adds a 3D control point to this curve.
     * 
     * The W coordinate is set to zero.
     * 
     * @param x X-coordinate of the control point.
     * @param y Y-coordinate of the control point.
     * @param z Z-coordinate of the control point.
     * 
     * @return this
     */
    virtual Ptr<ICurve> AddControlPoint(float64 x, float64 y, float64 z) = 0;
    
    /*!
     * @brief  Adds a 4D control point to this curve.
     * 
     * @param x X-coordinate of the control point.
     * @param y Y-coordinate of the control point.
     * @param z Z-coordinate of the control point.
     * @param w W-coordinate of the control point.
     * 
     * @return this
     */
    virtual Ptr<ICurve> AddControlPoint(float64 x, float64 y, float64 z, float64 w) = 0;
    
    /*!
     * @brief  Removes all control points from this curve.
     * 
     * @return <b>[not-null]</b>  this
     */
    virtual Ptr<ICurve> ClearControlPoints() = 0;
    
    /*!
     * @brief  Computes a point along this curve.
     * 
     * The following fields of \e sample  are used:
     *   - CurveSample::PositionX
     *   - CurveSample::PositionY
     *   - CurveSample::PositionZ
     *   - CurveSample::PositionW
     * 
     * @param controlPointIndex The control point index.
     * @param sample The output CurveSample object.
     */
    virtual void ComputePoint(float64 controlPointIndex, CurveSample* sample) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<ICurve> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x77CB7892;
    
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
      if ((ptr = ISerializable::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
} } } } 

#endif
