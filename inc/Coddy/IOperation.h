////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_UTIL_PROGRESS_IOPERATION_H
#define CLODDY_API_UTIL_PROGRESS_IOPERATION_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "CodeX/IDisposable.h"
#include "Cloddy/IProgressMonitor.h"
#include "Cloddy/IRunnable.h"

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Util { namespace Progress { class RunningOperation; } } } }

// Declare interface ::Cloddy::API::Util::Progress::IOperation.

namespace Cloddy { namespace API { namespace Util { namespace Progress
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::System::IRunnable;
  using CodeX::System::IDisposable;
  
  /*!
   * @brief  Base interface that can be run via the RunningOperation class.
   * 
   * A class that implements the IOperation interface performs a lenghty task.Typically,this task 
   * will be executed in a background thread (see #Background).Running background operations are 
   * represented by the RunningOperation class.
   * 
   * A running background operation provides its current progress via an IProgressMonitor object 
   * that has been passed to its #Prepare method.
   * 
   * When a background operation is executed,the following tasks are performed:
   *   -# The #Prepare method is called and the operation provides the number of upcoming progress 
   *   ticks (see IProgressMonitor::UpcomingTicks).
   *   -# The \c Run  method is called and the operation performs the actual work,providing the its 
   *   current progress using the given IProgressMonitor object.
   *   -# After the background operation has ended (finished,failed or cancelled),it is disposed (
   *   see IDisposable::Dispose).Cleanup should be performed here.
   * 
   * @see IProgressMonitor
   * @see IProgressListener
   * @see RunningOperation
   */
  class NO_VTABLE IOperation : public virtual IDisposable, public virtual IRunnable<Ref<IProgressMonitor> >
  {
    // ---------------------------------------------------------------------------------------------
    // Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Returns the human-readable name of this background operation.
     * 
     * @return <b>[not-null]</b>  The name.
     */
    virtual String GetName() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Returns an IOperation object that executes this background operation,followed by the 
     *         given operation.
     * 
     * @param operation <b>[not-null]</b>  The background operation to execute after this one has 
     * finished.
     * 
     * @return <b>[not-null]</b>  The combined IOperation object.
     */
    virtual Ptr<IOperation> Append(IOperation* operation) = 0;
    
    /*!
     * @brief  Runs the operation in a background thread.
     * 
     * @return <b>[not-null]</b>  The RunningOperation object that represents the running 
     * background operation.
     */
    virtual Ptr<RunningOperation> Background() = 0;
    
    /*!
     * @brief  Requests that the running background operation gracefully terminates.
     * 
     * An IOperation is free to honor a cancel request or to ignore it.Cancelling a background 
     * operation should be considered as a hint to terminate as soon as possible.
     */
    virtual void Cancel() = 0;
    
    /*!
     * @brief  Prepares the background operation and provides the number of upcoming ticks (
     *         see IProgressMonitor::UpcomingTicks).
     * 
     * If an exception is thrown by this method,the background operation is considered to have 
     * failed.
     * 
     * @param progressMonitor <b>[not-null]</b>  The IProgressMonitor to use for reporting progress 
     * during operation.
     */
    virtual void Prepare(IProgressMonitor* progressMonitor) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IOperation> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xAA3BFA97;
    
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
      if ((ptr = IDisposable::TryCast(typeId)) != 0) return ptr;
      if ((ptr = IRunnable<Ref<IProgressMonitor> >::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
} } } } 

#endif
