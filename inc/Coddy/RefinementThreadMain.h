////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_KERNEL_REFINEMENTTHREADMAIN_H
#define CLODDY_KERNEL_REFINEMENTTHREADMAIN_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IThreadJoinCallback.h"

// Include referenced classes.

#include "Cloddy/ThreadMainBase.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Threading { class IThreadContext; } } }
namespace Cloddy { namespace Kernel { class IRefinementBuffer; } }

// Forward declare referenced classes.

namespace Cloddy { namespace Kernel { class CloddyKernel; } }

// Declare class ::Cloddy::Kernel::RefinementThreadMain.

namespace Cloddy { namespace Kernel
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::Threading::IThreadContext;
  using Cloddy::Core::Threading::IThreadJoinCallback;
  
  // Use referenced classes.
  
  using Cloddy::Core::Threading::ThreadMainBase;
  
  class RefinementThreadMain : public ThreadMainBase, public virtual IThreadJoinCallback
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual void RequestStop();
    
    virtual void Run(IThreadContext* argument);
    
    virtual void WaitingForStop();
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
  protected:
    
    virtual void DisposeManaged();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The CloddyKernel instance.
     */
    Ptr<CloddyKernel> kernel;
    
    /*!
     * @brief  The used IRefinementBuffer instance.
     */
    Ptr<IRefinementBuffer> refinementBuffer;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<RefinementThreadMain> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xEA2ACFE9;
    
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
      if ((ptr = ThreadMainBase::TryCast(typeId)) != 0) return ptr;
      if ((ptr = IThreadJoinCallback::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } 

#endif
