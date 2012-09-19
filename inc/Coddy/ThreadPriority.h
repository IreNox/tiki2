////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_THREADING_THREADPRIORITY_H
#define CLODDY_CORE_THREADING_THREADPRIORITY_H

#include "CodeX/System.h"

// Declare enumeration ::Cloddy::Core::Threading::ThreadPriority.

namespace Cloddy { namespace Core { namespace Threading
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Enumeration of thread priorities.
   */
  enum ThreadPriority
  {
    /*!
     * @brief  Lowest thread priority.
     */
    ThreadPriority_Lowest = 0,
    
    /*!
     * @brief  Lower thread priority than #ThreadPriority_Normal.
     */
    ThreadPriority_Lower = 1,
    
    /*!
     * @brief  Normal thread priority.
     */
    ThreadPriority_Normal = 2,
    
    /*!
     * @brief  Higher thread priority than #ThreadPriority_Normal.
     */
    ThreadPriority_Higher = 3,
    
    /*!
     * @brief  Highest thread priority.
     */
    ThreadPriority_Highest = 4
  };
  
} } } 

#endif
