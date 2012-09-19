////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_SYSTEM_ERRORBARRIER_H
#define CLODDY_CORE_SYSTEM_ERRORBARRIER_H

#include "CodeX/System_Native.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace System { template<class> class IRunnable; } } }

// Forward declare referenced classes.

namespace CodeX { namespace System { class ErrorInfo; } }

// Declare class ::Cloddy::Core::System::ErrorBarrier.

namespace Cloddy { namespace Core { namespace System
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced classes.
  
  using CodeX::System::ErrorInfo;
  
  /*!
   * @brief  The ErrorBarrier is a helper class that executes the \c Run  method of an IRunnable 
   *         object and catches all thrown exceptions,wrapping them in an ErrorInfo object.
   */
  template<class T>
  class ErrorBarrier
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Calls the \c Run  method on \e runnable ,catches any thrown exception and returns 
     *         an ErrorInfo object that describes the thrown exception.
     * 
     * @param errorSource <b>[not-empty]</b>  The error source to use in case an exception is 
     * thrown.
     * @param runnable <b>[not-null]</b>  The runnable object.
     * @param argument Optional argument value.
     * 
     * @return \c null  if the called method returned without throwing an exception,the error 
     * message describing the thrown exception otherwise.
     */
    static Ptr<ErrorInfo> Run(String errorSource, IRunnable<T>* runnable, typename T::In argument);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Executes the \c Run  method of \e runnable ,catches all CoreException and returns 
     *         the contained ErrorInfo object.
     * 
     * @param runnable The runnable object.
     * @param argument The argument value.
     * 
     * @return The ErrorInfo object or \c null .
     */
    static Ptr<ErrorInfo> RunInternal(IRunnable<T>* runnable, typename T::In argument);
  };
  
} } } 

#endif
