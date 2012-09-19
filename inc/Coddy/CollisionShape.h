////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_MESHVISITORS_COLLISIONSHAPE_H
#define CLODDY_API_MESHVISITORS_COLLISIONSHAPE_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/ICollisionShape.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace MeshVisitors { class ICollisionShapeVisitor; } } }
namespace Cloddy { namespace API { namespace VertexData { class IVertexData; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace MeshVisitors { class ContactPointInfo; } } }
namespace Cloddy { namespace API { namespace Util { class WorldTransformPose; } } }

// Declare class ::Cloddy::API::MeshVisitors::CollisionShape.

namespace Cloddy { namespace API { namespace MeshVisitors
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::VertexData::IVertexData;
  
  // Use referenced classes.
  
  using Cloddy::API::Util::WorldTransformPose;
  
  /*!
   * @brief  Abstract base class for ICollisionShape implementations.
   */
  class CollisionShape : public virtual ICollisionShape
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual float32 GetBoundingSphereRadius();
    
    virtual void SetBoundingSphereRadius(float32 value);
    
    virtual Ptr<WorldTransformPose> GetPose();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void Accept(ICollisionShapeVisitor* visitor, Object* userData) = 0;
    
    virtual void BeginCollisionCheck(IVertexData* position);
    
    virtual bool CheckTriangleCollision(int32 v0, int32 v1, int32 v2, ContactPointInfo* contactPoint) = 0;
    
    virtual void EndCollisionCheck();
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Attributes
    // ---------------------------------------------------------------------------------------------
  protected:
    
    /*!
     * @brief  X-coordinate of shape center.
     */
    float64 centerX;
    
    /*!
     * @brief  Y-coordinate of shape center.
     */
    float64 centerY;
    
    /*!
     * @brief  Z-coordinate of shape center.
     */
    float64 centerZ;
    
    /*!
     * @brief  The global pose of this shape (ie. the world transform).
     */
    Ptr<WorldTransformPose> pose;
    
    /*!
     * @brief  Data container for vertex positions.
     */
    Ptr<IVertexData> position;
    
    /*!
     * @brief  Bounding sphere radius of this shape.
     */
    float32 radius;
    
    /*!
     * @brief  Square value of #radius.
     */
    float32 radiusSqr;
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of CollisionShape.
     */
    CollisionShape();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<CollisionShape> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x876ED7C5;
    
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
      if ((ptr = ICollisionShape::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
