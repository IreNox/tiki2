////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_THREADING_ITHREADJOINCALLBACK_H
#define CLODDY_CORE_THREADING_ITHREADJOINCALLBACK_H

#include "CodeX/System.h"

// Declare interface ::Cloddy::Core::Threading::IThreadJoinCallback.

namespace Cloddy { namespace Core { namespace Threading
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Base interface for classes that accept callbacks while waiting for a thread to 
   *         terminate.
   */
  class NO_VTABLE IThreadJoinCallback : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  This method is invoked regularly when one thread has requested another one to stop 
     *         and is waiting for its termination.
     * 
     * This callback allows a thread to perform actions while being blocked inside Thread::Join 
     * resp. Disposable::Dispose (which implicitly joins on the thread),for example flushing 
     * buffers in order to avoid dead locks.
     */
    virtual void WaitingForStop() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IThreadJoinCallback> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x42D60631;
    
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
