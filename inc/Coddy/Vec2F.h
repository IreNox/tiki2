////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_MATH_VECTORS_VEC2F_H
#define CLODDY_CORE_MATH_VECTORS_VEC2F_H

#include "CodeX/System.h"

// Include referenced structures.

#include "Cloddy/Vec3F.h"

// Declare class ::Cloddy::Core::Math::Vectors::Vec2F.

namespace Cloddy { namespace Core { namespace Math { namespace Vectors
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  A two-dimensional vector with 32-bit floating-point precision.
   * 
   * <pre>
   *     /     \\
   *     |  X  |
   *     |  Y  |
   *     \\     /
   * </pre>
   */
  struct Vec2F : StructType
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  The zero vector.
     */
    static const Vec2F Zero;
    
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
        float32 X;

        /*!
         * @brief  Y-coordinate of vector.
         */
        float32 Y;
      };

      float32 buffer[2];
    }; 
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of Vec2F.
     * 
     * @param x X-coordinate of vector.
     * @param y Y-coordinate of vector.
     */
    Vec2F(float32 x, float32 y);

    /*!
     * brief  Creates a new instance of Vec2F.
     *
     * @param members An array of two float32 (x/y).
     */
    Vec2F(float32* members);
    
    /*!
     * brief  Creates a new instance of Vec2F.
     */
    Vec2F();

    /*!
     * @brief Returns the internal buffer pointer.
     *
     * @returns The internal buffer pointer.
     */
    operator float32*() const
    {
      return (float32*)buffer;
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
    Vec2F Add(const Vec2F& v) const;
    
    /*!
     * @brief  Adds this vector and the given one.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * 
     * @return The resulting vector.
     */
    Vec2F Add(float32 x, float32 y) const;
    
    /*!
     * @brief  Computes the barycentric coordinates of this vector in the given triangle.
     * 
     * @param a First vertex of triangle.
     * @param b Second vertex of triangle.
     * @param c Third vertex of triangle.
     * 
     * @return The barycentric coordinates of this vector,where Vec3F::X,Vec3F::Y and Vec3F::Z 
     * represent the weights for the triangle vertices \e a ,\e b  and \e c  (in this order).
     */
    Vec3F Barycentric(const Vec2F& a, const Vec2F& b, const Vec2F& c) const;
    
    /*!
     * @brief  Computes the Z-component of the cross product between this vector and the given one.
     * 
     * @param v The vector.
     * 
     * @return The Z-component of the cross product vector.
     */
    float32 Cross(const Vec2F& v) const;
    
    /*!
     * @brief  Computes the Z-component of the cross product between this vector and the given one.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * 
     * @return The Z-component of the cross product vector.
     */
    float32 Cross(float32 x, float32 y) const;
    
    /*!
     * @brief  Divides this vector by the given scalar value.
     * 
     * @param v The scalar value.
     * 
     * @return The resulting vector.
     */
    Vec2F Div(float32 v) const;
    
    /*!
     * @brief  Computes the dot product between this vector and the given one.
     * 
     * @param v The vector.
     * 
     * @return The resulting vector.
     */
    float32 Dot(const Vec2F& v) const;
    
    /*!
     * @brief  Computes the dot product between this vector and the given one.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * 
     * @return The resulting vector.
     */
    float32 Dot(float32 x, float32 y) const;
    
    /*!
     * @brief  Checks if this vector and the given one are equal.
     * 
     * @param v The vector.
     * 
     * @return \c true  if both vectors are equal,\c false  if they are not.
     */
    bool Equals(const Vec2F& v) const;
    
    /*!
     * @brief  Checks if this vector and the given one are equal.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * 
     * @return \c true  if both vectors are equal,\c false  if they are not.
     */
    bool Equals(float32 x, float32 y) const;
    
    /*!
     * @brief  Computes the component-wise maximum of this vector and the given one.
     * 
     * @param v The vector.
     * 
     * @return The resulting vector.
     */
    Vec2F Max(const Vec2F& v) const;
    
    /*!
     * @brief  Computes the component-wise maximum of this vector and the given one.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * 
     * @return The resulting vector.
     */
    Vec2F Max(float32 x, float32 y) const;
    
    /*!
     * @brief  Computes the component-wise minimum of this vector and the given one.
     * 
     * @param v The vector.
     * 
     * @return The resulting vector.
     */
    Vec2F Min(const Vec2F& v) const;
    
    /*!
     * @brief  Computes the component-wise minimum of this vector and the given one.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * 
     * @return The resulting vector.
     */
    Vec2F Min(float32 x, float32 y) const;
    
    /*!
     * @brief  Multiplies this vector with the given one.
     * 
     * @param v The vector.
     * 
     * @return The resulting vector.
     */
    Vec2F Mul(const Vec2F& v) const;
    
    /*!
     * @brief  Multiplies this vector with the given one.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * 
     * @return The resulting vector.
     */
    Vec2F Mul(float32 x, float32 y) const;
    
    /*!
     * @brief  Multiplies this vector with the given scalar value.
     * 
     * @param v The scalar value.
     * 
     * @return The resulting vector.
     */
    Vec2F Mul(float32 v) const;
    
    /*!
     * @brief  Negates this vector.
     * 
     * @return The resulting vector.
     */
    Vec2F Neg() const;
    
    /*!
     * @brief  Normalizes this vector to unit length.
     * 
     * @return The resulting vector.
     */
    Vec2F Norm() const;
    
    /*!
     * @brief  Subtracts the given vector from this one.
     * 
     * @param v The vector.
     * 
     * @return The resulting vector.
     */
    Vec2F Sub(const Vec2F& v) const;
    
    /*!
     * @brief  Subtracts the given vector from this one.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * 
     * @return The resulting vector.
     */
    Vec2F Sub(float32 x, float32 y) const;
    
    // ---------------------------------------------------------------------------------------------
    //  Copy constructor and copy assignment operator
    // ---------------------------------------------------------------------------------------------
  public:
    
    Vec2F(const Vec2F& other);
    
    Vec2F& operator=(const Vec2F& other);
  };
  
} } } } 

#endif
