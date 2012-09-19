////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_MESHVISITORS_FRUSTUMEXAMPLES_H
#define CLODDY_API_MESHVISITORS_FRUSTUMEXAMPLES_H

#include "CodeX/System.h"

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace MeshVisitors { class Frustum; } } }

// Declare class ::Cloddy::API::MeshVisitors::FrustumExamples.

namespace Cloddy { namespace API { namespace MeshVisitors
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Code samples for Frustum.
   */
  class FrustumExamples
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Creating and configuring a Frustum object.
     */
    static void Example_1();
    
    /*!
     * @brief  Using offset point for improved floating-point precision.
     */
    static void Example_2();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Creates a new instance of Frustum.
     * 
     * @return The instance.
     */
    static Ptr<Frustum> CreateFrustum();
  };
  
} } } 

#endif
