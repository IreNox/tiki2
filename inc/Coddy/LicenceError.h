////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_KERNEL_LICENCEERROR_H
#define CLODDY_KERNEL_LICENCEERROR_H

#include "CodeX/System.h"

// Declare enumeration ::Cloddy::Kernel::LicenceError.

namespace Cloddy { namespace Kernel
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Enumeration of possible licence errors.
   */
  enum LicenceError
  {
    /*!
     * @brief  The licence has not been set.
     */
    LicenceError_NotSet = 0,
    
    /*!
     * @brief  The licence descriptor is corrupt.
     */
    LicenceError_Corrupt = 1,
    
    /*!
     * @brief  The licence cannot be used.
     * 
     * This error typically occurs when the licence platform does not concur with the host 
     * platform (eg. a licence key for C++is used for a Java application).
     */
    LicenceError_WrongUsage = 2,
    
    /*!
     * @brief  The licence has expired.
     */
    LicenceError_Expired = 3
  };
  
} } 

#endif
