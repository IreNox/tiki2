////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_UTIL_PROGRESS_IPROGRESSMONITOR_H
#define CLODDY_API_UTIL_PROGRESS_IPROGRESSMONITOR_H

#include "CodeX/System.h"

// Forward declare referenced classes.

namespace CodeX { namespace System { class ErrorInfo; } }

// Declare interface ::Cloddy::API::Util::Progress::IProgressMonitor.

namespace Cloddy { namespace API { namespace Util { namespace Progress
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced classes.
  
  using CodeX::System::ErrorInfo;
  
  /*!
   * @brief  A IProgressMonitor object tracks the progress of a running operation.
   */
  class NO_VTABLE IProgressMonitor : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Signals that a critical error has occurred and the operation has stopped.
     * 
     * @param errorInfo The error info object.
     */
    virtual void Error(ErrorInfo* errorInfo) = 0;
    
    /*!
     * @brief  Returns an IProgressMonitor object that will scale all upcoming and finished ticks 
     *         reported to it to a fixed range.The fixed progress will then be forwarded to this 
     *         progress monitor.
     * 
     * Using fixed range progress monitor wrappers allows operations to aggregate the progress 
     * reported by suboperations.
     * 
     * @param tickCount <b>[>0]</b>  Upper bound of fixed progress tick range.
     * 
     * @return <b>[not-null]</b>  The fixed range progress monitor.
     */
    virtual Ptr<IProgressMonitor> FixedRange(int64 tickCount) = 0;
    
    /*!
     * @brief  Provides a status message for the running operation.
     * 
     * @param message The status message.
     */
    virtual void StatusMessage(String message) = 0;
    
    /*!
     * @brief  The running operation has finished \e ticks  tick units.
     * 
     * Finished ticks should be reported only from within \c Run  method.
     * 
     * @param ticks The number of finished tick units.
     */
    virtual void TicksFinished(int64 ticks) = 0;
    
    /*!
     * @brief  The running operation will last for another \e ticks  tick units.
     * 
     * Upcoming ticks should be reported only from within IOperation::Prepare method.
     * 
     * @param ticks The number of upcoming tick units.
     */
    virtual void UpcomingTicks(int64 ticks) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IProgressMonitor> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x32CCE047;
    
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
} } } } 

#endif
