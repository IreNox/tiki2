////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_UTIL_PROGRESS_PROGRESSMONITORBASE_H
#define CLODDY_API_UTIL_PROGRESS_PROGRESSMONITORBASE_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IProgressMonitor.h"

// Forward declare referenced classes.

namespace CodeX { namespace System { class ErrorInfo; } }

// Declare class ::Cloddy::API::Util::Progress::ProgressMonitorBase.

namespace Cloddy { namespace API { namespace Util { namespace Progress
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced classes.
  
  using CodeX::System::ErrorInfo;
  
  /*!
   * @brief  Abstract base class for IProgressMonitor implementations.
   */
  class ProgressMonitorBase : public virtual IProgressMonitor
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual void Error(ErrorInfo* errorInfo) = 0;
    
    virtual Ptr<IProgressMonitor> FixedRange(int64 tickCount);
    
    virtual void StatusMessage(String message);
    
    virtual void TicksFinished(int64 ticks) = 0;
    
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
    public: typedef Ptr<ProgressMonitorBase> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x830BCFCB;
    
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
      if ((ptr = IProgressMonitor::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } 

#endif
