////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_MATH_VECTORS_MAT4D_H
#define CLODDY_CORE_MATH_VECTORS_MAT4D_H

#include "CodeX/System.h"

// Include referenced structures.

#include "Cloddy/Vec3D.h"
#include "Cloddy/Vec4D.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace IO { namespace Serialization { template<class> class IStructSerializer; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace Math { namespace Vectors { class Mat4D_Serializer; } } } }

// Declare class ::Cloddy::Core::Math::Vectors::Mat4D.

namespace Cloddy { namespace Core { namespace Math { namespace Vectors
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::IO::Serialization::IStructSerializer;
  
  /*!
   * @brief  A 4x4 matrix with 64-bit floating-point precision.
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
  struct Mat4D : StructType
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  The identity matrix.
     */
    static const Mat4D Identity;
    
    /*!
     * @brief  The serialization helper object for values of Mat4D.
     */
    static const StaticPtr<IStructSerializer<Val<Mat4D> > > Serializer;
    
    /*!
     * @brief  The zero matrix.
     */
    static const Mat4D Zero;
    
    /*!
     * @brief  Returns the determinant of this matrix.
     * 
     * @return The determinant value.
     */
    float64 GetDeterminant() const;
    
    /*!
     * @brief  Returns the inverse of this matrix.
     * 
     * @return The inverse matrix.
     */
    Mat4D GetInverse() const;

    /*!
     * @brief  Matrix component in first row,first column.
     */
    float64 M11;
    
    /*!
     * @brief  Matrix component in first row,second column.
     */
    float64 M12;
    
    /*!
     * @brief  Matrix component in first row,third column.
     */
    float64 M13;
    
    /*!
     * @brief  Matrix component in first row,fourth column.
     */
    float64 M14;
    
    /*!
     * @brief  Matrix component in second row,first column.
     */
    float64 M21;
    
    /*!
     * @brief  Matrix component in second row,second column.
     */
    float64 M22;
    
    /*!
     * @brief  Matrix component in second row,third column.
     */
    float64 M23;
    
    /*!
     * @brief  Matrix component in second row,fourth column.
     */
    float64 M24;
    
    /*!
     * @brief  Matrix component in third row,first column.
     */
    float64 M31;
    
    /*!
     * @brief  Matrix component in third row,second column.
     */
    float64 M32;
    
    /*!
     * @brief  Matrix component in third row,third column.
     */
    float64 M33;
    
    /*!
     * @brief  Matrix component in third row,fourth column.
     */
    float64 M34;
    
    /*!
     * @brief  Matrix component in fourth row,first column.
     */
    float64 M41;
    
    /*!
     * @brief  Matrix component in fourth row,second column.
     */
    float64 M42;
    
    /*!
     * @brief  Matrix component in fourth row,third column.
     */
    float64 M43;
    
    /*!
     * @brief  Matrix component in fourth row,fourth column.
     */
    float64 M44;
    
    /*!
     * @brief  Returns the transpose of this matrix.
     * 
     * @return The transposed matrix.
     */
    Mat4D GetTranspose() const;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of Mat4D.
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
    Mat4D(float64 m11, float64 m12, float64 m13, float64 m14, float64 m21, float64 m22, float64 m23, float64 m24, float64 m31, float64 m32, float64 m33, float64 m34, float64 m41, float64 m42, float64 m43, float64 m44);
    
    /*!
     * brief  Creates a new instance of Mat4D.
     *
     * @param members A 4x4 array of float64, in row-major order.
     */
    Mat4D(float64* members);

    Mat4D();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    static Mat4D Rotate(const Vec3D& axis, float64 angle);
    
    static Mat4D Rotate(float64 x, float64 y, float64 z, float64 angle);
    
    /*!
     * @brief  Returns a rotation matrix (counter-clockwise around X-axis).
     * 
     * @param angle The rotation angle,in radians.
     * 
     * @return The resulting matrix.
     */
    static Mat4D RotateX(float64 angle);
    
    /*!
     * @brief  Returns a rotation matrix (counter-clockwise around Y-axis).
     * 
     * @param angle The rotation angle,in radians.
     * 
     * @return The resulting matrix.
     */
    static Mat4D RotateY(float64 angle);
    
    /*!
     * @brief  Returns a rotation matrix (counter-clockwise around Z-axis).
     * 
     * @param angle The rotation angle,in radians.
     * 
     * @return The resulting matrix.
     */
    static Mat4D RotateZ(float64 angle);
    
    /*!
     * @brief  Returns a scaling matrix.
     * 
     * @param f The scale factor.
     * 
     * @return The resulting matrix.
     */
    static Mat4D Scale(float64 f);
    
    /*!
     * @brief  Returns a scaling matrix.
     * 
     * @param f The scale factors.
     * 
     * @return The resulting matrix.
     */
    static Mat4D Scale(const Vec4D& f);
    
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
    static Mat4D Scale(float64 fx, float64 fy, float64 fz, float64 fw);
    
    /*!
     * @brief  Returns a translation matrix.
     * 
     * @param v The translation vector.
     * 
     * @return The translation matrix.
     */
    static Mat4D Translate(const Vec3D& v);
    
    /*!
     * @brief  Returns a translation matrix.
     * 
     * @param x X-component of translation vector.
     * @param y Y-component of translation vector.
     * @param z Z-component of translation vector.
     * 
     * @return The translation matrix.
     */
    static Mat4D Translate(float64 x, float64 y, float64 z);
    
    /*!
     * @brief  Multiplies this matrix (left-side)with the given one (right-side):
     *         <c>result =this *m</c>.
     * 
     * @param m The matrix.
     * 
     * @return The resulting matrix.
     */
    Mat4D Mul(const Mat4D& m) const;
    
    /*!
     * @brief  Multiplies this matrix (left-side)with the given 3D vector (right-side):
     *         <c>result =this *v</c>.
     * 
     * @param v The vector.
     * @param w The W-component to assume.
     * 
     * @return The resulting vector,scaled by 1/W.
     */
    Vec3D Mul3(const Vec3D& v, float64 w) const;
    
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
    Vec3D Mul3(float64 x, float64 y, float64 z, float64 w) const;
    
    /*!
     * @brief  Multiplies this matrix (left-side)with the given 4D vector (right-side):
     *         <c>result =this *v</c>.
     * 
     * @param v The vector.
     * 
     * @return The resulting vector.
     */
    Vec4D Mul4(const Vec4D& v) const;
    
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
    Vec4D Mul4(float64 x, float64 y, float64 z, float64 w) const;

    // ---------------------------------------------------------------------------------------------
    //  Copy constructor and copy assignment operator
    // ---------------------------------------------------------------------------------------------
  public:
    
    Mat4D(const Mat4D& other);
    
    Mat4D& operator=(const Mat4D& other);
    
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
