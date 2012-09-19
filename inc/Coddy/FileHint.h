////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_IO_FILES_FILEHINT_H
#define CLODDY_CORE_IO_FILES_FILEHINT_H

#include "CodeX/System.h"

// Declare enumeration ::Cloddy::Core::IO::Files::FileHint.

namespace Cloddy { namespace Core { namespace IO { namespace Files
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Enumeration of file access hints.
   */
  enum FileHint
  {
    /*!
     * @brief  Files are opened and created with default OS file caching and synchronous access 
     *         mode.
     * 
     * The IByteAligned::GetByteAlignment for files will always be \c 1 .
     */
    FileHint_BufferedSynchronous = 0,
    
    /*!
     * @brief  The OS file caching should be disabled for files opened resp. created with this hint 
     *         and file access should be performed asynchronously.
     * 
     * The IByteAligned::GetByteAlignment for files will be the sector size of the volume that 
     * stores the file.
     */
    FileHint_UnbufferedAsynchronous = 1
  };
  
} } } } 

#endif
