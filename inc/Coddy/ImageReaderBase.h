////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_IMAGING_IMAGEREADERBASE_H
#define CLODDY_API_IMAGING_IMAGEREADERBASE_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/PixelCoverage.h"
#include "Cloddy/PixelFormat.h"

// Include referenced interfaces.

#include "Cloddy/IImageReader.h"

// Include referenced classes.

#include "CodeX/Disposable.h"

// Forward declare referenced classes.

namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::API::Imaging::ImageReaderBase.

namespace Cloddy { namespace API { namespace Imaging
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced classes.
  
  using CodeX::System::ByteBuffer;
  using CodeX::System::Disposable;
  
  /*!
   * @brief  Abstract base class for IImageReader implementations.
   */
  class ImageReaderBase : public Disposable, public virtual IImageReader
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual int32 GetBytesPerPixel();
    
    virtual bool CanNormalize();
    
    virtual bool HasFinished();
    
    virtual int32 GetHeight();
    
    virtual PixelFormat GetPixelFormat();
    
    virtual int32 GetScanlineLength();
    
    virtual int32 GetScanlineY();
    
    virtual void* GetUserData();
    
    virtual void SetUserData(void* value);
    
    virtual int32 GetWidth();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual Ptr<IImageReader> Blend(IImageReader* image, IImageReader* alpha);
    
    virtual Ptr<IImageReader> Clamp(int32 minimum, int32 maximum);
    
    virtual Ptr<IImageReader> Clip(int32 x, int32 y, int32 width, int32 height);
    
    virtual Ptr<IImageReader> Convert(PixelFormat pixelFormat);
    
    virtual Ptr<IImageReader> Normalize(float32 min, float32 max, float32 noData);
    
    virtual Ptr<IImageReader> Pad(int32 padWidth);
    
    virtual int32 ReadScanline(ByteBuffer* scanline);
    
    virtual Ptr<IImageReader> Scale(int32 width, int32 height);
    
    virtual void SkipScanlines(int32 count);
    
    virtual Ptr<IImageReader> Smooth(int32 strength);
    
    virtual Ptr<IImageReader> ToPixelCoverage(PixelCoverage source, PixelCoverage target);
    
    virtual Ptr<IImageReader> ToPixelCoverage(PixelCoverage source, PixelCoverage target, bool wrapX);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Attributes
    // ---------------------------------------------------------------------------------------------
  protected:
    
    /*!
     * @brief  Height of the processed image.
     * 
     * The value of this field must not be set explicitly.It will be initialized when 
     * the #InitImageReader method is called.
     */
    int32 height;
    
    /*!
     * @brief  Pixel format of the processed image.
     * 
     * The value of this field must not be set explicitly.It will be initialized when 
     * the #InitImageReader method is called.
     */
    PixelFormat pixelFormat;
    
    /*!
     * @brief  Width of the processed image.
     * 
     * The value of this field must not be set explicitly.It will be initialized when 
     * the #InitImageReader method is called.
     */
    int32 width;
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of ImageReaderBase.
     */
    ImageReaderBase();
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Processes the given scanline.
     * 
     * @param scanlineY Y-coordinate of the processed scanline.
     * @param scanline Data buffer that holds the scanline bytes.
     */
    virtual void DoReadScanline(int32 scanlineY, ByteBuffer* scanline) = 0;
    
    /*!
     * @brief  Performs implementation specific actions for skipping scanlines.
     * 
     * The value of #GetScanlineY is updated by this class after the #DoSkipScanlines returns.
     * 
     * @param count The number of scanlines to skip (will always be greater than zero).
     */
    virtual void DoSkipScanlines(int32 count) = 0;
    
    /*!
     * @brief  Initializes the ImageReaderBase.
     * 
     * This method must be called once during initialization.
     * 
     * @param width <b>[>0]</b>  Image width,in pixels.
     * @param height <b>[>0]</b>  Image height,in pixels.
     * @param pixelFormat Pixel format.
     */
    void InitImageReader(int32 width, int32 height, PixelFormat pixelFormat);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Length of a single image scanline,in bytes.
     */
    int32 scanlineLength;
    
    /*!
     * @brief  Y-coordinate of current image scanline.
     */
    int32 scanlineY;
    
    /*!
     * @brief  The current user data object.
     */
    void* userData;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Asserts that this ImageReaderBase object has not yet been initialized.
     */
    void AssertNotInitialized();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<ImageReaderBase> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xEAFFEF7D;
    
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
      if ((ptr = Disposable::TryCast(typeId)) != 0) return ptr;
      if ((ptr = IImageReader::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
