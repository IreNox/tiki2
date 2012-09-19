////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_IMAGING_MEMORYIMAGE_H
#define CLODDY_API_IMAGING_MEMORYIMAGE_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/PixelFormat.h"

// Include referenced classes.

#include "Cloddy/ImageBase.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Imaging { class IImage; } } }
namespace Cloddy { namespace API { namespace Imaging { class IImageReader; } } }
namespace Cloddy { namespace API { namespace Imaging { class IImageVisitor; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Imaging { class ImageInfo; } } }
namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::API::Imaging::MemoryImage.

namespace Cloddy { namespace API { namespace Imaging
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced classes.
  
  using CodeX::System::ByteBuffer;
  
  /*!
   * @brief  An Imaging Object Model node that represents an in-memory image.
   * 
   * The pixels of a MemoryImage can be accessed directly 
   */
  class MemoryImage : public ImageBase
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The image height.
     * 
     * @return <b>[>0]</b>  The image height,in pixels.
     */
    int32 GetHeight();
    
    /*!
     * @brief  The pixel format of the image.
     * 
     * @return The image pixel format.
     */
    PixelFormat GetPixelFormat();
    
    /*!
     * @brief  The image pixels.
     * 
     * The returned ByteBuffer stores the image pixels in row-major order,with zero padding between 
     * scanlines.The scanline layout corresponds to the pixel format of the image (see PixelFormat).
     * 
     * @return <b>[not-null]</b>  The image pixels.
     */
    Ptr<ByteBuffer> GetPixels();
    
    /*!
     * @brief  Distance between consecutive scanlines,in bytes.
     * 
     * @return <b>[>0]</b>  The length of a single scanline,in bytes.
     */
    int32 GetStride();
    
    /*!
     * @brief  The image width.
     * 
     * @return <b>[>0]</b>  The image width,in pixels.
     */
    int32 GetWidth();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of MemoryImage.
     * 
     * @param width <b>[>0]</b>  Image width,in pixels.
     * @param height <b>[>0]</b>  Image height,in pixels.
     * @param pixelFormat The desired pixel format.
     */
    MemoryImage(int32 width, int32 height, PixelFormat pixelFormat);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Reads the given image into a memory image.
     * 
     * @param image <b>[not-null]</b>  The image to read.
     * 
     * @return <b>[not-null]</b>  The memory image.
     */
    static Ptr<MemoryImage> Read(IImage* image);
    
    /*!
     * @brief  Reads the given image into a memory image.
     * 
     * @param imageReader <b>[not-null]</b>  The image to read.
     * 
     * @return <b>[not-null]</b>  The memory image.
     */
    static Ptr<MemoryImage> Read(IImageReader* imageReader);
    
    virtual void Accept(IImageVisitor* visitor, Object* userData);
    
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
     * @brief  The image height.
     */
    int32 height;
    
    /*!
     * @brief  The pixel format of the image.
     */
    PixelFormat pixelFormat;
    
    /*!
     * @brief  The image pixels.
     */
    Ptr<ByteBuffer> pixels;
    
    /*!
     * @brief  Distance between consecutive scanlines,in bytes.
     */
    int32 stride;
    
    /*!
     * @brief  The image width.
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
    public: typedef Ptr<MemoryImage> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x800FB7C0;
    
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
      if ((ptr = ImageBase::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
