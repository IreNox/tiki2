////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_MATH_VECTORS_VEC3D_H
#define CLODDY_CORE_MATH_VECTORS_VEC3D_H

#include "CodeX/System.h"

// Declare class ::Cloddy::Core::Math::Vectors::Vec3D.

namespace Cloddy { namespace Core { namespace Math { namespace Vectors
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  A three-dimensional vector with 64-bit floating-point precision.
   * 
   * <pre>
   *     /     \\
   *     |  X  |
   *     |  Y  |
   *     |  Z  |
   *     \\     /
   * </pre>
   */
  struct Vec3D : StructType
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  The zero vector.
     */
    static const Vec3D Zero;
    
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

        /*!
         * @brief  Z-coordinate of vector.
         */
        float64 Z;
      };

      float64 buffer[3];
    };  
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of Vec3D.
     * 
     * @param x X-coordinate of vector.
     * @param y Y-coordinate of vector.
     * @param z Z-coordinate of vector.
     */
    Vec3D(float64 x, float64 y, float64 z);

    /*!
     * brief  Creates a new instance of Vec3D.
     *
     * @param members An array of three float64 (x/y/z).
     */
    Vec3D(float64* members);
    
    /*!
     * brief  Creates a new instance of Vec3D.
     */
    Vec3D();

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
    Vec3D Add(const Vec3D& v) const;
    
    /*!
     * @brief  Adds this vector and the given one.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * @param z Z-component of vector.
     * 
     * @return The resulting vector.
     */
    Vec3D Add(float64 x, float64 y, float64 z) const;
    
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
    Vec3D Barycentric(const Vec3D& a, const Vec3D& b, const Vec3D& c) const;
    
    /*!
     * @brief  Computes the cross product between this vector and the given one.
     * 
     * @param v The vector.
     * 
     * @return The resulting vector.
     */
    Vec3D Cross(const Vec3D& v) const;
    
    /*!
     * @brief  Computes the cross product between this vector and the given one.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * @param z Z-component of vector.
     * 
     * @return The resulting vector.
     */
    Vec3D Cross(float64 x, float64 y, float64 z) const;
    
    /*!
     * @brief  Divides this vector by the given scalar value.
     * 
     * @param v The scalar value.
     * 
     * @return The resulting vector.
     */
    Vec3D Div(float64 v) const;
    
    /*!
     * @brief  Computes the dot product between this vector and the given one.
     * 
     * @param v The vector.
     * 
     * @return The resulting vector.
     */
    float64 Dot(const Vec3D& v) const;
    
    /*!
     * @brief  Computes the dot product between this vector and the given one.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * @param z Z-component of vector.
     * 
     * @return The resulting vector.
     */
    float64 Dot(float64 x, float64 y, float64 z) const;
    
    /*!
     * @brief  Checks if this vector and the given one are equal.
     * 
     * @param v The vector.
     * 
     * @return \c true  if both vectors are equal,\c false  if they are not.
     */
    bool Equals(const Vec3D& v) const;
    
    /*!
     * @brief  Checks if this vector and the given one are equal.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * @param z Z-component of vector.
     * 
     * @return \c true  if both vectors are equal,\c false  if they are not.
     */
    bool Equals(float64 x, float64 y, float64 z) const;
    
    /*!
     * @brief  Computes the component-wise maximum of this vector and the given one.
     * 
     * @param v The vector.
     * 
     * @return The resulting vector.
     */
    Vec3D Max(const Vec3D& v) const;
    
    /*!
     * @brief  Computes the component-wise maximum of this vector and the given one.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * @param z Z-component of vector.
     * 
     * @return The resulting vector.
     */
    Vec3D Max(float64 x, float64 y, float64 z) const;
    
    /*!
     * @brief  Computes the component-wise minimum of this vector and the given one.
     * 
     * @param v The vector.
     * 
     * @return The resulting vector.
     */
    Vec3D Min(const Vec3D& v) const;
    
    /*!
     * @brief  Computes the component-wise minimum of this vector and the given one.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * @param z Z-component of vector.
     * 
     * @return The resulting vector.
     */
    Vec3D Min(float64 x, float64 y, float64 z) const;
    
    /*!
     * @brief  Multiplies this vector with the given one.
     * 
     * @param v The vector.
     * 
     * @return The resulting vector.
     */
    Vec3D Mul(const Vec3D& v) const;
    
    /*!
     * @brief  Multiplies this vector with the given one.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * @param z Z-component of vector.
     * 
     * @return The resulting vector.
     */
    Vec3D Mul(float64 x, float64 y, float64 z) const;
    
    /*!
     * @brief  Multiplies this vector with the given scalar value.
     * 
     * @param v The scalar value.
     * 
     * @return The resulting vector.
     */
    Vec3D Mul(float64 v) const;
    
    /*!
     * @brief  Negates this vector.
     * 
     * @return The resulting vector.
     */
    Vec3D Neg() const;
    
    /*!
     * @brief  Normalizes this vector to unit length.
     * 
     * @return The resulting vector.
     */
    Vec3D Norm() const;
    
    /*!
     * @brief  Subtracts the given vector from this one.
     * 
     * @param v The vector.
     * 
     * @return The resulting vector.
     */
    Vec3D Sub(const Vec3D& v) const;
    
    /*!
     * @brief  Subtracts the given vector from this one.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * @param z Z-component of vector.
     * 
     * @return The resulting vector.
     */
    Vec3D Sub(float64 x, float64 y, float64 z) const;
    
    // ---------------------------------------------------------------------------------------------
    //  Copy constructor and copy assignment operator
    // ---------------------------------------------------------------------------------------------
  public:
    
    Vec3D(const Vec3D& other);
    
    Vec3D& operator=(const Vec3D& other);
  };
  
} } } } 

#endif
