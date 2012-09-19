////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_MESHVISITORS_FRUSTUM_H
#define CLODDY_API_MESHVISITORS_FRUSTUM_H

#include "CodeX/System.h"

// Include referenced structures.

#include "Cloddy/Plane.h"
#include "Cloddy/Vec3D.h"

// Include referenced interfaces.

#include "Cloddy/IFrustum.h"

// Declare class ::Cloddy::API::MeshVisitors::Frustum.

namespace Cloddy { namespace API { namespace MeshVisitors
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced structures.
  
  using Cloddy::Core::Math::Geom::Plane;
  using Cloddy::Core::Math::Vectors::Vec3D;
  
  /*!
   * @brief  Default implementation of the IFrustum interface.
   */
  class Frustum : public virtual IFrustum
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Coordinate system origin.
     * 
     * The origin coordinates are subtracted from any input coordinates before the frustum culling 
     * checks are performed.
     * 
     * @return The coordinate system origin.
     */
    Vec3D GetOrigin();
    
    /*!
     * @brief  Coordinate system origin.
     * 
     * The origin coordinates are subtracted from any input coordinates before the frustum culling 
     * checks are performed.
     * 
     * @param value The coordinate system origin.
     */
    void SetOrigin(const Vec3D& value);
    
    virtual int32 GetPlaneCount();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new frustum.
     * 
     * @param planeCount <b>[1..31]</b>  The number of frustum planes.
     */
    Frustum(int32 planeCount);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Returns the \e index -th frustum plane.
     * 
     * @param index <b>[0..#GetPlaneCount-1]</b>  The frustum plane index.
     * 
     * @return The frustum plane.
     */
    Plane GetFrustumPlane(int32 index);
    
    /*!
     * @brief  Sets the \e index -th frustum plane.
     * 
     * @param index <b>[0..#GetPlaneCount-1]</b>  The frustum plane index.
     * @param plane The frustum plane.
     * 
     * @return <b>[not-null]</b>  this
     */
    Ptr<Frustum> SetFrustumPlane(int32 index, const Plane& plane);
    
    virtual int32 TestSphere(const Vec3D& center, float64 radius, int32 insideMask);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Coordinate system origin.
     */
    Vec3D origin;
    
    /*!
     * @brief  Number of frustum planes.
     */
    int32 planeCount;
    
    /*!
     * @brief  The frustum planes.
     */
    Array<Plane> planes;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<Frustum> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x4714E5C6;
    
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
      if ((ptr = IFrustum::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
