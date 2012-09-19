////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_MATH_VECTORS_MAT4F_H
#define CLODDY_CORE_MATH_VECTORS_MAT4F_H

#include "CodeX/System.h"

// Include referenced structures.

#include "Cloddy/Vec3F.h"
#include "Cloddy/Vec4F.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace IO { namespace Serialization { template<class> class IStructSerializer; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace Math { namespace Vectors { class Mat4D_Serializer; } } } }

// Declare class ::Cloddy::Core::Math::Vectors::Mat4F.

namespace Cloddy { namespace Core { namespace Math { namespace Vectors
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::IO::Serialization::IStructSerializer;
  
  /*!
   * @brief  A 4x4 matrix with 32-bit floating-point precision.
   * 
   * <pre>
   *     /                      \
   *     |  M11  M12  M13  M14  |
   *     |  M21  M22  M23  M24  |
   *     |  M31  M32  M33  M34  |
   *     |  M41  M42  M43  M44  |
   *     \                      /
   * </pre>
   */
  struct Mat4F : StructType
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  The identity matrix.
     */
    static const Mat4F Identity;
    
    /*!
     * @brief  The serialization helper object for values of Mat4F.
     */
    static const StaticPtr<IStructSerializer<Val<Mat4F> > > Serializer;
    
    /*!
     * @brief  The zero matrix.
     */
    static const Mat4F Zero;
    
    /*!
     * @brief  Returns the determinant of this matrix.
     * 
     * @return The determinant value.
     */
    float32 GetDeterminant() const;
    
    /*!
     * @brief  Returns the inverse of this matrix.
     * 
     * @return The inverse matrix.
     */
    Mat4F GetInverse() const;

    /*!
     * @brief  Matrix component in first row,first column.
     */
    float32 M11;
    
    /*!
     * @brief  Matrix component in first row,second column.
     */
    float32 M12;
    
    /*!
     * @brief  Matrix component in first row,third column.
     */
    float32 M13;
    
    /*!
     * @brief  Matrix component in first row,fourth column.
     */
    float32 M14;
    
    /*!
     * @brief  Matrix component in second row,first column.
     */
    float32 M21;
    
    /*!
     * @brief  Matrix component in second row,second column.
     */
    float32 M22;
    
    /*!
     * @brief  Matrix component in second row,third column.
     */
    float32 M23;
    
    /*!
     * @brief  Matrix component in second row,fourth column.
     */
    float32 M24;
    
    /*!
     * @brief  Matrix component in third row,first column.
     */
    float32 M31;
    
    /*!
     * @brief  Matrix component in third row,second column.
     */
    float32 M32;
    
    /*!
     * @brief  Matrix component in third row,third column.
     */
    float32 M33;
    
    /*!
     * @brief  Matrix component in third row,fourth column.
     */
    float32 M34;
    
    /*!
     * @brief  Matrix component in fourth row,first column.
     */
    float32 M41;
    
    /*!
     * @brief  Matrix component in fourth row,second column.
     */
    float32 M42;
    
    /*!
     * @brief  Matrix component in fourth row,third column.
     */
    float32 M43;
    
    /*!
     * @brief  Matrix component in fourth row,fourth column.
     */
    float32 M44;
    
    /*!
     * @brief  Returns the transpose of this matrix.
     * 
     * @return The transposed matrix.
     */
    Mat4F GetTranspose() const;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of Mat4F.
     * 
     * @param m11 Matrix component in first row,first column.
     * @param m12 Matrix component in first row,second column.
     * @param m13 Matrix component in first row,third column.
     * @param m14 Matrix component in first row,fourth column.
     * @param m21 Matrix component in second row,first column.
     * @param m22 Matrix component in second row,second column.
     * @param m23 Matrix component in second row,third column.
     * @param m24 Matrix component in second row,fourth column.
     * @param m31 Matrix component in third row,first column.
     * @param m32 Matrix component in third row,second column.
     * @param m33 Matrix component in third row,third column.
     * @param m34 Matrix component in third row,fourth column.
     * @param m41 Matrix component in fourth row,first column.
     * @param m42 Matrix component in fourth row,second column.
     * @param m43 Matrix component in fourth row,third column.
     * @param m44 Matrix component in fourth row,fourth column.
     */
    Mat4F(float32 m11, float32 m12, float32 m13, float32 m14, float32 m21, float32 m22, float32 m23, float32 m24, float32 m31, float32 m32, float32 m33, float32 m34, float32 m41, float32 m42, float32 m43, float32 m44);
    
    /*!
     * brief  Creates a new instance of Mat4F.
     *
     * @param members A 4x4 array of float32, in row-major order.
     */
    Mat4F(float32* members);

    Mat4F();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    static Mat4F Rotate(const Vec3F& axis, float32 angle);
    
    static Mat4F Rotate(float32 x, float32 y, float32 z, float32 angle);
    
    /*!
     * @brief  Returns a rotation matrix (counter-clockwise around X-axis).
     * 
     * @param angle The rotation angle,in radians.
     * 
     * @return The resulting matrix.
     */
    static Mat4F RotateX(float32 angle);
    
    /*!
     * @brief  Returns a rotation matrix (counter-clockwise around Y-axis).
     * 
     * @param angle The rotation angle,in radians.
     * 
     * @return The resulting matrix.
     */
    static Mat4F RotateY(float32 angle);
    
    /*!
     * @brief  Returns a rotation matrix (counter-clockwise around Z-axis).
     * 
     * @param angle The rotation angle,in radians.
     * 
     * @return The resulting matrix.
     */
    static Mat4F RotateZ(float32 angle);
    
    /*!
     * @brief  Returns a scaling matrix.
     * 
     * @param f The scale factor.
     * 
     * @return The resulting matrix.
     */
    static Mat4F Scale(float32 f);
    
    /*!
     * @brief  Returns a scaling matrix.
     * 
     * @param f The scale factors.
     * 
     * @return The resulting matrix.
     */
    static Mat4F Scale(const Vec4F& f);
    
    /*!
     * @brief  Returns a scaling matrix.
     * 
     * @param fx The scale factor along the X-axis.
     * @param fy The scale factor along the Y-axis.
     * @param fz The scale factor along the Z-axis.
     * @param fw The scale factor along the W-axis.
     * 
     * @return The resulting matrix.
     */
    static Mat4F Scale(float32 fx, float32 fy, float32 fz, float32 fw);
    
    /*!
     * @brief  Returns a translation matrix.
     * 
     * @param v The translation vector.
     * 
     * @return The translation matrix.
     */
    static Mat4F Translate(const Vec3F& v);
    
    /*!
     * @brief  Returns a translation matrix.
     * 
     * @param x X-component of translation vector.
     * @param y Y-component of translation vector.
     * @param z Z-component of translation vector.
     * 
     * @return The translation matrix.
     */
    static Mat4F Translate(float32 x, float32 y, float32 z);
    
    /*!
     * @brief  Multiplies this matrix (left-side)with the given one (right-side):
     *         <c>result =this *m</c>.
     * 
     * @param m The matrix.
     * 
     * @return The resulting matrix.
     */
    Mat4F Mul(const Mat4F& m) const;
    
    /*!
     * @brief  Multiplies this matrix (left-side)with the given 3D vector (right-side):
     *         <c>result =this *v</c>.
     * 
     * @param v The vector.
     * @param w The W-component to assume.
     * 
     * @return The resulting vector,scaled by 1/W.
     */
    Vec3F Mul3(const Vec3F& v, float32 w) const;
    
    /*!
     * @brief  Multiplies this matrix (left-side)with the given 3D vector (right-side):
     *         <c>result =this *v</c>.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * @param z Z-component of vector.
     * @param w The W-component to assume.
     * 
     * @return The resulting vector,scaled by 1/W.
     */
    Vec3F Mul3(float32 x, float32 y, float32 z, float32 w) const;
    
    /*!
     * @brief  Multiplies this matrix (left-side)with the given 4D vector (right-side):
     *         <c>result =this *v</c>.
     * 
     * @param v The vector.
     * 
     * @return The resulting vector.
     */
    Vec4F Mul4(const Vec4F& v) const;
    
    /*!
     * @brief  Multiplies this matrix (left-side)with the given 4D vector (right-side):
     *         <c>result =this *v</c>.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * @param z Z-component of vector.
     * @param w W-component of vector.
     * 
     * @return The resulting vector.
     */
    Vec4F Mul4(float32 x, float32 y, float32 z, float32 w) const;

    // ---------------------------------------------------------------------------------------------
    //  Copy constructor and copy assignment operator
    // ---------------------------------------------------------------------------------------------
  public:
    
    Mat4F(const Mat4F& other);
    
    Mat4F& operator=(const Mat4F& other);
    
    // ---------------------------------------------------------------------------------------------
    // Static Initializer Functions
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief Static initializer function for field Serializer.
     */
    static Object* StaticInitializer_Serializer();
  };
  
} } } } 

#endif
