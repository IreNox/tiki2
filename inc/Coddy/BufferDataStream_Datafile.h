////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_DATAFILES_BUFFERDATASTREAM_DATAFILE_H
#define CLODDY_API_DATAFILES_BUFFERDATASTREAM_DATAFILE_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/BufferDataStreamBase.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Datafiles { class IDatafile; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Datafiles { class DatafileBase; } } }
namespace Cloddy { namespace Core { namespace IO { namespace Files { class Path; } } } }
namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::API::Datafiles::BufferDataStream_Datafile.

namespace Cloddy { namespace API { namespace Datafiles
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced classes.
  
  using Cloddy::Core::IO::Files::Path;
  using Cloddy::Core::IO::Streams::BufferDataStreamBase;
  using CodeX::System::ByteBuffer;
  
  /*!
   * @brief  An implementation of the IDataStream interface that accesses the bytes in a IDatafile.
   */
  class BufferDataStream_Datafile : public BufferDataStreamBase
  {
    // Declare friend classes.
    
    friend class DatafileBase;
    
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
     * @brief  The wrapped datafile.
     */
    Ptr<IDatafile> datafile;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of BufferDataStream_Datafile.
     * 
     * @param datafile The datafile to read from.
     * @param bufferSize The buffer size.
     */
    BufferDataStream_Datafile(IDatafile* datafile, int32 bufferSize);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<BufferDataStream_Datafile> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x280B0368;
    
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
  
} } } 

#endif
