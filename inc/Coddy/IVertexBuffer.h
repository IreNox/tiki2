////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_KERNEL_IVERTEXBUFFER_H
#define CLODDY_KERNEL_IVERTEXBUFFER_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/ICapacity.h"
#include "CodeX/IDisposable.h"
#include "Cloddy/IVertexSize.h"

// Forward declare referenced classes.

namespace Cloddy { namespace Kernel { class BufferLock; } }

// Declare interface ::Cloddy::Kernel::IVertexBuffer.

namespace Cloddy { namespace Kernel
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using CodeX::System::IDisposable;
  
  /*!
   * @brief  Represents the applications vertex buffer.
   */
  class NO_VTABLE IVertexBuffer : public virtual ICapacity, public virtual IVertexSize, public virtual IDisposable
  {
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Locks a region of the buffer for writing.
     * 
     * @param min <b>[>=0]</b>  Minimum vertex buffer element index.
     * @param max <b>[>=0]</b>  Maximum vertex buffer element index.
     * @param count <b>[>=0]</b>  The number of vertices that will be updated in the locked region.
     * @param userData Optional user data object.
     * @param bufferLock <b>[not-null]</b>  The BufferLock object to use for reporting the result 
     * of the region lock.
     */
    virtual void LockBuffer(int32 min, int32 max, int32 count, void* userData, BufferLock* bufferLock) = 0;
    
    /*!
     * @brief  Unlocks a previously locked buffer region.
     * 
     * The #Unlock method must only be called if a locked buffer has been specified 
     * via BufferLock::Locked.
     */
    virtual void Unlock() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IVertexBuffer> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x3246B55A;
    
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
      if ((ptr = ICapacity::TryCast(typeId)) != 0) return ptr;
      if ((ptr = IVertexSize::TryCast(typeId)) != 0) return ptr;
      if ((ptr = IDisposable::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
} } 

#endif
