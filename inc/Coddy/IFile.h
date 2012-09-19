////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_IO_FILES_IFILE_H
#define CLODDY_CORE_IO_FILES_IFILE_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IByteAligned.h"
#include "Cloddy/IDataStreamFactory.h"
#include "CodeX/IDisposable.h"
#include "Cloddy/IFlushable.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace IO { class IAsyncIO; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace IO { namespace Files { class Path; } } } }
namespace CodeX { namespace System { class ByteBuffer; } }

// Declare interface ::Cloddy::Core::IO::Files::IFile.

namespace Cloddy { namespace Core { namespace IO { namespace Files
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::IO::IAsyncIO;
  using Cloddy::Core::IO::IByteAligned;
  using Cloddy::Core::IO::IFlushable;
  using Cloddy::Core::IO::Streams::IDataStreamFactory;
  using CodeX::System::IDisposable;
  
  // Use referenced classes.
  
  using CodeX::System::ByteBuffer;
  
  /*!
   * @brief  Base interface for classes that provide raw access to I/O storage devices.
   */
  class NO_VTABLE IFile : public virtual IDisposable, public virtual IFlushable, public virtual IByteAligned, public virtual IDataStreamFactory
  {
    // ---------------------------------------------------------------------------------------------
    // Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Shall this file be deleted when the IFile object is disposed 
     *         via IDisposable::Dispose?
     * 
     * The default value is \c false .
     * 
     * @return \c true  if the file shall be deleted,\c false  if not.
     */
    virtual bool GetDeleteOnDispose() = 0;
    
    /*!
     * @brief  Shall this file be deleted when the IFile object is disposed 
     *         via IDisposable::Dispose?
     * 
     * The default value is \c false .
     * 
     * @param value \c true  if the file shall be deleted,\c false  if not.
     */
    virtual void SetDeleteOnDispose(bool value) = 0;
    
    /*!
     * @brief  Does this file allow read access only?
     * 
     * @return \c true  if this file only allows read access,\c false  if not.
     */
    virtual bool IsReadOnly() = 0;
    
    /*!
     * @brief  Returns or sets the file length.
     * 
     * The file length will be rounded up to the next multiple of IByteAligned::GetByteAlignment.
     * 
     * @return <b>[>=0]</b>  The current file length,in bytes.
     */
    virtual int64 GetLength() = 0;
    
    /*!
     * @brief  Returns or sets the file length.
     * 
     * The file length will be rounded up to the next multiple of IByteAligned::GetByteAlignment.
     * 
     * @param value <b>[>=0]</b>  The current file length,in bytes.
     */
    virtual void SetLength(int64 value) = 0;
    
    /*!
     * @brief  The file path.
     * 
     * @return <b>[not-null]</b>  The file path.
     */
    virtual Ptr<Path> GetFilePath() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Tries to map this file into the address space of the calling process.
     * 
     * Calling the #Map method multiple times will result in the file being mapped only once.The 
     * same ByteBuffer will be returned for each call.
     * 
     * Memory mapping a file can fail because of the following reasons:
     *   - The remaining address space is too small (files >4GB on 32-bit systems).
     *   - The OS does not offer memory mapping services (video game consoles).
     * 
     * The mapping will cover the entire file.If the file length is modified later,the mapping must 
     * be recreated in order to reflect the new file length.
     * 
     * @return The ByteBuffer which represents the mapped file or \c null  if the file cannot be 
     * mapped.
     */
    virtual Ptr<ByteBuffer> Map() = 0;
    
    /*!
     * @brief  Reads a chunk of bytes from the file.
     * 
     * The given file \e offset  must be a multiple of this files byte alignment (
     * see IByteAligned::GetByteAlignment),as well as the address of the memory location depicted 
     * be the current position of the provided buffer.
     * 
     * The number of bytes to read (see \e buffer )must be a multiple of this files byte alignment.
     * The actual number of read bytes may be lower than this limit when reading over the end of 
     * the file.The maximum number of bytes that can be read with a single call to #Read is 
     * <c>2^31-1</c>.
     * 
     * The method may return immediately,ie. before the read operation has finished.The IAsyncIO 
     * object provided via \e asyncIO  can be used to synchronize with the completion of this read 
     * access.
     * 
     * @param offset <b>[>=0]</b>  File offset of first byte to read.
     * @param buffer <b>[not-null]</b>  The output buffer.The read bytes will be written at the 
     * buffers current position.The number of bytes to read is the number of remaining bytes in the 
     * buffer.The ByteBuffer object will not be modified by this method.
     * @param asyncIO <b>[not-null]</b>  The IAsyncIO object to use for tracking this write access.
     * 
     * @see IFileSystem::CreateAsyncIO
     */
    virtual void Read(int64 offset, ByteBuffer* buffer, IAsyncIO* asyncIO) = 0;
    
    /*!
     * @brief  Unmaps this file.
     * 
     * If the file has not been mapped into the address space of the calling process,the method 
     * silently returns.
     */
    virtual void Unmap() = 0;
    
    /*!
     * @brief  Writes a chunk of bytes to the file.
     * 
     * The given file \e offset  must be a multiple of this files byte alignment (
     * see IByteAligned::GetByteAlignment),as well as the address of the memory location depicted 
     * be the current position of the provided buffer.
     * 
     * The number of bytes to write (see \e buffer )must be a multiple of this files byte alignment.
     * The maximum number of bytes that can be written with a single call to #Write is 
     * <c>2^31-1</c>.
     * 
     * The method may return immediately,ie. before the write operation has finished.The IAsyncIO 
     * object provided via \e asyncIO  can be used to synchronize with the completion of this write 
     * access.
     * 
     * @param offset <b>[>=0]</b>  File offset of first byte to write.
     * @param buffer <b>[not-null]</b>  The input buffer.The bytes to write are read from the 
     * buffer starting at its current position.The number of bytes to write is the number of 
     * remaining bytes in the buffer.The ByteBuffer object will not be modified by this method.
     * @param asyncIO <b>[not-null]</b>  The IAsyncIO object to use for tracking this write access.
     * 
     * @see IFileSystem::CreateAsyncIO
     */
    virtual void Write(int64 offset, ByteBuffer* buffer, IAsyncIO* asyncIO) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IFile> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xC6137841;
    
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
      if ((ptr = IFlushable::TryCast(typeId)) != 0) return ptr;
      if ((ptr = IByteAligned::TryCast(typeId)) != 0) return ptr;
      if ((ptr = IDataStreamFactory::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
} } } } 

#endif
