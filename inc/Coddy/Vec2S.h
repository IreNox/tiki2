////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_MATH_VECTORS_VEC2S_H
#define CLODDY_CORE_MATH_VECTORS_VEC2S_H

#include "CodeX/System.h"

// Declare class ::Cloddy::Core::Math::Vectors::Vec2S.

namespace Cloddy { namespace Core { namespace Math { namespace Vectors
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  A two-dimensional vector with 16-bit integer precision.
   * 
   * <pre>
   *     /     \\
   *     |  X  |
   *     |  Y  |
   *     \\     /
   * </pre>
   */
  struct Vec2S : StructType
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  The zero vector.
     */
    static const Vec2S Zero;
    
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
        int16 X;

        /*!
         * @brief  Y-coordinate of vector.
         */
        int16 Y;
      };

      int16 buffer[2];
    };
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of Vec2S.
     * 
     * @param x X-coordinate.
     * @param y Y-coordinate.
     */
    Vec2S(int32 x, int32 y);

    /*!
     * brief  Creates a new instance of Vec2S.
     *
     * @param members An array of two int32 (x/y).
     */
    Vec2S(int32* members);
    
    /*!
     * brief  Creates a new instance of Vec2S.
     */
    Vec2S();

    /*!
     * @brief Returns the internal buffer pointer.
     *
     * @returns The internal buffer pointer.
     */
    operator int16*() const
    {
      return (int16*)buffer;
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
    Vec2S Add(const Vec2S& v) const;
    
    /*!
     * @brief  Adds this vector and the given one.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * 
     * @return The resulting vector.
     */
    Vec2S Add(int16 x, int16 y) const;
    
    /*!
     * @brief  Computes the Z-component of the cross product between this vector and the given one.
     * 
     * @param v The vector.
     * 
     * @return The Z-component of the cross product vector.
     */
    int32 Cross(const Vec2S& v) const;
    
    /*!
     * @brief  Computes the Z-component of the cross product between this vector and the given one.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * 
     * @return The Z-component of the cross product vector.
     */
    int32 Cross(int32 x, int32 y) const;
    
    /*!
     * @brief  Computes the dot product between this vector and the given one.
     * 
     * @param v The vector.
     * 
     * @return The resulting vector.
     */
    int32 Dot(const Vec2S& v) const;
    
    /*!
     * @brief  Computes the dot product between this vector and the given one.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * 
     * @return The resulting vector.
     */
    int32 Dot(int32 x, int32 y) const;
    
    /*!
     * @brief  Checks if this vector and the given one are equal.
     * 
     * @param v The vector.
     * 
     * @return \c true  if both vectors are equal,\c false  if they are not.
     */
    bool Equals(const Vec2S& v) const;
    
    /*!
     * @brief  Checks if this vector and the given one are equal.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * 
     * @return \c true  if both vectors are equal,\c false  if they are not.
     */
    bool Equals(int16 x, int16 y) const;
    
    /*!
     * @brief  Computes the component-wise maximum of this vector and the given one.
     * 
     * @param v The vector.
     * 
     * @return The resulting vector.
     */
    Vec2S Max(const Vec2S& v) const;
    
    /*!
     * @brief  Computes the component-wise maximum of this vector and the given one.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * 
     * @return The resulting vector.
     */
    Vec2S Max(int16 x, int16 y) const;
    
    /*!
     * @brief  Computes the component-wise minimum of this vector and the given one.
     * 
     * @param v The vector.
     * 
     * @return The resulting vector.
     */
    Vec2S Min(const Vec2S& v) const;
    
    /*!
     * @brief  Computes the component-wise minimum of this vector and the given one.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * 
     * @return The resulting vector.
     */
    Vec2S Min(int16 x, int16 y) const;
    
    /*!
     * @brief  Multiplies this vector with the given one.
     * 
     * @param v The vector.
     * 
     * @return The resulting vector.
     */
    Vec2S Mul(const Vec2S& v) const;
    
    /*!
     * @brief  Multiplies this vector with the given one.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * 
     * @return The resulting vector.
     */
    Vec2S Mul(int16 x, int16 y) const;
    
    /*!
     * @brief  Multiplies this vector with the given scalar value.
     * 
     * @param v The scalar value.
     * 
     * @return The resulting vector.
     */
    Vec2S Mul(int16 v) const;
    
    /*!
     * @brief  Negates this vector.
     * 
     * @return The resulting vector.
     */
    Vec2S Neg() const;
    
    /*!
     * @brief  Performs a left bit shift on each component of this vector.
     * 
     * @param v The shift amount.
     * 
     * @return The resulting vector.
     */
    Vec2S ShiftLeft(int32 v) const;
    
    /*!
     * @brief  Performs a right bit shift on each component of this vector.
     * 
     * @param v The shift amount.
     * 
     * @return The resulting vector.
     */
    Vec2S ShiftRight(int32 v) const;
    
    /*!
     * @brief  Subtracts the given vector from this one.
     * 
     * @param v The vector.
     * 
     * @return The resulting vector.
     */
    Vec2S Sub(const Vec2S& v) const;
    
    /*!
     * @brief  Subtracts the given vector from this one.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * 
     * @return The resulting vector.
     */
    Vec2S Sub(int16 x, int16 y) const;
    
    // ---------------------------------------------------------------------------------------------
    //  Copy constructor and copy assignment operator
    // ---------------------------------------------------------------------------------------------
  public:
    
    Vec2S(const Vec2S& other);
    
    Vec2S& operator=(const Vec2S& other);
  };
  
} } } } 

#endif
