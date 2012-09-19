////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_IMAGING_FILEIMAGEREADER_PNG_H
#define CLODDY_API_IMAGING_FILEIMAGEREADER_PNG_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/ImageReaderBase.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace IO { namespace Streams { class IDataStream; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Imaging { class FileImage; } } }
namespace Cloddy { namespace API { namespace Imaging { class FileImageReader_Png_Crc; } } }
namespace Cloddy { namespace API { namespace Imaging { class FileImageReader_Png_Idat; } } }
namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::API::Imaging::FileImageReader_Png.

namespace Cloddy { namespace API { namespace Imaging
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::IO::Streams::IDataStream;
  
  // Use referenced classes.
  
  using CodeX::System::ByteBuffer;
  
  /*!
   * @brief  Reads a subset of PNG files.
   */
  class FileImageReader_Png : public ImageReaderBase
  {
    // Declare friend classes.
    
    friend class FileImage;
    friend class FileImageReader_Png_Idat;
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
  protected:
    
    virtual void DisposeManaged();
    
    virtual void DoReadScanline(int32 scanlineY, ByteBuffer* scanline);
    
    virtual void DoSkipScanlines(int32 count);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constants
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Chunk ID for 'IDAT'.
     */
    static const int32 IDAT = 0x49444154;
    
    /*!
     * @brief  Chunk ID for 'IEND'.
     */
    static const int32 IEND = 0x49454E44;
    
    /*!
     * @brief  Chunk ID for 'IHDR'.
     */
    static const int32 IHDR = 0x49484452;
    
    /*!
     * @brief  Magic number that identifies a PNG file.
     */
    static const int64 Magic = (int64) -8552249625308161526LL;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Number of bytes in a single scanline.
     */
    int32 bytesInScanline;
    
    /*!
     * @brief  Number of bytes per pixel.
     */
    int32 bytesPerPixel;
    
    /*!
     * @brief  The stream used to decompress image data.
     */
    Ptr<IDataStream> deflateStream;
    
    /*!
     * @brief  The last scanline.
     */
    Ptr<ByteBuffer> lastScanline;
    
    /*!
     * @brief  The PNG data stream.
     */
    Ptr<FileImageReader_Png_Crc> stream;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of this class.
     * 
     * @param imageFile The input PNG image file.
     */
    FileImageReader_Png(IDataStream* imageFile);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Implements the paeth predictor function.
     * 
     * @param a Left
     * @param b Above
     * @param c Left-above
     * 
     * @return The predicted value.
     */
    static int8 Paeth(int8 a, int8 b, int8 c);
    
    /*!
     * @brief  Creates the IDAT data stream for reading image data,if necessary.
     */
    void CreateIdatStream();
    
    /*!
     * @brief  Reads the IHDR chunk of a PNG file.
     * 
     * This method sets the #bytesPerPixel field and calls the ImageReaderBase::InitImageReader 
     * method.
     */
    void ReadIHDR();
    
    /*!
     * @brief  Unfilters the given scanline in-place.
     * 
     * @param filter The filter type byte.
     * @param scanline The filtered scanline.
     */
    void UnfilterScanlineBytes(int8 filter, ByteBuffer* scanline);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<FileImageReader_Png> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x1BB1DACC;
    
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
      if ((ptr = ImageReaderBase::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
