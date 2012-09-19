////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_IMAGING_CONSTANTIMAGE_H
#define CLODDY_API_IMAGING_CONSTANTIMAGE_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/PixelFormat.h"

// Include referenced classes.

#include "Cloddy/ImageBase.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Imaging { class IImageReader; } } }
namespace Cloddy { namespace API { namespace Imaging { class IImageVisitor; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Imaging { class ImageInfo; } } }

// Declare class ::Cloddy::API::Imaging::ConstantImage.

namespace Cloddy { namespace API { namespace Imaging
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  An image descriptor for images that are uniformly filled with a specified color.
   */
  class ConstantImage : public ImageBase
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual bool CanNormalize();
    
    /*!
     * @brief  The constant color of the image.
     * 
     * @return The constant color,as a 32-bit ARGB color value.
     */
    int32 GetColor();
    
    /*!
     * @brief  The constant color of the image.
     * 
     * @param value The constant color,as a 32-bit ARGB color value.
     */
    void SetColor(int32 value);
    
    /*!
     * @brief  Height of the constant image.
     * 
     * @return <b>[>0]</b>  Height of image,in pixels.
     */
    int32 GetHeight();
    
    /*!
     * @brief  Height of the constant image.
     * 
     * @param value <b>[>0]</b>  Height of image,in pixels.
     */
    void SetHeight(int32 value);
    
    /*!
     * @brief  The pixel format of the constant image.
     * 
     * @return The pixel format.
     */
    PixelFormat GetPixelFormat();
    
    /*!
     * @brief  The pixel format of the constant image.
     * 
     * @param value The pixel format.
     */
    void SetPixelFormat(PixelFormat value);
    
    /*!
     * @brief  Width of the constant image.
     * 
     * @return <b>[>0]</b>  Width of image,in pixels.
     */
    int32 GetWidth();
    
    /*!
     * @brief  Width of the constant image.
     * 
     * @param value <b>[>0]</b>  Width of image,in pixels.
     */
    void SetWidth(int32 value);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of ConstantImage.
     */
    ConstantImage();
    
    /*!
     * @brief  Creates a new instance of ConstantImage.
     * 
     * @param width <b>[>0]</b>  Width of the image.
     * @param height <b>[>0]</b>  Height of the image.
     * @param color The constant color of the image.
     * @param pixelFormat the pixel format of the image.
     */
    ConstantImage(int32 width, int32 height, int32 color, PixelFormat pixelFormat);
    
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
     * @brief  The constant color of the image.
     */
    int32 color;
    
    /*!
     * @brief  Height of the constant image.
     */
    int32 height;
    
    /*!
     * @brief  The pixel format of the constant image.
     */
    PixelFormat pixelFormat;
    
    /*!
     * @brief  Width of the constant image.
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
    public: typedef Ptr<ConstantImage> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x34CF61CB;
    
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
