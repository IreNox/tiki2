////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_VERTEXDATA_LONG2_H
#define CLODDY_API_VERTEXDATA_LONG2_H

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

// Include referenced classes.

#include "Cloddy/Long1.h"

// Declare class ::Cloddy::API::VertexData::Long2.

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
  
  /*!
   * @brief  Data container for application vertex data:two 64-bit integer values.
   */
  class Long2 : public Long1
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual int32 GetSize();
    
    /*!
     * @brief  Second value.
     */
    Array<int64> Y;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new data container.
     * 
     * @param capacity The capacity,in vertices.
     */
    Long2(int32 capacity);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual Vec2B Get2B(int32 index);
    
    virtual Vec2D Get2D(int32 index);
    
    virtual Vec2F Get2F(int32 index);
    
    virtual Vec2I Get2I(int32 index);
    
    virtual Vec2L Get2L(int32 index);
    
    virtual Vec2S Get2S(int32 index);
    
    virtual Vec3B Get3B(int32 index);
    
    virtual Vec3D Get3D(int32 index);
    
    virtual Vec3F Get3F(int32 index);
    
    virtual Vec3I Get3I(int32 index);
    
    virtual Vec3L Get3L(int32 index);
    
    virtual Vec3S Get3S(int32 index);
    
    virtual Vec4B Get4B(int32 index);
    
    virtual Vec4D Get4D(int32 index);
    
    virtual Vec4F Get4F(int32 index);
    
    virtual Vec4I Get4I(int32 index);
    
    virtual Vec4L Get4L(int32 index);
    
    virtual Vec4S Get4S(int32 index);
    
    virtual void Set1B(int32 index, int8 tuple);
    
    virtual void Set1D(int32 index, float64 tuple);
    
    virtual void Set1F(int32 index, float32 tuple);
    
    virtual void Set1I(int32 index, int32 tuple);
    
    virtual void Set1L(int32 index, int64 tuple);
    
    virtual void Set1S(int32 index, int16 tuple);
    
    virtual void Set2B(int32 index, const Vec2B& tuple);
    
    virtual void Set2B(int32 index, int8 x, int8 y);
    
    virtual void Set2D(int32 index, const Vec2D& tuple);
    
    virtual void Set2D(int32 index, float64 x, float64 y);
    
    virtual void Set2F(int32 index, const Vec2F& tuple);
    
    virtual void Set2F(int32 index, float32 x, float32 y);
    
    virtual void Set2I(int32 index, const Vec2I& tuple);
    
    virtual void Set2I(int32 index, int32 x, int32 y);
    
    virtual void Set2L(int32 index, const Vec2L& tuple);
    
    virtual void Set2L(int32 index, int64 x, int64 y);
    
    virtual void Set2S(int32 index, const Vec2S& tuple);
    
    virtual void Set2S(int32 index, int16 x, int16 y);
    
    virtual void Set3B(int32 index, const Vec3B& tuple);
    
    virtual void Set3B(int32 index, int8 x, int8 y, int8 z);
    
    virtual void Set3D(int32 index, const Vec3D& tuple);
    
    virtual void Set3D(int32 index, float64 x, float64 y, float64 z);
    
    virtual void Set3F(int32 index, const Vec3F& tuple);
    
    virtual void Set3F(int32 index, float32 x, float32 y, float32 z);
    
    virtual void Set3I(int32 index, const Vec3I& tuple);
    
    virtual void Set3I(int32 index, int32 x, int32 y, int32 z);
    
    virtual void Set3L(int32 index, const Vec3L& tuple);
    
    virtual void Set3L(int32 index, int64 x, int64 y, int64 z);
    
    virtual void Set3S(int32 index, const Vec3S& tuple);
    
    virtual void Set3S(int32 index, int16 x, int16 y, int16 z);
    
    virtual void Set4B(int32 index, const Vec4B& tuple);
    
    virtual void Set4B(int32 index, int8 x, int8 y, int8 z, int8 w);
    
    virtual void Set4D(int32 index, const Vec4D& tuple);
    
    virtual void Set4D(int32 index, float64 x, float64 y, float64 z, float64 w);
    
    virtual void Set4F(int32 index, const Vec4F& tuple);
    
    virtual void Set4F(int32 index, float32 x, float32 y, float32 z, float32 w);
    
    virtual void Set4I(int32 index, const Vec4I& tuple);
    
    virtual void Set4I(int32 index, int32 x, int32 y, int32 z, int32 w);
    
    virtual void Set4L(int32 index, const Vec4L& tuple);
    
    virtual void Set4L(int32 index, int64 x, int64 y, int64 z, int64 w);
    
    virtual void Set4S(int32 index, const Vec4S& tuple);
    
    virtual void Set4S(int32 index, int16 x, int16 y, int16 z, int16 w);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<Long2> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xB3897A38;
    
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
      if ((ptr = Long1::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
