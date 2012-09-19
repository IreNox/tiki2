////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_VISIBILITYCRITERIA_IVIEWPORT_H
#define CLODDY_API_VISIBILITYCRITERIA_IVIEWPORT_H

#include "CodeX/System.h"

// Include referenced structures.

#include "Cloddy/Mat4D.h"

// Declare interface ::Cloddy::API::VisibilityCriteria::IViewport.

namespace Cloddy { namespace API { namespace VisibilityCriteria
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced structures.
  
  using Cloddy::Core::Math::Vectors::Mat4D;
  
  class NO_VTABLE IViewport : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The transformation matrix from terrain-space to world-space.
     * 
     * Settings this matrix will also update #GetTerrainMatrixInv.
     * 
     * The default value is Mat4D::Identity.
     * 
     * @return The transformation matrix.
     * 
     * @see #GetTerrainMatrixInv
     */
    virtual Mat4D GetTerrainMatrix() = 0;
    
    /*!
     * @brief  The transformation matrix from terrain-space to world-space.
     * 
     * Settings this matrix will also update #GetTerrainMatrixInv.
     * 
     * The default value is Mat4D::Identity.
     * 
     * @param value The transformation matrix.
     * 
     * @see #GetTerrainMatrixInv
     */
    virtual void SetTerrainMatrix(const Mat4D& value) = 0;
    
    /*!
     * @brief  The transformation matrix from world-space to terrain-space.
     * 
     * Settings this matrix will also update #GetTerrainMatrix.
     * 
     * The default value is Mat4D::Identity.
     * 
     * @return The transformation matrix.
     * 
     * @see #GetTerrainMatrix
     */
    virtual Mat4D GetTerrainMatrixInv() = 0;
    
    /*!
     * @brief  The transformation matrix from world-space to terrain-space.
     * 
     * Settings this matrix will also update #GetTerrainMatrix.
     * 
     * The default value is Mat4D::Identity.
     * 
     * @param value The transformation matrix.
     * 
     * @see #GetTerrainMatrix
     */
    virtual void SetTerrainMatrixInv(const Mat4D& value) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Projects the given terrain-space error value into screen-space.
     * 
     * @param distanceToCameraSqr Squared distance from vertex to camera position,in terrain-space.
     * @param errorSqr Squared terrain-space error of vertex.
     * 
     * @return The squared projected error,in screen-space.
     */
    virtual float64 ProjectErrorSqr(float64 distanceToCameraSqr, float64 errorSqr) = 0;
    
    /*!
     * @brief  Projects a sphere in terrain-space to screen-space.
     * 
     * @param distanceToCamera Distance from sphere center to camera,in terrain-space.
     * @param radius Radius of sphere,in terrain-space.
     * 
     * @return Radius of sphere in screen-space.
     */
    virtual float64 ProjectSphere(float64 distanceToCamera, float64 radius) = 0;
    
    /*!
     * @brief  Projects the given screen-space error value <c>1.0</c> back into terrain-space.
     * 
     * @param distanceToCameraSqr Squared distance from vertex to camera position,in terrain-space.
     * 
     * @return The squared terrain-space error value.
     */
    virtual float64 UnprojectErrorSqr(float64 distanceToCameraSqr) = 0;
    
    /*!
     * @brief  Projects the given sphere from screen-space back into terrain-space.
     * 
     * @param distanceToCamera Distance from sphere center to camera,in terrain-space.
     * @param projectedRadius Radius of sphere in screen-space.
     * 
     * @return Radius of sphere,in terrain-space.
     */
    virtual float64 UnprojectSphere(float64 distanceToCamera, float64 projectedRadius) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IViewport> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x21D14456;
    
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
