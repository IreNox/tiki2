////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_UTIL_MAPTYPE_H
#define CLODDY_API_UTIL_MAPTYPE_H

#include "CodeX/System.h"

// Declare enumeration ::Cloddy::API::Util::MapType.

namespace Cloddy { namespace API { namespace Util
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Enumeration of map types (eg. datasets and heightmaps).
   */
  enum MapType
  {
    /*!
     * @brief  A rectangular map.
     * 
     * @see IMap
     */
    MapType_Rect = 0,
    
    /*!
     * @brief  A cubemap.
     * 
     * @see IMap
     */
    MapType_Cube = 1
  };
  
} } } 

#endif
