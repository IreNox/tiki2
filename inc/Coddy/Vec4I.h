////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_MATH_VECTORS_VEC4I_H
#define CLODDY_CORE_MATH_VECTORS_VEC4I_H

#include "CodeX/System.h"

// Declare class ::Cloddy::Core::Math::Vectors::Vec4I.

namespace Cloddy { namespace Core { namespace Math { namespace Vectors
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  A four-dimensional vector with 32-bit integer precision.
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
  struct Vec4I : StructType
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  The zero vector.
     */
    static const Vec4I Zero;
    
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
        int32 W;

        /*!
         * @brief  X-coordinate of vector.
         */
        int32 X;

        /*!
         * @brief  Y-coordinate of vector.
         */
        int32 Y;

        /*!
         * @brief  Z-coordinate of vector.
         */
        int32 Z;
      };

      int32 buffer[4];
    }; 
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of Vec4I.
     * 
     * @param x X-coordinate of vector.
     * @param y Y-coordinate of vector.
     * @param z Z-coordinate of vector.
     * @param w W-coordinate of vector.
     */
    Vec4I(int32 x, int32 y, int32 z, int32 w);

    /*!
     * brief  Creates a new instance of Vec4I.
     *
     * @param members An array of four int32 (x/y/z/w).
     */
    Vec4I(int32* members);
    
    /*!
     * brief  Creates a new instance of Vec4I.
     */
    Vec4I();

    /*!
     * @brief Returns the internal buffer pointer.
     *
     * @returns The internal buffer pointer.
     */
    operator int32*() const
    {
      return (int32*)buffer;
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
    Vec4I Add(const Vec4I& v) const;
    
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
    Vec4I Add(int32 x, int32 y, int32 z, int32 w) const;
    
    /*!
     * @brief  Computes the dot product between this vector and the given one.
     * 
     * @param v The vector.
     * 
     * @return The resulting vector.
     */
    int32 Dot(const Vec4I& v) const;
    
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
    int32 Dot(int32 x, int32 y, int32 z, int32 w) const;
    
    /*!
     * @brief  Checks if this vector and the given one are equal.
     * 
     * @param v The vector.
     * 
     * @return \c true  if both vectors are equal,\c false  if they are not.
     */
    bool Equals(const Vec4I& v) const;
    
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
    bool Equals(int32 x, int32 y, int32 z, int32 w) const;
    
    /*!
     * @brief  Computes the component-wise maximum of this vector and the given one.
     * 
     * @param v The vector.
     * 
     * @return The resulting vector.
     */
    Vec4I Max(const Vec4I& v) const;
    
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
    Vec4I Max(int32 x, int32 y, int32 z, int32 w) const;
    
    /*!
     * @brief  Computes the component-wise minimum of this vector and the given one.
     * 
     * @param v The vector.
     * 
     * @return The resulting vector.
     */
    Vec4I Min(const Vec4I& v) const;
    
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
    Vec4I Min(int32 x, int32 y, int32 z, int32 w) const;
    
    /*!
     * @brief  Multiplies this vector with the given one.
     * 
     * @param v The vector.
     * 
     * @return The resulting vector.
     */
    Vec4I Mul(const Vec4I& v) const;
    
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
    Vec4I Mul(int32 x, int32 y, int32 z, int32 w) const;
    
    /*!
     * @brief  Multiplies this vector with the given scalar value.
     * 
     * @param v The scalar value.
     * 
     * @return The resulting vector.
     */
    Vec4I Mul(int32 v) const;
    
    /*!
     * @brief  Negates this vector.
     * 
     * @return The resulting vector.
     */
    Vec4I Neg() const;
    
    /*!
     * @brief  Performs a left bit shift on each component of this vector.
     * 
     * @param v The shift amount.
     * 
     * @return The resulting vector.
     */
    Vec4I ShiftLeft(int32 v) const;
    
    /*!
     * @brief  Performs a right bit shift on each component of this vector.
     * 
     * @param v The shift amount.
     * 
     * @return The resulting vector.
     */
    Vec4I ShiftRight(int32 v) const;
    
    /*!
     * @brief  Subtracts the given vector from this one.
     * 
     * @param v The vector.
     * 
     * @return The resulting vector.
     */
    Vec4I Sub(const Vec4I& v) const;
    
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
    Vec4I Sub(int32 x, int32 y, int32 z, int32 w) const;
    
    // ---------------------------------------------------------------------------------------------
    //  Copy constructor and copy assignment operator
    // ---------------------------------------------------------------------------------------------
  public:
    
    Vec4I(const Vec4I& other);
    
    Vec4I& operator=(const Vec4I& other);
  };
  
} } } } 

#endif
