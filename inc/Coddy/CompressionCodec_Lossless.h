////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_DATASETS_COMPRESSION_COMPRESSIONCODEC_LOSSLESS_H
#define CLODDY_API_DATASETS_COMPRESSION_COMPRESSIONCODEC_LOSSLESS_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/CompressionCodec.h"

// Forward declare referenced classes.

namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::API::Datasets::Compression::CompressionCodec_Lossless.

namespace Cloddy { namespace API { namespace Datasets { namespace Compression
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced classes.
  
  using CodeX::System::ByteBuffer;
  
  /*!
   * @brief  This class implements the compression codec used by the compressed dataset formats.
   * 
   * The compression codec is a combination of a Paeth filter and a range compression algorithm.
   */
  class CompressionCodec_Lossless : public CompressionCodec
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual bool IsLossy();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new compression codec.
     * 
     * @param blockSize The block size,in bytes.Must be a power of two.
     * @param channels The number of dataset channels.
     */
    CompressionCodec_Lossless(int32 blockSize, int32 channels);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void Decode(ByteBuffer* input, ByteBuffer* output);
    
    virtual int32 Encode(ByteBuffer* input, ByteBuffer* output);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
  protected:
    
    virtual void DisposeManaged();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constants
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Lower boundary of the value interval used for range coding.
     */
    static const int64 Lower = ~(int64) 0xFFFFFFFFFFFFULL;
    
    /*!
     * @brief  Upper boundary of the value interval used for range coding.
     */
    static const int64 Upper = ~(int64) 0xFFFFFFFFFFFFFFULL;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Number of bytes in a block.
     */
    int32 blockBytes;
    
    /*!
     * @brief  Distance between two adjacent block rows,in bytes.
     */
    int32 blockStride;
    
    /*!
     * @brief  Intermediate buffer used during encoding.
     */
    Array<int8> buffer;
    
    /*!
     * @brief  Accumulated symbol frequencies.
     */
    Array<int32> freq;
    
    /*!
     * @brief  Address offset for above Paeth sample.
     */
    int32 offsetAbove;
    
    /*!
     * @brief  Address offset for left Paeth sample.
     */
    int32 offsetLeft;
    
    /*!
     * @brief  Address offset for left above Paeth sample.
     */
    int32 offsetLeftAbove;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Implements the Paeth predictor function.
     * 
     * @param a Left
     * @param b Above
     * @param c Left-above
     * 
     * @return The predicted value.
     */
    static int32 Paeth(int32 a, int32 b, int32 c);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<CompressionCodec_Lossless> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x30A80A7C;
    
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
      if ((ptr = CompressionCodec::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } 

#endif
