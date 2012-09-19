////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_SYSTEM_STANDARDIN_H
#define CLODDY_CORE_SYSTEM_STANDARDIN_H

#include "CodeX/System_Native.h"

// Declare class ::Cloddy::Core::System::StandardIn.

namespace Cloddy { namespace Core { namespace System
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Helper class for reading from the standard input stream.
   */
  class StandardIn
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Peeks at the next character from the standard input stream without changing the 
     *         stream position.
     * 
     * @return The next character or \c -1  if there are no characters available on the stream.
     */
    static int32 PeekChar();
    
    /*!
     * @brief  Reads the next character from the standard input stream.
     * 
     * @return The read character or \c -1  if there are no characters available on the stream.
     */
    static int32 ReadChar();
    
    /*!
     * @brief  Reads the next text line from the standard input stream.
     * 
     * @return The read text line or \c null  if there are no characters available on the stream.
     */
    static String ReadLine();
  };
  
} } } 

#endif
