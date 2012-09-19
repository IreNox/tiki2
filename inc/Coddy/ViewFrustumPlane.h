////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_MESHVISITORS_VIEWFRUSTUMPLANE_H
#define CLODDY_API_MESHVISITORS_VIEWFRUSTUMPLANE_H

#include "CodeX/System.h"

// Declare enumeration ::Cloddy::API::MeshVisitors::ViewFrustumPlane.

namespace Cloddy { namespace API { namespace MeshVisitors
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Enumeration of view frustum planes.
   */
  enum ViewFrustumPlane
  {
    ViewFrustumPlane_None = 0,
    
    ViewFrustumPlane_Left = 1,
    
    ViewFrustumPlane_Right = 2,
    
    ViewFrustumPlane_Top = 4,
    
    ViewFrustumPlane_Bottom = 8,
    
    ViewFrustumPlane_Near = 16,
    
    ViewFrustumPlane_Far = 32,
    
    ViewFrustumPlane_All = 63
  };
  
  static inline ViewFrustumPlane operator|=(ViewFrustumPlane a, ViewFrustumPlane b)
  {
    return (ViewFrustumPlane) ((int32) a | (int32) b);
  }
  
  static inline ViewFrustumPlane operator&=(ViewFrustumPlane a, ViewFrustumPlane b)
  {
    return (ViewFrustumPlane) ((int32) a & (int32) b);
  }
  
  static inline ViewFrustumPlane operator^=(ViewFrustumPlane a, ViewFrustumPlane b)
  {
    return (ViewFrustumPlane) ((int32) a ^ (int32) b);
  }
} } } 

#endif
