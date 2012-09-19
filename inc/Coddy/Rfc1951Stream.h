////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_IMAGING_DATAPROVIDERS_RFC1951STREAM_H
#define CLODDY_API_IMAGING_DATAPROVIDERS_RFC1951STREAM_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/DataStreamBase.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace IO { namespace Streams { class IDataStream; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace IO { namespace Files { class Path; } } } }
namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::API::Imaging::DataProviders::Rfc1951Stream.

namespace Cloddy { namespace API { namespace Imaging { namespace DataProviders
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
   * @brief  An input stream that decodes a compressed RFC-1951 data stream.
   */
  class Rfc1951Stream : public DataStreamBase
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
    
    virtual int64 GetPosition();
    
    virtual void SetPosition(int64 value);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of Rfc1951Stream.
     * 
     * @param stream The compressed input stream.
     * @param skipHeader Skip reading of the stream header bytes?
     * @param fileFormatName Name of the enclosing file format.
     */
    Rfc1951Stream(IDataStream* stream, bool skipHeader, String fileFormatName);
    
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
    // Private / Constants
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Size of input buffer,in bytes.
     */
    static const int32 InputBufferLength = 1024;
    
    /*!
     * @brief  Maximum code bit length.
     */
    static const int32 MaxBitLength = 15;
    
    /*!
     * @brief  Bitmask for computing modulo by window size.
     */
    static const int32 WindowMask = 65535;
    
    /*!
     * @brief  Size of the sliding window the decoder uses,in bytes.
     */
    static const int32 WindowSize = 65536;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Base distance per distance code.
     * 
     * <pre>
     *     Extra           Extra               Extra
     *     Code Bits Dist  Code Bits   Dist     Code Bits Distance
     *     ---- ---- ----  ---- ----  ------    ---- ---- --------
     *     0   0    1     10   4     33-48    20    9   1025-1536
     *     1   0    2     11   4     49-64    21    9   1537-2048
     *     2   0    3     12   5     65-96    22   10   2049-3072
     *     3   0    4     13   5     97-128   23   10   3073-4096
     *     4   1   5,6    14   6    129-192   24   11   4097-6144
     *     5   1   7,8    15   6    193-256   25   11   6145-8192
     *     6   2   9-12   16   7    257-384   26   12  8193-12288
     *     7   2  13-16   17   7    385-512   27   12 12289-16384
     *     8   3  17-24   18   8    513-768   28   13 16385-24576
     *     9   3  25-32   19   8   769-1024   29   13 24577-32768
     * </pre>
     */
    static const Array<int32> BaseDistancePerDistanceCode;
    
    /*!
     * @brief  Base length per length code.
     * 
     * <pre>
     *    Extra               Extra               Extra
     *    Code Bits Length(s) Code Bits Lengths   Code Bits Length(s)
     *    ---- ---- ------     ---- ---- -------   ---- ---- -------
     *    257   0     3       267   1   15,16     277   4   67-82
     *    258   0     4       268   1   17,18     278   4   83-98
     *    259   0     5       269   2   19-22     279   4   99-114
     *    260   0     6       270   2   23-26     280   4  115-130
     *    261   0     7       271   2   27-30     281   5  131-162
     *    262   0     8       272   2   31-34     282   5  163-194
     *    263   0     9       273   3   35-42     283   5  195-226
     *    264   0    10       274   3   43-50     284   5  227-257
     *    265   1  11,12      275   3   51-58     285   0    258
     *    266   1  13,14      276   3   59-66
     * </pre>
     */
    static const Array<int32> BaseLengthPerLengthCode;
    
    /*!
     * @brief  The order in which code lengths are stored for block using dynamic codes.
     */
    static const Array<int32> CodeLengthOrder;
    
    /*!
     * @brief  Extra bits count for distance codes.
     * 
     * <pre>
     *     Extra           Extra               Extra
     *     Code Bits Dist  Code Bits   Dist     Code Bits Distance
     *     ---- ---- ----  ---- ----  ------    ---- ---- --------
     *     0   0    1     10   4     33-48    20    9   1025-1536
     *     1   0    2     11   4     49-64    21    9   1537-2048
     *     2   0    3     12   5     65-96    22   10   2049-3072
     *     3   0    4     13   5     97-128   23   10   3073-4096
     *     4   1   5,6    14   6    129-192   24   11   4097-6144
     *     5   1   7,8    15   6    193-256   25   11   6145-8192
     *     6   2   9-12   16   7    257-384   26   12  8193-12288
     *     7   2  13-16   17   7    385-512   27   12 12289-16384
     *     8   3  17-24   18   8    513-768   28   13 16385-24576
     *     9   3  25-32   19   8   769-1024   29   13 24577-32768
     * </pre>
     */
    static const Array<int32> ExtraBitsPerDistanceCode;
    
    /*!
     * @brief  Extra bits count per length code.
     * 
     * <pre>
     *    Extra               Extra               Extra
     *    Code Bits Length(s) Code Bits Lengths   Code Bits Length(s)
     *    ---- ---- ------     ---- ---- -------   ---- ---- -------
     *    257   0     3       267   1   15,16     277   4   67-82
     *    258   0     4       268   1   17,18     278   4   83-98
     *    259   0     5       269   2   19-22     279   4   99-114
     *    260   0     6       270   2   23-26     280   4  115-130
     *    261   0     7       271   2   27-30     281   5  131-162
     *    262   0     8       272   2   31-34     282   5  163-194
     *    263   0     9       273   3   35-42     283   5  195-226
     *    264   0    10       274   3   43-50     284   5  227-257
     *    265   1  11,12      275   3   51-58     285   0    258
     *    266   1  13,14      276   3   59-66
     * </pre>
     */
    static const Array<int32> ExtraBitsPerLengthCode;
    
    /*!
     * @brief  This array holds the length and distance tables for blocks using fixed Huffman codes.
     * 
     * The first 1536 entries represent the length table,the last 96 entries represent the distance 
     * table.
     */
    static const Array<int32> FixedHuffmanCodeTable;
    
    /*!
     * @brief  The bit buffer.
     */
    int32 bitBuffer;
    
    /*!
     * @brief  Number of valid bits in #bitBuffer.
     */
    int32 bitBufferCount;
    
    /*!
     * @brief  This is a preallocated temp array.It is used during the construction of Huffman 
     *         codes.
     */
    Array<int32> bitLengthCount;
    
    /*!
     * @brief  The bit length of each code.
     */
    Array<int32> bitLengths;
    
    /*!
     * @brief  This is a preallocated temp array.It is used during the construction of Huffman 
     *         codes.
     */
    Array<int32> bitOffsets;
    
    /*!
     * @brief  This is a preallocated temp array.It is used during the construction of Huffman 
     *         codes.
     */
    Array<int32> codeStack;
    
    /*!
     * @brief  The bit count of the current distance code table.
     */
    int32 currentDistanceBits;
    
    /*!
     * @brief  The current length and distance code table.
     */
    Array<int32> currentLengthAndDistanceTable;
    
    /*!
     * @brief  The bit count of the current length code table.
     */
    int32 currentLengthBits;
    
    /*!
     * @brief  Current offset of the distance table.
     */
    int32 currentTableOffset;
    
    /*!
     * @brief  Dynamic Huffman codes are generated into this array.
     */
    Array<int32> dynamicHuffmanCodeTable;
    
    /*!
     * @brief  Name of the file format.
     */
    String fileFormatName;
    
    /*!
     * @brief  Temporary working space for building Huffman codes.
     */
    Array<int32> huffmanCodesTemp;
    
    /*!
     * @brief  The current input buffer.
     */
    Ptr<ByteBuffer> inputBuffer;
    
    /*!
     * @brief  The stream that delivers the compressed data.
     */
    Ptr<IDataStream> inputStream;
    
    /*!
     * @brief  Is the current block the last one?
     */
    bool isLastBlock;
    
    /*!
     * @brief  The current output buffer.
     */
    Ptr<ByteBuffer> outputBuffer;
    
    /*!
     * @brief  The byte position in the stream of decoded data.
     */
    int64 position;
    
    /*!
     * @brief  The value of this variable indicates the current decoder state.
     * 
     * A value greater than \c 0  indicates the number of bytes that need to be copied from the 
     * decoder input to the decoder window.
     * 
     * A value of \c 0  indicates that compressed blocks need to be decoded.
     * 
     * A value of \c -1  indicates that a new block must be read or the end of stream has been 
     * reached.
     */
    int32 state;
    
    /*!
     * @brief  Temporary working space for building Huffman codes.
     */
    Array<int32> tableStack;
    
    /*!
     * @brief  An output buffer of size one.
     */
    Ptr<ByteBuffer> tinyOutputBuffer;
    
    /*!
     * @brief  The decoder window.
     */
    Array<int8> window;
    
    /*!
     * @brief  Current read index in decoder window.
     */
    int32 windowReadIdx;
    
    /*!
     * @brief  Number of readable bytes in the decoder window.
     */
    int32 windowReadable;
    
    /*!
     * @brief  Current write index in decoder window.
     */
    int32 windowWriteIdx;
    
    /*!
     * @brief  Number of writeable bytes in the decoder window.
     */
    int32 windowWriteable;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Begins to decode a block that uses dynamic Huffman codes.
     */
    void BeginDynamicBlock();
    
    /*!
     * @brief  Begins to decode a block that uses fixed Huffman codes.
     */
    void BeginFixedBlock();
    
    /*!
     * @brief  Begins to process a stored block.
     */
    void BeginStoredBlock();
    
    /*!
     * @brief  Builds a Huffman tree table from the bit lengths in the #bitLengths array.
     * 
     * @param bitLengthsOffset Offset into #bitLengths to the bit length of the first Huffman code.
     * @param codeCount The number of Huffman codes to build.
     * @param literalCodeCount The number of literal Huffman codes.
     * @param codeBaseValues Optional base values per Huffman code.
     * @param codeExtraBits Optional extra bit counts per Huffman code.
     * @param bitsPerTable The proposed number of bits per table.
     * 
     * @return The actual number of bits per table.
     */
    int32 BuildHuffmanTree(int32 bitLengthsOffset, int32 codeCount, int32 literalCodeCount, Array<int32> codeBaseValues, Array<int32> codeExtraBits, int32 bitsPerTable);
    
    /*!
     * @brief  Copies bytes from the decoder input into the window.
     * 
     * @param count The maximum number of bytes to copy.
     * 
     * @return The actual number of copied bytes.
     */
    int32 CopyInputToWindow(int32 count);
    
    /*!
     * @brief  Fully reads the given number of bytes from the input buffer and stores them in the 
     *         provided buffer.
     * 
     * @param offset Offset into window.
     * @param count Total number of bytes to read.
     */
    void CopyInputToWindow(int32 offset, int32 count);
    
    /*!
     * @brief  Writes a single byte into the window.
     * 
     * @param value The byte to write.
     */
    void CopyValueToWindow(int8 value);
    
    /*!
     * @brief  Copies the readable bytes in the window to the output buffer.
     * 
     * @return \c true  if all bytes in the window have been copied,\c false  if not.
     */
    bool CopyWindowToOutput();
    
    /*!
     * @brief  Copies bytes from a previous window position into the window.
     * 
     * @param count The maximum number of bytes to copy.
     * @param distance The distance from the previous window position to the current position,in 
     * bytes.
     */
    void CopyWindowToWindow(int32 count, int32 distance);
    
    /*!
     * @brief  Decodes the current block.
     * 
     * @return \c true  if the block has been fully decoded,\c false  if not.
     */
    bool DecodeBlock();
    
    /*!
     * @brief  Fills the bit buffer until it holds at least the given number of bits.
     * 
     * @param bitCount The minimum bit count.
     */
    void FillBitBuffer(int32 bitCount);
    
    /*!
     * @brief  Fills the input buffer,if necessary.
     */
    void FillInputBuffer();
    
    /*!
     * @brief  Pads the count of the maximum code length.
     * 
     * @param minCodeLength The minimum code length.
     * @param maxCodeLength The maximum code length.
     */
    void PadLastCodeLength(int32 minCodeLength, int32 maxCodeLength);
    
    /*!
     * @brief  Reads the next \e n  bits from the input buffer.
     * 
     * @param n The number of bits to read.
     * 
     * @return The read bits.
     */
    int32 ReadBits(int32 n);
    
    /*!
     * @brief  Discards all bits until the next byte boundary and returns the next 32 bits from the 
     *         input buffer.
     * 
     * @return The read bits.
     */
    int32 ReadBits32();
    
    /*!
     * @brief  Returns the next byte from the input stream.
     * 
     * @return The next byte from the input stream.
     */
    int32 ReadInput();
    
    /*!
     * @brief  Consumes and verifies the RFC-1951 stream header.
     */
    void ReadStreamHeader();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<Rfc1951Stream> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x82854181;
    
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
