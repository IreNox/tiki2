////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_DATASETS_COMPRESSION_ICOMPRESSIONCODEC_H
#define CLODDY_API_DATASETS_COMPRESSION_ICOMPRESSIONCODEC_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "CodeX/IDisposable.h"

// Forward declare referenced classes.

namespace CodeX { namespace System { class ByteBuffer; } }

// Declare interface ::Cloddy::API::Datasets::Compression::ICompressionCodec.

namespace Cloddy { namespace API { namespace Datasets { namespace Compression
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using CodeX::System::IDisposable;
  
  // Use referenced classes.
  
  using CodeX::System::ByteBuffer;
  
  /*!
   * @brief  Base interface for classes that implement a compression codec for dataset blocks.
   * 
   * A dataset block is a 2D grid of samples,with its width and height being a power of two.A 
   * dataset sample can have one or more 8-bit channels.
   */
  class NO_VTABLE ICompressionCodec : public virtual IDisposable
  {
    // ---------------------------------------------------------------------------------------------
    // Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The dataset block size.
     * 
     * @return <b>[pow2]</b>  The dataset block size (both width and height).
     */
    virtual int32 GetBlockSize() = 0;
    
    /*!
     * @brief  The number of channels per dataset sample.
     * 
     * @return <b>[>1]</b>  The number of dataset samples.
     */
    virtual int32 GetChannels() = 0;
    
    /*!
     * @brief  Is this compression codec lossy (\c true )or lossless (\c false )?
     * 
     * @return \c true  if this codec performs lossy compression,\c false  it if performs lossless 
     * compression.
     */
    virtual bool IsLossy() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Decodes a sample block.
     * 
     * @param input Byte buffer for compressed input sample block.
     * @param output Byte buffer for uncompressed output sample block.
     */
    virtual void Decode(ByteBuffer* input, ByteBuffer* output) = 0;
    
    /*!
     * @brief  Encodes a sample block.
     * 
     * @param input Byte buffer for uncompressed input sample block.
     * @param output Byte buffer for compressed output sample block.
     * 
     * @return <b>[>0]</b>  The number of bytes that have been written to \e output .
     */
    virtual int32 Encode(ByteBuffer* input, ByteBuffer* output) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<ICompressionCodec> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xD2A35D20;
    
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
      return (void*) 0;
    }
  };
} } } } 

#endif
