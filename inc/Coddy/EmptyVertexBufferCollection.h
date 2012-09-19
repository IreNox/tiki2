////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_KERNEL_EMPTYVERTEXBUFFERCOLLECTION_H
#define CLODDY_KERNEL_EMPTYVERTEXBUFFERCOLLECTION_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IVertexBufferCollection.h"

// Include referenced classes.

#include "CodeX/Disposable.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Kernel { class IVertexBuffer; } }

// Forward declare referenced classes.

namespace Cloddy { namespace Kernel { class VertexBufferCollection; } }

// Declare class ::Cloddy::Kernel::EmptyVertexBufferCollection.

namespace Cloddy { namespace Kernel
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced classes.
  
  using CodeX::System::Disposable;
  
  /*!
   * @brief  An IVertexBufferCollection implementation that contains no vertex buffers.
   * 
   * The EmptyVertexBufferCollection class can be used when it is not necessary to generate GPU 
   * vertex data (eg. when exporting triangle meshes from a CLOD mesh during a preprocessing step).
   */
  class EmptyVertexBufferCollection : public Disposable, public virtual IVertexBufferCollection
  {
    // Declare friend classes.
    
    friend class VertexBufferCollection;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual int32 GetCapacity();
    
    virtual int32 GetCount();
    
    virtual int32 GetVertexSize();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual Ptr<IVertexBuffer> Get(int32 index);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The capacity of the vertex buffer collection.
     */
    int32 capacity;
    
    /*!
     * @brief  The vertex size of the vertex buffer collection,in bytes.
     */
    int32 vertexSize;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of EmptyVertexBufferCollection.
     * 
     * @param capacity The capacity of the vertex buffer collection.
     * @param vertexSize The vertex size of the vertex buffer collection,in bytes.
     */
    EmptyVertexBufferCollection(int32 capacity, int32 vertexSize);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<EmptyVertexBufferCollection> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xAA91A090;
    
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
      if ((ptr = Disposable::TryCast(typeId)) != 0) return ptr;
      if ((ptr = IVertexBufferCollection::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } 

#endif
