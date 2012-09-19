////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_MESHVISITORS_IFRUSTUM_H
#define CLODDY_API_MESHVISITORS_IFRUSTUM_H

#include "CodeX/System.h"

// Forward declare referenced structures.

namespace Cloddy { namespace Core { namespace Math { namespace Vectors { struct Vec3D; } } } }

// Declare interface ::Cloddy::API::MeshVisitors::IFrustum.

namespace Cloddy { namespace API { namespace MeshVisitors
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced structures.
  
  using Cloddy::Core::Math::Vectors::Vec3D;
  
  /*!
   * @brief  Represents a frustum in terrain-space.
   */
  class NO_VTABLE IFrustum : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The number of frustum planes,in the range <c>[1..31]</c>.
     * 
     * @return <b>[1..31]</b>  The number of frustum planes.
     */
    virtual int32 GetPlaneCount() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Tests if the given sphere lies inside the frustum.
     * 
     * @param center Coordinates of sphere center.
     * @param radius Radius of sphere.
     * @param insideMask A bitmask indicating for which planes the sphere is already known to lie 
     * completely inside the planes inner half-space:for plane \c n  within 
     * <c>[0..PlaneCount-1]</c>,the corresponding bit is <c>2^n</c>.
     * 
     * @return The resulting inside mask (with <c>(1 &lt;&lt; PlaneCount)- 1</c> resp. 0x7FFFFFFF 
     * indicating that the sphere fully lies inside the frustum),\c -1  if the sphere lies outside 
     * the frustum.Any other value indicates that the sphere intersects with at least one frustum 
     * plane.
     */
    virtual int32 TestSphere(const Vec3D& center, float64 radius, int32 insideMask) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IFrustum> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x28D7B517;
    
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
