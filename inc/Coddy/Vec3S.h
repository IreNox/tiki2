////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_MATH_VECTORS_VEC3S_H
#define CLODDY_CORE_MATH_VECTORS_VEC3S_H

#include "CodeX/System.h"

// Declare class ::Cloddy::Core::Math::Vectors::Vec3S.

namespace Cloddy { namespace Core { namespace Math { namespace Vectors
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  A three-dimensional vector with 16-bit integer precision.
   * 
   * <pre>
   *     /     \\
   *     |  X  |
   *     |  Y  |
   *     |  Z  |
   *     \\     /
   * </pre>
   */
  struct Vec3S : StructType
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  The zero vector.
     */
    static const Vec3S Zero;
    
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

        /*!
         * @brief  Z-coordinate of vector.
         */
        int16 Z;
      };

      int16 buffer[3];
    };  
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of Vec3S.
     * 
     * @param x X-coordinate.
     * @param y Y-coordinate.
     * @param z Z-coordinate.
     */
    Vec3S(int32 x, int32 y, int32 z);

    /*!
     * brief  Creates a new instance of Vec3S.
     *
     * @param members An array of three int32 (x/y/z).
     */
    Vec3S(int32* members);
    
    /*!
     * brief  Creates a new instance of Vec3S.
     */
    Vec3S();

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
    Vec3S Add(const Vec3S& v) const;
    
    /*!
     * @brief  Adds this vector and the given one.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * @param z Z-component of vector.
     * 
     * @return The resulting vector.
     */
    Vec3S Add(int16 x, int16 y, int16 z) const;
    
    /*!
     * @brief  Computes the cross product between this vector and the given one.
     * 
     * @param v The vector.
     * 
     * @return The resulting vector.
     */
    Vec3S Cross(const Vec3S& v) const;
    
    /*!
     * @brief  Computes the cross product between this vector and the given one.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * @param z Z-component of vector.
     * 
     * @return The resulting vector.
     */
    Vec3S Cross(int16 x, int16 y, int16 z) const;
    
    /*!
     * @brief  Computes the dot product between this vector and the given one.
     * 
     * @param v The vector.
     * 
     * @return The resulting vector.
     */
    int32 Dot(const Vec3S& v) const;
    
    /*!
     * @brief  Computes the dot product between this vector and the given one.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * @param z Z-component of vector.
     * 
     * @return The resulting vector.
     */
    int32 Dot(int32 x, int32 y, int32 z) const;
    
    /*!
     * @brief  Checks if this vector and the given one are equal.
     * 
     * @param v The vector.
     * 
     * @return \c true  if both vectors are equal,\c false  if they are not.
     */
    bool Equals(const Vec3S& v) const;
    
    /*!
     * @brief  Checks if this vector and the given one are equal.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * @param z Z-component of vector.
     * 
     * @return \c true  if both vectors are equal,\c false  if they are not.
     */
    bool Equals(int16 x, int16 y, int16 z) const;
    
    /*!
     * @brief  Computes the component-wise maximum of this vector and the given one.
     * 
     * @param v The vector.
     * 
     * @return The resulting vector.
     */
    Vec3S Max(const Vec3S& v) const;
    
    /*!
     * @brief  Computes the component-wise maximum of this vector and the given one.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * @param z Z-component of vector.
     * 
     * @return The resulting vector.
     */
    Vec3S Max(int16 x, int16 y, int16 z) const;
    
    /*!
     * @brief  Computes the component-wise minimum of this vector and the given one.
     * 
     * @param v The vector.
     * 
     * @return The resulting vector.
     */
    Vec3S Min(const Vec3S& v) const;
    
    /*!
     * @brief  Computes the component-wise minimum of this vector and the given one.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * @param z Z-component of vector.
     * 
     * @return The resulting vector.
     */
    Vec3S Min(int16 x, int16 y, int16 z) const;
    
    /*!
     * @brief  Multiplies this vector with the given one.
     * 
     * @param v The vector.
     * 
     * @return The resulting vector.
     */
    Vec3S Mul(const Vec3S& v) const;
    
    /*!
     * @brief  Multiplies this vector with the given one.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * @param z Z-component of vector.
     * 
     * @return The resulting vector.
     */
    Vec3S Mul(int16 x, int16 y, int16 z) const;
    
    /*!
     * @brief  Multiplies this vector with the given scalar value.
     * 
     * @param v The scalar value.
     * 
     * @return The resulting vector.
     */
    Vec3S Mul(int16 v) const;
    
    /*!
     * @brief  Negates this vector.
     * 
     * @return The resulting vector.
     */
    Vec3S Neg() const;
    
    /*!
     * @brief  Performs a left bit shift on each component of this vector.
     * 
     * @param v The shift amount.
     * 
     * @return The resulting vector.
     */
    Vec3S ShiftLeft(int32 v) const;
    
    /*!
     * @brief  Performs a right bit shift on each component of this vector.
     * 
     * @param v The shift amount.
     * 
     * @return The resulting vector.
     */
    Vec3S ShiftRight(int32 v) const;
    
    /*!
     * @brief  Subtracts the given vector from this one.
     * 
     * @param v The vector.
     * 
     * @return The resulting vector.
     */
    Vec3S Sub(const Vec3S& v) const;
    
    /*!
     * @brief  Subtracts the given vector from this one.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * @param z Z-component of vector.
     * 
     * @return The resulting vector.
     */
    Vec3S Sub(int16 x, int16 y, int16 z) const;
    
    // ---------------------------------------------------------------------------------------------
    //  Copy constructor and copy assignment operator
    // ---------------------------------------------------------------------------------------------
  public:
    
    Vec3S(const Vec3S& other);
    
    Vec3S& operator=(const Vec3S& other);
  };
  
} } } } 

#endif
