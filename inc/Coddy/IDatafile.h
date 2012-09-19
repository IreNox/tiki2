////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_DATAFILES_IDATAFILE_H
#define CLODDY_API_DATAFILES_IDATAFILE_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IBeginEnd.h"
#include "Cloddy/IDataStreamFactory.h"
#include "CodeX/IDisposable.h"
#include "Cloddy/IFlushable.h"
#include "Cloddy/IIoStatsProvider.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Collections { template<class> class ISetConst; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace IO { namespace Files { class Path; } } } }
namespace CodeX { namespace System { class ByteBuffer; } }

// Declare interface ::Cloddy::API::Datafiles::IDatafile.

namespace Cloddy { namespace API { namespace Datafiles
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Util::IBeginEnd;
  using Cloddy::Core::Collections::ISetConst;
  using Cloddy::Core::IO::IFlushable;
  using Cloddy::Core::IO::Streams::IDataStreamFactory;
  using CodeX::System::IDisposable;
  
  // Use referenced classes.
  
  using Cloddy::Core::IO::Files::Path;
  using CodeX::System::ByteBuffer;
  
  /*!
   * @brief  Base interface for classes that represent datafiles.
   * 
   * In the context of the CloddySDK,a datafile is simply a binary large object (BLOB).
   */
  class NO_VTABLE IDatafile : public virtual IFlushable, public virtual IBeginEnd, public virtual IIoStatsProvider, public virtual IDataStreamFactory, public virtual IDisposable
  {
    // ---------------------------------------------------------------------------------------------
    // Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Returns the path to the file in the local filesystem.
     * 
     * @return <b>[not-null]</b>  The file path.
     */
    virtual Ptr<Path> GetFilePath() = 0;
    
    /*!
     * @brief  Is this datafile read only?
     * 
     * @return \c true  if this datafile supports read access only,\c false  if not.
     */
    virtual bool IsReadOnly() = 0;
    
    /*!
     * @brief  The length of this datafile.
     * 
     * A datafile can be shrunk or grown by simply setting the length to the desired value.
     * 
     * @return <b>[>=0]</b>  The length of this datafile,in bytes.
     */
    virtual int64 GetLength() = 0;
    
    /*!
     * @brief  The length of this datafile.
     * 
     * A datafile can be shrunk or grown by simply setting the length to the desired value.
     * 
     * @param value <b>[>=0]</b>  The length of this datafile,in bytes.
     */
    virtual void SetLength(int64 value) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Preloads a byte sequence of the datafile.
     * 
     * @param offset <b>[>=0]</b>  Offset of the byte sequence to preload.
     * @param count <b>[>=0]</b>  The size of the byte sequence.
     */
    virtual void PreLoad(int64 offset, int32 count) = 0;
    
    /*!
     * @brief  Preloads a series of byte sequences from the datafile.
     * 
     * @param offsets <b>[not-null]</b>  The offsets of the first byte of each byte sequence to 
     * read.
     * @param count <b>[>=0]</b>  The size of each byte sequence,in bytes.
     */
    virtual void PreLoad(ISetConst<Prm<int64> >* offsets, int32 count) = 0;
    
    /*!
     * @brief  Reads a sequence of bytes from the datafile.
     * 
     * <i>Note:</i>
     * The returned ByteBuffer object is managed by this IDatafile instance,so the application must 
     * not dispose it.
     * 
     * @param offset <b>[>=0]</b>  The offset of the first byte to read.
     * @param bytes <b>[0..#GetLength-offset]</b>  The number of bytes to read.
     * 
     * @return <b>[not-null]</b>  A ByteBuffer object that contains the read bytes.
     */
    virtual Ptr<ByteBuffer> Read(int64 offset, int32 bytes) = 0;
    
    /*!
     * @brief  Writes a sequence of bytes to the datafile.
     * 
     * The returned ByteBuffer object is managed by this IDatafile instance,so the application must 
     * not dispose it.
     * 
     * @param offset <b>[>=0]</b>  The offset of the first byte to write.
     * @param bytes <b>[>=0]</b>  The number of bytes to write.
     * 
     * @return <b>[not-null]</b>  A ByteBuffer object where the bytes to write shall be stored.
     */
    virtual Ptr<ByteBuffer> Write(int64 offset, int32 bytes) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IDatafile> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xF292620C;
    
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
      if ((ptr = IBeginEnd::TryCast(typeId)) != 0) return ptr;
      if ((ptr = IIoStatsProvider::TryCast(typeId)) != 0) return ptr;
      if ((ptr = IDataStreamFactory::TryCast(typeId)) != 0) return ptr;
      if ((ptr = IDisposable::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
} } } 

#endif
