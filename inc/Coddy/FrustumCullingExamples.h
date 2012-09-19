////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_MESHVISITORS_FRUSTUMCULLINGEXAMPLES_H
#define CLODDY_API_MESHVISITORS_FRUSTUMCULLINGEXAMPLES_H

#include "CodeX/System.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace MeshVisitors { class IFrustum; } } }
namespace Cloddy { namespace Kernel { class IMesh; } }
namespace Cloddy { namespace Kernel { class ITriangulationCallback; } }

// Declare class ::Cloddy::API::MeshVisitors::FrustumCullingExamples.

namespace Cloddy { namespace API { namespace MeshVisitors
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Kernel::IMesh;
  using Cloddy::Kernel::ITriangulationCallback;
  
  /*!
   * @brief  Code samples for FrustumCulling.
   */
  class FrustumCullingExamples
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Creating and using a FrustumCulling object.
     */
    static void Example_1();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Creates a new instance of IFrustum.
     * 
     * @return The instance.
     */
    static Ptr<IFrustum> CreateFrustum();
    
    /*!
     * @brief  Creates a new instance of IMesh.
     * 
     * @return The instance.
     */
    static Ptr<IMesh> CreateMesh();
    
    /*!
     * @brief  Creates a new instance of ITriangulationCallback.
     * 
     * @return The instance.
     */
    static Ptr<ITriangulationCallback> CreateTriangulationCallback();
  };
  
} } } 

#endif
