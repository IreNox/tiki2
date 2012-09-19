////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_VERTEXFACTORIES_VERTEXFORMATS_COLORFORMAT_H
#define CLODDY_API_VERTEXFACTORIES_VERTEXFORMATS_COLORFORMAT_H

#include "CodeX/System.h"

// Declare enumeration ::Cloddy::API::VertexFactories::VertexFormats::ColorFormat.

namespace Cloddy { namespace API { namespace VertexFactories { namespace VertexFormats
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Enumeration of color formats when using 32-bit integer values.
   */
  enum ColorFormat
  {
    /*!
     * @brief  32-bit ARGB color value.
     * 
     * The color channels are written to consecutive memory addresses in the following order:red,
     * green,blue,alpha.
     */
    ColorFormat_RGBA = 0,
    
    /*!
     * @brief  32-bit ARGB color value.
     * 
     * The color channels are written to consecutive memory addresses in the following order:blue,
     * green,red,alpha.
     */
    ColorFormat_BGRA = 1
  };
  
} } } } 

#endif
