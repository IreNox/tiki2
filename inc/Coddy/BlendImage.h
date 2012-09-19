////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_IMAGING_BLENDIMAGE_H
#define CLODDY_API_IMAGING_BLENDIMAGE_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/CompositeImage.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Imaging { class IImage; } } }
namespace Cloddy { namespace API { namespace Imaging { class IImageReader; } } }
namespace Cloddy { namespace API { namespace Imaging { class IImageVisitor; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Imaging { class ImageInfo; } } }

// Declare class ::Cloddy::API::Imaging::BlendImage.

namespace Cloddy { namespace API { namespace Imaging
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  An Imaging Object Model node that blends the samples of two input images using a third 
   *         blend factor image.
   */
  class BlendImage : public CompositeImage
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The blend factor image.
     * 
     * This image will be converted to 8-bit grayscale and the resulting pixel intensities will be 
     * used as scale factors for blending between the first and second image:
     * <pre>
     *       finalPixel := (firstPixel * (255 - factor) + secondPixel * factor) / 255
     * </pre>
     * where \c finalPixel  is the pixel of the blended image,\c firstPixel  is the pixel from the 
     * first input image,\c secondPixel  is the pixel from the second input image and \c factor  is 
     * the grayscale intensity value of the pixel from the blend factor image.
     * 
     * The blend factor image will be resized to match the dimensions of the first input image (
     * see #GetFirst).
     * 
     * @return <b>[not-null]</b>  The blend factor image.
     */
    Ptr<IImage> GetAlpha();
    
    /*!
     * @brief  The blend factor image.
     * 
     * This image will be converted to 8-bit grayscale and the resulting pixel intensities will be 
     * used as scale factors for blending between the first and second image:
     * <pre>
     *       finalPixel := (firstPixel * (255 - factor) + secondPixel * factor) / 255
     * </pre>
     * where \c finalPixel  is the pixel of the blended image,\c firstPixel  is the pixel from the 
     * first input image,\c secondPixel  is the pixel from the second input image and \c factor  is 
     * the grayscale intensity value of the pixel from the blend factor image.
     * 
     * The blend factor image will be resized to match the dimensions of the first input image (
     * see #GetFirst).
     * 
     * @param value <b>[not-null]</b>  The blend factor image.
     */
    void SetAlpha(IImage* value);
    
    /*!
     * @brief  The first input image.
     * 
     * @return <b>[not-null]</b>  The first input image.
     */
    Ptr<IImage> GetFirst();
    
    /*!
     * @brief  The first input image.
     * 
     * @param value <b>[not-null]</b>  The first input image.
     */
    void SetFirst(IImage* value);
    
    /*!
     * @brief  The second input image.
     * 
     * The second input image will be resized and converted to match the dimensions and pixel 
     * format of the first input image (see #GetFirst).
     * 
     * @return <b>[not-null]</b>  The second input image.
     */
    Ptr<IImage> GetSecond();
    
    /*!
     * @brief  The second input image.
     * 
     * The second input image will be resized and converted to match the dimensions and pixel 
     * format of the first input image (see #GetFirst).
     * 
     * @param value <b>[not-null]</b>  The second input image.
     */
    void SetSecond(IImage* value);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of BlendImage.
     */
    BlendImage();
    
    /*!
     * @brief  Creates a new instance of BlendImage.
     * 
     * @param first <b>[not-null]</b>  The first input image (see #GetFirst).
     * @param second <b>[not-null]</b>  The second input image (see #GetSecond).
     * @param alpha <b>[not-null]</b>  The blend factor image (see #GetAlpha).
     */
    BlendImage(IImage* first, IImage* second, IImage* alpha);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void Accept(IImageVisitor* visitor, Object* userData);
    
    virtual void Validate();
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Attributes
    // ---------------------------------------------------------------------------------------------
  protected:
    
    virtual int32 GetSourceImageCount();
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual Ptr<IImageReader> DoReadImage();
    
    virtual Ptr<ImageInfo> DoReadImageInfo();
    
    virtual Ptr<IImage> GetSourceImageAt(int32 index);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The blend factor image.
     * 
     * The blend factor image is read as an PixelFormat::PixelFormat_Grayscale8 image and each 
     * pixel is interpreted as the blend factor used for blending between the first and second 
     * input image.
     */
    Ptr<IImage> alpha;
    
    /*!
     * @brief  The first input image.
     */
    Ptr<IImage> first;
    
    /*!
     * @brief  The second input image.
     */
    Ptr<IImage> second;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<BlendImage> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x5610CE74;
    
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
      if ((ptr = CompositeImage::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
