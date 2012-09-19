////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_MESHVISITORS_ICOLLISIONSHAPE_H
#define CLODDY_API_MESHVISITORS_ICOLLISIONSHAPE_H

#include "CodeX/System.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace MeshVisitors { class ICollisionShapeVisitor; } } }
namespace Cloddy { namespace API { namespace VertexData { class IVertexData; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace MeshVisitors { class ContactPointInfo; } } }
namespace Cloddy { namespace API { namespace Util { class WorldTransformPose; } } }

// Declare interface ::Cloddy::API::MeshVisitors::ICollisionShape.

namespace Cloddy { namespace API { namespace MeshVisitors
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::VertexData::IVertexData;
  
  // Use referenced classes.
  
  using Cloddy::API::Util::WorldTransformPose;
  
  /*!
   * @brief  Base interface for collision shapes.
   */
  class NO_VTABLE ICollisionShape : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The bounding sphere radius of this collision shape.
     * 
     * @return <b>[>0]</b>  The bounding sphere radius,in terrain-space.
     */
    virtual float32 GetBoundingSphereRadius() = 0;
    
    /*!
     * @brief  The bounding sphere radius of this collision shape.
     * 
     * @param value <b>[>0]</b>  The bounding sphere radius,in terrain-space.
     */
    virtual void SetBoundingSphereRadius(float32 value) = 0;
    
    /*!
     * @brief  Returns the global pose of this collision shape in terrain-space.
     * 
     * @return <b>[not-null]</b>  The world transform object that represents the global pose.
     */
    virtual Ptr<WorldTransformPose> GetPose() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Accepts the given visitor object.
     * 
     * @param visitor <b>[not-null]</b>  The visitor object.
     * @param userData Optional user data.
     */
    virtual void Accept(ICollisionShapeVisitor* visitor, Object* userData) = 0;
    
    /*!
     * @brief  Begins a collision test on this shape.
     * 
     * @param position <b>[not-null]</b>  Data container for vertex positions.
     */
    virtual void BeginCollisionCheck(IVertexData* position) = 0;
    
    /*!
     * @brief  Performs a collision test between this shape and the given triangle.
     * 
     * @param v0 <b>[>=0]</b>  Index of first triangle vertex.
     * @param v1 <b>[>=0]</b>  Index of second triangle vertex.
     * @param v2 <b>[>=0]</b>  Index of third triangle vertex.
     * @param contactPoint <b>[not-null]</b>  The output contact point.
     * 
     * @return \c true  if a collision has been detected,\c false  if not.
     */
    virtual bool CheckTriangleCollision(int32 v0, int32 v1, int32 v2, ContactPointInfo* contactPoint) = 0;
    
    /*!
     * @brief  Ends the current collision test.
     */
    virtual void EndCollisionCheck() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<ICollisionShape> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xF2741582;
    
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
      return (void*) 0;
    }
  };
} } } 

#endif
