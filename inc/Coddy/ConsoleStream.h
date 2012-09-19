////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_LOGGING_HANDLERS_CONSOLESTREAM_H
#define CLODDY_CORE_LOGGING_HANDLERS_CONSOLESTREAM_H

#include "CodeX/System.h"

// Declare enumeration ::Cloddy::Core::Logging::Handlers::ConsoleStream.

namespace Cloddy { namespace Core { namespace Logging { namespace Handlers
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Enumeration of standard console streams available for ConsoleMessageHandler object.
   */
  enum ConsoleStream
  {
    /*!
     * @brief  Log messages are not written at all.
     */
    ConsoleStream_None = 0,
    
    /*!
     * @brief  Log messages are written to the standard output stream.
     */
    ConsoleStream_StandardOut = 1,
    
    /*!
     * @brief  Log messages are written to the standard error stream.
     */
    ConsoleStream_StandardError = 2
  };
  
  static inline ConsoleStream operator|=(ConsoleStream a, ConsoleStream b)
  {
    return (ConsoleStream) ((int32) a | (int32) b);
  }
  
  static inline ConsoleStream operator&=(ConsoleStream a, ConsoleStream b)
  {
    return (ConsoleStream) ((int32) a & (int32) b);
  }
  
  static inline ConsoleStream operator^=(ConsoleStream a, ConsoleStream b)
  {
    return (ConsoleStream) ((int32) a ^ (int32) b);
  }
} } } } 

#endif
