////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_IMAGING_RAWIMAGE_H
#define CLODDY_API_IMAGING_RAWIMAGE_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/RawSampleFormat.h"

// Include referenced classes.

#include "Cloddy/FileBasedImage.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Imaging { class IImageReader; } } }
namespace Cloddy { namespace API { namespace Imaging { class IImageVisitor; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Imaging { class ImageInfo; } } }

// Declare class ::Cloddy::API::Imaging::RawImage.

namespace Cloddy { namespace API { namespace Imaging
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  An Imaging Object Model node that describes the data layout for image data that is 
   *         stored as raw data in a file in the local filesystem.
   */
  class RawImage : public FileBasedImage
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual bool CanNormalize();
    
    /*!
     * @brief  File offset into the file depicted by FileBasedImage::GetFilePath to the first byte 
     *         of the raw image data.
     * 
     * The default value is \c 0 .
     * 
     * @return <b>[>=0]</b>  The file offset,in bytes.
     */
    int64 GetFileOffset();
    
    /*!
     * @brief  File offset into the file depicted by FileBasedImage::GetFilePath to the first byte 
     *         of the raw image data.
     * 
     * The default value is \c 0 .
     * 
     * @param value <b>[>=0]</b>  The file offset,in bytes.
     */
    void SetFileOffset(int64 value);
    
    /*!
     * @brief  Height of raw image.
     * 
     * @return <b>[>0]</b>  The image height,in pixels.
     */
    int32 GetHeight();
    
    /*!
     * @brief  Height of raw image.
     * 
     * @param value <b>[>0]</b>  The image height,in pixels.
     */
    void SetHeight(int32 value);
    
    /*!
     * @brief  Data format of the pixel samples.
     * 
     * @return The RawSampleFormat.
     */
    RawSampleFormat GetSampleFormat();
    
    /*!
     * @brief  Data format of the pixel samples.
     * 
     * @param value The RawSampleFormat.
     */
    void SetSampleFormat(RawSampleFormat value);
    
    /*!
     * @brief  Number of samples per pixel.
     * 
     * The default value is \c 1 .
     * 
     * @return <b>[>0]</b>  The number of samples per pixel.
     */
    int32 GetSamplesPerPixel();
    
    /*!
     * @brief  Number of samples per pixel.
     * 
     * The default value is \c 1 .
     * 
     * @param value <b>[>0]</b>  The number of samples per pixel.
     */
    void SetSamplesPerPixel(int32 value);
    
    /*!
     * @brief  Distance between adjacent scanlines,in bytes.
     * 
     * The default value is \c 0 .
     * 
     * When set to \c 0 ,the stride will be computed as follows:
     * <pre>
     *       stride := width * samplesPerPixel * bitsPerSample / 8
     * </pre>
     * 
     * @return <b>[>=0]</b>  The scanline stride,in bytes.
     */
    int32 GetScanlineStride();
    
    /*!
     * @brief  Distance between adjacent scanlines,in bytes.
     * 
     * The default value is \c 0 .
     * 
     * When set to \c 0 ,the stride will be computed as follows:
     * <pre>
     *       stride := width * samplesPerPixel * bitsPerSample / 8
     * </pre>
     * 
     * @param value <b>[>=0]</b>  The scanline stride,in bytes.
     */
    void SetScanlineStride(int32 value);
    
    /*!
     * @brief  Width of raw image.
     * 
     * @return <b>[>0]</b>  The image width,in pixels.
     */
    int32 GetWidth();
    
    /*!
     * @brief  Width of raw image.
     * 
     * @param value <b>[>0]</b>  The image width,in pixels.
     */
    void SetWidth(int32 value);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of RawImage.
     */
    RawImage();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void Accept(IImageVisitor* visitor, Object* userData);
    
    virtual void Validate();
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
  protected:
    
    virtual Ptr<IImageReader> DoReadImage();
    
    virtual Ptr<ImageInfo> DoReadImageInfo();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  File offset into the file depicted by FileBasedImage::GetFilePath to the first byte 
     *         of the raw image data.
     */
    int64 fileOffset;
    
    /*!
     * @brief  Number of pixels per row.
     */
    int32 height;
    
    /*!
     * @brief  Data format of the pixel samples.
     */
    RawSampleFormat sampleFormat;
    
    /*!
     * @brief  Number of samples per pixel.
     */
    int32 samplesPerPixel;
    
    /*!
     * @brief  Distance between adjacent scanlines,in bytes.
     */
    int32 scanlineStride;
    
    /*!
     * @brief  Number of pixels per column.
     */
    int32 width;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<RawImage> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x798F4D7D;
    
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
      if ((ptr = FileBasedImage::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
