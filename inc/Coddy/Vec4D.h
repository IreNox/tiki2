////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_MATH_VECTORS_VEC4D_H
#define CLODDY_CORE_MATH_VECTORS_VEC4D_H

#include "CodeX/System.h"

// Declare class ::Cloddy::Core::Math::Vectors::Vec4D.

namespace Cloddy { namespace Core { namespace Math { namespace Vectors
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  A four-dimensional vector with 64-bit floating-point precision.
   * 
   * <pre>
   *     /     \\
   *     |  X  |
   *     |  Y  |
   *     |  Z  |
   *     |  W  |
   *     \\     /
   * </pre>
   */
  struct Vec4D : StructType
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  The zero vector.
     */
    static const Vec4D Zero;
    
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
         * @brief  W-coordinate of vector.
         */
        float64 W;

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

      float64 buffer[4];
    };  
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of Vec4D.
     * 
     * @param x X-coordinate of vector.
     * @param y Y-coordinate of vector.
     * @param z Z-coordinate of vector.
     * @param w W-coordinate of vector.
     */
    Vec4D(float64 x, float64 y, float64 z, float64 w);

    /*!
     * brief  Creates a new instance of Vec4D.
     *
     * @param members An array of four float64 (x/y/z/w).
     */
    Vec4D(float64* members);
    
    /*!
     * brief  Creates a new instance of Vec4D.
     */
    Vec4D();

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
    Vec4D Add(const Vec4D& v) const;
    
    /*!
     * @brief  Adds this vector and the given one.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * @param z Z-component of vector.
     * @param w W-component of vector.
     * 
     * @return The resulting vector.
     */
    Vec4D Add(float64 x, float64 y, float64 z, float64 w) const;
    
    /*!
     * @brief  Divides this vector by the given scalar value.
     * 
     * @param v The scalar value.
     * 
     * @return The resulting vector.
     */
    Vec4D Div(float64 v) const;
    
    /*!
     * @brief  Computes the dot product between this vector and the given one.
     * 
     * @param v The vector.
     * 
     * @return The resulting vector.
     */
    float64 Dot(const Vec4D& v) const;
    
    /*!
     * @brief  Computes the dot product between this vector and the given one.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * @param z Z-component of vector.
     * @param w W-component of vector.
     * 
     * @return The resulting vector.
     */
    float64 Dot(float64 x, float64 y, float64 z, float64 w) const;
    
    /*!
     * @brief  Checks if this vector and the given one are equal.
     * 
     * @param v The vector.
     * 
     * @return \c true  if both vectors are equal,\c false  if they are not.
     */
    bool Equals(const Vec4D& v) const;
    
    /*!
     * @brief  Checks if this vector and the given one are equal.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * @param z Z-component of vector.
     * @param w W-component of vector.
     * 
     * @return \c true  if both vectors are equal,\c false  if they are not.
     */
    bool Equals(float64 x, float64 y, float64 z, float64 w) const;
    
    /*!
     * @brief  Computes the component-wise maximum of this vector and the given one.
     * 
     * @param v The vector.
     * 
     * @return The resulting vector.
     */
    Vec4D Max(const Vec4D& v) const;
    
    /*!
     * @brief  Computes the component-wise maximum of this vector and the given one.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * @param z Z-component of vector.
     * @param w W-component of vector.
     * 
     * @return The resulting vector.
     */
    Vec4D Max(float64 x, float64 y, float64 z, float64 w) const;
    
    /*!
     * @brief  Computes the component-wise minimum of this vector and the given one.
     * 
     * @param v The vector.
     * 
     * @return The resulting vector.
     */
    Vec4D Min(const Vec4D& v) const;
    
    /*!
     * @brief  Computes the component-wise minimum of this vector and the given one.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * @param z Z-component of vector.
     * @param w W-component of vector.
     * 
     * @return The resulting vector.
     */
    Vec4D Min(float64 x, float64 y, float64 z, float64 w) const;
    
    /*!
     * @brief  Multiplies this vector with the given one.
     * 
     * @param v The vector.
     * 
     * @return The resulting vector.
     */
    Vec4D Mul(const Vec4D& v) const;
    
    /*!
     * @brief  Multiplies this vector with the given one.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * @param z Z-component of vector.
     * @param w W-component of vector.
     * 
     * @return The resulting vector.
     */
    Vec4D Mul(float64 x, float64 y, float64 z, float64 w) const;
    
    /*!
     * @brief  Multiplies this vector with the given scalar value.
     * 
     * @param v The scalar value.
     * 
     * @return The resulting vector.
     */
    Vec4D Mul(float64 v) const;
    
    /*!
     * @brief  Negates this vector.
     * 
     * @return The resulting vector.
     */
    Vec4D Neg() const;
    
    /*!
     * @brief  Normalizes this vector to unit length.
     * 
     * @return The resulting vector.
     */
    Vec4D Norm() const;
    
    /*!
     * @brief  Subtracts the given vector from this one.
     * 
     * @param v The vector.
     * 
     * @return The resulting vector.
     */
    Vec4D Sub(const Vec4D& v) const;
    
    /*!
     * @brief  Subtracts the given vector from this one.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * @param z Z-component of vector.
     * @param w W-component of vector.
     * 
     * @return The resulting vector.
     */
    Vec4D Sub(float64 x, float64 y, float64 z, float64 w) const;
    
    // ---------------------------------------------------------------------------------------------
    //  Copy constructor and copy assignment operator
    // ---------------------------------------------------------------------------------------------
  public:
    
    Vec4D(const Vec4D& other);
    
    Vec4D& operator=(const Vec4D& other);
  };
  
} } } } 

#endif
