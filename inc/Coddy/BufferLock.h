////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_KERNEL_BUFFERLOCK_H
#define CLODDY_KERNEL_BUFFERLOCK_H

#include "CodeX/System.h"

// Forward declare referenced classes.

namespace Cloddy { namespace Kernel { class RefinementBufferDual; } }
namespace Cloddy { namespace Kernel { class RefinementBufferSingle; } }
namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::Kernel::BufferLock.

namespace Cloddy { namespace Kernel
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced classes.
  
  using CodeX::System::ByteBuffer;
  
  /*!
   * @brief  A BufferLock object is used to represent the result of a call 
   *         to IVertexBuffer::LockBuffer.
   * 
   * When locking a vertex buffer,the following situations can arise:
   *   - The requested vertex buffer region has been locked,the locked vertices can be updated (
   *   see #Locked).
   *   - The requested vertex buffer region is temporarily unavailable,the vertex updates must be 
   *   performed at a later time (see #Delay).
   *   - The application is shutting down,the vertex updates can be discarded (see #Discard).
   */
  class BufferLock : public virtual Object
  {
    // Declare friend classes.
    
    friend class RefinementBufferDual;
    friend class RefinementBufferSingle;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Returns the locked vertex buffer region.
     * 
     * @return The ByteBuffer representing the locked vertex buffer region.
     */
    Ptr<ByteBuffer> GetBuffer();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  The requested vertex buffer region is temporarily unavailable.
     * 
     * The currently buffered vertex updates are preserved and will be applied at a later time.
     */
    void Delay();
    
    /*!
     * @brief  The application is shutting down,the buffered vertex updates can be discarded.
     */
    void Discard();
    
    /*!
     * @brief  The requested vertex buffer region has been locked and the buffered vertex updates 
     *         can be applied.
     * 
     * The first byte of the given ByteBuffer (i.e.ByteBuffer::GetPosition)corresponds to the first 
     * byte of the first locked vertex.
     * 
     * @param buffer <b>[not-null]</b>  The ByteBuffer that represents the locked vertex buffer 
     * region.
     */
    void Locked(ByteBuffer* buffer);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The locked vertex buffer region.
     */
    Ptr<ByteBuffer> buffer;
    
    /*!
     * @brief  Can the buffered vertex updates be discarded?
     */
    bool discard;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Has the vertex buffer update been delayed?
     * 
     * @return \c true  if the update has been delayed,\c false  if not.
     */
    bool IsDelayed();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
  public:
    
    BufferLock();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<BufferLock> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x567137D2;
    
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
  
} } 

#endif
