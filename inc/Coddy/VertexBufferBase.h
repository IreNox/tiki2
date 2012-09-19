////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_KERNEL_VERTEXBUFFERBASE_H
#define CLODDY_KERNEL_VERTEXBUFFERBASE_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IVertexBuffer.h"

// Include referenced classes.

#include "CodeX/Disposable.h"

// Forward declare referenced classes.

namespace Cloddy { namespace Kernel { class BufferLock; } }

// Declare class ::Cloddy::Kernel::VertexBufferBase.

namespace Cloddy { namespace Kernel
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced classes.
  
  using CodeX::System::Disposable;
  
  /*!
   * @brief  Abstract base class for IVertexBuffer implementations.
   */
  class VertexBufferBase : public Disposable, public virtual IVertexBuffer
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual int32 GetCapacity();
    
    virtual int32 GetVertexSize();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void LockBuffer(int32 min, int32 max, int32 count, void* userData, BufferLock* bufferLock) = 0;
    
    virtual void Unlock() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Constructors
    // ---------------------------------------------------------------------------------------------
  protected:
    
    /*!
     * @brief  Creates a new instance of VertexBufferBase.
     * 
     * @param capacity <b>[>0]</b>  The vertex buffer capacity,in vertices.
     * @param vertexSize <b>[>0]</b>  The vertes size,in bytes.
     */
    VertexBufferBase(int32 capacity, int32 vertexSize);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The vertex buffer capacity,in vertices.
     */
    int32 capacity;
    
    /*!
     * @brief  The vertes size,in bytes.
     */
    int32 vertexSize;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<VertexBufferBase> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x2605FA0E;
    
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
      if ((ptr = IVertexBuffer::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } 

#endif
