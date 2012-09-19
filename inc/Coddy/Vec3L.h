////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_MATH_VECTORS_VEC3L_H
#define CLODDY_CORE_MATH_VECTORS_VEC3L_H

#include "CodeX/System.h"

// Declare class ::Cloddy::Core::Math::Vectors::Vec3L.

namespace Cloddy { namespace Core { namespace Math { namespace Vectors
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  A three-dimensional vector with 64-bit integer precision.
   * 
   * <pre>
   *     /     \\
   *     |  X  |
   *     |  Y  |
   *     |  Z  |
   *     \\     /
   * </pre>
   */
  struct Vec3L : StructType
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  The zero vector.
     */
    static const Vec3L Zero;
    
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
        int64 X;

        /*!
         * @brief  Y-coordinate of vector.
         */
        int64 Y;

        /*!
         * @brief  Z-coordinate of vector.
         */
        int64 Z;
      };

      int64 buffer[3];
    };  
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of Vec3L.
     * 
     * @param x X-coordinate of vector.
     * @param y Y-coordinate of vector.
     * @param z Z-coordinate of vector.
     */
    Vec3L(int64 x, int64 y, int64 z);

    /*!
     * brief  Creates a new instance of Vec3L.
     *
     * @param members An array of three int64 (x/y/z).
     */
    Vec3L(int64* members);
    
    /*!
     * brief  Creates a new instance of Vec3L.
     */
    Vec3L();

    /*!
     * @brief Returns the internal buffer pointer.
     *
     * @returns The internal buffer pointer.
     */
    operator int64*() const
    {
      return (int64*)buffer;
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
    Vec3L Add(const Vec3L& v) const;
    
    /*!
     * @brief  Adds this vector and the given one.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * @param z Z-component of vector.
     * 
     * @return The resulting vector.
     */
    Vec3L Add(int64 x, int64 y, int64 z) const;
    
    /*!
     * @brief  Computes the cross product between this vector and the given one.
     * 
     * @param v The vector.
     * 
     * @return The resulting vector.
     */
    Vec3L Cross(const Vec3L& v) const;
    
    /*!
     * @brief  Computes the cross product between this vector and the given one.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * @param z Z-component of vector.
     * 
     * @return The resulting vector.
     */
    Vec3L Cross(int64 x, int64 y, int64 z) const;
    
    /*!
     * @brief  Computes the dot product between this vector and the given one.
     * 
     * @param v The vector.
     * 
     * @return The resulting vector.
     */
    int64 Dot(const Vec3L& v) const;
    
    /*!
     * @brief  Computes the dot product between this vector and the given one.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * @param z Z-component of vector.
     * 
     * @return The resulting vector.
     */
    int64 Dot(int64 x, int64 y, int64 z) const;
    
    /*!
     * @brief  Checks if this vector and the given one are equal.
     * 
     * @param v The vector.
     * 
     * @return \c true  if both vectors are equal,\c false  if they are not.
     */
    bool Equals(const Vec3L& v) const;
    
    /*!
     * @brief  Checks if this vector and the given one are equal.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * @param z Z-component of vector.
     * 
     * @return \c true  if both vectors are equal,\c false  if they are not.
     */
    bool Equals(int64 x, int64 y, int64 z) const;
    
    /*!
     * @brief  Computes the component-wise maximum of this vector and the given one.
     * 
     * @param v The vector.
     * 
     * @return The resulting vector.
     */
    Vec3L Max(const Vec3L& v) const;
    
    /*!
     * @brief  Computes the component-wise maximum of this vector and the given one.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * @param z Z-component of vector.
     * 
     * @return The resulting vector.
     */
    Vec3L Max(int64 x, int64 y, int64 z) const;
    
    /*!
     * @brief  Computes the component-wise minimum of this vector and the given one.
     * 
     * @param v The vector.
     * 
     * @return The resulting vector.
     */
    Vec3L Min(const Vec3L& v) const;
    
    /*!
     * @brief  Computes the component-wise minimum of this vector and the given one.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * @param z Z-component of vector.
     * 
     * @return The resulting vector.
     */
    Vec3L Min(int64 x, int64 y, int64 z) const;
    
    /*!
     * @brief  Multiplies this vector with the given one.
     * 
     * @param v The vector.
     * 
     * @return The resulting vector.
     */
    Vec3L Mul(const Vec3L& v) const;
    
    /*!
     * @brief  Multiplies this vector with the given one.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * @param z Z-component of vector.
     * 
     * @return The resulting vector.
     */
    Vec3L Mul(int64 x, int64 y, int64 z) const;
    
    /*!
     * @brief  Multiplies this vector with the given scalar value.
     * 
     * @param v The scalar value.
     * 
     * @return The resulting vector.
     */
    Vec3L Mul(int64 v) const;
    
    /*!
     * @brief  Negates this vector.
     * 
     * @return The resulting vector.
     */
    Vec3L Neg() const;
    
    /*!
     * @brief  Performs a left bit shift on each component of this vector.
     * 
     * @param v The shift amount.
     * 
     * @return The resulting vector.
     */
    Vec3L ShiftLeft(int32 v) const;
    
    /*!
     * @brief  Performs a right bit shift on each component of this vector.
     * 
     * @param v The shift amount.
     * 
     * @return The resulting vector.
     */
    Vec3L ShiftRight(int32 v) const;
    
    /*!
     * @brief  Subtracts the given vector from this one.
     * 
     * @param v The vector.
     * 
     * @return The resulting vector.
     */
    Vec3L Sub(const Vec3L& v) const;
    
    /*!
     * @brief  Subtracts the given vector from this one.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * @param z Z-component of vector.
     * 
     * @return The resulting vector.
     */
    Vec3L Sub(int64 x, int64 y, int64 z) const;
    
    // ---------------------------------------------------------------------------------------------
    //  Copy constructor and copy assignment operator
    // ---------------------------------------------------------------------------------------------
  public:
    
    Vec3L(const Vec3L& other);
    
    Vec3L& operator=(const Vec3L& other);
  };
  
} } } } 

#endif
