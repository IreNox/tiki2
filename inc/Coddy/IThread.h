////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_THREADING_ITHREAD_H
#define CLODDY_CORE_THREADING_ITHREAD_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/ThreadPriority.h"

// Declare interface ::Cloddy::Core::Threading::IThread.

namespace Cloddy { namespace Core { namespace Threading
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Base interface for background threads.
   */
  class NO_VTABLE IThread : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Returns if this thread is running.
     * 
     * @return \c true  if this thread is running,\c false  if it is not.
     */
    virtual bool IsAlive() = 0;
    
    /*!
     * @brief  Returns the thread name.
     * 
     * @return The thread name or \c null  if this does not have a name.
     */
    virtual String GetName() = 0;
    
    /*!
     * @brief  Returns the native thread handle.
     * 
     * This value can be used to set platform-specific scheduling options.
     * 
     * @return The thread ID value.
     */
    virtual void* GetNativeThreadId() = 0;
    
    /*!
     * @brief  Gets or sets the thread priority.
     * 
     * The default value is ThreadPriority::ThreadPriority_Normal.
     * 
     * @return The thread priority.
     */
    virtual ThreadPriority GetPriority() = 0;
    
    /*!
     * @brief  Gets or sets the thread priority.
     * 
     * The default value is ThreadPriority::ThreadPriority_Normal.
     * 
     * @param value The thread priority.
     */
    virtual void SetPriority(ThreadPriority value) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IThread> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xA0652446;
    
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
