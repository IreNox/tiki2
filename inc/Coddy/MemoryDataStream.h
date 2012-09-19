////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_IO_STREAMS_MEMORYDATASTREAM_H
#define CLODDY_CORE_IO_STREAMS_MEMORYDATASTREAM_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/DataStreamBase.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace IO { namespace Streams { class IDataStream; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace IO { namespace Files { class Path; } } } }
namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::Core::IO::Streams::MemoryDataStream.

namespace Cloddy { namespace Core { namespace IO { namespace Streams
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced classes.
  
  using Cloddy::Core::IO::Files::Path;
  using CodeX::System::ByteBuffer;
  
  /*!
   * @brief  An implementation of the IDataStream that uses a growing memory buffer.
   */
  class MemoryDataStream : public DataStreamBase
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual bool CanRead();
    
    virtual bool CanSeek();
    
    virtual bool CanWrite();
    
    virtual Ptr<Path> GetFilePath();
    
    virtual int64 GetLength();
    
    /*!
     * @brief  The memory buffer of this stream.
     * 
     * @return <b>[not-null]</b>  The memory buffer.
     */
    Ptr<ByteBuffer> GetMemoryBuffer();
    
    virtual int64 GetPosition();
    
    virtual void SetPosition(int64 value);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of MemoryDataStream.
     */
    MemoryDataStream();
    
    /*!
     * @brief  Creates a new instance of MemoryDataStream.
     * 
     * @param initialBufferSize <b>[>0]</b>  The initial buffer size,in bytes.
     */
    MemoryDataStream(int64 initialBufferSize);
    
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
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
  protected:
    
    virtual void DisposeManaged();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    static const StaticPtr<Path> MyPath;
    
    /*!
     * @brief  The memory buffer.
     */
    Ptr<ByteBuffer> buffer;
    
    /*!
     * @brief  The file path name used by this memory stream.
     */
    Ptr<Path> filePath;
    
    /*!
     * @brief  The current memory stream length,in bytes.
     */
    int64 length;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Checks the capacity of the memory buffer and grows it if necessary.
     * 
     * @param required The minimum required buffer capacity.
     */
    void Grow(int64 required);
    
    // ---------------------------------------------------------------------------------------------
    // Static Initializer Functions
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Static initializer function for field MyPath.
     */
    static Object* StaticInitializer_MyPath();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<MemoryDataStream> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x681D31A5;
    
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
