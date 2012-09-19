////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_IO_FILES_BUFFERDATASTREAM_FILE_H
#define CLODDY_CORE_IO_FILES_BUFFERDATASTREAM_FILE_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/BufferDataStreamBase.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace IO { namespace Files { class IFile; } } } }
namespace Cloddy { namespace Core { namespace IO { class IAsyncIO; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace IO { namespace Files { class FileBase; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Files { class Path; } } } }
namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::Core::IO::Files::BufferDataStream_File.

namespace Cloddy { namespace Core { namespace IO { namespace Files
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::IO::IAsyncIO;
  
  // Use referenced classes.
  
  using Cloddy::Core::IO::Streams::BufferDataStreamBase;
  using CodeX::System::ByteBuffer;
  
  /*!
   * @brief  An implementation of the IDataStream that performs memory buffered I/O on a IFile 
   *         object.
   */
  class BufferDataStream_File : public BufferDataStreamBase
  {
    // Declare friend classes.
    
    friend class FileBase;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual bool CanRead();
    
    virtual bool CanSeek();
    
    virtual bool CanWrite();
    
    virtual Ptr<Path> GetFilePath();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void Flush();
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
  protected:
    
    virtual void DisposeManaged();
    
    virtual void DisposeManagedChildren();
    
    virtual int64 DoRead(int64 position, ByteBuffer* buffer);
    
    virtual void DoWrite(int64 position, ByteBuffer* buffer);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The underlying file.
     */
    Ptr<IFile> file;
    
    /*!
     * @brief  The I/O handle.
     */
    Ptr<IAsyncIO> io;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of BufferDataStream_File.
     * 
     * @param file The underlying file.
     * @param bufferSize The buffer size.
     */
    BufferDataStream_File(IFile* file, int32 bufferSize);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<BufferDataStream_File> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xE273EE1F;
    
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
               if ((ptr = BufferDataStreamBase::TryCast(typeId)) != 0) return ptr;
               return (void*) 0;
             }
  };
  
} } } } 

#endif
