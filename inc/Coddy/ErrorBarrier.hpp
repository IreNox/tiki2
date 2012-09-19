////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_SYSTEM_ERRORBARRIER_HPP
#define CLODDY_CORE_SYSTEM_ERRORBARRIER_HPP

#include "Cloddy/ErrorBarrier.h"

// Include referenced interfaces.

#include "Cloddy/IRunnable.h"

// Include referenced classes.

#include "CodeX/CoreException.h"
#include "CodeX/ErrorInfo.h"
#include "CodeX/InvalidArgumentException.h"

namespace Cloddy { namespace Core { namespace System {

// Use referenced namespaces.

using namespace CodeX;

// Use referenced classes.

using CodeX::System::CoreException;
using CodeX::System::ErrorInfo;
using CodeX::System::InvalidArgumentException;

// -------------------------------------------------------------------------------------------------
// Public / Methods
// -------------------------------------------------------------------------------------------------

/*!
 * @brief  Calls the \c Run  method on \e runnable ,catches any thrown exception and returns 
 *         an ErrorInfo object that describes the thrown exception.
 * 
 * @param errorSource <b>[not-empty]</b>  The error source to use in case an exception is thrown.
 * @param runnable <b>[not-null]</b>  The runnable object.
 * @param argument Optional argument value.
 * 
 * @return \c null  if the called method returned without throwing an exception,the error message 
 * describing the thrown exception otherwise.
 */
template<class T>
Ptr<ErrorInfo> ErrorBarrier<T>::Run(String errorSource, IRunnable<T>* runnable, typename T::In argument)
{
#ifdef _DEBUG
  if (errorSource == null || errorSource.Length() == 0) throw InvalidArgumentException::NotEmpty(ZSTRING("ErrorBarrier.Run"), ZSTRING("errorSource"));
  if (runnable == null) throw InvalidArgumentException::NotNull(ZSTRING("ErrorBarrier.Run"), ZSTRING("runnable"));
#endif
  
  Ptr<ErrorInfo> result;
  
  // Execute 'result = RunInternal(runnable, argument);', catch any platform-specific
  // exception and create an ErrorInfo object for it, using the given error source string.
  
  NATIVE_REGION_BEGIN ("F2AFEC93-B3C0-4704-BA73-A2FD9B08DCD6")
  
  try
  {
    result = RunInternal(runnable, argument);
  }
  catch(std::bad_alloc&)
  {
    result = new ErrorInfo(errorSource, "Out of memory!", null);
  }
  catch(std::exception& e)
  {
    result = new ErrorInfo(errorSource, e.what(), null);
  }
  catch(...)
  {
    result = new ErrorInfo(errorSource, "Unknown C++ exception", null);
  }
  
  NATIVE_REGION_END   ("F2AFEC93-B3C0-4704-BA73-A2FD9B08DCD6")
  
  return result;
}

// -------------------------------------------------------------------------------------------------
// Private / Methods
// -------------------------------------------------------------------------------------------------

/*!
 * @brief  Executes the \c Run  method of \e runnable ,catches all CoreException and returns the 
 *         contained ErrorInfo object.
 * 
 * @param runnable The runnable object.
 * @param argument The argument value.
 * 
 * @return The ErrorInfo object or \c null .
 */
template<class T>
Ptr<ErrorInfo> ErrorBarrier<T>::RunInternal(IRunnable<T>* runnable, typename T::In argument)
{
  try
  {
    runnable->Run(argument);
    
    return null;
  }
  catch (CoreException& e)
  {
    return e.GetErrorInfo();
  }
}

} } } 

#endif
