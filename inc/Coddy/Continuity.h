////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_UTIL_CURVES_CONTINUITY_H
#define CLODDY_API_UTIL_CURVES_CONTINUITY_H

#include "CodeX/System.h"

// Declare enumeration ::Cloddy::API::Util::Curves::Continuity.

namespace Cloddy { namespace API { namespace Util { namespace Curves
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Enumeration of continuity types for ICurves.
   */
  enum Continuity
  {
    /*!
     * @brief  The curve provides C0 continuity,ie. it is steady in respect to position.
     */
    Continuity_Position = 0,
    
    /*!
     * @brief  The curve provides C1 continuity,ie. it is steady in respect to tangents.
     */
    Continuity_Tangent = 1,
    
    /*!
     * @brief  The curve provides C2 continuity,ie. it is steady in respect to curvature.
     */
    Continuity_Curvature = 2
  };
  
} } } } 

#endif
