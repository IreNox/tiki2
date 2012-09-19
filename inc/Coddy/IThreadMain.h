////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_THREADING_ITHREADMAIN_H
#define CLODDY_CORE_THREADING_ITHREADMAIN_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "CodeX/IDisposable.h"
#include "Cloddy/IRunnable.h"
#include "Cloddy/IThreadContext.h"

// Declare interface ::Cloddy::Core::Threading::IThreadMain.

namespace Cloddy { namespace Core { namespace Threading
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::System::IRunnable;
  using CodeX::System::IDisposable;
  
  /*!
   * @brief  Base interface for classes that provide a main method for a background thread.
   */
  class NO_VTABLE IThreadMain : public virtual IRunnable<Ref<IThreadContext> >, public virtual IDisposable
  {
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Signals the running thread main method to terminate gracefully.
     * 
     * This method is called exactly once;either when the Thread::Stop method is invoked for the 
     * first time or the thread is disposed.
     */
    virtual void RequestStop() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IThreadMain> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xFB0E50D;
    
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
      if ((ptr = IRunnable<Ref<IThreadContext> >::TryCast(typeId)) != 0) return ptr;
      if ((ptr = IDisposable::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
} } } 

#endif
