////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_MATH_VECTORS_VEC3F_H
#define CLODDY_CORE_MATH_VECTORS_VEC3F_H

#include "CodeX/System.h"

// Declare class ::Cloddy::Core::Math::Vectors::Vec3F.

namespace Cloddy { namespace Core { namespace Math { namespace Vectors
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  A three-dimensional vector with 32-bit floating-point precision.
   * 
   * <pre>
   *     /     \\
   *     |  X  |
   *     |  Y  |
   *     |  Z  |
   *     \\     /
   * </pre>
   */
  struct Vec3F : StructType
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  The zero vector.
     */
    static const Vec3F Zero;
    
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

        /*!
         * @brief  Z-coordinate of vector.
         */
        float32 Z;
      };

      float32 buffer[3];
    };  
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of Vec3F.
     * 
     * @param x X-coordinate of vector.
     * @param y Y-coordinate of vector.
     * @param z Z-coordinate of vector.
     */
    Vec3F(float32 x, float32 y, float32 z);

    /*!
     * brief  Creates a new instance of Vec3F.
     *
     * @param members An array of three float32 (x/y/z).
     */
    Vec3F(float32* members);
    
    /*!
     * brief  Creates a new instance of Vec3F.
     */
    Vec3F();

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
    Vec3F Add(const Vec3F& v) const;
    
    /*!
     * @brief  Adds this vector and the given one.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * @param z Z-component of vector.
     * 
     * @return The resulting vector.
     */
    Vec3F Add(float32 x, float32 y, float32 z) const;
    
    /*!
     * @brief  Computes the barycentric coordinates of this vector in the given triangle.
     * 
     * The triangle vertices must be specified in counter-clockwise direction.
     * 
     * @param a First vertex of triangle.
     * @param b Second vertex of triangle.
     * @param c Third vertex of triangle.
     * 
     * @return The barycentric coordinates of this vector,where #X,#Y and #Z represent the weights 
     * for the triangle vertices \e a ,\e b  and \e c  (in this order).
     */
    Vec3F Barycentric(const Vec3F& a, const Vec3F& b, const Vec3F& c) const;
    
    /*!
     * @brief  Computes the cross product between this vector and the given one.
     * 
     * @param v The vector.
     * 
     * @return The resulting vector.
     */
    Vec3F Cross(const Vec3F& v) const;
    
    /*!
     * @brief  Computes the cross product between this vector and the given one.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * @param z Z-component of vector.
     * 
     * @return The resulting vector.
     */
    Vec3F Cross(float32 x, float32 y, float32 z) const;
    
    /*!
     * @brief  Divides this vector by the given scalar value.
     * 
     * @param v The scalar value.
     * 
     * @return The resulting vector.
     */
    Vec3F Div(float32 v) const;
    
    /*!
     * @brief  Computes the dot product between this vector and the given one.
     * 
     * @param v The vector.
     * 
     * @return The resulting vector.
     */
    float32 Dot(const Vec3F& v) const;
    
    /*!
     * @brief  Computes the dot product between this vector and the given one.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * @param z Z-component of vector.
     * 
     * @return The resulting vector.
     */
    float32 Dot(float32 x, float32 y, float32 z) const;
    
    /*!
     * @brief  Checks if this vector and the given one are equal.
     * 
     * @param v The vector.
     * 
     * @return \c true  if both vectors are equal,\c false  if they are not.
     */
    bool Equals(const Vec3F& v) const;
    
    /*!
     * @brief  Checks if this vector and the given one are equal.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * @param z Z-component of vector.
     * 
     * @return \c true  if both vectors are equal,\c false  if they are not.
     */
    bool Equals(float32 x, float32 y, float32 z) const;
    
    /*!
     * @brief  Computes the component-wise maximum of this vector and the given one.
     * 
     * @param v The vector.
     * 
     * @return The resulting vector.
     */
    Vec3F Max(const Vec3F& v) const;
    
    /*!
     * @brief  Computes the component-wise maximum of this vector and the given one.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * @param z Z-component of vector.
     * 
     * @return The resulting vector.
     */
    Vec3F Max(float32 x, float32 y, float32 z) const;
    
    /*!
     * @brief  Computes the component-wise minimum of this vector and the given one.
     * 
     * @param v The vector.
     * 
     * @return The resulting vector.
     */
    Vec3F Min(const Vec3F& v) const;
    
    /*!
     * @brief  Computes the component-wise minimum of this vector and the given one.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * @param z Z-component of vector.
     * 
     * @return The resulting vector.
     */
    Vec3F Min(float32 x, float32 y, float32 z) const;
    
    /*!
     * @brief  Multiplies this vector with the given one.
     * 
     * @param v The vector.
     * 
     * @return The resulting vector.
     */
    Vec3F Mul(const Vec3F& v) const;
    
    /*!
     * @brief  Multiplies this vector with the given one.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * @param z Z-component of vector.
     * 
     * @return The resulting vector.
     */
    Vec3F Mul(float32 x, float32 y, float32 z) const;
    
    /*!
     * @brief  Multiplies this vector with the given scalar value.
     * 
     * @param v The scalar value.
     * 
     * @return The resulting vector.
     */
    Vec3F Mul(float32 v) const;
    
    /*!
     * @brief  Negates this vector.
     * 
     * @return The resulting vector.
     */
    Vec3F Neg() const;
    
    /*!
     * @brief  Normalizes this vector to unit length.
     * 
     * @return The resulting vector.
     */
    Vec3F Norm() const;
    
    /*!
     * @brief  Subtracts the given vector from this one.
     * 
     * @param v The vector.
     * 
     * @return The resulting vector.
     */
    Vec3F Sub(const Vec3F& v) const;
    
    /*!
     * @brief  Subtracts the given vector from this one.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * @param z Z-component of vector.
     * 
     * @return The resulting vector.
     */
    Vec3F Sub(float32 x, float32 y, float32 z) const;
    
    // ---------------------------------------------------------------------------------------------
    //  Copy constructor and copy assignment operator
    // ---------------------------------------------------------------------------------------------
  public:
    
    Vec3F(const Vec3F& other);
    
    Vec3F& operator=(const Vec3F& other);
  };
  
} } } } 

#endif
