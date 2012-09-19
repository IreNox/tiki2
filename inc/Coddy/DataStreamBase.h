////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_IO_STREAMS_DATASTREAMBASE_H
#define CLODDY_CORE_IO_STREAMS_DATASTREAMBASE_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "CodeX/ByteOrder.h"

// Include referenced interfaces.

#include "Cloddy/IDataStream.h"

// Include referenced classes.

#include "CodeX/Disposable.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Collections { template<class> class IList; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace IO { namespace Files { class Path; } } } }
namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::Core::IO::Streams::DataStreamBase.

namespace Cloddy { namespace Core { namespace IO { namespace Streams
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  using namespace CodeX::System;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::Collections::IList;
  
  // Use referenced classes.
  
  using Cloddy::Core::IO::Files::Path;
  
  /*!
   * @brief  Abstract implementation of the IDataStream interface.
   */
  class DataStreamBase : public Disposable, public virtual IDataStream
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual bool CanRead() = 0;
    
    virtual bool CanSeek() = 0;
    
    virtual bool CanWrite() = 0;
    
    virtual ByteOrder GetEndianess();
    
    virtual void SetEndianess(ByteOrder value);
    
    virtual Ptr<Path> GetFilePath() = 0;
    
    virtual int64 GetLength() = 0;
    
    virtual int64 GetPosition() = 0;
    
    virtual void SetPosition(int64 value) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual Ptr<IDataStream> Buffer(int32 bufferSize);
    
    virtual void Flush() = 0;
    
    virtual void PopPosition();
    
    virtual void Preload(int32 n);
    
    virtual void PushPosition();
    
    virtual void Read(IDataStream* stream);
    
    virtual int64 Read(ByteBuffer* bytes) = 0;
    
    virtual float32 ReadFloat32();
    
    virtual float64 ReadFloat64();
    
    virtual int16 ReadInt16();
    
    virtual int32 ReadInt32();
    
    virtual int64 ReadInt64();
    
    virtual int8 ReadInt8() = 0;
    
    virtual int32 ReadUInt16();
    
    virtual int64 ReadUInt32();
    
    virtual int32 ReadUInt8();
    
    virtual void Skip(int64 count);
    
    virtual void Write(IDataStream* stream);
    
    virtual void Write(ByteBuffer* bytes) = 0;
    
    virtual void WriteFloat32(float32 value);
    
    virtual void WriteFloat64(float64 value);
    
    virtual void WriteInt16(int16 value);
    
    virtual void WriteInt32(int32 value);
    
    virtual void WriteInt64(int64 value);
    
    virtual void WriteInt8(int8 value) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Constructors
    // ---------------------------------------------------------------------------------------------
  protected:
    
    /*!
     * @brief  Creates a new instance of DataStreamBase.
     */
    DataStreamBase();
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Asserts that this stream supports reading.
     * 
     * @see #CanRead
     */
    void AssertCanRead();
    
    /*!
     * @brief  Asserts that this stream supports seeking.
     * 
     * @see #CanSeek
     */
    void AssertCanSeek();
    
    /*!
     * @brief  Asserts that this stream supports writing.
     * 
     * @see #CanWrite
     */
    void AssertCanWrite();
    
    virtual void DisposeManaged();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The byte-order to use for reading and writing multibyte values.
     */
    ByteOrder endianess;
    
    /*!
     * @brief  The stack of file cursor positions.
     */
    Ptr<IList<Prm<int64> > > stack;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Asserts that the stream position stack is not empty.
     */
    void AssertStackNotEmpty();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<DataStreamBase> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xB0ABEE69;
    
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
      if ((ptr = Disposable::TryCast(typeId)) != 0) return ptr;
      if ((ptr = IDataStream::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } 

#endif
