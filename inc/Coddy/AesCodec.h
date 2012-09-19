////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_DATASETS_COMPRESSION_AESCODEC_H
#define CLODDY_API_DATASETS_COMPRESSION_AESCODEC_H

#include "CodeX/System.h"

// Forward declare referenced classes.

namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::API::Datasets::Compression::AesCodec.

namespace Cloddy { namespace API { namespace Datasets { namespace Compression
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced classes.
  
  using CodeX::System::ByteBuffer;
  
  class AesCodec : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    void Initialize(Array<int8> keyData, bool encrypt);
    
    void ProcessBlock(ByteBuffer* input, ByteBuffer* output);
    
    void ProcessBlock(Array<int8> input, int32 inputOffset, Array<int8> output, int32 outputOffset);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    static const Array<int16> R;
    
    static const Array<int16> S;
    
    static const Array<int16> SInv;
    
    static const Array<int32> T0;
    
    static const Array<int32> T0Inv;
    
    static const Array<int32> T1;
    
    static const Array<int32> T1Inv;
    
    static const Array<int32> T2;
    
    static const Array<int32> T2Inv;
    
    static const Array<int32> T3;
    
    static const Array<int32> T3Inv;
    
    int32 c0;
    
    int32 c1;
    
    int32 c2;
    
    int32 c3;
    
    bool encrypt;
    
    Array<int32> k0;
    
    Array<int32> k1;
    
    Array<int32> k2;
    
    Array<int32> k3;
    
    int32 rounds;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    static void AssertValidKeyLength(int32 keyLength, int32 keyColumns);
    
    static int32 InvMixColumns(int32 v);
    
    static int32 Mul(int32 v);
    
    static int32 Shift16(int32 v);
    
    static int32 Shift24(int32 v);
    
    static int32 Shift8(int32 v);
    
    static int32 SubWord(int32 x);
    
    void DecryptBlock();
    
    void EncryptBlock();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
  public:
    
    AesCodec();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<AesCodec> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x84903B6A;
    
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
      return (void*) 0;
    }
  };
  
} } } } 

#endif
