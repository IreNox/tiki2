////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_IMAGING_IMAGEINFO_H
#define CLODDY_API_IMAGING_IMAGEINFO_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/FileImageFormat.h"
#include "Cloddy/PixelFormat.h"

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Imaging { class PadImage; } } }
namespace Cloddy { namespace API { namespace Imaging { class PixelCoverageImage; } } }
namespace Cloddy { namespace Core { namespace IO { namespace Files { class Path; } } } }

// Declare class ::Cloddy::API::Imaging::ImageInfo.

namespace Cloddy { namespace API { namespace Imaging
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced classes.
  
  using Cloddy::Core::IO::Files::Path;
  
  /*!
   * @brief  Provides information about an image.
   */
  class ImageInfo : public virtual Object
  {
    // Declare friend classes.
    
    friend class PadImage;
    friend class PixelCoverageImage;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The file format of the image file.
     * 
     * The file format will be FileImageFormat::FileImageFormat_UnknownFileFormat if the image data 
     * is not stored in an image file in the local filesystem (ie. it is created on-the-fly).
     * 
     * @return The image file format.
     */
    FileImageFormat GetFileFormat();
    
    /*!
     * @brief  Path to the image file in the filesystem.
     * 
     * @return Path to the image file in the filesystem or \c null  if the image data is not stored 
     * in an image file in the local filesystem (ie. it is created on-the-fly).
     */
    Ptr<Path> GetFilePath();
    
    /*!
     * @brief  Height of the image,in pixels.
     * 
     * @return <b>[>0]</b>  Height of the image,in pixels.
     */
    int32 GetHeight();
    
    /*!
     * @brief  The pixel format of the image.
     * 
     * @return The pixel format of the image.
     */
    PixelFormat GetPixelFormat();
    
    /*!
     * @brief  Width of the image,in pixels.
     * 
     * @return <b>[>0]</b>  Width of the image,in pixels.
     */
    int32 GetWidth();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of ImageInfo.
     * 
     * @param width <b>[>0]</b>  Width of the image,in pixels.
     * @param height <b>[>0]</b>  Height of the image,in pixels.
     * @param pixelFormat The pixel format of the image.
     */
    ImageInfo(int32 width, int32 height, PixelFormat pixelFormat);
    
    /*!
     * @brief  Creates a new instance of ImageInfo.
     * 
     * @param filePath <b>[not-null]</b>  Path to the image file in the filesystem.
     * @param fileFormat The file format of the image file.
     * @param width <b>[>0]</b>  Width of the image,in pixels.
     * @param height <b>[>0]</b>  Height of the image,in pixels.
     * @param pixelFormat The pixel format of the image.
     */
    ImageInfo(Path* filePath, FileImageFormat fileFormat, int32 width, int32 height, PixelFormat pixelFormat);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The file format of the image file.
     */
    FileImageFormat fileFormat;
    
    /*!
     * @brief  Path to the image file in the filesystem.
     */
    Ptr<Path> filePath;
    
    /*!
     * @brief  Height of the image,in pixels.
     */
    int32 height;
    
    /*!
     * @brief  The pixel format of the image.
     */
    PixelFormat pixelFormat;
    
    /*!
     * @brief  Width of the image,in pixels.
     */
    int32 width;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Adjusts the size of this image info by the given relative amount.
     * 
     * @param deltaWidth The width delta.
     * @param deltaHeight The height delta.
     * 
     * @return <b>[not-null]</b>  The resulting ImageInfo object.
     */
    Ptr<ImageInfo> AdjustSize(int32 deltaWidth, int32 deltaHeight);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<ImageInfo> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x9AA39AB3;
    
    /*!
     * @brief Tries to cast this object to the given type.
     *
     * @param typeId The ID of the type to cast to.
     *
     * @return The result of the type cast. Can be \c 0 if the requested cast is an invalid 
     *         downcast.
     */
    protected: virtual void* TryCast(int typeId)
    {
      if (typeId == TypeId) return (void*) this;
      return (void*) 0;
    }
  };
  
} } } 

#endif
