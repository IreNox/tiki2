////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_IO_STREAMS_IDATASTREAM_H
#define CLODDY_CORE_IO_STREAMS_IDATASTREAM_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "CodeX/ByteOrder.h"

// Include referenced interfaces.

#include "CodeX/IDisposable.h"
#include "Cloddy/IFlushable.h"

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace IO { namespace Files { class Path; } } } }
namespace CodeX { namespace System { class ByteBuffer; } }

// Declare interface ::Cloddy::Core::IO::Streams::IDataStream.

namespace Cloddy { namespace Core { namespace IO { namespace Streams
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  using namespace CodeX::System;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::IO::IFlushable;
  
  // Use referenced classes.
  
  using Cloddy::Core::IO::Files::Path;
  
  /*!
   * @brief  An IDataStream object provides access to a file in the filesystem in a stream 
   *         oriented (ie. sequential)manner.
   * 
   * The interface provides methods for manipulating the file cursor of the underlying file in the 
   * filesystem and methods for reading and writing of single bytes values and blocks of bytes.
   * 
   * Additional methods provide support for reading and writing of multibyte values,byte endianess 
   * and a file cursor stack for simplified navigation in data streams that support seeking.
   */
  class NO_VTABLE IDataStream : public virtual IFlushable, public virtual IDisposable
  {
    // ---------------------------------------------------------------------------------------------
    // Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Does this stream support read access?
     * 
     * @return \c true  if this stream supports reading,\c false  if not.
     */
    virtual bool CanRead() = 0;
    
    /*!
     * @brief  Does this stream support seeking (via #GetPosition)?
     * 
     * @return \c true  if this stream supports seeking,\c false  if not.
     */
    virtual bool CanSeek() = 0;
    
    /*!
     * @brief  Does this stream support write access?
     * 
     * @return \c true  if this stream supports writing,\c false  if not.
     */
    virtual bool CanWrite() = 0;
    
    /*!
     * @brief  The byte-order to use for reading and writing multibyte values.
     * 
     * The default byte-order is ByteOrder::ByteOrder_LittleEndian.
     * 
     * @return The byte-order to use.
     */
    virtual ByteOrder GetEndianess() = 0;
    
    /*!
     * @brief  The byte-order to use for reading and writing multibyte values.
     * 
     * The default byte-order is ByteOrder::ByteOrder_LittleEndian.
     * 
     * @param value The byte-order to use.
     */
    virtual void SetEndianess(ByteOrder value) = 0;
    
    /*!
     * @brief  Path to the file in the filesystem.
     * 
     * @return <b>[not-null]</b>  Path to the file in the filesystem.
     */
    virtual Ptr<Path> GetFilePath() = 0;
    
    /*!
     * @brief  Length of this data stream.
     * 
     * @return <b>[>=0]</b>  The length of this data stream.If the length is unknown resp. the 
     * stream does not support seeking (see #CanSeek),\c 0  is returned.
     */
    virtual int64 GetLength() = 0;
    
    /*!
     * @brief  The current position of the file cursor.
     * 
     * @return <b>[>=0]</b>  The file cursor position,as an absolute offset from the beginning of 
     * the file,in bytes.
     * 
     * @exception CoreException  
     *   - If the parameters are invalid.
     *   - If an I/O error occurs.
     *   - If the position is set and #CanSeek return \c false .
     */
    virtual int64 GetPosition() = 0;
    
    /*!
     * @brief  The current position of the file cursor.
     * 
     * @param value <b>[>=0]</b>  The file cursor position,as an absolute offset from the beginning 
     * of the file,in bytes.
     * 
     * @exception CoreException  
     *   - If the parameters are invalid.
     *   - If an I/O error occurs.
     *   - If the position is set and #CanSeek return \c false .
     */
    virtual void SetPosition(int64 value) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Wraps this data stream in a buffered stream.
     * 
     * When mixing read and write operations using a buffered stream,seeking will become necessary 
     * on this stream (see #CanSeek).
     * 
     * @param bufferSize <b>[>=0]</b>  The buffer size,in bytes.
     * 
     * @return <b>[not-null]</b>  The buffered data stream.
     */
    virtual Ptr<IDataStream> Buffer(int32 bufferSize) = 0;
    
    /*!
     * @brief  Pops the topmost position from the stack and sets the current file cursor position 
     *         to that value.
     * 
     * The #PushPosition and #PopPosition are convenience methods that can be used jump back and 
     * forth in the file for reading/writing disjoint blocks of data.
     * 
     * @exception CoreException  
     *   - If the stack is empty.
     *   - If an I/O error occurs.
     *   - If #CanSeek return \c false .
     */
    virtual void PopPosition() = 0;
    
    /*!
     * @brief  Starts to preload the next \e n  bytes from the stream.
     * 
     * @param n <b>[>=0]</b>  The number of bytes to preload.
     */
    virtual void Preload(int32 n) = 0;
    
    /*!
     * @brief  Pushes the current file cursor position onto the stack.
     * 
     * The #PushPosition and #PopPosition are convenience methods that can be used jump back and 
     * forth in the file for reading/writing disjoint blocks of data.
     * 
     * @exception CoreException  
     *   - If an I/O error occurs.
     *   - If #CanSeek return \c false .
     */
    virtual void PushPosition() = 0;
    
    /*!
     * @brief  Copies all remaining bytes in this stream to the given stream.
     * 
     * @param stream <b>[not-null]</b>  The stream.
     */
    virtual void Read(IDataStream* stream) = 0;
    
    /*!
     * @brief  Reads a number of bytes from the stream.
     * 
     * The number of bytes that are read from the stream may be less than to the number 
     * of ByteBuffer::GetRemaining bytes in the given ByteBuffer.
     * 
     * @param bytes <b>[not-null]</b>  The buffer where the read bytes will be stored.
     * 
     * @return <b>[>=0]</b>  The number of bytes the have been read.A return value of \c 0  
     * indicates that the end of the stream has been reached.
     * 
     * @exception CoreException  
     *   - If the parameters are invalid.
     *   - If an I/O error occurs.
     *   - If #CanRead returns \c false .
     */
    virtual int64 Read(ByteBuffer* bytes) = 0;
    
    /*!
     * @brief  Reads a 32-bit floating point value from the data stream using the current 
     *         endianess (see #GetEndianess).
     * 
     * @return The read value.
     * 
     * @exception CoreException  
     *   - If the end of the stream has been reached.
     *   - If an I/O error occurs.
     *   - If #CanRead returns \c false .
     */
    virtual float32 ReadFloat32() = 0;
    
    /*!
     * @brief  Reads a 64-bit floating point value from the data stream using the current 
     *         endianess (see #GetEndianess).
     * 
     * @return The read value.
     * 
     * @exception CoreException  
     *   - If the end of the stream has been reached.
     *   - If an I/O error occurs.
     *   - If #CanRead returns \c false .
     */
    virtual float64 ReadFloat64() = 0;
    
    /*!
     * @brief  Reads a signed 16-bit integer value from the data stream using the current 
     *         endianess (see #GetEndianess).
     * 
     * @return The read value.
     * 
     * @exception CoreException  
     *   - If the end of the stream has been reached.
     *   - If an I/O error occurs.
     *   - If #CanRead returns \c false .
     */
    virtual int16 ReadInt16() = 0;
    
    /*!
     * @brief  Reads a signed 32-bit integer value from the data stream using the current 
     *         endianess (see #GetEndianess).
     * 
     * @return The read value.
     * 
     * @exception CoreException  
     *   - If the end of the stream has been reached.
     *   - If an I/O error occurs.
     *   - If #CanRead returns \c false .
     */
    virtual int32 ReadInt32() = 0;
    
    /*!
     * @brief  Reads a signed 64-bit integer value from the data stream using the current 
     *         endianess (see #GetEndianess).
     * 
     * @return The read value.
     * 
     * @exception CoreException  
     *   - If the end of the stream has been reached.
     *   - If an I/O error occurs.
     *   - If #CanRead returns \c false .
     */
    virtual int64 ReadInt64() = 0;
    
    /*!
     * @brief  Reads an 8-bit value from the stream.
     * 
     * @return The read value.
     * 
     * @exception CoreException  
     *   - If the end of the stream has been reached.
     *   - If an I/O error occurs.
     *   - If #CanRead returns \c false .
     */
    virtual int8 ReadInt8() = 0;
    
    /*!
     * @brief  Reads an unsigned 16-bit integer value from the data stream using the current 
     *         endianess (see #GetEndianess).
     * 
     * @return The read value.
     * 
     * @exception CoreException  
     *   - If the end of the stream has been reached.
     *   - If an I/O error occurs.
     *   - If #CanRead returns \c false .
     */
    virtual int32 ReadUInt16() = 0;
    
    /*!
     * @brief  Reads an unsigned 32-bit integer value from the data stream using the current 
     *         endianess (see #GetEndianess).
     * 
     * @return The read value.
     * 
     * @exception CoreException  
     *   - If the end of the stream has been reached.
     *   - If an I/O error occurs.
     *   - If #CanRead returns \c false .
     */
    virtual int64 ReadUInt32() = 0;
    
    /*!
     * @brief  Reads an unsigned 8-bit integer from the data stream.
     * 
     * @return The read value.
     * 
     * @exception CoreException  
     *   - If the end of the stream has been reached.
     *   - If an I/O error occurs.
     *   - If #CanRead returns \c false .
     */
    virtual int32 ReadUInt8() = 0;
    
    /*!
     * @brief  Skips the next bytes in the stream.
     * 
     * @param count <b>[>=0]</b>  The number of bytes to skip.
     */
    virtual void Skip(int64 count) = 0;
    
    /*!
     * @brief  Copies all remaining bytes in the given stream to this stream.
     * 
     * @param stream <b>[not-null]</b>  The stream.
     */
    virtual void Write(IDataStream* stream) = 0;
    
    /*!
     * @brief  Writes a number of bytes to the stream.
     * 
     * @param bytes <b>[not-null]</b>  The bytes to write.
     * 
     * @exception CoreException  
     *   - If the parameters are invalid.
     *   - If an I/O error occurs.
     *   - If #CanWrite returns \c false .
     */
    virtual void Write(ByteBuffer* bytes) = 0;
    
    /*!
     * @brief  Writes a 32-bit floating point value to the data stream using the current endianess.(
     *         see #GetEndianess).
     * 
     * @param value The value to write.
     * 
     * @exception CoreException  
     *   - If an I/O error occurs.
     *   - If #CanWrite returns \c false .
     */
    virtual void WriteFloat32(float32 value) = 0;
    
    /*!
     * @brief  Writes a 64-bit floating point value to the data stream using the current endianess.(
     *         see #GetEndianess).
     * 
     * @param value The value to write.
     * 
     * @exception CoreException  
     *   - If an I/O error occurs.
     *   - If #CanWrite returns \c false .
     */
    virtual void WriteFloat64(float64 value) = 0;
    
    /*!
     * @brief  Writes a signed 16-bit integer value to the data stream using the current endianess.(
     *         see #GetEndianess).
     * 
     * @param value The value to write.
     * 
     * @exception CoreException  
     *   - If an I/O error occurs.
     *   - If #CanWrite returns \c false .
     */
    virtual void WriteInt16(int16 value) = 0;
    
    /*!
     * @brief  Writes a signed 32-bit integer value to the data stream using the current endianess.(
     *         see #GetEndianess).
     * 
     * @param value The value to write.
     * 
     * @exception CoreException  
     *   - If an I/O error occurs.
     *   - If #CanWrite returns \c false .
     */
    virtual void WriteInt32(int32 value) = 0;
    
    /*!
     * @brief  Writes a signed 64-bit integer value to the data stream using the current endianess.(
     *         see #GetEndianess).
     * 
     * @param value The value to write.
     * 
     * @exception CoreException  
     *   - If an I/O error occurs.
     *   - If #CanWrite returns \c false .
     */
    virtual void WriteInt64(int64 value) = 0;
    
    /*!
     * @brief  Writes an 8-bit integer value to the stream.
     * 
     * @param value The value to write.
     * 
     * @exception CoreException  
     *   - If an I/O error occurs.
     *   - If #CanWrite returns \c false .
     */
    virtual void WriteInt8(int8 value) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IDataStream> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x79D8207D;
    
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
      if ((ptr = IFlushable::TryCast(typeId)) != 0) return ptr;
      if ((ptr = IDisposable::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
} } } } 

#endif
