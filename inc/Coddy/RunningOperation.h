////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_UTIL_PROGRESS_RUNNINGOPERATION_H
#define CLODDY_API_UTIL_PROGRESS_RUNNINGOPERATION_H

#include "CodeX/System_Native.h"

// Include referenced classes.

#include "CodeX/Disposable.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Util { namespace Progress { class IOperation; } } } }
namespace Cloddy { namespace API { namespace Util { namespace Progress { class IProgressListener; } } } }
namespace Cloddy { namespace Core { namespace Collections { template<class> class IList; } } }
namespace Cloddy { namespace Core { namespace Logging { class ILogger; } } }
namespace Cloddy { namespace Core { namespace Threading { class IThread; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Util { namespace Progress { class Operation; } } } }
namespace Cloddy { namespace API { namespace Util { namespace Progress { class ProgressMonitor; } } } }
namespace Cloddy { namespace API { namespace Util { namespace Progress { class RunningOperation_ThreadMain; } } } }
namespace Cloddy { namespace Core { namespace Logging { class LoggingHelper; } } }
namespace Cloddy { namespace Core { namespace Threading { class Thread; } } }
namespace CodeX { namespace System { class ErrorInfo; } }
namespace CodeX { namespace System { class Monitor; } }

// Declare class ::Cloddy::API::Util::Progress::RunningOperation.

namespace Cloddy { namespace API { namespace Util { namespace Progress
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::Collections::IList;
  using Cloddy::Core::Logging::ILogger;
  using Cloddy::Core::Threading::IThread;
  
  // Use referenced classes.
  
  using Cloddy::Core::Logging::LoggingHelper;
  using Cloddy::Core::Threading::Thread;
  using CodeX::System::Disposable;
  using CodeX::System::ErrorInfo;
  using CodeX::System::Monitor;
  
  /*!
   * @brief  Represents a running operation.
   * 
   * @see IOperation
   * @see IProgressMonitor
   */
  class RunningOperation : public Disposable
  {
    // Declare friend classes.
    
    friend class Operation;
    friend class RunningOperation_ThreadMain;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Returns the background thread that executes the operation.
     * 
     * @return <b>[not-null]</b>  The background thread.
     */
    Ptr<IThread> GetBackgroundThread();
    
    /*!
     * @brief  The current status message.
     * 
     * @return The current status message.
     */
    String GetCurrentStatusMessage();
    
    /*!
     * @brief  The elapsed time of the operation,in seconds.
     * 
     * @return The elapsed time,in seconds.
     */
    float64 GetElapsedTime();
    
    /*!
     * @brief  The error that has occured most recently.
     * 
     * @return The error or \c null .
     */
    Ptr<ErrorInfo> GetError();
    
    /*!
     * @brief  The current progress,in percent.
     * 
     * @return <b>[0..100]</b>  The current progress,in percent.
     */
    int32 GetFinishedPercent();
    
    /*!
     * @brief  The estimated remaining time of the operation,in seconds.
     * 
     * @return The remaining time,in seconds.
     */
    float64 GetRemainingTime();
    
    /*!
     * @brief  The estimated total time of the operation,in seconds.
     * 
     * @return The total time,in seconds.
     */
    float64 GetTotalTime();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Adds a new progress listener.
     * 
     * @param progressListener <b>[not-null]</b>  The progress listener to add.
     */
    void AddProgressListener(IProgressListener* progressListener);
    
    void Cancel();
    
    /*!
     * @brief  Removes the given progress listener.
     * 
     * @param progressListener <b>[not-null]</b>  The progress listener to remove.
     */
    void RemoveProgressListener(IProgressListener* progressListener);
    
    /*!
     * @brief  Updates the progress values.
     * 
     * @return \c true  if the operation is running,\c false  if the operation has finished or an 
     * error has occurred.
     */
    bool Update();
    
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
     * @brief  The logger object of this class.
     */
    static const StaticPtr<ILogger> Logger;
    
    /*!
     * @brief  The elapsed time of the operation,in seconds.
     */
    float64 elapsedTime;
    
    /*!
     * @brief  The error that has occured most recently.
     */
    Ptr<ErrorInfo> error;
    
    /*!
     * @brief  The current progress,in percent.
     */
    int32 finishedPercent;
    
    /*!
     * @brief  The monitor used for thread synchronization.
     */
    Ptr<Monitor> monitor;
    
    /*!
     * @brief  The operation that is running.
     */
    Ptr<IOperation> operation;
    
    /*!
     * @brief  The registered progress listeners.
     */
    Ptr<IList<Ref<IProgressListener> > > progressListeners;
    
    /*!
     * @brief  The progress monitor object used for tracking the progress of the running operation.
     */
    Ptr<ProgressMonitor> progressMonitor;
    
    /*!
     * @brief  The estimated remaining time of the operation,in seconds.
     */
    float64 remainingTime;
    
    /*!
     * @brief  The start time of the operation.
     */
    int32 startTime;
    
    /*!
     * @brief  The thread that executes the background operation.
     */
    Ptr<Thread> thread;
    
    /*!
     * @brief  The estimated total time of the operation,in seconds.
     */
    float64 totalTime;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of RunningOperation.
     * 
     * @param operation The operation to run.
     */
    RunningOperation(IOperation* operation);
    
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
    public: typedef Ptr<RunningOperation> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x32051831;
    
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
      return (void*) 0;
    }
    
    // ---------------------------------------------------------------------------------------------
    // Native code
    // ---------------------------------------------------------------------------------------------
    
    NATIVE_BLOCK_BEGIN ("CCFA3AB7-ECFC-45DB-8892-CA9CF8F4E255")
    
    // Nothing to do here.
    
    NATIVE_BLOCK_END   ("CCFA3AB7-ECFC-45DB-8892-CA9CF8F4E255")
  };
  
} } } } 

#endif
