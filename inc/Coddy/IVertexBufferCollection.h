////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_KERNEL_IVERTEXBUFFERCOLLECTION_H
#define CLODDY_KERNEL_IVERTEXBUFFERCOLLECTION_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/ICapacity.h"
#include "CodeX/IDisposable.h"
#include "Cloddy/IVertexSize.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Kernel { class IVertexBuffer; } }

// Declare interface ::Cloddy::Kernel::IVertexBufferCollection.

namespace Cloddy { namespace Kernel
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using CodeX::System::IDisposable;
  
  /*!
   * @brief  Base interface for classes that represent a collection of vertex buffers.
   */
  class NO_VTABLE IVertexBufferCollection : public virtual IDisposable, public virtual ICapacity, public virtual IVertexSize
  {
    // ---------------------------------------------------------------------------------------------
    // Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The number of vertex buffers in this collection.
     * 
     * @return <b>[>=0]</b>  The number of vertex buffers.
     */
    virtual int32 GetCount() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Returns an IVertexBuffer of this collection.
     * 
     * @param index <b>[0..#GetCount-1]</b>  Index of the vertex buffer to return.
     * 
     * @return <b>[not-null]</b>  The IVertexBuffer object.
     */
    virtual Ptr<IVertexBuffer> Get(int32 index) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IVertexBufferCollection> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x5B5731DE;
    
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
      if ((ptr = ICapacity::TryCast(typeId)) != 0) return ptr;
      if ((ptr = IVertexSize::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
} } 

#endif
