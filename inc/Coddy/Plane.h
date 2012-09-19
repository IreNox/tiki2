////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_MATH_GEOM_PLANE_H
#define CLODDY_CORE_MATH_GEOM_PLANE_H

#include "CodeX/System.h"

// Include referenced structures.

#include "Cloddy/Vec3D.h"
#include "Cloddy/Vec4D.h"

// Declare class ::Cloddy::Core::Math::Geom::Plane.

namespace Cloddy { namespace Core { namespace Math { namespace Geom
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced structures.
  
  using Cloddy::Core::Math::Vectors::Vec3D;
  using Cloddy::Core::Math::Vectors::Vec4D;
  
  /*!
   * @brief  Represents a plane in 3D space.
   */
  struct Plane : StructType
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  The XY-plane,having the positive Z-axis as normal vector.
     */
    static const Plane XY;
    
    /*!
     * @brief  The XZ-plane,having the positive Y-axis as normal vector.
     */
    static const Plane XZ;
    
    /*!
     * @brief  The YZ-plane,having the positive X-axis as normal vector.
     */
    static const Plane YZ;
    
    /*!
     * @brief  Returns the plane coefficients.
     * 
     * This value refers to the general plane equation:
     * <pre>
     *     a*x + b*y + c*z + d = 0
     * </pre>
     * where \c a ,\c b ,\c c  and \c d  are returned as the Vec4D::X,Vec4D::Y,Vec4D::Z 
     * and Vec4D::W components.
     * 
     * @return The coefficients vector.
     */
    Vec4D GetCoefficients() const;
    
    /*!
     * @brief  Distance from plane to coordinate origin.
     * 
     * This value refers to the Hessian Normal Form:
     * <pre>
     *     normal * X = -distance
     * </pre>
     * where 
     * 
     * @return The distance value.
     */
    float64 GetDistanceToOrigin() const;
    
    /*!
     * @brief  Unit-length plane normal vector.
     * 
     * This value refers to the Hessian Normal Form:
     * <pre>
     *     normal * X = -distance
     * </pre>
     * where 
     * 
     * @return The unit normal vector.
     */
    Vec3D GetNormal() const;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of Plane.
     * 
     * The plane is computed using the following formula:
     * <pre>
     *     a*x + b*y + c*z + d = 0
     * </pre>
     * 
     * @param a First plane coefficient.
     * @param b Second plane coefficient.
     * @param c Third plane coefficient.
     * @param d Fourth plane coefficient.
     * 
     * @return The plane.
     */
    static Plane FromEquation(float64 a, float64 b, float64 c, float64 d);
    
    /*!
     * @brief  Creates a new instance of Plane.
     * 
     * The plane is computed using the following formula:
     * <pre>
     *     normal * X = -distance
     * </pre>
     * where 
     * 
     * @param normal The plane normal vector.
     * @param distance Euclidean distance from plane to origin.
     * 
     * @return The plane
     */
    static Plane FromHessian(const Vec3D& normal, float64 distance);
    
    /*!
     * @brief  Creates a new instance of Plane.
     * 
     * The plane is computed from the triangle which the given vertices span (assuming 
     * counter-clockwise vertex orientation and a right-handed coordinate system).
     * 
     * @param a First triangle vertex.
     * @param b Second triangle vertex.
     * @param c Third triangle vertex.
     * 
     * @return The plane.
     */
    static Plane FromPoints(const Vec3D& a, const Vec3D& b, const Vec3D& c);
    
    /*!
     * @brief  Computes the distance of the given point to the plane.
     * 
     * @param point The point.
     * 
     * @return The distance to this plane.
     */
    float64 DistanceToPoint(const Vec3D& point) const;
    
    /*!
     * @brief  Computes the distance of the given point to the plane.
     * 
     * @param x X-coordinate of point.
     * @param y Y-coordinate of point.
     * @param z Z-coordinate of point.
     * 
     * @return The distance to this plane.
     */
    float64 DistanceToPoint(float64 x, float64 y, float64 z) const;
    
    /*!
     * @brief  Flips the normal vector of this plane.
     * 
     * @return The resulting plane.
     */
    Plane Flip() const;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Distance to plane along normal vector.
     */
    float64 distanceToOrigin;
    
    /*!
     * @brief  Plane normal vector pointing towards positive halfspace.
     */
    Vec3D normal;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of Plane.
     * 
     * @param normal The plane normal.
     * @param distanceToOrigin Negative distance to origin.
     */
    Plane(const Vec3D& normal, float64 distanceToOrigin);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
  public:
    
    Plane();
    
    // ---------------------------------------------------------------------------------------------
    //  Copy constructor and copy assignment operator
    // ---------------------------------------------------------------------------------------------
  public:
    
    Plane(const Plane& other);
    
    Plane& operator=(const Plane& other);
  };
  
} } } } 

#endif
