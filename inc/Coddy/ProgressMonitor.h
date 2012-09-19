////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_UTIL_PROGRESS_PROGRESSMONITOR_H
#define CLODDY_API_UTIL_PROGRESS_PROGRESSMONITOR_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IProgressMonitor.h"

// Include referenced classes.

#include "CodeX/Disposable.h"

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Util { namespace Progress { class RunningOperation_ThreadMain; } } } }
namespace CodeX { namespace System { class ErrorInfo; } }
namespace CodeX { namespace System { class Monitor; } }

// Declare class ::Cloddy::API::Util::Progress::ProgressMonitor.

namespace Cloddy { namespace API { namespace Util { namespace Progress
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced classes.
  
  using CodeX::System::Disposable;
  using CodeX::System::ErrorInfo;
  using CodeX::System::Monitor;
  
  /*!
   * @brief  An implementation of the IProgressMonitor interface that keeps track of the progress 
   *         made by an IOperation.
   */
  class ProgressMonitor : public Disposable, public virtual IProgressMonitor
  {
    // Declare friend classes.
    
    friend class RunningOperation_ThreadMain;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The current status message.
     * 
     * @return The status message.
     */
    String GetCurrentStatusMessage();
    
    /*!
     * @brief  The total number of finished ticks.
     * 
     * @return <b>[>=0]</b>  The number of finished ticks.
     */
    int64 GetFinishedTicks();
    
    /*!
     * @brief  Has the progress changed?
     * 
     * The progress change flag is reset to \c false  before the method returns.
     * 
     * @return \c true  if the progress has changed,\c false  if not.
     */
    bool HasProgressChanged();
    
    /*!
     * @brief  Has the status message changed?
     * 
     * The status message change flag is reset to \c false  before the method returns.
     * 
     * @return \c true  if the status message has changed,\c false  if not.
     */
    bool HasStatusMessageChanged();
    
    /*!
     * @brief  The total number of ticks.
     * 
     * @return <b>[>=0]</b>  The total number of ticks.
     */
    int64 GetTotalTicks();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of ProgressMonitor.
     */
    ProgressMonitor();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    static void Error(IProgressMonitor* progressMonitor, ErrorInfo* error);
    
    static void StatusMessage(IProgressMonitor* progressMonitor, String message);
    
    static void TicksFinished(IProgressMonitor* progressMonitor, int64 ticks);
    
    static void UpcomingTicks(IProgressMonitor* progressMonitor, int64 ticks);
    
    virtual void Error(ErrorInfo* errorInfo);
    
    /*!
     * @brief  Returns the last error that has been reported.
     * 
     * The last error will be reset to \c null  before the method returns,so a subsequent call 
     * to #FetchLastError will return \c null .
     * 
     * @return The last error.
     */
    Ptr<ErrorInfo> FetchLastError();
    
    virtual Ptr<IProgressMonitor> FixedRange(int64 tickCount);
    
    virtual void StatusMessage(String message);
    
    virtual void TicksFinished(int64 ticks);
    
    virtual void UpcomingTicks(int64 ticks);
    
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
     * @brief  The current status message.
     */
    String currentStatusMessage;
    
    /*!
     * @brief  The total number of finished ticks.
     */
    int64 finishedTicks;
    
    /*!
     * @brief  Has the progress changed?
     */
    bool hasProgressChanged;
    
    /*!
     * @brief  Has the status message changed?
     */
    bool hasStatusMessageChanged;
    
    /*!
     * @brief  The error that has occured most recently.
     */
    Ptr<ErrorInfo> lastError;
    
    /*!
     * @brief  Monitor object used for synchronization.
     */
    Ptr<Monitor> monitor;
    
    /*!
     * @brief  The total number of ticks.
     */
    int64 totalTicks;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    void AllFinished();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<ProgressMonitor> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x3EB8EF10;
    
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
      if ((ptr = IProgressMonitor::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } 

#endif
