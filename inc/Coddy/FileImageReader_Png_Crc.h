////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_IMAGING_FILEIMAGEREADER_PNG_CRC_H
#define CLODDY_API_IMAGING_FILEIMAGEREADER_PNG_CRC_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/DataStreamBase.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace IO { namespace Streams { class IDataStream; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Imaging { class FileImageReader_Png; } } }
namespace Cloddy { namespace Core { namespace IO { namespace Files { class Path; } } } }
namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::API::Imaging::FileImageReader_Png_Crc.

namespace Cloddy { namespace API { namespace Imaging
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::IO::Streams::IDataStream;
  
  // Use referenced classes.
  
  using Cloddy::Core::IO::Files::Path;
  using Cloddy::Core::IO::Streams::DataStreamBase;
  using CodeX::System::ByteBuffer;
  
  /*!
   * @brief  A delegating IDataStream implementation that computes a running CRC value while 
   *         reading /writing bytes.
   * 
   * The default endianess of a FileImageReader_Png_Crc is ByteOrder::ByteOrder_BigEndian.
   */
  class FileImageReader_Png_Crc : public DataStreamBase
  {
    // Declare friend classes.
    
    friend class FileImageReader_Png;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual bool CanRead();
    
    virtual bool CanSeek();
    
    virtual bool CanWrite();
    
    virtual Ptr<Path> GetFilePath();
    
    virtual int64 GetLength();
    
    virtual int64 GetPosition();
    
    virtual void SetPosition(int64 value);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Begins to compute a running CRC value for all future bytes being read or written.
     */
    void BeginCrc();
    
    /*!
     * @brief  Ends the current running CRC.
     * 
     * @return The CRC value.
     */
    int32 EndCrc();
    
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
    
    /*!
     * @brief  The precomputed CRC table.
     */
    static const Array<int32> CrcTable;
    
    /*!
     * @brief  The current running CRC value.
     */
    int32 crc;
    
    /*!
     * @brief  Is a running CRC value being computed?
     */
    bool runningCrc;
    
    /*!
     * @brief  The underlying IDataStream object.
     */
    Ptr<IDataStream> stream;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new big-endian reader.
     * 
     * @param stream The I/O stream to read from.
     */
    FileImageReader_Png_Crc(IDataStream* stream);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Updates the given running CRC value.
     * 
     * @param crc The running CRC value.
     * @param buffer The data to use for updating the CRC.
     * @param count Number of bytes of \e buffer  to include in CRC.
     * 
     * @return The updated CRC value.
     */
    static int32 UpdateCrc(int32 crc, ByteBuffer* buffer, int64 count);
    
    /*!
     * @brief  Updates the given running CRC value.
     * 
     * @param crc The running CRC value.
     * @param b The value to use for updating the CRC.
     * 
     * @return The updated CRC value.
     */
    static int32 UpdateCrc(int32 crc, int8 b);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<FileImageReader_Png_Crc> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x4034A141;
    
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
  
} } } 

#endif
