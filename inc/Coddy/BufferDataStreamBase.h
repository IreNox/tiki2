////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_IO_STREAMS_BUFFERDATASTREAMBASE_H
#define CLODDY_CORE_IO_STREAMS_BUFFERDATASTREAMBASE_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/DataStreamBase.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace IO { namespace Streams { class IDataStream; } } } }

// Forward declare referenced classes.

namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::Core::IO::Streams::BufferDataStreamBase.

namespace Cloddy { namespace Core { namespace IO { namespace Streams
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced classes.
  
  using CodeX::System::ByteBuffer;
  
  /*!
   * @brief  Abstract base class for IDataStream implementations that use a memory buffer for 
   *         increasing I/O performance.
   */
  class BufferDataStreamBase : public DataStreamBase
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual int64 GetLength();
    
    virtual int64 GetPosition();
    
    virtual void SetPosition(int64 value);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual Ptr<IDataStream> Buffer(int32 bufferSize);
    
    virtual void Flush();
    
    virtual int64 Read(ByteBuffer* bytes);
    
    virtual int8 ReadInt8();
    
    virtual void Write(ByteBuffer* bytes);
    
    virtual void WriteInt8(int8 value);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Constructors
    // ---------------------------------------------------------------------------------------------
  protected:
    
    /*!
     * @brief  Creates a new instance of BufferDataStreamBase.
     * 
     * @param bufferSize The buffer size,in bytes.
     * @param initialPosition The initial stream position.
     * @param initialLength The initial stream length.
     */
    BufferDataStreamBase(int32 bufferSize, int64 initialPosition, int64 initialLength);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void DisposeManaged();
    
    /*!
     * @brief  Reads a number of bytes.
     * 
     * @param position The stream position to start reading at.
     * @param buffer The output buffer.
     * 
     * @return The number of read bytes.
     */
    virtual int64 DoRead(int64 position, ByteBuffer* buffer) = 0;
    
    /*!
     * @brief  Writes a number of bytes.
     * 
     * @param position The stream position to start writing at.
     * @param buffer The input buffer.
     */
    virtual void DoWrite(int64 position, ByteBuffer* buffer) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The memory buffer.
     */
    Ptr<ByteBuffer> buffer;
    
    /*!
     * @brief  The current number of remaining bytes in the memory buffer.
     * 
     * A positive number indicates that the buffer is used for reading,a negative number indicates 
     * that the buffer is used for writing.The absolute value represents the number of buffered 
     * bytes.
     * 
     * When the buffer bytes count is positive,#buffer is used for buffering read operations.
     * 
     * When the buffer bytes count is negative,#buffer is used for buffering write operations.
     * 
     * In either case,the base stream will be positioned at #position +#bufferBytes.
     */
    int32 bufferBytes;
    
    /*!
     * @brief  Size of the memory buffer,in bytes.
     */
    int32 bufferSize;
    
    /*!
     * @brief  The current stream length.
     */
    int64 length;
    
    /*!
     * @brief  The current position of the buffer stream.
     */
    int64 position;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Clears the memory buffer.
     */
    void ClearBuffer();
    
    /*!
     * @brief  Fills the read buffer.
     */
    void FillReadBuffer();
    
    /*!
     * @brief  Flushes the write buffer.
     */
    void FlushWriteBuffer();
    
    /*!
     * @brief  Prepares the write buffer.
     * 
     * @return <b>[>=1]</b>  The number of bytes that can be copied into the write buffer.
     */
    int32 PrepareWriteBuffer();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<BufferDataStreamBase> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x7CD3F4A5;
    
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
      if ((ptr = DataStreamBase::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } 

#endif
