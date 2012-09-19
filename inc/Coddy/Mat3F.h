////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_MATH_VECTORS_MAT3F_H
#define CLODDY_CORE_MATH_VECTORS_MAT3F_H

#include "CodeX/System.h"

// Include referenced structures.

#include "Cloddy/Vec3F.h"

// Forward declare referenced structures.

namespace Cloddy { namespace Core { namespace Math { namespace Vectors { struct Vec2F; } } } }

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace IO { namespace Serialization { template<class> class IStructSerializer; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace Math { namespace Vectors { class Mat3F_Serializer; } } } }

// Declare class ::Cloddy::Core::Math::Vectors::Mat3F.

namespace Cloddy { namespace Core { namespace Math { namespace Vectors
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::IO::Serialization::IStructSerializer;
  
  /*!
   * @brief  A 3x3 matrix with 32-bit floating-point precision.
   * 
   * <pre>
   *     /                 \
   *     |  M11  M12  M13  |
   *     |  M21  M22  M23  |
   *     |  M31  M32  M33  |
   *     \                 /
   * </pre>
   */
  struct Mat3F : StructType
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  The identity matrix.
     */
    static const Mat3F Identity;
    
    /*!
     * @brief  The serialization helper object for values of Mat3F.
     */
    static const StaticPtr<IStructSerializer<Val<Mat3F> > > Serializer;
    
    /*!
     * @brief  The zero matrix.
     */
    static const Mat3F Zero;
    
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
    Mat3F GetInverse() const;
    
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
     * @brief  Returns the transpose of this matrix.
     * 
     * @return The transposed matrix.
     */
    Mat3F GetTranspose() const;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of Mat3F.
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
    Mat3F(float32 m11, float32 m12, float32 m13, float32 m21, float32 m22, float32 m23, float32 m31, float32 m32, float32 m33);
    
    /*!
     * brief  Creates a new instance of Mat3F.
     *
     * @param members A 3x3 array of float32, in row-major order.
     */
    Mat3F(float32* members);

    Mat3F();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    static Mat3F Rotate(const Vec3F& axis, float32 angle);
    
    static Mat3F Rotate(float32 x, float32 y, float32 z, float32 angle);
    
    /*!
     * @brief  Returns a rotation matrix (counter-clockwise around X-axis).
     * 
     * @param angle The rotation angle,in radians.
     * 
     * @return The resulting matrix.
     */
    static Mat3F RotateX(float32 angle);
    
    /*!
     * @brief  Returns a rotation matrix (counter-clockwise around Y-axis).
     * 
     * @param angle The rotation angle,in radians.
     * 
     * @return The resulting matrix.
     */
    static Mat3F RotateY(float32 angle);
    
    /*!
     * @brief  Returns a rotation matrix (counter-clockwise around Z-axis).
     * 
     * @param angle The rotation angle,in radians.
     * 
     * @return The resulting matrix.
     */
    static Mat3F RotateZ(float32 angle);
    
    /*!
     * @brief  Returns a scaling matrix.
     * 
     * @param f The scale factor.
     * 
     * @return The resulting matrix.
     */
    static Mat3F Scale(float32 f);
    
    /*!
     * @brief  Returns a scaling matrix.
     * 
     * @param f The scale factors.
     * 
     * @return The resulting matrix.
     */
    static Mat3F Scale(const Vec3F& f);
    
    /*!
     * @brief  Returns a scaling matrix.
     * 
     * @param fx The scale factor along the X-axis.
     * @param fy The scale factor along the Y-axis.
     * @param fz The scale factor along the Z-axis.
     * 
     * @return The resulting matrix.
     */
    static Mat3F Scale(float32 fx, float32 fy, float32 fz);
    
    static Mat3F Translate(const Vec2F& v);
    
    static Mat3F Translate(float32 x, float32 y);
    
    /*!
     * @brief  Multiplies this matrix (left-side)with the given one (right-side):
     *         <c>result =this *m</c>.
     * 
     * @param m The matrix.
     * 
     * @return The resulting matrix.
     */
    Mat3F Mul(const Mat3F& m) const;
    
    /*!
     * @brief  Multiplies this matrix (left-side)with the given vector (right-side):
     *         <c>result =this *v</c>.
     * 
     * @param v The vector.
     * 
     * @return The resulting vector.
     */
    Vec3F Mul(const Vec3F& v) const;
    
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
    Vec3F Mul(float32 x, float32 y, float32 z) const;
    
    // ---------------------------------------------------------------------------------------------
    //  Copy constructor and copy assignment operator
    // ---------------------------------------------------------------------------------------------
  public:
    
    Mat3F(const Mat3F& other);
    
    Mat3F& operator=(const Mat3F& other);
    
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
