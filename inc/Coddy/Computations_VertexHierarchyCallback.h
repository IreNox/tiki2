////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_VERTEXFACTORIES_COMPUTATIONS_VERTEXHIERARCHYCALLBACK_H
#define CLODDY_API_VERTEXFACTORIES_COMPUTATIONS_VERTEXHIERARCHYCALLBACK_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IMeshCallback.h"
#include "Cloddy/IVertexHierarchyCallback.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace VertexData { class IVertexData; } } }
namespace Cloddy { namespace Kernel { class IProvider; } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace VertexData { class Int1; } } }
namespace Cloddy { namespace API { namespace VertexFactories { class Computations; } } }

// Declare class ::Cloddy::API::VertexFactories::Computations_VertexHierarchyCallback.

namespace Cloddy { namespace API { namespace VertexFactories
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::VertexData::IVertexData;
  using Cloddy::Kernel::IMeshCallback;
  using Cloddy::Kernel::IProvider;
  using Cloddy::Kernel::IVertexHierarchyCallback;
  
  // Use referenced classes.
  
  using Cloddy::API::VertexData::Int1;
  
  class Computations_VertexHierarchyCallback : public virtual IVertexHierarchyCallback, public virtual IMeshCallback
  {
    // Declare friend classes.
    
    friend class Computations;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual void BeginMeshAction(IProvider* provider);
    
    virtual void EndMeshAction();
    
    virtual bool VertexHierarchyNode(int32 vertex, int32 parent);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    bool computeElevationMax;
    
    bool computeElevationMin;
    
    bool computeRadius;
    
    int32 elevation;
    
    Ptr<Int1> elevationMax;
    
    Ptr<Int1> elevationMin;
    
    Ptr<IVertexData> position;
    
    Ptr<IVertexData> radius;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
  public:
    
    Computations_VertexHierarchyCallback();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<Computations_VertexHierarchyCallback> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xF939FAE1;
    
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
      if ((ptr = IVertexHierarchyCallback::TryCast(typeId)) != 0) return ptr;
      if ((ptr = IMeshCallback::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
