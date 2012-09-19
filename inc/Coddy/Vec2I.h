////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_MATH_VECTORS_VEC2I_H
#define CLODDY_CORE_MATH_VECTORS_VEC2I_H

#include "CodeX/System.h"

// Declare class ::Cloddy::Core::Math::Vectors::Vec2I.

namespace Cloddy { namespace Core { namespace Math { namespace Vectors
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  A two-dimensional vector with 32-bit integer precision.
   * 
   * <pre>
   *     /     \\
   *     |  X  |
   *     |  Y  |
   *     \\     /
   * </pre>
   */
  struct Vec2I : StructType
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  The zero vector.
     */
    static const Vec2I Zero;
    
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
        int32 X;

        /*!
         * @brief  Y-coordinate of vector.
         */
        int32 Y;
      };

      int32 buffer[2];
    }; 
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of Vec2I.
     * 
     * @param x X-coordinate of vector.
     * @param y Y-coordinate of vector.
     */
    Vec2I(int32 x, int32 y);

    /*!
     * brief  Creates a new instance of Vec2I.
     *
     * @param members An array of two int32 (x/y).
     */
    Vec2I(int32* members);
    
    /*!
     * brief  Creates a new instance of Vec2I.
     */
    Vec2I();

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
    Vec2I Add(const Vec2I& v) const;
    
    /*!
     * @brief  Adds this vector and the given one.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * 
     * @return The resulting vector.
     */
    Vec2I Add(int32 x, int32 y) const;
    
    /*!
     * @brief  Computes the Z-component of the cross product between this vector and the given one.
     * 
     * @param v The vector.
     * 
     * @return The Z-component of the cross product vector.
     */
    int32 Cross(const Vec2I& v) const;
    
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
    int32 Dot(const Vec2I& v) const;
    
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
    bool Equals(const Vec2I& v) const;
    
    /*!
     * @brief  Checks if this vector and the given one are equal.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * 
     * @return \c true  if both vectors are equal,\c false  if they are not.
     */
    bool Equals(int32 x, int32 y) const;
    
    /*!
     * @brief  Computes the component-wise maximum of this vector and the given one.
     * 
     * @param v The vector.
     * 
     * @return The resulting vector.
     */
    Vec2I Max(const Vec2I& v) const;
    
    /*!
     * @brief  Computes the component-wise maximum of this vector and the given one.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * 
     * @return The resulting vector.
     */
    Vec2I Max(int32 x, int32 y) const;
    
    /*!
     * @brief  Computes the component-wise minimum of this vector and the given one.
     * 
     * @param v The vector.
     * 
     * @return The resulting vector.
     */
    Vec2I Min(const Vec2I& v) const;
    
    /*!
     * @brief  Computes the component-wise minimum of this vector and the given one.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * 
     * @return The resulting vector.
     */
    Vec2I Min(int32 x, int32 y) const;
    
    /*!
     * @brief  Multiplies this vector with the given one.
     * 
     * @param v The vector.
     * 
     * @return The resulting vector.
     */
    Vec2I Mul(const Vec2I& v) const;
    
    /*!
     * @brief  Multiplies this vector with the given one.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * 
     * @return The resulting vector.
     */
    Vec2I Mul(int32 x, int32 y) const;
    
    /*!
     * @brief  Multiplies this vector with the given scalar value.
     * 
     * @param v The scalar value.
     * 
     * @return The resulting vector.
     */
    Vec2I Mul(int32 v) const;
    
    /*!
     * @brief  Negates this vector.
     * 
     * @return The resulting vector.
     */
    Vec2I Neg() const;
    
    /*!
     * @brief  Performs a left bit shift on each component of this vector.
     * 
     * @param v The shift amount.
     * 
     * @return The resulting vector.
     */
    Vec2I ShiftLeft(int32 v) const;
    
    /*!
     * @brief  Performs a right bit shift on each component of this vector.
     * 
     * @param v The shift amount.
     * 
     * @return The resulting vector.
     */
    Vec2I ShiftRight(int32 v) const;
    
    /*!
     * @brief  Subtracts the given vector from this one.
     * 
     * @param v The vector.
     * 
     * @return The resulting vector.
     */
    Vec2I Sub(const Vec2I& v) const;
    
    /*!
     * @brief  Subtracts the given vector from this one.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * 
     * @return The resulting vector.
     */
    Vec2I Sub(int32 x, int32 y) const;
    
    // ---------------------------------------------------------------------------------------------
    //  Copy constructor and copy assignment operator
    // ---------------------------------------------------------------------------------------------
  public:
    
    Vec2I(const Vec2I& other);
    
    Vec2I& operator=(const Vec2I& other);
  };
  
} } } } 

#endif
