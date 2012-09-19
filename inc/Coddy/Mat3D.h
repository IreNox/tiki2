////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_MATH_VECTORS_MAT3D_H
#define CLODDY_CORE_MATH_VECTORS_MAT3D_H

#include "CodeX/System.h"

// Include referenced structures.

#include "Cloddy/Vec3D.h"

// Forward declare referenced structures.

namespace Cloddy { namespace Core { namespace Math { namespace Vectors { struct Vec2D; } } } }

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace IO { namespace Serialization { template<class> class IStructSerializer; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace Math { namespace Vectors { class Mat3D_Serializer; } } } }

// Declare class ::Cloddy::Core::Math::Vectors::Mat3D.

namespace Cloddy { namespace Core { namespace Math { namespace Vectors
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::IO::Serialization::IStructSerializer;
  
  /*!
   * @brief  A 3x3 matrix with 64-bit floating-point precision.
   * 
   * <pre>
   *     /                 \\
   *     |  M11  M12  M13  |
   *     |  M21  M22  M23  |
   *     |  M31  M32  M33  |
   *     \\                 /
   * </pre>
   */
  struct Mat3D : StructType
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  The identity matrix.
     */
    static const Mat3D Identity;
    
    /*!
     * @brief  The serialization helper object for values of Mat3D.
     */
    static const StaticPtr<IStructSerializer<Val<Mat3D> > > Serializer;
    
    /*!
     * @brief  The zero matrix.
     */
    static const Mat3D Zero;
    
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
    Mat3D GetInverse() const;
    
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
     * @brief  Returns the transpose of this matrix.
     * 
     * @return The transposed matrix.
     */
    Mat3D GetTranspose() const;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of Mat3D.
     * 
     * @param m11 Matrix component in first row,first column.
     * @param m12 Matrix component in first row,second column.
     * @param m13 Matrix component in first row,third column.
     * @param m21  Matrix component in second row,first column.
     * @param m22 Matrix component in second row,second column.
     * @param m23 Matrix component in second row,third column.
     * @param m31  Matrix component in third row,first column.
     * @param m32 Matrix component in third row,second column.
     * @param m33 Matrix component in third row,third column.
     */
    Mat3D(float64 m11, float64 m12, float64 m13, float64 m21, float64 m22, float64 m23, float64 m31, float64 m32, float64 m33);
    
    /*!
     * brief  Creates a new instance of Mat3D.
     *
     * @param members A 3x3 array of float64, in row-major order.
     */
    Mat3D(float64* members);

    Mat3D();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    static Mat3D Rotate(const Vec3D& axis, float64 angle);
    
    static Mat3D Rotate(float64 x, float64 y, float64 z, float64 angle);
    
    /*!
     * @brief  Returns a rotation matrix (counter-clockwise around X-axis).
     * 
     * @param angle The rotation angle,in radians.
     * 
     * @return The resulting matrix.
     */
    static Mat3D RotateX(float64 angle);
    
    /*!
     * @brief  Returns a rotation matrix (counter-clockwise around Y-axis).
     * 
     * @param angle The rotation angle,in radians.
     * 
     * @return The resulting matrix.
     */
    static Mat3D RotateY(float64 angle);
    
    /*!
     * @brief  Returns a rotation matrix (counter-clockwise around Z-axis).
     * 
     * @param angle The rotation angle,in radians.
     * 
     * @return The resulting matrix.
     */
    static Mat3D RotateZ(float64 angle);
    
    /*!
     * @brief  Returns a scaling matrix.
     * 
     * @param f The scale factor.
     * 
     * @return The resulting matrix.
     */
    static Mat3D Scale(float64 f);
    
    /*!
     * @brief  Returns a scaling matrix.
     * 
     * @param f The scale factors.
     * 
     * @return The resulting matrix.
     */
    static Mat3D Scale(const Vec3D& f);
    
    /*!
     * @brief  Returns a scaling matrix.
     * 
     * @param fx The scale factor along the X-axis.
     * @param fy The scale factor along the Y-axis.
     * @param fz The scale factor along the Z-axis.
     * 
     * @return The resulting matrix.
     */
    static Mat3D Scale(float64 fx, float64 fy, float64 fz);
    
    static Mat3D Translate(const Vec2D& v);
    
    static Mat3D Translate(float64 x, float64 y);
    
    /*!
     * @brief  Multiplies this matrix (left-side)with the given one (right-side):
     *         <c>result =this *m</c>.
     * 
     * @param m The matrix.
     * 
     * @return The resulting matrix.
     */
    Mat3D Mul(const Mat3D& m) const;
    
    /*!
     * @brief  Multiplies this matrix (left-side)with the given vector (right-side):
     *         <c>result =this *v</c>.
     * 
     * @param v The vector.
     * 
     * @return The resulting vector.
     */
    Vec3D Mul(const Vec3D& v) const;
    
    /*!
     * @brief  Multiplies this matrix (left-side)with the given vector (right-side):
     *         <c>result =this *v</c>.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * @param z Z-component of vector.
     * 
     * @return The resulting vector.
     */
    Vec3D Mul(float64 x, float64 y, float64 z) const;
    
    // ---------------------------------------------------------------------------------------------
    //  Copy constructor and copy assignment operator
    // ---------------------------------------------------------------------------------------------
  public:
    
    Mat3D(const Mat3D& other);
    
    Mat3D& operator=(const Mat3D& other);
    
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
