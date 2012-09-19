////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_MATH_VECTORS_VEC2D_H
#define CLODDY_CORE_MATH_VECTORS_VEC2D_H

#include "CodeX/System.h"

// Include referenced structures.

#include "Cloddy/Vec3D.h"

// Declare class ::Cloddy::Core::Math::Vectors::Vec2D.

namespace Cloddy { namespace Core { namespace Math { namespace Vectors
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  A two-dimensional vector with 64-bit floating-point precision.
   * 
   * <pre>
   *     /     \\
   *     |  X  |
   *     |  Y  |
   *     \\     /
   * </pre>
   */
  struct Vec2D : StructType
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  The zero vector.
     */
    static const Vec2D Zero;
    
    /*!
     * @brief  Returns the length of this vector.
     * 
     * @return <b>[>=0]</b>  The vector length.
     */
    float64 GetLength() const;
    
    /*!
     * @brief  Returns the squared length of this vector.
     * 
     * @return <b>[>=0]</b>  The squared vector length.
     */
    float64 GetLengthSqr() const;
    
    union
    {
      struct
      {
        /*!
         * @brief  X-coordinate of vector.
         */
        float64 X;

        /*!
         * @brief  Y-coordinate of vector.
         */
        float64 Y;
      };

      float64 buffer[2];
    };  
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of Vec2D.
     * 
     * @param x X-coordinate of vector.
     * @param y Y-coordinate of vector.
     */
    Vec2D(float64 x, float64 y);

    /*!
     * brief  Creates a new instance of Vec2D.
     *
     * @param members An array of two float64 (x/y).
     */
    Vec2D(float64* members);
    
    /*!
     * brief  Creates a new instance of Vec2D.
     */
    Vec2D();

    // ---------------------------------------------------------------------------------------------
    // Public / Operators
    // ---------------------------------------------------------------------------------------------

    /*!
     * @brief Returns the internal buffer pointer.
     *
     * @returns The internal buffer pointer.
     */
    operator float64*() const
    {
      return (float64*)buffer;
    }
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Adds this vector and the given one.
     * 
     * @param v The vector.
     * 
     * @return The resulting vector.
     */
    Vec2D Add(const Vec2D& v) const;
    
    /*!
     * @brief  Adds this vector and the given one.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * 
     * @return The resulting vector.
     */
    Vec2D Add(float64 x, float64 y) const;
    
    /*!
     * @brief  Computes the barycentric coordinates of this vector in the given triangle.
     * 
     * @param a First vertex of triangle.
     * @param b Second vertex of triangle.
     * @param c Third vertex of triangle.
     * 
     * @return The barycentric coordinates of this vector,where Vec3D::X,Vec3D::Y and Vec3D::Z 
     * represent the weights for the triangle vertices \e a ,\e b  and \e c  (in this order).
     */
    Vec3D Barycentric(const Vec2D& a, const Vec2D& b, const Vec2D& c) const;
    
    /*!
     * @brief  Computes the Z-component of the cross product between this vector and the given one.
     * 
     * @param v The vector.
     * 
     * @return The Z-component of the cross product vector.
     */
    float64 Cross(const Vec2D& v) const;
    
    /*!
     * @brief  Computes the Z-component of the cross product between this vector and the given one.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * 
     * @return The Z-component of the cross product vector.
     */
    float64 Cross(float64 x, float64 y) const;
    
    /*!
     * @brief  Divides this vector by the given scalar value.
     * 
     * @param v The scalar value.
     * 
     * @return The resulting vector.
     */
    Vec2D Div(float64 v) const;
    
    /*!
     * @brief  Computes the dot product between this vector and the given one.
     * 
     * @param v The vector.
     * 
     * @return The resulting vector.
     */
    float64 Dot(const Vec2D& v) const;
    
    /*!
     * @brief  Computes the dot product between this vector and the given one.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * 
     * @return The resulting vector.
     */
    float64 Dot(float64 x, float64 y) const;
    
    /*!
     * @brief  Checks if this vector and the given one are equal.
     * 
     * @param v The vector.
     * 
     * @return \c true  if both vectors are equal,\c false  if they are not.
     */
    bool Equals(const Vec2D& v) const;
    
    /*!
     * @brief  Checks if this vector and the given one are equal.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * 
     * @return \c true  if both vectors are equal,\c false  if they are not.
     */
    bool Equals(float64 x, float64 y) const;
    
    /*!
     * @brief  Computes the component-wise maximum of this vector and the given one.
     * 
     * @param v The vector.
     * 
     * @return The resulting vector.
     */
    Vec2D Max(const Vec2D& v) const;
    
    /*!
     * @brief  Computes the component-wise maximum of this vector and the given one.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * 
     * @return The resulting vector.
     */
    Vec2D Max(float64 x, float64 y) const;
    
    /*!
     * @brief  Computes the component-wise minimum of this vector and the given one.
     * 
     * @param v The vector.
     * 
     * @return The resulting vector.
     */
    Vec2D Min(const Vec2D& v) const;
    
    /*!
     * @brief  Computes the component-wise minimum of this vector and the given one.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * 
     * @return The resulting vector.
     */
    Vec2D Min(float64 x, float64 y) const;
    
    /*!
     * @brief  Multiplies this vector with the given one.
     * 
     * @param v The vector.
     * 
     * @return The resulting vector.
     */
    Vec2D Mul(const Vec2D& v) const;
    
    /*!
     * @brief  Multiplies this vector with the given one.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * 
     * @return The resulting vector.
     */
    Vec2D Mul(float64 x, float64 y) const;
    
    /*!
     * @brief  Multiplies this vector with the given scalar value.
     * 
     * @param v The scalar value.
     * 
     * @return The resulting vector.
     */
    Vec2D Mul(float64 v) const;
    
    /*!
     * @brief  Negates this vector.
     * 
     * @return The resulting vector.
     */
    Vec2D Neg() const;
    
    /*!
     * @brief  Normalizes this vector to unit length.
     * 
     * @return The resulting vector.
     */
    Vec2D Norm() const;
    
    /*!
     * @brief  Subtracts the given vector from this one.
     * 
     * @param v The vector.
     * 
     * @return The resulting vector.
     */
    Vec2D Sub(const Vec2D& v) const;
    
    /*!
     * @brief  Subtracts the given vector from this one.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * 
     * @return The resulting vector.
     */
    Vec2D Sub(float64 x, float64 y) const;
    
    // ---------------------------------------------------------------------------------------------
    //  Copy constructor and copy assignment operator
    // ---------------------------------------------------------------------------------------------
  public:
    
    Vec2D(const Vec2D& other);
    
    Vec2D& operator=(const Vec2D& other);
  };
  
} } } } 

#endif
