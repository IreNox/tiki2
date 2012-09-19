////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_PHYSICS_ICOLLISIONGEOMETRYBUILDER_H
#define CLODDY_API_PHYSICS_ICOLLISIONGEOMETRYBUILDER_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "CodeX/IDisposable.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Physics { class ICollisionGeometry; } } }
namespace Cloddy { namespace API { namespace VertexData { class IVertexDataCollection; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Rendering { class MeshBuilder; } } }

// Declare interface ::Cloddy::API::Physics::ICollisionGeometryBuilder.

namespace Cloddy { namespace API { namespace Physics
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::VertexData::IVertexDataCollection;
  using CodeX::System::IDisposable;
  
  // Use referenced classes.
  
  using Cloddy::API::Rendering::MeshBuilder;
  
  /*!
   * @brief  Base interface for classes that build static collision geometry for a physics module.
   */
  class NO_VTABLE ICollisionGeometryBuilder : public virtual IDisposable
  {
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Creates static collision geometry using the given exported CLOD mesh data.
     * 
     * @param meshBuilder <b>[not-null]</b>  The MeshBuilder object that has been used to export 
     * CLOD mesh data.
     * @param vertexDataCollection <b>[not-null]</b>  The application vertex data containers.
     * 
     * @return <b>[not-null]</b>  The created ICollisionGeometry object.
     */
    virtual Ptr<ICollisionGeometry> BuildCollisionGeometry(MeshBuilder* meshBuilder, IVertexDataCollection* vertexDataCollection) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<ICollisionGeometryBuilder> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xABBEDB33;
    
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
      if ((ptr = IDisposable::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
} } } 

#endif
