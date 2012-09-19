////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_SYSTEM_STANDARDERROR_H
#define CLODDY_CORE_SYSTEM_STANDARDERROR_H

#include "CodeX/System_Native.h"

// Declare class ::Cloddy::Core::System::StandardError.

namespace Cloddy { namespace Core { namespace System
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Helper class for writing to the standard error stream.
   */
  class StandardError
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Flushes the standard output stream.
     */
    static void Flush();
    
    /*!
     * @brief  Writes the given text to the standard error stream.
     * 
     * @param text <b>[not-null]</b>  The text to write.
     */
    static void Write(String text);
    
    /*!
     * @brief  Writes a line break to the standard error stream.
     */
    static void WriteLine();
    
    /*!
     * @brief  Writes the given text to the standard error stream,followed by a line break.
     * 
     * @param text <b>[not-null]</b>  The text to write.
     */
    static void WriteLine(String text);
  };
  
} } } 

#endif
