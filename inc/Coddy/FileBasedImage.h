////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_IMAGING_FILEBASEDIMAGE_H
#define CLODDY_API_IMAGING_FILEBASEDIMAGE_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/ImageBase.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Imaging { namespace DataProviders { class IFileDataProvider; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace IO { namespace Files { class Path; } } } }

// Declare class ::Cloddy::API::Imaging::FileBasedImage.

namespace Cloddy { namespace API { namespace Imaging
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Imaging::DataProviders::IFileDataProvider;
  
  // Use referenced classes.
  
  using Cloddy::Core::IO::Files::Path;
  
  /*!
   * @brief  Abstract base class for IImage classes that read image data from files in the local 
   *         filesystem.
   */
  class FileBasedImage : public ImageBase
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The file data provider.
     * 
     * @return <b>[not-null]</b>  The file data provider.
     */
    Ptr<IFileDataProvider> GetFileData();
    
    /*!
     * @brief  The file data provider.
     * 
     * @param value <b>[not-null]</b>  The file data provider.
     */
    void SetFileData(IFileDataProvider* value);
    
    /*!
     * @brief  The file path of the file that is used by this image descriptor.
     * 
     * Setting this property has the same effect as assigning a LocalFileDataProvider object to 
     * the #GetFileData property.
     * 
     * @return <b>[not-null]</b>  Path to the file in the local filesystem.
     */
    Ptr<Path> GetFilePath();
    
    /*!
     * @brief  The file path of the file that is used by this image descriptor.
     * 
     * Setting this property has the same effect as assigning a LocalFileDataProvider object to 
     * the #GetFileData property.
     * 
     * @param value <b>[not-null]</b>  Path to the file in the local filesystem.
     */
    void SetFilePath(Path* value);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void Validate();
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Constructors
    // ---------------------------------------------------------------------------------------------
  protected:
    
    /*!
     * @brief  Creates a new instance of FileBasedImage.
     */
    FileBasedImage();
    
    /*!
     * @brief  Creates a new instance of FileBasedImage.
     * 
     * @param filePath <b>[not-null]</b>  Path to the file in the local filesystem.
     */
    FileBasedImage(Path* filePath);
    
    /*!
     * @brief  Creates a new instance of FileBasedImage.
     * 
     * @param fileData <b>[not-null]</b>  The file data provider.
     */
    FileBasedImage(IFileDataProvider* fileData);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The file data provider.
     */
    Ptr<IFileDataProvider> fileData;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<FileBasedImage> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xC0B33956;
    
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
      if ((ptr = ImageBase::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
