////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_MATH_VECTORS_MAT_H
#define CLODDY_CORE_MATH_VECTORS_MAT_H

#include "CodeX/System.h"

// Include referenced structures.

#include "Cloddy/Mat2D.h"
#include "Cloddy/Mat2F.h"
#include "Cloddy/Mat3D.h"
#include "Cloddy/Mat3F.h"
#include "Cloddy/Mat4D.h"
#include "Cloddy/Mat4F.h"

// Declare class ::Cloddy::Core::Math::Vectors::Mat.

namespace Cloddy { namespace Core { namespace Math { namespace Vectors
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Utility class for conversions between matrix structs.
   */
  class Mat
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:

    /*!
     * @brief  Converts the given matrix to a 2x2 matrix.
     * 
     * @param m The input matrix.
     * 
     * @return The resulting matrix.
     */
    static Mat2D To2D(const Mat2F& m);

    /*!
     * @brief  Converts the given matrix to a 2x2 matrix.
     * 
     * @param m The input matrix.
     * 
     * @return The resulting matrix.
     */
    static Mat2D To2D(const Mat3D& m);

    /*!
     * @brief  Converts the given matrix to a 2x2 matrix.
     * 
     * @param m The input matrix.
     * 
     * @return The resulting matrix.
     */
    static Mat2D To2D(const Mat3F& m);

    /*!
     * @brief  Converts the given matrix to a 2x2 matrix.
     * 
     * @param m The input matrix.
     * 
     * @return The resulting matrix.
     */
    static Mat2D To2D(const Mat4D& m);

    /*!
     * @brief  Converts the given matrix to a 2x2 matrix.
     * 
     * @param m The input matrix.
     * 
     * @return The resulting matrix.
     */
    static Mat2D To2D(const Mat4F& m);

    /*!
     * @brief  Converts the given matrix to a 2x2 matrix.
     * 
     * @param m The input matrix.
     * 
     * @return The resulting matrix.
     */
    static Mat2F To2F(const Mat2D& m);   

    /*!
     * @brief  Converts the given matrix to a 2x2 matrix.
     * 
     * @param m The input matrix.
     * 
     * @return The resulting matrix.
     */
    static Mat2F To2F(const Mat3D& m);

    /*!
     * @brief  Converts the given matrix to a 2x2 matrix.
     * 
     * @param m The input matrix.
     * 
     * @return The resulting matrix.
     */
    static Mat2F To2F(const Mat3F& m);

    /*!
     * @brief  Converts the given matrix to a 2x2 matrix.
     * 
     * @param m The input matrix.
     * 
     * @return The resulting matrix.
     */
    static Mat2F To2F(const Mat4D& m);

    /*!
     * @brief  Converts the given matrix to a 2x2 matrix.
     * 
     * @param m The input matrix.
     * 
     * @return The resulting matrix.
     */
    static Mat2F To2F(const Mat4F& m);    



        
    /*!
     * @brief  Converts the given matrix to a 3x3 matrix.
     * 
     * @param m The input matrix.
     * 
     * @return The resulting matrix.
     */
    static Mat3D To3D(const Mat2D& m);

    /*!
     * @brief  Converts the given matrix to a 3x3 matrix.
     * 
     * @param m The input matrix.
     * 
     * @return The resulting matrix.
     */
    static Mat3D To3D(const Mat2F& m);

    /*!
     * @brief  Converts the given matrix to a 3x3 matrix.
     * 
     * @param m The input matrix.
     * 
     * @return The resulting matrix.
     */
    static Mat3D To3D(const Mat3F& m);
    
    /*!
     * @brief  Converts the given matrix to a 3x3 matrix.
     * 
     * @param m The input matrix.
     * 
     * @return The resulting matrix.
     */
    static Mat3D To3D(const Mat4D& m);

    /*!
     * @brief  Converts the given matrix to a 3x3 matrix.
     * 
     * @param m The input matrix.
     * 
     * @return The resulting matrix.
     */
    static Mat3D To3D(const Mat4F& m);

    /*!
     * @brief  Converts the given matrix to a 3x3 matrix.
     * 
     * @param m The input matrix.
     * 
     * @return The resulting matrix.
     */
    static Mat3F To3F(const Mat2D& m);

    /*!
     * @brief  Converts the given matrix to a 3x3 matrix.
     * 
     * @param m The input matrix.
     * 
     * @return The resulting matrix.
     */
    static Mat3F To3F(const Mat2F& m);

    /*!
     * @brief  Converts the given matrix to a 3x3 matrix.
     * 
     * @param m The input matrix.
     * 
     * @return The resulting matrix.
     */
    static Mat3F To3F(const Mat3D& m);
    
    /*!
     * @brief  Converts the given matrix to a 3x3 matrix.
     * 
     * @param m The input matrix.
     * 
     * @return The resulting matrix.
     */
    static Mat3F To3F(const Mat4D& m);

    /*!
     * @brief  Converts the given matrix to a 3x3 matrix.
     * 
     * @param m The input matrix.
     * 
     * @return The resulting matrix.
     */
    static Mat3F To3F(const Mat4F& m);
    


        
    /*!
     * @brief  Converts the given matrix to a 4x4 matrix.
     * 
     * @param m The input matrix.
     * 
     * @return The resulting matrix.
     */
    static Mat4D To4D(const Mat2D& m);

    /*!
     * @brief  Converts the given matrix to a 4x4 matrix.
     * 
     * @param m The input matrix.
     * 
     * @return The resulting matrix.
     */
    static Mat4D To4D(const Mat2F& m);
    
    /*!
     * @brief  Converts the given matrix to a 4x4 matrix.
     * 
     * @param m The input matrix.
     * 
     * @return The resulting matrix.
     */
    static Mat4D To4D(const Mat3D& m);

    /*!
     * @brief  Converts the given matrix to a 4x4 matrix.
     * 
     * @param m The input matrix.
     * 
     * @return The resulting matrix.
     */
    static Mat4D To4D(const Mat3F& m);

    /*!
     * @brief  Converts the given matrix to a 4x4 matrix.
     * 
     * @param m The input matrix.
     * 
     * @return The resulting matrix.
     */
    static Mat4D To4D(const Mat4F& m);

    /*!
     * @brief  Converts the given matrix to a 4x4 matrix.
     * 
     * @param m The input matrix.
     * 
     * @return The resulting matrix.
     */
    static Mat4F To4F(const Mat2D& m);

    /*!
     * @brief  Converts the given matrix to a 4x4 matrix.
     * 
     * @param m The input matrix.
     * 
     * @return The resulting matrix.
     */
    static Mat4F To4F(const Mat2F& m);
    
    /*!
     * @brief  Converts the given matrix to a 4x4 matrix.
     * 
     * @param m The input matrix.
     * 
     * @return The resulting matrix.
     */
    static Mat4F To4F(const Mat3D& m);

    /*!
     * @brief  Converts the given matrix to a 4x4 matrix.
     * 
     * @param m The input matrix.
     * 
     * @return The resulting matrix.
     */
    static Mat4F To4F(const Mat3F& m);

    /*!
     * @brief  Converts the given matrix to a 4x4 matrix.
     * 
     * @param m The input matrix.
     * 
     * @return The resulting matrix.
     */
    static Mat4F To4F(const Mat4D& m);
  };
  
} } } } 

#endif
