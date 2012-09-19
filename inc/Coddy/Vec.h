////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_MATH_VECTORS_VEC_H
#define CLODDY_CORE_MATH_VECTORS_VEC_H

#include "CodeX/System.h"

// Include referenced structures.

#include "Cloddy/Vec2B.h"
#include "Cloddy/Vec2D.h"
#include "Cloddy/Vec2F.h"
#include "Cloddy/Vec2I.h"
#include "Cloddy/Vec2L.h"
#include "Cloddy/Vec2S.h"
#include "Cloddy/Vec3B.h"
#include "Cloddy/Vec3D.h"
#include "Cloddy/Vec3F.h"
#include "Cloddy/Vec3I.h"
#include "Cloddy/Vec3L.h"
#include "Cloddy/Vec3S.h"
#include "Cloddy/Vec4B.h"
#include "Cloddy/Vec4D.h"
#include "Cloddy/Vec4F.h"
#include "Cloddy/Vec4I.h"
#include "Cloddy/Vec4L.h"
#include "Cloddy/Vec4S.h"

// Declare class ::Cloddy::Core::Math::Vectors::Vec.

namespace Cloddy { namespace Core { namespace Math { namespace Vectors
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Utility class for conversions between vector structs.
   */
  class Vec
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 8-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2B To2B(const Vec3B& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 8-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2B To2B(const Vec4B& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 8-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2B To2B(const Vec2S& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 8-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2B To2B(const Vec3S& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 8-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2B To2B(const Vec4S& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 8-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2B To2B(const Vec2I& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 8-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2B To2B(const Vec3I& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 8-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2B To2B(const Vec4I& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 8-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2B To2B(const Vec2L& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 8-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2B To2B(const Vec3L& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 8-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2B To2B(const Vec4L& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 8-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2B To2B(const Vec2F& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 8-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2B To2B(const Vec3F& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 8-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2B To2B(const Vec4F& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 8-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2B To2B(const Vec2D& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 8-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2B To2B(const Vec3D& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 8-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2B To2B(const Vec4D& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 64-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2D To2D(const Vec2B& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 64-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2D To2D(const Vec3B& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 64-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2D To2D(const Vec4B& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 64-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2D To2D(const Vec2S& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 64-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2D To2D(const Vec3S& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 64-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2D To2D(const Vec4S& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 64-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2D To2D(const Vec2I& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 64-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2D To2D(const Vec3I& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 64-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2D To2D(const Vec4I& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 64-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2D To2D(const Vec2L& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 64-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2D To2D(const Vec3L& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 64-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2D To2D(const Vec4L& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 64-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2D To2D(const Vec2F& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 64-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2D To2D(const Vec3F& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 64-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2D To2D(const Vec4F& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 64-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2D To2D(const Vec3D& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 64-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2D To2D(const Vec4D& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 32-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2F To2F(const Vec2B& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 32-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2F To2F(const Vec3B& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 32-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2F To2F(const Vec4B& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 32-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2F To2F(const Vec2S& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 32-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2F To2F(const Vec3S& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 32-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2F To2F(const Vec4S& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 32-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2F To2F(const Vec2I& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 32-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2F To2F(const Vec3I& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 32-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2F To2F(const Vec4I& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 32-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2F To2F(const Vec2L& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 32-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2F To2F(const Vec3L& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 32-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2F To2F(const Vec4L& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 32-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2F To2F(const Vec3F& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 32-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2F To2F(const Vec4F& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 32-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2F To2F(const Vec2D& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 32-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2F To2F(const Vec3D& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 32-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2F To2F(const Vec4D& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 32-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2I To2I(const Vec2B& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 32-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2I To2I(const Vec3B& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 32-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2I To2I(const Vec4B& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 32-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2I To2I(const Vec2S& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 32-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2I To2I(const Vec3S& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 32-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2I To2I(const Vec4S& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 32-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2I To2I(const Vec3I& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 32-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2I To2I(const Vec4I& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 32-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2I To2I(const Vec2L& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 32-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2I To2I(const Vec3L& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 32-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2I To2I(const Vec4L& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 32-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2I To2I(const Vec2F& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 32-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2I To2I(const Vec3F& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 32-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2I To2I(const Vec4F& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 32-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2I To2I(const Vec2D& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 32-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2I To2I(const Vec3D& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 32-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2I To2I(const Vec4D& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 64-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2L To2L(const Vec2B& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 64-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2L To2L(const Vec3B& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 64-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2L To2L(const Vec4B& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 64-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2L To2L(const Vec2S& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 64-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2L To2L(const Vec3S& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 64-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2L To2L(const Vec4S& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 64-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2L To2L(const Vec2I& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 64-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2L To2L(const Vec3I& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 64-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2L To2L(const Vec4I& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 64-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2L To2L(const Vec3L& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 64-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2L To2L(const Vec4L& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 64-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2L To2L(const Vec2F& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 64-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2L To2L(const Vec3F& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 64-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2L To2L(const Vec4F& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 64-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2L To2L(const Vec2D& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 64-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2L To2L(const Vec3D& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 64-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2L To2L(const Vec4D& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 16-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2S To2S(const Vec2B& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 16-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2S To2S(const Vec3B& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 16-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2S To2S(const Vec4B& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 16-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2S To2S(const Vec3S& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 16-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2S To2S(const Vec4S& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 16-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2S To2S(const Vec2I& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 16-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2S To2S(const Vec3I& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 16-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2S To2S(const Vec4I& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 16-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2S To2S(const Vec2L& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 16-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2S To2S(const Vec3L& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 16-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2S To2S(const Vec4L& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 16-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2S To2S(const Vec2F& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 16-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2S To2S(const Vec3F& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 16-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2S To2S(const Vec4F& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 16-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2S To2S(const Vec2D& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 16-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2S To2S(const Vec3D& v);
    
    /*!
     * @brief  Converts the given vector to a two-dimensional vector with 16-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec2S To2S(const Vec4D& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 8-bit integer precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3B To3B(const Vec2B& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 8-bit integer precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * 
     * @return The resulting vector.
     */
    static Vec3B To3B(const Vec2B& v, int8 z);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 8-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3B To3B(const Vec4B& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 8-bit integer precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3B To3B(const Vec2S& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 8-bit integer precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * 
     * @return The resulting vector.
     */
    static Vec3B To3B(const Vec2S& v, int8 z);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 8-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3B To3B(const Vec3S& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 8-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3B To3B(const Vec4S& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 8-bit integer precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3B To3B(const Vec2I& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 8-bit integer precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * 
     * @return The resulting vector.
     */
    static Vec3B To3B(const Vec2I& v, int8 z);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 8-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3B To3B(const Vec3I& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 8-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3B To3B(const Vec4I& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 8-bit integer precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3B To3B(const Vec2L& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 8-bit integer precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * 
     * @return The resulting vector.
     */
    static Vec3B To3B(const Vec2L& v, int8 z);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 8-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3B To3B(const Vec3L& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 8-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3B To3B(const Vec4L& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 8-bit integer precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3B To3B(const Vec2F& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 8-bit integer precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * 
     * @return The resulting vector.
     */
    static Vec3B To3B(const Vec2F& v, int8 z);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 8-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3B To3B(const Vec3F& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 8-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3B To3B(const Vec4F& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 8-bit integer precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3B To3B(const Vec2D& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 8-bit integer precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * 
     * @return The resulting vector.
     */
    static Vec3B To3B(const Vec2D& v, int8 z);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 8-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3B To3B(const Vec3D& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 8-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3B To3B(const Vec4D& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 64-bit floating-point 
     *         precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3D To3D(const Vec2B& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 64-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * 
     * @return The resulting vector.
     */
    static Vec3D To3D(const Vec2B& v, float64 z);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 64-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3D To3D(const Vec3B& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 64-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3D To3D(const Vec4B& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 64-bit floating-point 
     *         precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3D To3D(const Vec2S& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 64-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * 
     * @return The resulting vector.
     */
    static Vec3D To3D(const Vec2S& v, float64 z);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 64-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3D To3D(const Vec3S& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 64-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3D To3D(const Vec4S& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 64-bit floating-point 
     *         precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3D To3D(const Vec2I& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 64-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * 
     * @return The resulting vector.
     */
    static Vec3D To3D(const Vec2I& v, float64 z);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 64-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3D To3D(const Vec3I& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 64-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3D To3D(const Vec4I& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 64-bit floating-point 
     *         precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3D To3D(const Vec2L& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 64-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * 
     * @return The resulting vector.
     */
    static Vec3D To3D(const Vec2L& v, float64 z);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 64-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3D To3D(const Vec3L& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 64-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3D To3D(const Vec4L& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 64-bit floating-point 
     *         precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3D To3D(const Vec2F& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 64-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * 
     * @return The resulting vector.
     */
    static Vec3D To3D(const Vec2F& v, float64 z);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 64-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3D To3D(const Vec3F& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 64-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3D To3D(const Vec4F& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 64-bit floating-point 
     *         precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3D To3D(const Vec2D& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 64-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * 
     * @return The resulting vector.
     */
    static Vec3D To3D(const Vec2D& v, float64 z);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 64-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3D To3D(const Vec4D& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 32-bit floating-point 
     *         precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3F To3F(const Vec2B& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 32-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * 
     * @return The resulting vector.
     */
    static Vec3F To3F(const Vec2B& v, float32 z);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 32-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3F To3F(const Vec3B& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 32-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3F To3F(const Vec4B& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 32-bit floating-point 
     *         precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3F To3F(const Vec2S& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 32-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * 
     * @return The resulting vector.
     */
    static Vec3F To3F(const Vec2S& v, float32 z);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 32-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3F To3F(const Vec3S& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 32-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3F To3F(const Vec4S& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 32-bit floating-point 
     *         precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3F To3F(const Vec2I& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 32-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * 
     * @return The resulting vector.
     */
    static Vec3F To3F(const Vec2I& v, float32 z);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 32-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3F To3F(const Vec3I& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 32-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3F To3F(const Vec4I& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 32-bit floating-point 
     *         precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3F To3F(const Vec2L& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 32-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * 
     * @return The resulting vector.
     */
    static Vec3F To3F(const Vec2L& v, float32 z);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 32-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3F To3F(const Vec3L& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 32-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3F To3F(const Vec4L& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 32-bit floating-point 
     *         precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3F To3F(const Vec2F& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 32-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * 
     * @return The resulting vector.
     */
    static Vec3F To3F(const Vec2F& v, float32 z);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 32-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3F To3F(const Vec4F& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 32-bit floating-point 
     *         precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3F To3F(const Vec2D& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 32-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * 
     * @return The resulting vector.
     */
    static Vec3F To3F(const Vec2D& v, float32 z);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 32-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3F To3F(const Vec3D& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 32-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3F To3F(const Vec4D& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 32-bit integer 
     *         precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3I To3I(const Vec2B& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 32-bit integer 
     *         precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * 
     * @return The resulting vector.
     */
    static Vec3I To3I(const Vec2B& v, int32 z);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 32-bit integer 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3I To3I(const Vec3B& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 32-bit integer 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3I To3I(const Vec4B& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 32-bit integer 
     *         precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3I To3I(const Vec2S& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 32-bit integer 
     *         precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * 
     * @return The resulting vector.
     */
    static Vec3I To3I(const Vec2S& v, int32 z);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 32-bit integer 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3I To3I(const Vec3S& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 32-bit integer 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3I To3I(const Vec4S& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 32-bit integer 
     *         precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3I To3I(const Vec2I& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 32-bit integer 
     *         precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * 
     * @return The resulting vector.
     */
    static Vec3I To3I(const Vec2I& v, int32 z);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 32-bit integer 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3I To3I(const Vec4I& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 32-bit integer 
     *         precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3I To3I(const Vec2L& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 32-bit integer 
     *         precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * 
     * @return The resulting vector.
     */
    static Vec3I To3I(const Vec2L& v, int32 z);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 32-bit integer 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3I To3I(const Vec3L& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 32-bit integer 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3I To3I(const Vec4L& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 32-bit integer 
     *         precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3I To3I(const Vec2F& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 32-bit integer 
     *         precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * 
     * @return The resulting vector.
     */
    static Vec3I To3I(const Vec2F& v, int32 z);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 32-bit integer 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3I To3I(const Vec3F& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 32-bit integer 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3I To3I(const Vec4F& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 32-bit integer 
     *         precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3I To3I(const Vec2D& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 32-bit integer 
     *         precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * 
     * @return The resulting vector.
     */
    static Vec3I To3I(const Vec2D& v, int32 z);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 32-bit integer 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3I To3I(const Vec3D& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 32-bit integer 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3I To3I(const Vec4D& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 64-bit integer 
     *         precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3L To3L(const Vec2B& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 64-bit integer 
     *         precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * 
     * @return The resulting vector.
     */
    static Vec3L To3L(const Vec2B& v, int64 z);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 64-bit integer 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3L To3L(const Vec3B& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 64-bit integer 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3L To3L(const Vec4B& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 64-bit integer 
     *         precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3L To3L(const Vec2S& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 64-bit integer 
     *         precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * 
     * @return The resulting vector.
     */
    static Vec3L To3L(const Vec2S& v, int64 z);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 64-bit integer 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3L To3L(const Vec3S& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 64-bit integer 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3L To3L(const Vec4S& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 64-bit integer 
     *         precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3L To3L(const Vec2I& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 64-bit integer 
     *         precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * 
     * @return The resulting vector.
     */
    static Vec3L To3L(const Vec2I& v, int64 z);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 64-bit integer 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3L To3L(const Vec3I& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 64-bit integer 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3L To3L(const Vec4I& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 64-bit integer 
     *         precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3L To3L(const Vec2L& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 64-bit integer 
     *         precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * 
     * @return The resulting vector.
     */
    static Vec3L To3L(const Vec2L& v, int64 z);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 64-bit integer 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3L To3L(const Vec4L& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 64-bit integer 
     *         precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3L To3L(const Vec2F& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 64-bit integer 
     *         precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * 
     * @return The resulting vector.
     */
    static Vec3L To3L(const Vec2F& v, int64 z);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 64-bit integer 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3L To3L(const Vec3F& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 64-bit integer 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3L To3L(const Vec4F& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 64-bit integer 
     *         precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3L To3L(const Vec2D& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 64-bit integer 
     *         precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * 
     * @return The resulting vector.
     */
    static Vec3L To3L(const Vec2D& v, int64 z);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 64-bit integer 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3L To3L(const Vec3D& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 64-bit integer 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3L To3L(const Vec4D& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 16-bit integer 
     *         precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3S To3S(const Vec2B& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 16-bit integer 
     *         precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * 
     * @return The resulting vector.
     */
    static Vec3S To3S(const Vec2B& v, int16 z);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 16-bit integer 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3S To3S(const Vec3B& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 16-bit integer 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3S To3S(const Vec4B& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 16-bit integer 
     *         precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3S To3S(const Vec2S& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 16-bit integer 
     *         precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * 
     * @return The resulting vector.
     */
    static Vec3S To3S(const Vec2S& v, int16 z);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 16-bit integer 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3S To3S(const Vec4S& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 16-bit integer 
     *         precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3S To3S(const Vec2I& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 16-bit integer 
     *         precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * 
     * @return The resulting vector.
     */
    static Vec3S To3S(const Vec2I& v, int16 z);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 16-bit integer 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3S To3S(const Vec3I& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 16-bit integer 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3S To3S(const Vec4I& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 16-bit integer 
     *         precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3S To3S(const Vec2L& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 16-bit integer 
     *         precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * 
     * @return The resulting vector.
     */
    static Vec3S To3S(const Vec2L& v, int16 z);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 16-bit integer 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3S To3S(const Vec3L& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 16-bit integer 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3S To3S(const Vec4L& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 16-bit integer 
     *         precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3S To3S(const Vec2F& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 16-bit integer 
     *         precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * 
     * @return The resulting vector.
     */
    static Vec3S To3S(const Vec2F& v, int16 z);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 16-bit integer 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3S To3S(const Vec3F& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 16-bit integer 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3S To3S(const Vec4F& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 16-bit integer 
     *         precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3S To3S(const Vec2D& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 16-bit integer 
     *         precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * 
     * @return The resulting vector.
     */
    static Vec3S To3S(const Vec2D& v, int16 z);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 16-bit integer 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3S To3S(const Vec3D& v);
    
    /*!
     * @brief  Converts the given vector to a three-dimensional vector with 16-bit integer 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec3S To3S(const Vec4D& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 8-bit integer precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4B To4B(const Vec2B& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 8-bit integer precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4B To4B(const Vec2B& v, int8 z, int8 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 8-bit integer precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4B To4B(const Vec3B& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 8-bit integer precision.
     * 
     * @param v The vector to convert.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4B To4B(const Vec3B& v, int8 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 8-bit integer precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4B To4B(const Vec2S& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 8-bit integer precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4B To4B(const Vec2S& v, int8 z, int8 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 8-bit integer precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4B To4B(const Vec3S& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 8-bit integer precision.
     * 
     * @param v The vector to convert.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4B To4B(const Vec3S& v, int8 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 8-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4B To4B(const Vec4S& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 8-bit integer precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4B To4B(const Vec2I& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 8-bit integer precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4B To4B(const Vec2I& v, int8 z, int8 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 8-bit integer precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4B To4B(const Vec3I& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 8-bit integer precision.
     * 
     * @param v The vector to convert.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4B To4B(const Vec3I& v, int8 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 8-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4B To4B(const Vec4I& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 8-bit integer precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4B To4B(const Vec2L& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 8-bit integer precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4B To4B(const Vec2L& v, int8 z, int8 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 8-bit integer precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4B To4B(const Vec3L& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 8-bit integer precision.
     * 
     * @param v The vector to convert.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4B To4B(const Vec3L& v, int8 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 8-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4B To4B(const Vec4L& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 8-bit integer precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4B To4B(const Vec2F& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 8-bit integer precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4B To4B(const Vec2F& v, int8 z, int8 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 8-bit integer precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4B To4B(const Vec3F& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 8-bit integer precision.
     * 
     * @param v The vector to convert.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4B To4B(const Vec3F& v, int8 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 8-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4B To4B(const Vec4F& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 8-bit integer precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4B To4B(const Vec2D& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 8-bit integer precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4B To4B(const Vec2D& v, int8 z, int8 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 8-bit integer precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4B To4B(const Vec3D& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 8-bit integer precision.
     * 
     * @param v The vector to convert.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4B To4B(const Vec3D& v, int8 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 8-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4B To4B(const Vec4D& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 64-bit floating-point 
     *         precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4D To4D(const Vec2B& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 64-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4D To4D(const Vec2B& v, float64 z, float64 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 64-bit floating-point 
     *         precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4D To4D(const Vec3B& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 64-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4D To4D(const Vec3B& v, float64 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 64-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4D To4D(const Vec4B& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 64-bit floating-point 
     *         precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4D To4D(const Vec2S& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 64-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4D To4D(const Vec2S& v, float64 z, float64 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 64-bit floating-point 
     *         precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4D To4D(const Vec3S& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 64-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4D To4D(const Vec3S& v, float64 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 64-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4D To4D(const Vec4S& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 64-bit floating-point 
     *         precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4D To4D(const Vec2I& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 64-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4D To4D(const Vec2I& v, float64 z, float64 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 64-bit floating-point 
     *         precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4D To4D(const Vec3I& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 64-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4D To4D(const Vec3I& v, float64 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 64-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4D To4D(const Vec4I& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 64-bit floating-point 
     *         precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4D To4D(const Vec2L& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 64-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4D To4D(const Vec2L& v, float64 z, float64 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 64-bit floating-point 
     *         precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4D To4D(const Vec3L& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 64-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4D To4D(const Vec3L& v, float64 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 64-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4D To4D(const Vec4L& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 64-bit floating-point 
     *         precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4D To4D(const Vec2F& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 64-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4D To4D(const Vec2F& v, float64 z, float64 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 64-bit floating-point 
     *         precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4D To4D(const Vec3F& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 64-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4D To4D(const Vec3F& v, float64 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 64-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4D To4D(const Vec4F& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 64-bit floating-point 
     *         precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4D To4D(const Vec2D& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 64-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4D To4D(const Vec2D& v, float64 z, float64 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 64-bit floating-point 
     *         precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4D To4D(const Vec3D& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 64-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4D To4D(const Vec3D& v, float64 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 32-bit floating-point 
     *         precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4F To4F(const Vec2B& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 32-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4F To4F(const Vec2B& v, float32 z, float32 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 32-bit floating-point 
     *         precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4F To4F(const Vec3B& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 32-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4F To4F(const Vec3B& v, float32 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 32-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4F To4F(const Vec4B& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 32-bit floating-point 
     *         precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4F To4F(const Vec2S& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 32-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4F To4F(const Vec2S& v, float32 z, float32 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 32-bit floating-point 
     *         precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4F To4F(const Vec3S& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 32-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4F To4F(const Vec3S& v, float32 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 32-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4F To4F(const Vec4S& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 32-bit floating-point 
     *         precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4F To4F(const Vec2I& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 32-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4F To4F(const Vec2I& v, float32 z, float32 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 32-bit floating-point 
     *         precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4F To4F(const Vec3I& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 32-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4F To4F(const Vec3I& v, float32 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 32-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4F To4F(const Vec4I& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 32-bit floating-point 
     *         precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4F To4F(const Vec2L& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 32-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4F To4F(const Vec2L& v, float32 z, float32 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 32-bit floating-point 
     *         precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4F To4F(const Vec3L& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 32-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4F To4F(const Vec3L& v, float32 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 32-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4F To4F(const Vec4L& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 32-bit floating-point 
     *         precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4F To4F(const Vec2F& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 32-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4F To4F(const Vec2F& v, float32 z, float32 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 32-bit floating-point 
     *         precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4F To4F(const Vec3F& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 32-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4F To4F(const Vec3F& v, float32 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 32-bit floating-point 
     *         precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4F To4F(const Vec2D& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 32-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4F To4F(const Vec2D& v, float32 z, float32 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 32-bit floating-point 
     *         precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4F To4F(const Vec3D& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 32-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4F To4F(const Vec3D& v, float32 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 32-bit floating-point 
     *         precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4F To4F(const Vec4D& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 32-bit integer precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4I To4I(const Vec2B& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 32-bit integer precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4I To4I(const Vec2B& v, int32 z, int32 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 32-bit integer precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4I To4I(const Vec3B& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 32-bit integer precision.
     * 
     * @param v The vector to convert.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4I To4I(const Vec3B& v, int32 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 32-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4I To4I(const Vec4B& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 32-bit integer precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4I To4I(const Vec2S& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 32-bit integer precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4I To4I(const Vec2S& v, int32 z, int32 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 32-bit integer precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4I To4I(const Vec3S& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 32-bit integer precision.
     * 
     * @param v The vector to convert.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4I To4I(const Vec3S& v, int32 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 32-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4I To4I(const Vec4S& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 32-bit integer precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4I To4I(const Vec2I& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 32-bit integer precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4I To4I(const Vec2I& v, int32 z, int32 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 32-bit integer precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4I To4I(const Vec3I& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 32-bit integer precision.
     * 
     * @param v The vector to convert.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4I To4I(const Vec3I& v, int32 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 32-bit integer precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4I To4I(const Vec2L& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 32-bit integer precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4I To4I(const Vec2L& v, int32 z, int32 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 32-bit integer precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4I To4I(const Vec3L& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 32-bit integer precision.
     * 
     * @param v The vector to convert.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4I To4I(const Vec3L& v, int32 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 32-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4I To4I(const Vec4L& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 32-bit integer precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4I To4I(const Vec2F& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 32-bit integer precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4I To4I(const Vec2F& v, int32 z, int32 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 32-bit integer precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4I To4I(const Vec3F& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 32-bit integer precision.
     * 
     * @param v The vector to convert.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4I To4I(const Vec3F& v, int32 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 32-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4I To4I(const Vec4F& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 32-bit integer precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4I To4I(const Vec2D& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 32-bit integer precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4I To4I(const Vec2D& v, int32 z, int32 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 32-bit integer precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4I To4I(const Vec3D& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 32-bit integer precision.
     * 
     * @param v The vector to convert.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4I To4I(const Vec3D& v, int32 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 32-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4I To4I(const Vec4D& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 64-bit integer precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4L To4L(const Vec2B& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 64-bit integer precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4L To4L(const Vec2B& v, int64 z, int64 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 64-bit integer precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4L To4L(const Vec3B& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 64-bit integer precision.
     * 
     * @param v The vector to convert.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4L To4L(const Vec3B& v, int64 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 64-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4L To4L(const Vec4B& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 64-bit integer precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4L To4L(const Vec2S& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 64-bit integer precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4L To4L(const Vec2S& v, int64 z, int64 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 64-bit integer precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4L To4L(const Vec3S& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 64-bit integer precision.
     * 
     * @param v The vector to convert.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4L To4L(const Vec3S& v, int64 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 64-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4L To4L(const Vec4S& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 64-bit integer precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4L To4L(const Vec2I& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 64-bit integer precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4L To4L(const Vec2I& v, int64 z, int64 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 64-bit integer precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4L To4L(const Vec3I& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 64-bit integer precision.
     * 
     * @param v The vector to convert.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4L To4L(const Vec3I& v, int64 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 64-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4L To4L(const Vec4I& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 64-bit integer precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4L To4L(const Vec2L& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 64-bit integer precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4L To4L(const Vec2L& v, int64 z, int64 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 64-bit integer precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4L To4L(const Vec3L& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 64-bit integer precision.
     * 
     * @param v The vector to convert.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4L To4L(const Vec3L& v, int64 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 64-bit integer precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4L To4L(const Vec2F& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 64-bit integer precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4L To4L(const Vec2F& v, int64 z, int64 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 64-bit integer precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4L To4L(const Vec3F& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 64-bit integer precision.
     * 
     * @param v The vector to convert.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4L To4L(const Vec3F& v, int64 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 64-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4L To4L(const Vec4F& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 64-bit integer precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4L To4L(const Vec2D& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 64-bit integer precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4L To4L(const Vec2D& v, int64 z, int64 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 64-bit integer precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4L To4L(const Vec3D& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 64-bit integer precision.
     * 
     * @param v The vector to convert.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4L To4L(const Vec3D& v, int64 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 64-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4L To4L(const Vec4D& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 16-bit integer precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4S To4S(const Vec2B& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 16-bit integer precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4S To4S(const Vec2B& v, int16 z, int16 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 16-bit integer precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4S To4S(const Vec3B& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 16-bit integer precision.
     * 
     * @param v The vector to convert.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4S To4S(const Vec3B& v, int16 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 16-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4S To4S(const Vec4B& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 16-bit integer precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4S To4S(const Vec2S& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 16-bit integer precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4S To4S(const Vec2S& v, int16 z, int16 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 16-bit integer precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4S To4S(const Vec3S& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 16-bit integer precision.
     * 
     * @param v The vector to convert.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4S To4S(const Vec3S& v, int16 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 16-bit integer precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4S To4S(const Vec2I& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 16-bit integer precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4S To4S(const Vec2I& v, int16 z, int16 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 16-bit integer precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4S To4S(const Vec3I& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 16-bit integer precision.
     * 
     * @param v The vector to convert.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4S To4S(const Vec3I& v, int16 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 16-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4S To4S(const Vec4I& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 16-bit integer precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4S To4S(const Vec2L& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 16-bit integer precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4S To4S(const Vec2L& v, int16 z, int16 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 16-bit integer precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4S To4S(const Vec3L& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 16-bit integer precision.
     * 
     * @param v The vector to convert.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4S To4S(const Vec3L& v, int16 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 16-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4S To4S(const Vec4L& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 16-bit integer precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4S To4S(const Vec2F& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 16-bit integer precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4S To4S(const Vec2F& v, int16 z, int16 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 16-bit integer precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4S To4S(const Vec3F& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 16-bit integer precision.
     * 
     * @param v The vector to convert.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4S To4S(const Vec3F& v, int16 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 16-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4S To4S(const Vec4F& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 16-bit integer precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4S To4S(const Vec2D& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 16-bit integer precision.
     * 
     * @param v The vector to convert.
     * @param z The Z-component.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4S To4S(const Vec2D& v, int16 z, int16 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 16-bit integer precision.
     * 
     * Additonal vector components will be set to \c 0 .
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4S To4S(const Vec3D& v);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 16-bit integer precision.
     * 
     * @param v The vector to convert.
     * @param w The W-component.
     * 
     * @return The resulting vector.
     */
    static Vec4S To4S(const Vec3D& v, int16 w);
    
    /*!
     * @brief  Converts the given vector to a four-dimensional vector with 16-bit integer precision.
     * 
     * @param v The vector to convert.
     * 
     * @return The resulting vector.
     */
    static Vec4S To4S(const Vec4D& v);
  };
  
} } } } 

#endif
