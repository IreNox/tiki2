////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_SAMPLEFORMATS_SAMPLECONVERTERTYPE_H
#define CLODDY_API_HEIGHTMAPS_SAMPLEFORMATS_SAMPLECONVERTERTYPE_H

#include "CodeX/System.h"

// Declare enumeration ::Cloddy::API::Heightmaps::SampleFormats::SampleConverterType.

namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleFormats
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Enumeration of sample converter types.
   */
  enum SampleConverterType
  {
    /*!
     * @brief  8-bit elevation values (one dataset channel).
     */
    SampleConverterType_E8 = 0,
    
    /*!
     * @brief  16-bit elevation values (two dataset channels).
     */
    SampleConverterType_E16 = 1,
    
    /*!
     * @brief  24-bit elevation values (three dataset channels).
     */
    SampleConverterType_E24 = 2,
    
    /*!
     * @brief  8-bit grayscale diffuse color values (one dataset channel).
     */
    SampleConverterType_C8 = 3,
    
    /*!
     * @brief  16-bit 565 RGB diffuse color values(two dataset channels).
     */
    SampleConverterType_C16 = 4,
    
    /*!
     * @brief  24-bit RGB diffuse color values (three dataset channels).
     */
    SampleConverterType_C24 = 5,
    
    /*!
     * @brief  32-bit ARGB diffuse color values (four dataset channels).
     */
    SampleConverterType_C32 = 6,
    
    /*!
     * @brief  24-bit XYZ displacement values (three dataset channels).
     */
    SampleConverterType_D24 = 7,
    
    /*!
     * @brief  48-bit XYZ displacement values (six dataset channels,two per axis).
     */
    SampleConverterType_D48 = 8,
    
    /*!
     * @brief  32-bit detail values (four dataset channels).
     */
    SampleConverterType_X32 = 9,
    
    /*!
     * @brief  64-bit detail values (eight dataset channels).
     */
    SampleConverterType_X64 = 10,
    
    /*!
     * @brief  96-bit detail values (twelve dataset channels).
     */
    SampleConverterType_X96 = 11,
    
    /*!
     * @brief  128-bit detail values (sixteen dataset channels).
     */
    SampleConverterType_X128 = 12
  };
  
} } } } 

#endif
