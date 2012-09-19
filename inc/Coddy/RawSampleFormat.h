////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_IMAGING_RAWSAMPLEFORMAT_H
#define CLODDY_API_IMAGING_RAWSAMPLEFORMAT_H

#include "CodeX/System.h"

// Declare enumeration ::Cloddy::API::Imaging::RawSampleFormat.

namespace Cloddy { namespace API { namespace Imaging
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Enumeration of sample formats that can be used with RawImage.
   */
  enum RawSampleFormat
  {
    /*!
     * @brief  Unknown sample format.
     */
    RawSampleFormat_UnknownRawSampleFormat = 0,
    
    /*!
     * @brief  Signed 8-bit integer.
     */
    RawSampleFormat_Int8 = 1,
    
    /*!
     * @brief  Unsigned 8-bit integer.
     */
    RawSampleFormat_UInt8 = 2,
    
    /*!
     * @brief  Signed 16-bit big-endian integer.
     */
    RawSampleFormat_Int16BE = 3,
    
    /*!
     * @brief  Signed 16-bit little-endian integer.
     */
    RawSampleFormat_Int16LE = 4,
    
    /*!
     * @brief  Unsigned 16-bit big-endian integer.
     */
    RawSampleFormat_UInt16BE = 5,
    
    /*!
     * @brief  Unsigned 16-bit little-endian integer.
     */
    RawSampleFormat_UInt16LE = 6,
    
    /*!
     * @brief  32-bit big-endian floating point value.
     */
    RawSampleFormat_Float32BE = 7,
    
    /*!
     * @brief  32-bit little-endian floating point value.
     */
    RawSampleFormat_Float32LE = 8
  };
  
} } } 

#endif
