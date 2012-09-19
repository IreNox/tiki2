////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_UTIL_PERSPECTIVEPROJECTION_H
#define CLODDY_API_UTIL_PERSPECTIVEPROJECTION_H

#include "CodeX/System.h"

// Declare class ::Cloddy::API::Util::PerspectiveProjection.

namespace Cloddy { namespace API { namespace Util
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  The PerspectiveProjection mimics a typical projection transformation as used in most 
   *         3D application.
   * 
   * Instances of this class are used to project terrain-space error values and bounding spheres to 
   * screen-space.
   */
  class PerspectiveProjection : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Field of view along the viewport pixels (#GetViewportSize),in degrees;defaults to 
     *         <c>90 degrees</c>.
     * 
     * @return <b>[>0]</b>  The field of view,in degrees.
     */
    float64 GetFieldOfView();
    
    /*!
     * @brief  Field of view along the viewport pixels (#GetViewportSize),in degrees;defaults to 
     *         <c>90 degrees</c>.
     * 
     * @param value <b>[>0]</b>  The field of view,in degrees.
     */
    void SetFieldOfView(float64 value);
    
    /*!
     * @brief  The focal length of the current projection.
     * 
     * @return The focal length.
     */
    float64 GetFocalLength();
    
    /*!
     * @brief  Size of the viewport (width or height),in pixels;defaults to \c 1024 .
     * 
     * @return <b>[>0]</b>  The viewport size,in pixels.
     */
    int32 GetViewportSize();
    
    /*!
     * @brief  Size of the viewport (width or height),in pixels;defaults to \c 1024 .
     * 
     * @param value <b>[>0]</b>  The viewport size,in pixels.
     */
    void SetViewportSize(int32 value);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new perspective projection with default values.
     */
    PerspectiveProjection();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Projects the given terrain-space error value into screen-space.
     * 
     * @param distanceToCameraSqr Squared distance from vertex to camera position,in terrain-space.
     * @param errorSqr Squared terrain-space error of vertex.
     * 
     * @return The squared projected error,in screen-space.
     */
    float64 ProjectErrorSqr(float64 distanceToCameraSqr, float64 errorSqr);
    
    /*!
     * @brief  Projects a sphere in terrain-space to screen-space.
     * 
     * @param distanceToCamera Distance from sphere center to camera,in terrain-space.
     * @param radius Radius of sphere,in terrain-space.
     * 
     * @return Radius of sphere in screen-space.
     */
    float64 ProjectSphere(float64 distanceToCamera, float64 radius);
    
    /*!
     * @brief  Projects the given screen-space error value back into terrain-space.
     * 
     * @param distanceToCameraSqr Squared distance from vertex to camera position,in terrain-space.
     * @param projectedErrorSqr The squared screen-space error value.
     * 
     * @return The squared terrain-space error value.
     */
    float64 UnprojectErrorSqr(float64 distanceToCameraSqr, float64 projectedErrorSqr);
    
    /*!
     * @brief  Projects the given screen-space error value <c>1.0</c> back into terrain-space.
     * 
     * @param distanceToCameraSqr Squared distance from vertex to camera position,in terrain-space.
     * 
     * @return The squared terrain-space error value.
     */
    float64 UnprojectErrorSqr(float64 distanceToCameraSqr);
    
    /*!
     * @brief  Projects the given sphere from screen-space back into terrain-space.
     * 
     * @param distanceToCamera Distance from sphere center to camera,in terrain-space.
     * @param projectedRadius Radius of sphere in screen-space.
     * 
     * @return Radius of sphere,in terrain-space.
     */
    float64 UnprojectSphere(float64 distanceToCamera, float64 projectedRadius);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Current field of view,in degrees.
     */
    float64 fieldOfView;
    
    /*!
     * @brief  The focal length of the current projection.
     */
    float64 focalLength;
    
    /*!
     * @brief  Precomputed value used in visibility test.
     */
    float64 ny;
    
    /*!
     * @brief  Reciprocal of #focalLength.
     */
    float64 rFocalLength;
    
    /*!
     * @brief  Reciprocal of #ny.
     */
    float64 rNy;
    
    /*!
     * @brief  Current viewport size,in pixels.
     */
    int32 viewportSize;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Computes #ny.
     */
    void ComputeNyAndFocalLength();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<PerspectiveProjection> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xA7F1FE81;
    
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
  
} } } 

#endif
