////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_THREADING_THREAD_H
#define CLODDY_CORE_THREADING_THREAD_H

#include "CodeX/System_Native.h"

// Include referenced enumerations.

#include "Cloddy/ThreadPriority.h"

// Include referenced interfaces.

#include "Cloddy/IThread.h"
#include "Cloddy/IThreadContext.h"

// Include referenced classes.

#include "CodeX/Disposable.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Logging { class ILogger; } } }
namespace Cloddy { namespace Core { namespace Threading { class IThreadJoinCallback; } } }
namespace Cloddy { namespace Core { namespace Threading { class IThreadMain; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace Logging { class LoggingHelper; } } }
namespace CodeX { namespace System { class ErrorInfo; } }
namespace CodeX { namespace System { class Monitor; } }

// Declare class ::Cloddy::Core::Threading::Thread.

namespace Cloddy { namespace Core { namespace Threading
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::Logging::ILogger;
  
  // Use referenced classes.
  
  using Cloddy::Core::Logging::LoggingHelper;
  using CodeX::System::Disposable;
  using CodeX::System::ErrorInfo;
  using CodeX::System::Monitor;
  
  /*!
   * @brief  The Thread represents a background thread.
   * 
   * This class is platform and framework independent.In order to create a background thread,
   * the IThreadMain interface must be implemented and an instance must be passed to the #Start 
   * method.
   */
  class Thread : public Disposable, public virtual IThread, public virtual IThreadContext
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The error info of the exception that has occurred in the \c Run  method of the 
     *         threads main method (see IThreadMain).
     * 
     * @return The ErrorInfo object or \c null .
     */
    Ptr<ErrorInfo> GetError();
    
    virtual bool IsAlive();
    
    /*!
     * @brief  The callback object to notify when this thread is being terminated.
     * 
     * @return The callback object.
     */
    Ptr<IThreadJoinCallback> GetJoinCallback();
    
    /*!
     * @brief  The callback object to notify when this thread is being terminated.
     * 
     * @param value The callback object.
     */
    void SetJoinCallback(IThreadJoinCallback* value);
    
    virtual String GetName();
    
    virtual void SetName(String value);
    
    virtual void* GetNativeThreadId();
    
    virtual Ptr<Object> GetParameter();
    
    virtual void SetParameter(Object* value);
    
    virtual ThreadPriority GetPriority();
    
    virtual void SetPriority(ThreadPriority value);
    
    virtual bool ShallQuit();
    
    /*!
     * @brief  Gets or sets the thread main method.
     * 
     * @return <b>[not-null]</b>  The thread main method.
     */
    Ptr<IThreadMain> GetThreadMain();
    
    /*!
     * @brief  Gets or sets the thread main method.
     * 
     * @param value <b>[not-null]</b>  The thread main method.
     */
    void SetThreadMain(IThreadMain* value);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of Thread.
     */
    Thread();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates and starts a background thread.
     * 
     * @param main <b>[not-null]</b>  The thread main method.
     * 
     * @return <b>[not-null]</b>  The running Thread object.
     */
    static Ptr<Thread> Run(IThreadMain* main);
    
    /*!
     * @brief  Creates and starts a background thread.
     * 
     * @param main <b>[not-null]</b>  The thread main method.
     * @param parameter Optional parameter to pass to thread main method.
     * 
     * @return <b>[not-null]</b>  The running Thread object.
     */
    static Ptr<Thread> Run(IThreadMain* main, Object* parameter);
    
    /*!
     * @brief  Creates and starts a background thread.
     * 
     * @param main <b>[not-null]</b>  The thread main method.
     * @param parameter Optional parameter to pass to thread main method.
     * @param joinCallback Optional join callback object to notify when the thread is being 
     * terminated.
     * 
     * @return <b>[not-null]</b>  The running Thread object.
     */
    static Ptr<Thread> Run(IThreadMain* main, Object* parameter, IThreadJoinCallback* joinCallback);
    
    /*!
     * @brief  Creates and starts a background thread.
     * 
     * @param name Name of the background thread.
     * @param main <b>[not-null]</b>  The thread main method.
     * 
     * @return <b>[not-null]</b>  The running Thread object.
     */
    static Ptr<Thread> Run(String name, IThreadMain* main);
    
    /*!
     * @brief  Creates and starts a background thread.
     * 
     * @param name Name of the background thread.
     * @param main <b>[not-null]</b>  The thread main method.
     * @param parameter Optional parameter to pass to thread main method.
     * 
     * @return <b>[not-null]</b>  The running Thread object.
     */
    static Ptr<Thread> Run(String name, IThreadMain* main, Object* parameter);
    
    /*!
     * @brief  Creates and starts a background thread.
     * 
     * @param name Name of the background thread.
     * @param main <b>[not-null]</b>  The thread main method.
     * @param parameter Optional parameter to pass to thread main method.
     * @param joinCallback Optional join callback object to notify when the thread is being 
     * terminated.
     * 
     * @return <b>[not-null]</b>  The running Thread object.
     */
    static Ptr<Thread> Run(String name, IThreadMain* main, Object* parameter, IThreadJoinCallback* joinCallback);
    
    /*!
     * @brief  Suspends the calling thread for the given amount of time.
     * 
     * @param milliSeconds <b>[>=0]</b>  The number of milliseconds to sleep.
     */
    static void Sleep(int32 milliSeconds);
    
    /*!
     * @brief  Waits until this threads has terminated.
     * 
     * If the thread has already been terminated,the method returns silently.
     */
    void Join();
    
    /*!
     * @brief  Starts this thread.
     * 
     * The method creates a new background thread which will execute the \c Run  method of the 
     * given IThreadMain object (see #GetThreadMain property).
     * 
     * If the thread has already been started,the method silently returns.
     */
    void Start();
    
    /*!
     * @brief  Stops the thread.
     * 
     * The thread will be signaled to stop.It will not have been terminated when this method 
     * returns.Use the #Join method for waiting for the termination of the thread.
     * 
     * If the thread has already been stopped,the method returns silently.
     */
    void Stop();
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
  protected:
    
    virtual void DisposeManaged();
    
    virtual void DisposeManagedChildren();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The logger object of this class.
     */
    static const StaticPtr<ILogger> Logger;
    
    /*!
     * @brief  The error info of the exception that has occurred in the \c Run  method of IRunnable.
     */
    Ptr<ErrorInfo> errorInfo;
    
    /*!
     * @brief  The callback object to notify when this thread is being terminated.
     */
    Ptr<IThreadJoinCallback> joinCallback;
    
    /*!
     * @brief  Monitor object used for synchronization.
     */
    Ptr<Monitor> monitor;
    
    /*!
     * @brief  The name of this thread.
     */
    String name;
    
    Ptr<Object> parameter;
    
    /*!
     * @brief  The current thread priority.
     */
    ThreadPriority priority;
    
    /*!
     * @brief  Is the thread currently alive?
     * 
     * A thread is alive right after it is instantiated until the \c Run  method of IRunnable 
     * returns (either by \c return  or by a thrown exception).
     */
    bool started;
    
    bool stopped;
    
    /*!
     * @brief  Is the thread currently performing a graceful shutdown?
     * 
     * This flag is set when the #Stop or #Join method is called.
     */
    bool stopping;
    
    /*!
     * @brief  The thread main method.
     */
    Ptr<IThreadMain> threadMain;
    
    /*!
     * @brief  Is the thread currently waiting for a graceful shutdown to finish?
     */
    bool waiting;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Applies the thread priority to the running thread.
     * 
     * @param priority The thread priority to apply.
     */
    void ApplyThreadPriority(ThreadPriority priority);
    
    /*!
     * @brief  Asserts that this thread has not been started yet.
     */
    void AssertNotStarted();
    
    /*!
     * @brief  Creates and starts a new background thread that executes the #Main method of 
     *         this Thread object.
     * 
     * @param name The thread name or \c null .
     */
    void CreateAndStartThread(String name);
    
    /*!
     * @brief  This method represents the outer main method of the thread.
     * 
     * The #Main method handles state management,synchronization and exceptions.The actual thread 
     * main method is the \c Run  method of IRunnable,which is invoked from this method.
     */
    void Main();
    
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
    public: typedef Ptr<Thread> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x16869BF7;
    
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
      if ((ptr = IThread::TryCast(typeId)) != 0) return ptr;
      if ((ptr = IThreadContext::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
    
    // ---------------------------------------------------------------------------------------------
    // Native code
    // ---------------------------------------------------------------------------------------------
    
    NATIVE_BLOCK_BEGIN ("BDF344E4-1B69-4D52-9852-B27CC8C132EB")
    
#if defined(CODEX_PLATFORM_WINDOWS) || defined(CODEX_PLATFORM_WINCE)

    friend DWORD WINAPI ThreadMainFunction(LPVOID pArgument);    

#elif defined(CODEX_PLATFORM_LINUX) || defined(CODEX_PLATFORM_MAC)

    friend void* ThreadMainFunction(void*);

#else

  #error Unsupported platform!

#endif

  private:

    /*!
     * @brief The native thread handle.
     */
    void* hThread;
    
    NATIVE_BLOCK_END   ("BDF344E4-1B69-4D52-9852-B27CC8C132EB")
  };
  
} } } 

#endif
