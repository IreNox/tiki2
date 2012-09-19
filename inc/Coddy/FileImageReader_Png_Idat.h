////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_IMAGING_FILEIMAGEREADER_PNG_IDAT_H
#define CLODDY_API_IMAGING_FILEIMAGEREADER_PNG_IDAT_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/DataStreamBase.h"

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Imaging { class FileImageReader_Png; } } }
namespace Cloddy { namespace API { namespace Imaging { class FileImageReader_Png_Crc; } } }
namespace Cloddy { namespace Core { namespace IO { namespace Files { class Path; } } } }
namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::API::Imaging::FileImageReader_Png_Idat.

namespace Cloddy { namespace API { namespace Imaging
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced classes.
  
  using Cloddy::Core::IO::Files::Path;
  using Cloddy::Core::IO::Streams::DataStreamBase;
  using CodeX::System::ByteBuffer;
  
  /*!
   * @brief  An IDataStream that reads the image data contained in the IDAT chunks of a PNG image.
   */
  class FileImageReader_Png_Idat : public DataStreamBase
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
     * @brief  Processing the first IDAT chunk?
     */
    bool checkCrc;
    
    /*!
     * @brief  Current position in IDAT stream.
     */
    int64 position;
    
    /*!
     * @brief  Remaining bytes of the current IDAT chunk.
     */
    int64 remainingIdatBytes;
    
    /*!
     * @brief  The FileImageReader_Png_Crc used for computing CRC values on IDAT chunk data.
     */
    Ptr<FileImageReader_Png_Crc> stream;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of this class.
     * 
     * @param stream The underlying PNG data stream;the stream must point to the beginning of a 
     * chunk (ie. the PNG signature must have been read already).
     */
    FileImageReader_Png_Idat(FileImageReader_Png_Crc* stream);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Scans the PNG data stream for the next IDAT chunk.
     * 
     * @return \c true  if another IDAT chunk is present in the PNG file,\c false  if not.
     */
    bool NextIdat();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<FileImageReader_Png_Idat> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x88E641EB;
    
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
