////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_IMAGING_FILEIMAGE_H
#define CLODDY_API_IMAGING_FILEIMAGE_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/FileImageFormat.h"

// Include referenced classes.

#include "Cloddy/FileBasedImage.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Imaging { namespace DataProviders { class IFileDataProvider; } } } }
namespace Cloddy { namespace API { namespace Imaging { class IImageReader; } } }
namespace Cloddy { namespace API { namespace Imaging { class IImageVisitor; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Imaging { class ImageInfo; } } }
namespace Cloddy { namespace Core { namespace IO { namespace Files { class Path; } } } }

// Declare class ::Cloddy::API::Imaging::FileImage.

namespace Cloddy { namespace API { namespace Imaging
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Imaging::DataProviders::IFileDataProvider;
  
  // Use referenced classes.
  
  using Cloddy::Core::IO::Files::Path;
  
  /*!
   * @brief  An Imaging Object Model node that represents an image file (such as TIFF or PNG)in the 
   *         local filesystem.
   */
  class FileImage : public FileBasedImage
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual bool CanNormalize();
    
    /*!
     * @brief  The file format of the image file.
     * 
     * The default value is FileImageFormat::FileImageFormat_UnknownFileFormat.
     * 
     * If FileImageFormat::FileImageFormat_UnknownFileFormat,the file format will be guessed from 
     * the file extension.
     * 
     * @return The image file format.
     */
    FileImageFormat GetFormat();
    
    /*!
     * @brief  The file format of the image file.
     * 
     * The default value is FileImageFormat::FileImageFormat_UnknownFileFormat.
     * 
     * If FileImageFormat::FileImageFormat_UnknownFileFormat,the file format will be guessed from 
     * the file extension.
     * 
     * @param value The image file format.
     */
    void SetFormat(FileImageFormat value);
    
    /*!
     * @brief  An optional ImageInfo object that stores the knwon width,height,pixel and file 
     *         format of the referenced image file.
     * 
     * This property can be set when information about an image file is known in advance.When set,
     * the IImage::ReadImageInfo method does not need to access the image file (which may require 
     * decompression and decoding),which can dramatically increases performance.
     * 
     * @return The image info object or \c null .
     */
    Ptr<ImageInfo> GetKnownImageInfo();
    
    /*!
     * @brief  An optional ImageInfo object that stores the knwon width,height,pixel and file 
     *         format of the referenced image file.
     * 
     * This property can be set when information about an image file is known in advance.When set,
     * the IImage::ReadImageInfo method does not need to access the image file (which may require 
     * decompression and decoding),which can dramatically increases performance.
     * 
     * @param value The image info object or \c null .
     */
    void SetKnownImageInfo(ImageInfo* value);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of FileImage.
     */
    FileImage();
    
    /*!
     * @brief  Creates a new instance of FileImage.
     * 
     * @param filePath <b>[not-null]</b>  The file path of the image file.
     */
    FileImage(Path* filePath);
    
    /*!
     * @brief  Creates a new instance of FileImage.
     * 
     * When \e format  is set to FileImageFormat::FileImageFormat_UnknownFileFormat,the file format 
     * will be guessed from the file extension.
     * 
     * @param filePath <b>[not-null]</b>  The file path of the image file.
     * @param format The file format of the image file.
     */
    FileImage(Path* filePath, FileImageFormat format);
    
    /*!
     * @brief  Creates a new instance of FileImage.
     * 
     * @param fileData <b>[not-null]</b>  The file data provider.
     */
    FileImage(IFileDataProvider* fileData);
    
    /*!
     * @brief  Creates a new instance of FileImage.
     * 
     * When \e format  is set to FileImageFormat::FileImageFormat_UnknownFileFormat,the file format 
     * will be guessed from the file extension.
     * 
     * @param fileData <b>[not-null]</b>  The file data provider.
     * @param format The file format of the image file.
     */
    FileImage(IFileDataProvider* fileData, FileImageFormat format);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of FileImage.
     * 
     * @param filePath <b>[not-null]</b>  The file path.
     * 
     * @return <b>[not-null]</b>  The FileImage object.
     */
    static Ptr<FileImage> FromFile(Path* filePath);
    
    /*!
     * @brief  Creates a new instance of FileImage.
     * 
     * @param filePath <b>[not-null]</b>  The file path.
     * @param fileFormat The file format.
     * 
     * @return <b>[not-null]</b>  The FileImage object.
     */
    static Ptr<FileImage> FromFile(Path* filePath, FileImageFormat fileFormat);
    
    virtual void Accept(IImageVisitor* visitor, Object* userData);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
  protected:
    
    virtual Ptr<IImageReader> DoReadImage();
    
    virtual Ptr<ImageInfo> DoReadImageInfo();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The file format of the image file.
     * 
     * When set to FileImageFormat::FileImageFormat_UnknownFileFormat,the file format will be 
     * guessed from the file extension.
     */
    FileImageFormat format;
    
    /*!
     * @brief  An optional ImageInfo object that stores the width,height and pixel format of the 
     *         referenced image file.
     */
    Ptr<ImageInfo> knownImageInfo;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Returns the FileImageFormat to use for reading the image file.
     * 
     * @return The FileImageFormat to use.
     */
    FileImageFormat GetFileFormat();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<FileImage> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xEA79BC9F;
    
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
      void* ptr;
      if ((ptr = FileBasedImage::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
