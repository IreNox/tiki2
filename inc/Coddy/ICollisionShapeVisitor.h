////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_MESHVISITORS_ICOLLISIONSHAPEVISITOR_H
#define CLODDY_API_MESHVISITORS_ICOLLISIONSHAPEVISITOR_H

#include "CodeX/System.h"

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace MeshVisitors { class SphereCollisionShape; } } }

// Declare interface ::Cloddy::API::MeshVisitors::ICollisionShapeVisitor.

namespace Cloddy { namespace API { namespace MeshVisitors
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Visitor interface for ICollisionShape implementations.
   */
  class NO_VTABLE ICollisionShapeVisitor : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Visits the given collision shape.
     * 
     * @param shape <b>[not-null]</b>  The collision shape.
     * @param userData Optional user object.
     */
    virtual void Visit(SphereCollisionShape* shape, Object* userData) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<ICollisionShapeVisitor> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xD0AC3254;
    
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
