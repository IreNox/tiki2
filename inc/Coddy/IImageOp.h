////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_IMAGING_IIMAGEOP_H
#define CLODDY_API_IMAGING_IIMAGEOP_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/PixelCoverage.h"
#include "Cloddy/PixelFormat.h"

// Declare interface ::Cloddy::API::Imaging::IImageOp.

namespace Cloddy { namespace API { namespace Imaging
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Base interface that declares image operations that can be performed on IImage 
   *         and IImageReader objects.
   * 
   * Image operations can be performed on IImage objects and IImageReader object.
   */
  template<class T>
  class NO_VTABLE IImageOp : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Does this image support sample value normalization via #Normalize?
     * 
     * @return \c true  if this image reader supports normalization,\c false  if not.
     */
    virtual bool CanNormalize() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Blends this image with the given one,using the third image as the alpha channel.
     * 
     * The \e alpha  will be converted to 8-bit grayscale and the resulting pixel intensities will 
     * be used as scale factors for blending between this and the given image:
     * <pre>
     *       finalPixel := (this * (255 - alpha) + image * alpha) / 255
     * </pre>
     * where \c finalPixel  is the pixel of the blend image,\c this  is the pixel from this image,
     * \c image  is the pixel from the given image and \c alpha  is the grayscale intensity value 
     * of the pixel from the alpha image.
     * 
     * @param image <b>[not-null]</b>  The image to blend with.
     * @param alpha <b>[not-null]</b>  The image to use as the alpha channel.
     * 
     * @return <b>[not-null]</b>  The resulting image.
     */
    virtual typename T::Out Blend(typename T::In image, typename T::In alpha) = 0;
    
    /*!
     * @brief  Clamps the color channel values of this image to the given range.
     * 
     * Clamping will be performed after normalization,if set.
     * 
     * The user object of this image (see IUserData::GetUserData)will be set for the returned image 
     * as well.
     * 
     * @param minimum Minimum color channel value,inclusive.
     * @param maximum Maximum color channel value,exclusive.
     * 
     * @return <b>[not-null]</b>  The resulting image.
     */
    virtual typename T::Out Clamp(int32 minimum, int32 maximum) = 0;
    
    /*!
     * @brief  Returns an image that represents a sub rectangle of this image.
     * 
     * The user object of this image (see IUserData::GetUserData)will be set for the returned image 
     * as well.
     * 
     * @param x <b>[>=0]</b>  X-coordinate of top-left corner of rectangle.
     * @param y <b>[>=0]</b>  Y-coordinate of top-left corner of rectangle.
     * @param width <b>[>0]</b>  Width of rectangle.
     * @param height <b>[>0]</b>  Height of rectangle.
     * 
     * @return <b>[not-null]</b>  The resulting image.
     */
    virtual typename T::Out Clip(int32 x, int32 y, int32 width, int32 height) = 0;
    
    /*!
     * @brief  Returns an image that represents this image in a different pixel format.
     * 
     * Truecolor pixels are converted to grayscale pixels using the following formula:
     * <pre>
     *       intensity := (30 * red + 59 * green + 11 * blue + 50) / 100
     * </pre>
     * 
     * The user object of this image descriptor (see IUserData::GetUserData)will be set for the 
     * returned image descriptor as well.
     * 
     * @param pixelFormat The pixel format of the converted image.
     * 
     * @return <b>[not-null]</b>  The resulting image.
     */
    virtual typename T::Out Convert(PixelFormat pixelFormat) = 0;
    
    /*!
     * @brief  Sets the normalization range for this image.
     * 
     * An image file stores pixels,which consist of one or more samples.This method is used to 
     * translate the values of the samples of a pixel to a different value range.This is usually 
     * done when normalising heightmaps (ie. elevation data).
     * 
     * Depending on the image format,the value range of a pixels sample can be 8-bits,16-bits or 
     * 32-bits wide;the sample format can be an unsigned integer,a singed integer or a 
     * floating-point value.
     * 
     * The Imaging API supports only those image files that have a uniform sample bit-depth and 
     * sample format.Image files that specify different bit-depth and/or sample formats for the red,
     * green,blue and alpha channels cannot be read.This does not apply to grayscale images,since 
     * these contains only a single channel.
     * 
     * When reading image data via the IImageReader interface,pixel channel values are returned 
     * either as 8-bit or 16-bit unsigned integers.This method can be used to configure the mapping 
     * from pixel sample value to pixel channel value.The default mapping is done using the 
     * following sample value ranges:
     * <pre>
     *       sample    | channel   |               | default     | default
     *       bit-depth | bit-depth | sample format | min value   | max value
     *       ----------+-----------+---------------+-------------+-----------
     *       8-bit     | 8-bit     | unsigned int  | 0           | 255
     *       16-bit    | 16-bit    | unsigned int  | 0           | 65535
     *       8-bit     | 8-bit     | signed int    | -128        | 127
     *       16-bit    | 16-bit    | signed int    | -32768      | 32767
     *       32-bit    | 16-bit    | float         | -10000      | 10000
     *       sample bit-depth  := Bit-depth of the pixel sample values (as found in image file)
     *       channel bit-depth := Bit-depth of the pixel channel values (as returned by image reader)
     * </pre>
     * 
     * The user object of this image descriptor (see IUserData::GetUserData)will be set for the 
     * returned image descriptor as well.
     * 
     * @param min Minimum sample value.
     * @param max Maximum sample value.
     * @param noData The pixel sample value that represents missing data (will be set to zero 
     * elevation).
     * 
     * @return <b>[not-null]</b>  The resulting image.
     */
    virtual typename T::Out Normalize(float32 min, float32 max, float32 noData) = 0;
    
    /*!
     * @brief  Enlarges this images by duplicating its border pixels.
     * 
     * @param padWidth <b>[>=0]</b>  Size of the padded region,in pixels.
     * 
     * @return <b>[not-null]</b>  The resulting image.
     */
    virtual typename T::Out Pad(int32 padWidth) = 0;
    
    /*!
     * @brief  Transforms this image from the given pixel coverage semantic to the given one.
     * 
     * The user object of this image (see IUserData::GetUserData)will be set for the returned image 
     * as well.
     * 
     * @param source The pixel coverage semantic of this image.
     * @param target The pixel coverage semantic of the resulting image.
     * 
     * @return <b>[not-null]</b>  The resulting image.
     */
    virtual typename T::Out ToPixelCoverage(PixelCoverage source, PixelCoverage target) = 0;
    
    /*!
     * @brief  Transforms this image from the given pixel coverage semantic to the given one.
     * 
     * The user object of this image (see IUserData::GetUserData)will be set for the returned image 
     * as well.
     * 
     * @param source The pixel coverage semantic of this image.
     * @param target The pixel coverage semantic of the resulting image.
     * @param wrapX Is this image wrapped around the X-axis?
     * 
     * @return <b>[not-null]</b>  The resulting image.
     */
    virtual typename T::Out ToPixelCoverage(PixelCoverage source, PixelCoverage target, bool wrapX) = 0;
    
    /*!
     * @brief  Returns an image that represents a scaled version of this image.
     * 
     * The user object of this image descriptor (see IUserData::GetUserData)will be set for the 
     * returned image descriptor as well.
     * 
     * @param width <b>[>0]</b>  Width of the scaled image.
     * @param height <b>[>0]</b>  Height of the scaled image.
     * 
     * @return <b>[not-null]</b>  The resulting image.
     */
    virtual typename T::Out Scale(int32 width, int32 height) = 0;
    
    /*!
     * @brief  Applies a bilateral smoothing filter to this image.
     * 
     * The user object of this image descriptor (see IUserData::GetUserData)will be set for the 
     * returned image descriptor as well.
     * 
     * @param strength <b>[0..10]</b>  The strength of the smoothing effect (\c 0  :=no smoothing,
     * \c 10  :=maximum smoothing).
     * 
     * @return <b>[not-null]</b>  The IImage object.
     */
    virtual typename T::Out Smooth(int32 strength) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IImageOp<T> > ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xE5B7007B;
    
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
} } } 

#endif
