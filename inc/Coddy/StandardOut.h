////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_SYSTEM_STANDARDOUT_H
#define CLODDY_CORE_SYSTEM_STANDARDOUT_H

#include "CodeX/System_Native.h"

// Include referenced enumerations.

#include "Cloddy/SimpleColor.h"

// Declare class ::Cloddy::Core::System::StandardOut.

namespace Cloddy { namespace Core { namespace System
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Helper class for writing to the standard output stream.
   */
  class StandardOut
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The current background color for console output.
     * 
     * @return The background color.
     */
    static SimpleColor GetBackground();
    
    /*!
     * @brief  The current background color for console output.
     * 
     * @param value The background color.
     */
    static void SetBackground(SimpleColor value);
    
    /*!
     * @brief  The current foreground color for console output.
     * 
     * @return The foreground color.
     */
    static SimpleColor GetForeground();
    
    /*!
     * @brief  The current foreground color for console output.
     * 
     * @param value The foreground color.
     */
    static void SetForeground(SimpleColor value);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Flushes the standard output stream.
     */
    static void Flush();
    
    /*!
     * @brief  Writes the given text to the standard output stream.
     * 
     * @param text <b>[not-null]</b>  The text to write.
     */
    static void Write(String text);
    
    /*!
     * @brief  Writes a line break to the standard output stream.
     */
    static void WriteLine();
    
    /*!
     * @brief  Writes the given text to the standard output stream,followed by a line break.
     * 
     * @param text <b>[not-null]</b>  The text to write.
     */
    static void WriteLine(String text);
  };
  
} } } 

#endif
