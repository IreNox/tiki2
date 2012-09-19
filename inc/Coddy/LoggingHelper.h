////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_LOGGING_LOGGINGHELPER_H
#define CLODDY_CORE_LOGGING_LOGGINGHELPER_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/LogSeverity.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Logging { class ILogger; } } }
namespace Cloddy { namespace Core { namespace Logging { class ILoggerCategory; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace Logging { class LoggerCategory; } } }

// Declare class ::Cloddy::Core::Logging::LoggingHelper.

namespace Cloddy { namespace Core { namespace Logging
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Static helper class for accessing the Logging API.
   */
  class LoggingHelper
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The singleton category which represents the root of the category hierarchy.
     */
    static const StaticPtr<ILoggerCategory> Root;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Performs basic configuration on the #Root logger category.
     */
    static void BasicConfiguration();
    
    /*!
     * @brief  Performs basic configuration on the #Root logger category.
     * 
     * @param severity The root severity level.
     */
    static void BasicConfiguration(LogSeverity severity);
    
    /*!
     * @brief  Returns the ILoggerCategory for the given full name.
     * 
     * @param fullName <b>[not-null]</b>  The full name.
     * 
     * @return <b>[not-null]</b>  The logger category.
     */
    static Ptr<ILoggerCategory> GetCategory(String fullName);
    
    /*!
     * @brief  Returns an ILogger instance for the given full name.
     * 
     * @param fullName <b>[not-null]</b>  The full name.
     * 
     * @return The ILogger instance.
     */
    static Ptr<ILogger> GetLogger(String fullName);
    
    /*!
     * @brief  Shuts the logging framework down.
     */
    static void Shutdown();
    
    // ---------------------------------------------------------------------------------------------
    // Static Initializer Functions
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief Static initializer function for field Root.
     */
    static Object* StaticInitializer_Root();
  };
  
} } } 

#endif
