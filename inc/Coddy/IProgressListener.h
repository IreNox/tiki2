////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_UTIL_PROGRESS_IPROGRESSLISTENER_H
#define CLODDY_API_UTIL_PROGRESS_IPROGRESSLISTENER_H

#include "CodeX/System.h"

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Util { namespace Progress { class RunningOperation; } } } }

// Declare interface ::Cloddy::API::Util::Progress::IProgressListener.

namespace Cloddy { namespace API { namespace Util { namespace Progress
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Classes that listen to the progress of a running operation implement this interface.
   */
  class NO_VTABLE IProgressListener : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Notification delegate for running operations.
     * 
     * @param runningOperation The running operation which has made some progress.
     * @param statusMessageChanged Has the status message changed?
     * @param finishedPercentChanged Has the finished percent value changed?
     */
    virtual void ProgressChanged(RunningOperation* runningOperation, bool statusMessageChanged, bool finishedPercentChanged) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IProgressListener> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x46B6A449;
    
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
