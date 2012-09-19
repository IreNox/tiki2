////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_IMAGING_IMAGEUTIL_H
#define CLODDY_API_IMAGING_IMAGEUTIL_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/FileImageFormat.h"
#include "Cloddy/PixelFormat.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Imaging { class IImage; } } }
namespace Cloddy { namespace API { namespace Imaging { class IImageReader; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace IO { namespace Files { class Path; } } } }
namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::API::Imaging::ImageUtil.

namespace Cloddy { namespace API { namespace Imaging
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced classes.
  
  using Cloddy::Core::IO::Files::Path;
  using CodeX::System::ByteBuffer;
  
  /*!
   * @brief  Utility class for working with image files.
   */
  class ImageUtil
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Returns the number of bytes per pixel for the given pixel format.
     * 
     * @param pixelFormat The pixel format.
     * 
     * @return <b>[>0]</b>  The number of bytes per pixel.
     */
    static int32 GetBytesPerPixel(PixelFormat pixelFormat);
    
    /*!
     * @brief  Returns the number of channels per pixel for the given pixel format.
     * 
     * @param pixelFormat The pixel format.
     * 
     * @return <b>[>0]</b>  The number of channels per pixel.
     */
    static int32 GetChannelsPerPixel(PixelFormat pixelFormat);
    
    /*!
     * @brief  Returns a combined pixel format that is best suited to represents pixels of the 
     *         given input pixel formats.
     * 
     * The following table shows how pixel formats are combined:
     * <pre>
     *     pixel       | pixel       | resulting
     *     format #1   | format #2   | pixel format
     *     -------------+-------------+-------------
     *     Grayscale8  | Grayscale8  | Grayscale8
     *     Grayscale8  | Grayscale16 | Grayscale16
     *     Grayscale8  | Truecolor24 | Truecolor24
     *     Grayscale8  | Truecolor32 | Truecolor32
     *     Grayscale16 | Grayscale8  | Grayscale16
     *     Grayscale16 | Grayscale16 | Grayscale16
     *     Grayscale16 | Truecolor24 | Truecolor24
     *     Grayscale16 | Truecolor32 | Truecolor32
     *     Truecolor24 | Grayscale8  | Truecolor24
     *     Truecolor24 | Grayscale16 | Truecolor24
     *     Truecolor24 | Truecolor24 | Truecolor24
     *     Truecolor24 | Truecolor32 | Truecolor32
     *     Truecolor32 | Grayscale8  | Truecolor32
     *     Truecolor32 | Grayscale16 | Truecolor32
     *     Truecolor32 | Truecolor24 | Truecolor32
     *     Truecolor32 | Truecolor32 | Truecolor32
     * </pre>
     * 
     * @param a First input pixel format.
     * @param b Second input pixel format.
     * 
     * @return The combined pixel format.
     */
    static PixelFormat GetCombinedPixelFormat(PixelFormat a, PixelFormat b);
    
    /*!
     * @brief  Returns the file format of the given image file.The file format is determined from 
     *         the file extension.///
     * 
     * @param imageFile The image file path.
     * 
     * @return The image file format (can be FileImageFormat::FileImageFormat_UnknownFileFormat).
     */
    static FileImageFormat GetFileFormat(Path* imageFile);
    
    /*!
     * @brief  Fully reads the given image into the specified buffer.
     * 
     * @param image <b>[not-null]</b>  The image to read.
     * @param buffer <b>[not-null]</b>  The output buffer.
     */
    static void ReadIntoBuffer(IImage* image, ByteBuffer* buffer);
    
    /*!
     * @brief  Fully reads the given image into the specified buffer.
     * 
     * @param imageReader <b>[not-null]</b>  The image reader to use.
     * @param buffer <b>[not-null]</b>  The output buffer.
     */
    static void ReadIntoBuffer(IImageReader* imageReader, ByteBuffer* buffer);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Returns the file format for the given file extension.
     * 
     * @param fileExtension The file extension,including the leading period.
     * 
     * @return The suggested FileImageFormat.
     */
    static FileImageFormat GetFileFormatForFileExtension(String fileExtension);
  };
  
} } } 

#endif
