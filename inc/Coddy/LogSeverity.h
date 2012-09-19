////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_LOGGING_LOGSEVERITY_H
#define CLODDY_CORE_LOGGING_LOGSEVERITY_H

#include "CodeX/System.h"

// Declare enumeration ::Cloddy::Core::Logging::LogSeverity.

namespace Cloddy { namespace Core { namespace Logging
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Enumeration of log severity levels.
   */
  enum LogSeverity
  {
    /*!
     * @brief  The minimum log severity level.
     */
    LogSeverity_Min = 0,
    
    /*!
     * @brief  A fatal error has occurred.
     * 
     * The application cannot continue execution after a fatal error has occurred.
     */
    LogSeverity_Fatal = 0,
    
    /*!
     * @brief  An error has occurred.
     * 
     * The applications proper function is limited due to the error that has occurred,but it can 
     * continue execution.
     */
    LogSeverity_Error = 1,
    
    /*!
     * @brief  A potential error has occurred.
     * 
     * The application has encountered a situation which might cause errors,but it can continue 
     * execution without limitations.
     */
    LogSeverity_Warning = 2,
    
    /*!
     * @brief  The application reports status messages about its normal operation.
     * 
     * Log messages of this severity should be rare and concise.They should represent what the 
     * application is doing on a coarse-grained level.
     */
    LogSeverity_Common = 3,
    
    /*!
     * @brief  The application reports additional information messages about its normal operation.
     * 
     * Log messages of this severity should represent what the application is doing on a 
     * fine-grained level.
     */
    LogSeverity_Info = 4,
    
    /*!
     * @brief  The application emits debug information messages.
     * 
     * Log messages of this severity should provide technical information about the applications 
     * execution for assisting developers in finding and fixing bugs.
     */
    LogSeverity_Debug = 5,
    
    /*!
     * @brief  The application emits detailed trace information messages about its execution paths.
     * 
     * Log messages of this severity provide provide information about which execution paths are 
     * used by the running application.They are used solely by developers to fix nasty bugs.
     */
    LogSeverity_Trace = 6,
    
    /*!
     * @brief  The maximum log severity level.
     */
    LogSeverity_Max = 6
  };
  
} } } 

#endif
