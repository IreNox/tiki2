////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_UTIL_PROGRESS_RUNNINGOPERATION_THREADMAIN_H
#define CLODDY_API_UTIL_PROGRESS_RUNNINGOPERATION_THREADMAIN_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/ThreadMainBase.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Logging { class ILogger; } } }
namespace Cloddy { namespace Core { namespace Threading { class IThreadContext; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace Logging { class LoggingHelper; } } }

// Declare class ::Cloddy::API::Util::Progress::RunningOperation_ThreadMain.

namespace Cloddy { namespace API { namespace Util { namespace Progress
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::Logging::ILogger;
  using Cloddy::Core::Threading::IThreadContext;
  
  // Use referenced classes.
  
  using Cloddy::Core::Logging::LoggingHelper;
  using Cloddy::Core::Threading::ThreadMainBase;
  
  class RunningOperation_ThreadMain : public ThreadMainBase
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual void Run(IThreadContext* argument);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The logger object of this class.
     */
    static const StaticPtr<ILogger> Logger;
    
    // ---------------------------------------------------------------------------------------------
    // Static Initializer Functions
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Static initializer function for field Logger.
     */
    static Object* StaticInitializer_Logger();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<RunningOperation_ThreadMain> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xF2E98013;
    
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
      return (void*) 0;
    }
  };
  
} } } } 

#endif
