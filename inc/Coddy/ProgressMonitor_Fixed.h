////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_UTIL_PROGRESS_PROGRESSMONITOR_FIXED_H
#define CLODDY_API_UTIL_PROGRESS_PROGRESSMONITOR_FIXED_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/ProgressMonitorBase.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Util { namespace Progress { class IProgressMonitor; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Util { namespace Progress { class ProgressMonitor; } } } }
namespace Cloddy { namespace API { namespace Util { namespace Progress { class ProgressMonitorBase; } } } }
namespace CodeX { namespace System { class ErrorInfo; } }

// Declare class ::Cloddy::API::Util::Progress::ProgressMonitor_Fixed.

namespace Cloddy { namespace API { namespace Util { namespace Progress
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced classes.
  
  using CodeX::System::ErrorInfo;
  
  /*!
   * @brief  An implementation of the IProgressMonitor that scales the reported upcoming and 
   *         finished ticks to a fixed range and reports the fixed progress values to a 
   *         wrapped IProgressMonitor object.
   */
  class ProgressMonitor_Fixed : public ProgressMonitorBase
  {
    // Declare friend classes.
    
    friend class ProgressMonitor;
    friend class ProgressMonitorBase;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual void Error(ErrorInfo* errorInfo);
    
    virtual void StatusMessage(String message);
    
    virtual void TicksFinished(int64 ticks);
    
    virtual void UpcomingTicks(int64 ticks);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The finished ticks,reported to this progress monitor.
     */
    int64 finished;
    
    /*!
     * @brief  The fixed number of progress ticks to report.
     */
    int64 fixedTickCount;
    
    /*!
     * @brief  The wrapped progress monitor.
     */
    Ptr<IProgressMonitor> progressMonitor;
    
    /*!
     * @brief  The finished ticks,reported to the wrapped progress monitor.
     */
    int64 reported;
    
    /*!
     * @brief  The upcoming ticks,reported to this progress monitor.
     */
    int64 upcoming;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of ProgressMonitor_Fixed.
     * 
     * @param progressMonitor The progress monitor to wrap.
     * @param fixedTickCount The fixed number of ticks to report for the wrapped progress monitor.
     */
    ProgressMonitor_Fixed(IProgressMonitor* progressMonitor, int64 fixedTickCount);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Updates the fixed range ticks.
     */
    void UpdateTicks();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<ProgressMonitor_Fixed> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xB1F6FDF;
    
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
      if ((ptr = ProgressMonitorBase::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } 

#endif
