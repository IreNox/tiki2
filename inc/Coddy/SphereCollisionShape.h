////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_MESHVISITORS_SPHERECOLLISIONSHAPE_H
#define CLODDY_API_MESHVISITORS_SPHERECOLLISIONSHAPE_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/CollisionShape.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace MeshVisitors { class ICollisionShapeVisitor; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace MeshVisitors { class ContactPointInfo; } } }

// Declare class ::Cloddy::API::MeshVisitors::SphereCollisionShape.

namespace Cloddy { namespace API { namespace MeshVisitors
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  A sphere collision shape.
   */
  class SphereCollisionShape : public CollisionShape
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual void Accept(ICollisionShapeVisitor* visitor, Object* userData);
    
    virtual bool CheckTriangleCollision(int32 v0, int32 v1, int32 v2, ContactPointInfo* contactPoint);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<SphereCollisionShape> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x5768FD0C;
    
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
      if ((ptr = CollisionShape::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
