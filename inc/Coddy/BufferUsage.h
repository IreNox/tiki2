////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_GAL_BUFFERUSAGE_H
#define CLODDY_GAL_BUFFERUSAGE_H

#include "CodeX/System.h"

// Declare enumeration ::Cloddy::GAL::BufferUsage.

namespace Cloddy { namespace GAL
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Enumeration of usage semantics for creating GPU buffers.
   */
  enum BufferUsage
  {
    /*!
     * @brief  The buffer content is set once upon initialization.
     */
    BufferUsage_Static = 0,
    
    /*!
     * @brief  The buffer content is updated periodically (eg. once per frame).
     */
    BufferUsage_Dynamic = 1,
    
    /*!
     * @brief  The buffer content is discarded each frame.
     */
    BufferUsage_Volatile = 2
  };
  
} } 

#endif
