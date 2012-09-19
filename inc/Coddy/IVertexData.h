////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_VERTEXDATA_IVERTEXDATA_H
#define CLODDY_API_VERTEXDATA_IVERTEXDATA_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/TupleType.h"

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

// Include referenced interfaces.

#include "Cloddy/ICapacity.h"

// Declare interface ::Cloddy::API::VertexData::IVertexData.

namespace Cloddy { namespace API { namespace VertexData
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced structures.
  
  using Cloddy::Core::Math::Vectors::Vec2B;
  using Cloddy::Core::Math::Vectors::Vec2D;
  using Cloddy::Core::Math::Vectors::Vec2F;
  using Cloddy::Core::Math::Vectors::Vec2I;
  using Cloddy::Core::Math::Vectors::Vec2L;
  using Cloddy::Core::Math::Vectors::Vec2S;
  using Cloddy::Core::Math::Vectors::Vec3B;
  using Cloddy::Core::Math::Vectors::Vec3D;
  using Cloddy::Core::Math::Vectors::Vec3F;
  using Cloddy::Core::Math::Vectors::Vec3I;
  using Cloddy::Core::Math::Vectors::Vec3L;
  using Cloddy::Core::Math::Vectors::Vec3S;
  using Cloddy::Core::Math::Vectors::Vec4B;
  using Cloddy::Core::Math::Vectors::Vec4D;
  using Cloddy::Core::Math::Vectors::Vec4F;
  using Cloddy::Core::Math::Vectors::Vec4I;
  using Cloddy::Core::Math::Vectors::Vec4L;
  using Cloddy::Core::Math::Vectors::Vec4S;
  
  // Use referenced interfaces.
  
  using Cloddy::Kernel::ICapacity;
  
  /*!
   * @brief  Base interface for vertex data containers.
   */
  class NO_VTABLE IVertexData : public virtual ICapacity
  {
    // ---------------------------------------------------------------------------------------------
    // Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The tuple size.
     * 
     * @return <b>[>=1]</b>  The tuple size.
     */
    virtual int32 GetSize() = 0;
    
    /*!
     * @brief  The tuple element type.
     * 
     * @return The tuple element type.
     */
    virtual TupleType GetTupleType() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Returns the \e index -th tuple with 8-bit integer precision.
     * 
     * All missing tuple components will be set to \c 0 .
     * 
     * @param index <b>[0..ICapacity::GetCapacity-1]</b>  Index of the tuple to get.
     * 
     * @return The read tuple.
     */
    virtual int8 Get1B(int32 index) = 0;
    
    /*!
     * @brief  Returns the \e index -th tuple with 64-bit floating-point precision.
     * 
     * All missing tuple components will be set to \c 0 .
     * 
     * @param index <b>[0..ICapacity::GetCapacity-1]</b>  Index of the tuple to get.
     * 
     * @return The read tuple.
     */
    virtual float64 Get1D(int32 index) = 0;
    
    /*!
     * @brief  Returns the \e index -th tuple with 32-bit floating-point precision.
     * 
     * All missing tuple components will be set to \c 0 .
     * 
     * @param index <b>[0..ICapacity::GetCapacity-1]</b>  Index of the tuple to get.
     * 
     * @return The read tuple.
     */
    virtual float32 Get1F(int32 index) = 0;
    
    /*!
     * @brief  Returns the \e index -th tuple with 32-bit integer precision.
     * 
     * All missing tuple components will be set to \c 0 .
     * 
     * @param index <b>[0..ICapacity::GetCapacity-1]</b>  Index of the tuple to get.
     * 
     * @return The read tuple.
     */
    virtual int32 Get1I(int32 index) = 0;
    
    /*!
     * @brief  Returns the \e index -th tuple with 64-bit integer precision.
     * 
     * All missing tuple components will be set to \c 0 .
     * 
     * @param index <b>[0..ICapacity::GetCapacity-1]</b>  Index of the tuple to get.
     * 
     * @return The read tuple.
     */
    virtual int64 Get1L(int32 index) = 0;
    
    /*!
     * @brief  Returns the \e index -th tuple with 16-bit integer precision.
     * 
     * All missing tuple components will be set to \c 0 .
     * 
     * @param index <b>[0..ICapacity::GetCapacity-1]</b>  Index of the tuple to get.
     * 
     * @return The read tuple.
     */
    virtual int16 Get1S(int32 index) = 0;
    
    /*!
     * @brief  Returns the \e index -th tuple with 8-bit integer precision.
     * 
     * All missing tuple components will be set to \c 0 .
     * 
     * @param index <b>[0..ICapacity::GetCapacity-1]</b>  Index of the tuple to get.
     * 
     * @return The read tuple.
     */
    virtual Vec2B Get2B(int32 index) = 0;
    
    /*!
     * @brief  Returns the \e index -th tuple with 64-bit floating-point precision.
     * 
     * All missing tuple components will be set to \c 0 .
     * 
     * @param index <b>[0..ICapacity::GetCapacity-1]</b>  Index of the tuple to get.
     * 
     * @return The read tuple.
     */
    virtual Vec2D Get2D(int32 index) = 0;
    
    /*!
     * @brief  Returns the \e index -th tuple with 32-bit floating-point precision.
     * 
     * All missing tuple components will be set to \c 0 .
     * 
     * @param index <b>[0..ICapacity::GetCapacity-1]</b>  Index of the tuple to get.
     * 
     * @return The read tuple.
     */
    virtual Vec2F Get2F(int32 index) = 0;
    
    /*!
     * @brief  Returns the \e index -th tuple with 32-bit integer precision.
     * 
     * All missing tuple components will be set to \c 0 .
     * 
     * @param index <b>[0..ICapacity::GetCapacity-1]</b>  Index of the tuple to get.
     * 
     * @return The read tuple.
     */
    virtual Vec2I Get2I(int32 index) = 0;
    
    /*!
     * @brief  Returns the \e index -th tuple with 64-bit integer precision.
     * 
     * All missing tuple components will be set to \c 0 .
     * 
     * @param index <b>[0..ICapacity::GetCapacity-1]</b>  Index of the tuple to get.
     * 
     * @return The read tuple.
     */
    virtual Vec2L Get2L(int32 index) = 0;
    
    /*!
     * @brief  Returns the \e index -th tuple with 16-bit integer precision.
     * 
     * All missing tuple components will be set to \c 0 .
     * 
     * @param index <b>[0..ICapacity::GetCapacity-1]</b>  Index of the tuple to get.
     * 
     * @return The read tuple.
     */
    virtual Vec2S Get2S(int32 index) = 0;
    
    /*!
     * @brief  Returns the \e index -th tuple with 8-bit integer precision.
     * 
     * All missing tuple components will be set to \c 0 .
     * 
     * @param index <b>[0..ICapacity::GetCapacity-1]</b>  Index of the tuple to get.
     * 
     * @return The read tuple.
     */
    virtual Vec3B Get3B(int32 index) = 0;
    
    /*!
     * @brief  Returns the \e index -th tuple with 64-bit floating-point precision.
     * 
     * All missing tuple components will be set to \c 0 .
     * 
     * @param index <b>[0..ICapacity::GetCapacity-1]</b>  Index of the tuple to get.
     * 
     * @return The read tuple.
     */
    virtual Vec3D Get3D(int32 index) = 0;
    
    /*!
     * @brief  Returns the \e index -th tuple with 32-bit floating-point precision.
     * 
     * All missing tuple components will be set to \c 0 .
     * 
     * @param index <b>[0..ICapacity::GetCapacity-1]</b>  Index of the tuple to get.
     * 
     * @return The read tuple.
     */
    virtual Vec3F Get3F(int32 index) = 0;
    
    /*!
     * @brief  Returns the \e index -th tuple with 32-bit integer precision.
     * 
     * All missing tuple components will be set to \c 0 .
     * 
     * @param index <b>[0..ICapacity::GetCapacity-1]</b>  Index of the tuple to get.
     * 
     * @return The read tuple.
     */
    virtual Vec3I Get3I(int32 index) = 0;
    
    /*!
     * @brief  Returns the \e index -th tuple with 64-bit integer precision.
     * 
     * All missing tuple components will be set to \c 0 .
     * 
     * @param index <b>[0..ICapacity::GetCapacity-1]</b>  Index of the tuple to get.
     * 
     * @return The read tuple.
     */
    virtual Vec3L Get3L(int32 index) = 0;
    
    /*!
     * @brief  Returns the \e index -th tuple with 16-bit integer precision.
     * 
     * All missing tuple components will be set to \c 0 .
     * 
     * @param index <b>[0..ICapacity::GetCapacity-1]</b>  Index of the tuple to get.
     * 
     * @return The read tuple.
     */
    virtual Vec3S Get3S(int32 index) = 0;
    
    /*!
     * @brief  Returns the \e index -th tuple with 8-bit integer precision.
     * 
     * All missing tuple components will be set to \c 0 .
     * 
     * @param index <b>[0..ICapacity::GetCapacity-1]</b>  Index of the tuple to get.
     * 
     * @return The read tuple.
     */
    virtual Vec4B Get4B(int32 index) = 0;
    
    /*!
     * @brief  Returns the \e index -th tuple with 64-bit floating-point precision.
     * 
     * All missing tuple components will be set to \c 0 .
     * 
     * @param index <b>[0..ICapacity::GetCapacity-1]</b>  Index of the tuple to get.
     * 
     * @return The read tuple.
     */
    virtual Vec4D Get4D(int32 index) = 0;
    
    /*!
     * @brief  Returns the \e index -th tuple with 32-bit floating-point precision.
     * 
     * All missing tuple components will be set to \c 0 .
     * 
     * @param index <b>[0..ICapacity::GetCapacity-1]</b>  Index of the tuple to get.
     * 
     * @return The read tuple.
     */
    virtual Vec4F Get4F(int32 index) = 0;
    
    /*!
     * @brief  Returns the \e index -th tuple with 32-bit integer precision.
     * 
     * All missing tuple components will be set to \c 0 .
     * 
     * @param index <b>[0..ICapacity::GetCapacity-1]</b>  Index of the tuple to get.
     * 
     * @return The read tuple.
     */
    virtual Vec4I Get4I(int32 index) = 0;
    
    /*!
     * @brief  Returns the \e index -th tuple with 64-bit integer precision.
     * 
     * All missing tuple components will be set to \c 0 .
     * 
     * @param index <b>[0..ICapacity::GetCapacity-1]</b>  Index of the tuple to get.
     * 
     * @return The read tuple.
     */
    virtual Vec4L Get4L(int32 index) = 0;
    
    /*!
     * @brief  Returns the \e index -th tuple with 16-bit integer precision.
     * 
     * All missing tuple components will be set to \c 0 .
     * 
     * @param index <b>[0..ICapacity::GetCapacity-1]</b>  Index of the tuple to get.
     * 
     * @return The read tuple.
     */
    virtual Vec4S Get4S(int32 index) = 0;
    
    /*!
     * @brief  Sets the \e index -th tuple.
     * 
     * All extra tuple components will be ignored;all missing components will be set to \c 0 .
     * 
     * @param index <b>[0..ICapacity::GetCapacity-1]</b>  Index of the tuple to set.
     * @param tuple The new tuple value.
     */
    virtual void Set1B(int32 index, int8 tuple) = 0;
    
    /*!
     * @brief  Sets the \e index -th tuple.
     * 
     * All extra tuple components will be ignored;all missing components will be set to \c 0 .
     * 
     * @param index <b>[0..ICapacity::GetCapacity-1]</b>  Index of the tuple to set.
     * @param tuple The new tuple value.
     */
    virtual void Set1D(int32 index, float64 tuple) = 0;
    
    /*!
     * @brief  Sets the \e index -th tuple.
     * 
     * All extra tuple components will be ignored;all missing components will be set to \c 0 .
     * 
     * @param index <b>[0..ICapacity::GetCapacity-1]</b>  Index of the tuple to set.
     * @param tuple The new tuple value.
     */
    virtual void Set1F(int32 index, float32 tuple) = 0;
    
    /*!
     * @brief  Sets the \e index -th tuple.
     * 
     * All extra tuple components will be ignored;all missing components will be set to \c 0 .
     * 
     * @param index <b>[0..ICapacity::GetCapacity-1]</b>  Index of the tuple to set.
     * @param tuple The new tuple value.
     */
    virtual void Set1I(int32 index, int32 tuple) = 0;
    
    /*!
     * @brief  Sets the \e index -th tuple.
     * 
     * All extra tuple components will be ignored;all missing components will be set to \c 0 .
     * 
     * @param index <b>[0..ICapacity::GetCapacity-1]</b>  Index of the tuple to set.
     * @param tuple The new tuple value.
     */
    virtual void Set1L(int32 index, int64 tuple) = 0;
    
    /*!
     * @brief  Sets the \e index -th tuple.
     * 
     * All extra tuple components will be ignored;all missing components will be set to \c 0 .
     * 
     * @param index <b>[0..ICapacity::GetCapacity-1]</b>  Index of the tuple to set.
     * @param tuple The new tuple value.
     */
    virtual void Set1S(int32 index, int16 tuple) = 0;
    
    /*!
     * @brief  Sets the \e index -th tuple.
     * 
     * All extra tuple components will be ignored;all missing components will be set to \c 0 .
     * 
     * @param index <b>[0..ICapacity::GetCapacity-1]</b>  Index of the tuple to set.
     * @param tuple The new tuple value.
     */
    virtual void Set2B(int32 index, const Vec2B& tuple) = 0;
    
    /*!
     * @brief  Sets the \e index -th tuple.
     * 
     * All extra tuple components will be ignored;all missing components will be set to \c 0 .
     * 
     * @param index <b>[0..ICapacity::GetCapacity-1]</b>  Index of the tuple to set.
     * @param x The new tuple X-coordinate value.
     * @param y The new tuple Y-coordinate value.
     */
    virtual void Set2B(int32 index, int8 x, int8 y) = 0;
    
    /*!
     * @brief  Sets the \e index -th tuple.
     * 
     * All extra tuple components will be ignored;all missing components will be set to \c 0 .
     * 
     * @param index <b>[0..ICapacity::GetCapacity-1]</b>  Index of the tuple to set.
     * @param tuple The new tuple value.
     */
    virtual void Set2D(int32 index, const Vec2D& tuple) = 0;
    
    /*!
     * @brief  Sets the \e index -th tuple.
     * 
     * All extra tuple components will be ignored;all missing components will be set to \c 0 .
     * 
     * @param index <b>[0..ICapacity::GetCapacity-1]</b>  Index of the tuple to set.
     * @param x The new tuple X-coordinate value.
     * @param y The new tuple Y-coordinate value.
     */
    virtual void Set2D(int32 index, float64 x, float64 y) = 0;
    
    /*!
     * @brief  Sets the \e index -th tuple.
     * 
     * All extra tuple components will be ignored;all missing components will be set to \c 0 .
     * 
     * @param index <b>[0..ICapacity::GetCapacity-1]</b>  Index of the tuple to set.
     * @param tuple The new tuple value.
     */
    virtual void Set2F(int32 index, const Vec2F& tuple) = 0;
    
    /*!
     * @brief  Sets the \e index -th tuple.
     * 
     * All extra tuple components will be ignored;all missing components will be set to \c 0 .
     * 
     * @param index <b>[0..ICapacity::GetCapacity-1]</b>  Index of the tuple to set.
     * @param x The new tuple X-coordinate value.
     * @param y The new tuple Y-coordinate value.
     */
    virtual void Set2F(int32 index, float32 x, float32 y) = 0;
    
    /*!
     * @brief  Sets the \e index -th tuple.
     * 
     * All extra tuple components will be ignored;all missing components will be set to \c 0 .
     * 
     * @param index <b>[0..ICapacity::GetCapacity-1]</b>  Index of the tuple to set.
     * @param tuple The new tuple value.
     */
    virtual void Set2I(int32 index, const Vec2I& tuple) = 0;
    
    /*!
     * @brief  Sets the \e index -th tuple.
     * 
     * All extra tuple components will be ignored;all missing components will be set to \c 0 .
     * 
     * @param index <b>[0..ICapacity::GetCapacity-1]</b>  Index of the tuple to set.
     * @param x The new tuple X-coordinate value.
     * @param y The new tuple Y-coordinate value.
     */
    virtual void Set2I(int32 index, int32 x, int32 y) = 0;
    
    /*!
     * @brief  Sets the \e index -th tuple.
     * 
     * All extra tuple components will be ignored;all missing components will be set to \c 0 .
     * 
     * @param index <b>[0..ICapacity::GetCapacity-1]</b>  Index of the tuple to set.
     * @param tuple The new tuple value.
     */
    virtual void Set2L(int32 index, const Vec2L& tuple) = 0;
    
    /*!
     * @brief  Sets the \e index -th tuple.
     * 
     * All extra tuple components will be ignored;all missing components will be set to \c 0 .
     * 
     * @param index <b>[0..ICapacity::GetCapacity-1]</b>  Index of the tuple to set.
     * @param x The new tuple X-coordinate value.
     * @param y The new tuple Y-coordinate value.
     */
    virtual void Set2L(int32 index, int64 x, int64 y) = 0;
    
    /*!
     * @brief  Sets the \e index -th tuple.
     * 
     * All extra tuple components will be ignored;all missing components will be set to \c 0 .
     * 
     * @param index <b>[0..ICapacity::GetCapacity-1]</b>  Index of the tuple to set.
     * @param tuple The new tuple value.
     */
    virtual void Set2S(int32 index, const Vec2S& tuple) = 0;
    
    /*!
     * @brief  Sets the \e index -th tuple.
     * 
     * All extra tuple components will be ignored;all missing components will be set to \c 0 .
     * 
     * @param index <b>[0..ICapacity::GetCapacity-1]</b>  Index of the tuple to set.
     * @param x The new tuple X-coordinate value.
     * @param y The new tuple Y-coordinate value.
     */
    virtual void Set2S(int32 index, int16 x, int16 y) = 0;
    
    /*!
     * @brief  Sets the \e index -th tuple.
     * 
     * All extra tuple components will be ignored;all missing components will be set to \c 0 .
     * 
     * @param index <b>[0..ICapacity::GetCapacity-1]</b>  Index of the tuple to set.
     * @param tuple The new tuple value.
     */
    virtual void Set3B(int32 index, const Vec3B& tuple) = 0;
    
    /*!
     * @brief  Sets the \e index -th tuple.
     * 
     * All extra tuple components will be ignored;all missing components will be set to \c 0 .
     * 
     * @param index <b>[0..ICapacity::GetCapacity-1]</b>  Index of the tuple to set.
     * @param x The new tuple X-coordinate value.
     * @param y The new tuple Y-coordinate value.
     * @param z The new tuple Z-coordinate value.
     */
    virtual void Set3B(int32 index, int8 x, int8 y, int8 z) = 0;
    
    /*!
     * @brief  Sets the \e index -th tuple.
     * 
     * All extra tuple components will be ignored;all missing components will be set to \c 0 .
     * 
     * @param index <b>[0..ICapacity::GetCapacity-1]</b>  Index of the tuple to set.
     * @param tuple The new tuple value.
     */
    virtual void Set3D(int32 index, const Vec3D& tuple) = 0;
    
    /*!
     * @brief  Sets the \e index -th tuple.
     * 
     * All extra tuple components will be ignored;all missing components will be set to \c 0 .
     * 
     * @param index <b>[0..ICapacity::GetCapacity-1]</b>  Index of the tuple to set.
     * @param x The new tuple X-coordinate value.
     * @param y The new tuple Y-coordinate value.
     * @param z The new tuple Z-coordinate value.
     */
    virtual void Set3D(int32 index, float64 x, float64 y, float64 z) = 0;
    
    /*!
     * @brief  Sets the \e index -th tuple.
     * 
     * All extra tuple components will be ignored;all missing components will be set to \c 0 .
     * 
     * @param index <b>[0..ICapacity::GetCapacity-1]</b>  Index of the tuple to set.
     * @param tuple The new tuple value.
     */
    virtual void Set3F(int32 index, const Vec3F& tuple) = 0;
    
    /*!
     * @brief  Sets the \e index -th tuple.
     * 
     * All extra tuple components will be ignored;all missing components will be set to \c 0 .
     * 
     * @param index <b>[0..ICapacity::GetCapacity-1]</b>  Index of the tuple to set.
     * @param x The new tuple X-coordinate value.
     * @param y The new tuple Y-coordinate value.
     * @param z The new tuple Z-coordinate value.
     */
    virtual void Set3F(int32 index, float32 x, float32 y, float32 z) = 0;
    
    /*!
     * @brief  Sets the \e index -th tuple.
     * 
     * All extra tuple components will be ignored;all missing components will be set to \c 0 .
     * 
     * @param index <b>[0..ICapacity::GetCapacity-1]</b>  Index of the tuple to set.
     * @param tuple The new tuple value.
     */
    virtual void Set3I(int32 index, const Vec3I& tuple) = 0;
    
    /*!
     * @brief  Sets the \e index -th tuple.
     * 
     * All extra tuple components will be ignored;all missing components will be set to \c 0 .
     * 
     * @param index <b>[0..ICapacity::GetCapacity-1]</b>  Index of the tuple to set.
     * @param x The new tuple X-coordinate value.
     * @param y The new tuple Y-coordinate value.
     * @param z The new tuple Z-coordinate value.
     */
    virtual void Set3I(int32 index, int32 x, int32 y, int32 z) = 0;
    
    /*!
     * @brief  Sets the \e index -th tuple.
     * 
     * All extra tuple components will be ignored;all missing components will be set to \c 0 .
     * 
     * @param index <b>[0..ICapacity::GetCapacity-1]</b>  Index of the tuple to set.
     * @param tuple The new tuple value.
     */
    virtual void Set3L(int32 index, const Vec3L& tuple) = 0;
    
    /*!
     * @brief  Sets the \e index -th tuple.
     * 
     * All extra tuple components will be ignored;all missing components will be set to \c 0 .
     * 
     * @param index <b>[0..ICapacity::GetCapacity-1]</b>  Index of the tuple to set.
     * @param x The new tuple X-coordinate value.
     * @param y The new tuple Y-coordinate value.
     * @param z The new tuple Z-coordinate value.
     */
    virtual void Set3L(int32 index, int64 x, int64 y, int64 z) = 0;
    
    /*!
     * @brief  Sets the \e index -th tuple.
     * 
     * All extra tuple components will be ignored;all missing components will be set to \c 0 .
     * 
     * @param index <b>[0..ICapacity::GetCapacity-1]</b>  Index of the tuple to set.
     * @param tuple The new tuple value.
     */
    virtual void Set3S(int32 index, const Vec3S& tuple) = 0;
    
    /*!
     * @brief  Sets the \e index -th tuple.
     * 
     * All extra tuple components will be ignored;all missing components will be set to \c 0 .
     * 
     * @param index <b>[0..ICapacity::GetCapacity-1]</b>  Index of the tuple to set.
     * @param x The new tuple X-coordinate value.
     * @param y The new tuple Y-coordinate value.
     * @param z The new tuple Z-coordinate value.
     */
    virtual void Set3S(int32 index, int16 x, int16 y, int16 z) = 0;
    
    /*!
     * @brief  Sets the \e index -th tuple.
     * 
     * All extra tuple components will be ignored;all missing components will be set to \c 0 .
     * 
     * @param index <b>[0..ICapacity::GetCapacity-1]</b>  Index of the tuple to set.
     * @param tuple The new tuple value.
     */
    virtual void Set4B(int32 index, const Vec4B& tuple) = 0;
    
    /*!
     * @brief  Sets the \e index -th tuple.
     * 
     * All extra tuple components will be ignored;all missing components will be set to \c 0 .
     * 
     * @param index <b>[0..ICapacity::GetCapacity-1]</b>  Index of the tuple to set.
     * @param x The new tuple X-coordinate value.
     * @param y The new tuple Y-coordinate value.
     * @param z The new tuple Z-coordinate value.
     * @param w The new tuple W-coordinate value.
     */
    virtual void Set4B(int32 index, int8 x, int8 y, int8 z, int8 w) = 0;
    
    /*!
     * @brief  Sets the \e index -th tuple.
     * 
     * All extra tuple components will be ignored;all missing components will be set to \c 0 .
     * 
     * @param index <b>[0..ICapacity::GetCapacity-1]</b>  Index of the tuple to set.
     * @param tuple The new tuple value.
     */
    virtual void Set4D(int32 index, const Vec4D& tuple) = 0;
    
    /*!
     * @brief  Sets the \e index -th tuple.
     * 
     * All extra tuple components will be ignored;all missing components will be set to \c 0 .
     * 
     * @param index <b>[0..ICapacity::GetCapacity-1]</b>  Index of the tuple to set.
     * @param x The new tuple X-coordinate value.
     * @param y The new tuple Y-coordinate value.
     * @param z The new tuple Z-coordinate value.
     * @param w The new tuple W-coordinate value.
     */
    virtual void Set4D(int32 index, float64 x, float64 y, float64 z, float64 w) = 0;
    
    /*!
     * @brief  Sets the \e index -th tuple.
     * 
     * All extra tuple components will be ignored;all missing components will be set to \c 0 .
     * 
     * @param index <b>[0..ICapacity::GetCapacity-1]</b>  Index of the tuple to set.
     * @param tuple The new tuple value.
     */
    virtual void Set4F(int32 index, const Vec4F& tuple) = 0;
    
    /*!
     * @brief  Sets the \e index -th tuple.
     * 
     * All extra tuple components will be ignored;all missing components will be set to \c 0 .
     * 
     * @param index <b>[0..ICapacity::GetCapacity-1]</b>  Index of the tuple to set.
     * @param x The new tuple X-coordinate value.
     * @param y The new tuple Y-coordinate value.
     * @param z The new tuple Z-coordinate value.
     * @param w The new tuple W-coordinate value.
     */
    virtual void Set4F(int32 index, float32 x, float32 y, float32 z, float32 w) = 0;
    
    /*!
     * @brief  Sets the \e index -th tuple.
     * 
     * All extra tuple components will be ignored;all missing components will be set to \c 0 .
     * 
     * @param index <b>[0..ICapacity::GetCapacity-1]</b>  Index of the tuple to set.
     * @param tuple The new tuple value.
     */
    virtual void Set4I(int32 index, const Vec4I& tuple) = 0;
    
    /*!
     * @brief  Sets the \e index -th tuple.
     * 
     * All extra tuple components will be ignored;all missing components will be set to \c 0 .
     * 
     * @param index <b>[0..ICapacity::GetCapacity-1]</b>  Index of the tuple to set.
     * @param x The new tuple X-coordinate value.
     * @param y The new tuple Y-coordinate value.
     * @param z The new tuple Z-coordinate value.
     * @param w The new tuple W-coordinate value.
     */
    virtual void Set4I(int32 index, int32 x, int32 y, int32 z, int32 w) = 0;
    
    /*!
     * @brief  Sets the \e index -th tuple.
     * 
     * All extra tuple components will be ignored;all missing components will be set to \c 0 .
     * 
     * @param index <b>[0..ICapacity::GetCapacity-1]</b>  Index of the tuple to set.
     * @param tuple The new tuple value.
     */
    virtual void Set4L(int32 index, const Vec4L& tuple) = 0;
    
    /*!
     * @brief  Sets the \e index -th tuple.
     * 
     * All extra tuple components will be ignored;all missing components will be set to \c 0 .
     * 
     * @param index <b>[0..ICapacity::GetCapacity-1]</b>  Index of the tuple to set.
     * @param x The new tuple X-coordinate value.
     * @param y The new tuple Y-coordinate value.
     * @param z The new tuple Z-coordinate value.
     * @param w The new tuple W-coordinate value.
     */
    virtual void Set4L(int32 index, int64 x, int64 y, int64 z, int64 w) = 0;
    
    /*!
     * @brief  Sets the \e index -th tuple.
     * 
     * All extra tuple components will be ignored;all missing components will be set to \c 0 .
     * 
     * @param index <b>[0..ICapacity::GetCapacity-1]</b>  Index of the tuple to set.
     * @param tuple The new tuple value.
     */
    virtual void Set4S(int32 index, const Vec4S& tuple) = 0;
    
    /*!
     * @brief  Sets the \e index -th tuple.
     * 
     * All extra tuple components will be ignored;all missing components will be set to \c 0 .
     * 
     * @param index <b>[0..ICapacity::GetCapacity-1]</b>  Index of the tuple to set.
     * @param x The new tuple X-coordinate value.
     * @param y The new tuple Y-coordinate value.
     * @param z The new tuple Z-coordinate value.
     * @param w The new tuple W-coordinate value.
     */
    virtual void Set4S(int32 index, int16 x, int16 y, int16 z, int16 w) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IVertexData> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x412BAF05;
    
    /*!
     * @brief Tries to cast this object to the given type.
     *
     * @param typeId The ID of the type to cast to.
     *
     * @return The result of the type cast. Can be \c 0 if the requested cast is an invalid 
     *         downcast.
     */
    protected: virtual void* TryCast(int typeId)
    {
      if (typeId == TypeId) return (void*) this;
      void* ptr;
      if ((ptr = ICapacity::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
} } } 

#endif
