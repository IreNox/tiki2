////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_IO_FILES_IFILESYSTEM_H
#define CLODDY_CORE_IO_FILES_IFILESYSTEM_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/FileHint.h"

// Include referenced interfaces.

#include "CodeX/IDisposable.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace IO { namespace Files { class IFile; } } } }
namespace Cloddy { namespace Core { namespace IO { class IAsyncIO; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace IO { namespace Files { class Path; } } } }

// Declare interface ::Cloddy::Core::IO::Files::IFileSystem.

namespace Cloddy { namespace Core { namespace IO { namespace Files
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::IO::IAsyncIO;
  using CodeX::System::IDisposable;
  
  /*!
   * @brief  This interface defines all platform and framework specific methods.
   */
  class NO_VTABLE IFileSystem : public virtual IDisposable
  {
    // ---------------------------------------------------------------------------------------------
    // Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Gets or sets the current directory of this filesystem.
     * 
     * The returned directory will always be in canonical form,ie. it is not necessary to 
     * call #GetCanonicalPath.
     * 
     * @return <b>[not-null]</b>  The current directory.
     */
    virtual Ptr<Path> GetDirectory() = 0;
    
    /*!
     * @brief  Gets or sets the current directory of this filesystem.
     * 
     * The returned directory will always be in canonical form,ie. it is not necessary to 
     * call #GetCanonicalPath.
     * 
     * @param value <b>[not-null]</b>  The current directory.
     */
    virtual void SetDirectory(Path* value) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new file,overwriting any existing files.
     * 
     * @param path <b>[not-null]</b>  Path to the file to create.
     * @param length <b>[>=0]</b>  Initial length of the file,in bytes.The file length may be 
     * rounded up to the byte alignment (see IByteAligned::GetByteAlignment)of the returned IFile 
     * object.
     * @param hint The file access mode hint to use.
     * 
     * @return <b>[not-null]</b>  The created IFile object.
     */
    virtual Ptr<IFile> Create(Path* path, int64 length, FileHint hint) = 0;
    
    /*!
     * @brief  Creates the given directory.
     * 
     * If the given directory already exists,the method returns silently.
     * 
     * The method will create all ancestor directories if necessary.
     * 
     * @param path <b>[not-null]</b>  The directory path.
     */
    virtual void Create(Path* path) = 0;
    
    /*!
     * @brief  Creates an IAsyncIO object that can be used with IFile instances that haven been 
     *         opened resp. created using this platform.
     * 
     * @return <b>[not-null]</b>  The created IAsyncIO object.
     */
    virtual Ptr<IAsyncIO> CreateAsyncIO() = 0;
    
    /*!
     * @brief  Deletes the given file or directory.
     * 
     * A directory can only be deleted if it is empty.
     * 
     * @param path <b>[not-null]</b>  The path.
     */
    virtual void Delete(Path* path) = 0;
    
    /*!
     * @brief  Checks if the given directory exists.
     * 
     * @param path <b>[not-null]</b>  The directory path.
     * 
     * @return \c true  if the directory exists,\c false  if not.
     */
    virtual bool DirectoryExists(Path* path) = 0;
    
    /*!
     * @brief  Checks if the given file exists.
     * 
     * @param path <b>[not-null]</b>  The file path.
     * 
     * @return \c true  if the file exists,\c false  if not.
     */
    virtual bool FileExists(Path* path) = 0;
    
    /*!
     * @brief  Returns the canonical name of the given path (ie. the fully resolved absolute path).
     * 
     * @param path <b>[not-null]</b>  The path.
     * 
     * @return <b>[not-null]</b>  The canonical path.
     */
    virtual Ptr<Path> GetCanonicalPath(Path* path) = 0;
    
    /*!
     * @brief  Opens an existing file.
     * 
     * @param path <b>[not-null]</b>  Path to the file to open.
     * @param readOnly Open the file as read only?
     * @param hint The file access mode hint to use.
     * 
     * @return <b>[not-null]</b>  The opened IFile object.
     */
    virtual Ptr<IFile> Open(Path* path, bool readOnly, FileHint hint) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IFileSystem> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x36601DDE;
    
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
      if ((ptr = IDisposable::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
} } } } 

#endif
