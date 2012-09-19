////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_IO_IOERROR_H
#define CLODDY_CORE_IO_IOERROR_H

#include "CodeX/System.h"

// Declare enumeration ::Cloddy::Core::IO::IOError.

namespace Cloddy { namespace Core { namespace IO
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Enumeration of well-known I/O errors.
   */
  enum IOError
  {
    /*!
     * @brief  A file or directory has not been found.
     */
    IOError_FileNotFound = 0,
    
    /*!
     * @brief  The end of a file has been reached.
     */
    IOError_EndOfFile = 1,
    
    /*!
     * @brief  The given file or directory path name is invalid (eg. bad characters).
     */
    IOError_BadPath = 2,
    
    /*!
     * @brief  The storage device is full.
     */
    IOError_DiskFull = 3,
    
    /*!
     * @brief  The I/O operation cannot be performed because of missing privileges.
     */
    IOError_MissingPrivilege = 4,
    
    /*!
     * @brief  Access to the I/O resource is denied.
     */
    IOError_AccessDenied = 5,
    
    /*!
     * @brief  Another process is already accessing the I/O resource in a conflicting way.
     */
    IOError_SharingViolation = 6,
    
    /*!
     * @brief  Bad file access (check byte alignment for async file I/O).
     * 
     * @see IByteAligned
     */
    IOError_BadAccess = 7,
    
    /*!
     * @brief  The requested I/O operation has timed out.
     */
    IOError_TimeOut = 8,
    
    /*!
     * @brief  Some other I/O error has occured.
     */
    IOError_Other = 9
  };
  
} } } 

#endif
