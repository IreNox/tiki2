////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_KERNEL_THREADEDNESS_H
#define CLODDY_KERNEL_THREADEDNESS_H

#include "CodeX/System.h"

// Declare enumeration ::Cloddy::Kernel::Threadedness.

namespace Cloddy { namespace Kernel
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Enumeration of threading modes of the CloddyKernel.
   */
  enum Threadedness
  {
    /*!
     * @brief  A single thread is used for both mesh refinement (see IVisibilityCriterion)and 
     *         vertex computation (see IVertexFactory).
     * 
     * Since all calls to the IVisibilityCriterion and IVertexFactory interfaces are made from the 
     * same thread,implementors do not need to be thread-safe.
     * <pre>
     *     . . . . . . . . . . . . . . . .
     *     . RefinementThread              .
     *     .                               .
     *     .         +---------+           .
     *     .         | Refine  |           .
     *     .         +---------+           .
     *     .         | Compute |           .
     *     .         +---------+           .
     *     .              |                .
     *      . . . . . . . | . . . . . . . .
     *     . RenderThread |                .
     *     .              V                .
     *     .         +---------+           .
     *     .         | Update  |           .
     *     .         +---------+           .
     *     . . . . . . . . . . . . . . . .
     * </pre>
     */
    Threadedness_Single = 0,
    
    /*!
     * @brief  Two threads are used for mesh refinement (see IVisibilityCriterion)and vertex 
     *         computation (see IVertexFactory).
     * 
     * All calls to the IVisibilityCriterion and IVertexFactory interfaces are made from one thread 
     * at a time,so implementors do not need to be thread-safe.
     * <pre>
     *     . . . . . . . . . . . . . . . .
     *     . RefineThread  . ComputeThread .
     *     .               .               .
     *     . +---------+  -->  +---------+ .
     *     . | Refine  |   .   | Compute | .
     *     . +---------+  &lt;--  +---------+ .
     *     .     |         .         |     .
     *      . . .|. . . . . . . . . .|. . .
     *     .     |    RenderThread   |     .
     *     .     |                   |     .
     *     .     |    +---------+    |     .
     *     .     \\--> | Update  | &lt;--/     .
     *     .          +---------+          .
     *     . . . . . . . . . . . . . . . .
     * </pre>
     */
    Threadedness_Dual = 1,
    
    /*!
     * @brief  Automatically choose a treading mode depending on the number of processors.
     * 
     * If more than two processors are available (
     * see LowLevel::GetProcessorCount),#Threadedness_Dual will be chosen;
     * otherwise #Threadedness_Single is used.
     */
    Threadedness_Auto = 2
  };
  
} } 

#endif
