////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_MATH_VECTORS_MAT2D_H
#define CLODDY_CORE_MATH_VECTORS_MAT2D_H

#include "CodeX/System.h"

// Include referenced structures.

#include "Cloddy/Vec2D.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace IO { namespace Serialization { template<class> class IStructSerializer; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace Math { namespace Vectors { class Mat2D_Serializer; } } } }

// Declare class ::Cloddy::Core::Math::Vectors::Mat2D.

namespace Cloddy { namespace Core { namespace Math { namespace Vectors
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::IO::Serialization::IStructSerializer;
  
  /*!
   * @brief  A 2x2 matrix with 64-bit floating-point precision.
   * 
   * <pre>
   *     /            \
   *     |  M11  M12  |
   *     |  M21  M22  |
   *     \            /
   * </pre>
   */
  struct Mat2D : StructType
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  The identity matrix.
     */
    static const Mat2D Identity;
    
    /*!
     * @brief  The serialization helper object for values of Mat2D.
     */
    static const StaticPtr<IStructSerializer<Val<Mat2D> > > Serializer;
    
    /*!
     * @brief  The zero matrix.
     */
    static const Mat2D Zero;
    
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
    Mat2D GetInverse() const;
    
    /*!
     * @brief  Matrix component in first row,first column.
     */
    float64 M11;
    
    /*!
     * @brief  Matrix component in first row,second column.
     */
    float64 M12;
    
    /*!
     * @brief  Matrix component in second row,first column.
     */
    float64 M21;
    
    /*!
     * @brief  Matrix component in second row,second column.
     */
    float64 M22;
    
    /*!
     * @brief  Returns the transpose of this matrix.
     * 
     * @return The transposed matrix.
     */
    Mat2D GetTranspose() const;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of Mat2D.
     * 
     * @param m11 Matrix component in first row,first column.
     * @param m12 Matrix component in first row,second column.
     * @param m21  Matrix component in second row,first column.
     * @param m22 Matrix component in second row,second column.
     */
    Mat2D(float64 m11, float64 m12, float64 m21, float64 m22);

    /*!
      * brief  Creates a new instance of Mat2D.
      *
      * @param members A 2x2 array of float64, in row-major order.
      */
    Mat2D(float64* members);
    
    Mat2D();
    
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
    static Mat2D Rotate(float64 angle);
    
    /*!
     * @brief  Returns a scaling matrix.
     * 
     * @param f The scale factor.
     * 
     * @return The resulting matrix.
     */
    static Mat2D Scale(float64 f);
    
    /*!
     * @brief  Returns a scaling matrix.
     * 
     * @param f The scale factors.
     * 
     * @return The resulting matrix.
     */
    static Mat2D Scale(const Vec2D& f);
    
    /*!
     * @brief  Returns a scaling matrix.
     * 
     * @param fx The scale factor along the X-axis.
     * @param fy The scale factor along the Y-axis.
     * 
     * @return The resulting matrix.
     */
    static Mat2D Scale(float64 fx, float64 fy);
    
    /*!
     * @brief  Multiplies this matrix (left-side)with the given one (right-side):
     *         <c>result =this *m</c>.
     * 
     * @param m The matrix.
     * 
     * @return The resulting matrix.
     */
    Mat2D Mul(const Mat2D& m) const;
    
    /*!
     * @brief  Multiplies this matrix (left-side)with the given vector (right-side):
     *         <c>result =this *v</c>.
     * 
     * @param v The vector.
     * 
     * @return The resulting vector.
     */
    Vec2D Mul(const Vec2D& v) const;
    
    // ---------------------------------------------------------------------------------------------
    //  Copy constructor and copy assignment operator
    // ---------------------------------------------------------------------------------------------
  public:
    
    Mat2D(const Mat2D& other);
    
    Mat2D& operator=(const Mat2D& other);
    
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
