////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_IMAGING_FILEIMAGEFORMAT_H
#define CLODDY_API_IMAGING_FILEIMAGEFORMAT_H

#include "CodeX/System.h"

// Declare enumeration ::Cloddy::API::Imaging::FileImageFormat.

namespace Cloddy { namespace API { namespace Imaging
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Enumeration of supported image file formats.
   */
  enum FileImageFormat
  {
    /*!
     * @brief  The file format is unknown.
     */
    FileImageFormat_UnknownFileFormat = 0,
    
    /*!
     * @brief  The PNG image file format.
     */
    FileImageFormat_PortableNetworkGraphics = 1,
    
    /*!
     * @brief  The TIFF image file format.
     */
    FileImageFormat_TaggedImageFileFormat = 2
  };
  
} } } 

#endif
