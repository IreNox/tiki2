////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_KERNEL_REFINEMENTSTATUS_H
#define CLODDY_KERNEL_REFINEMENTSTATUS_H

#include "CodeX/System.h"

// Declare enumeration ::Cloddy::Kernel::RefinementStatus.

namespace Cloddy { namespace Kernel
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Enumeration of background refinement status values.
   */
  enum RefinementStatus
  {
    /*!
     * @brief  Background refinement is currently active.
     */
    RefinementStatus_Running = 0,
    
    /*!
     * @brief  Background refinement has finished,ie. the mesh structure is optimal according to 
     *         the visibility criterion.
     */
    RefinementStatus_Finished = 1,
    
    /*!
     * @brief  Background refinement has finished (see #RefinementStatus_Finished)and has been 
     *         paused until the application explicitly resumes it.
     */
    RefinementStatus_Paused = 2,
    
    /*!
     * @brief  Background refinement was paused but has been resumed (
     *         see IRefinementProgress::ResumeRefinement).
     */
    RefinementStatus_Resumed = 3
  };
  
} } 

#endif
