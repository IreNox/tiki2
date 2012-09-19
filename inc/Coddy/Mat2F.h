////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_MATH_VECTORS_MAT2F_H
#define CLODDY_CORE_MATH_VECTORS_MAT2F_H

#include "CodeX/System.h"

// Include referenced structures.

#include "Cloddy/Vec2F.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace IO { namespace Serialization { template<class> class IStructSerializer; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace Math { namespace Vectors { class Mat2F_Serializer; } } } }

// Declare class ::Cloddy::Core::Math::Vectors::Mat2F.

namespace Cloddy { namespace Core { namespace Math { namespace Vectors
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::IO::Serialization::IStructSerializer;
  
  /*!
   * @brief  A 2x2 matrix with 32-bit floating-point precision.
   * 
   * <pre>
   *     /            \
   *     |  M11  M12  |
   *     |  M21  M22  |
   *     \            /
   * </pre>
   */
  struct Mat2F : StructType
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  The identity matrix.
     */
    static const Mat2F Identity;
    
    /*!
     * @brief  The serialization helper object for values of Mat2F.
     */
    static const StaticPtr<IStructSerializer<Val<Mat2F> > > Serializer;
    
    /*!
     * @brief  The zero matrix.
     */
    static const Mat2F Zero;
    
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
    Mat2F GetInverse() const;
    
    /*!
     * @brief  Matrix component in first row,first column.
     */
    float32 M11;
    
    /*!
     * @brief  Matrix component in first row,second column.
     */
    float32 M12;
    
    /*!
     * @brief  Matrix component in second row,first column.
     */
    float32 M21;
    
    /*!
     * @brief  Matrix component in second row,second column.
     */
    float32 M22;
    
    /*!
     * @brief  Returns the transpose of this matrix.
     * 
     * @return The transposed matrix.
     */
    Mat2F GetTranspose() const;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of Mat2F.
     * 
     * @param m11 Matrix component in first row,first column.
     * @param m12 Matrix component in first row,second column.
     * @param m21  Matrix component in second row,first column.
     * @param m22 Matrix component in second row,second column.
     */
    Mat2F(float32 m11, float32 m12, float32 m21, float32 m22);

    /*!
      * brief  Creates a new instance of Mat2F.
      *
      * @param members A 2x2 array of float32, in row-major order.
      */
    Mat2F(float32* members);
    
    Mat2F();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Returns a rotation matrix (counter-clockwise around origin).
     * 
     * @param angle The rotation angle,in radians.
     * 
     * @return The resulting matrix.
     */
    static Mat2F Rotate(float32 angle);
    
    /*!
     * @brief  Returns a scaling matrix.
     * 
     * @param f The scale factor.
     * 
     * @return The resulting matrix.
     */
    static Mat2F Scale(float32 f);
    
    /*!
     * @brief  Returns a scaling matrix.
     * 
     * @param f The scale factors.
     * 
     * @return The resulting matrix.
     */
    static Mat2F Scale(const Vec2F& f);
    
    /*!
     * @brief  Returns a scaling matrix.
     * 
     * @param fx The scale factor along the X-axis.
     * @param fy The scale factor along the Y-axis.
     * 
     * @return The resulting matrix.
     */
    static Mat2F Scale(float32 fx, float32 fy);
    
    /*!
     * @brief  Multiplies this matrix (left-side)with the given one (right-side):
     *         <c>result =this *m</c>.
     * 
     * @param m The matrix.
     * 
     * @return The resulting matrix.
     */
    Mat2F Mul(const Mat2F& m) const;
    
    /*!
     * @brief  Multiplies this matrix (left-side)with the given vector (right-side):
     *         <c>result =this *v</c>.
     * 
     * @param v The vector.
     * 
     * @return The resulting vector.
     */
    Vec2F Mul(const Vec2F& v) const;
    
    // ---------------------------------------------------------------------------------------------
    //  Copy constructor and copy assignment operator
    // ---------------------------------------------------------------------------------------------
  public:
    
    Mat2F(const Mat2F& other);
    
    Mat2F& operator=(const Mat2F& other);
    
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
