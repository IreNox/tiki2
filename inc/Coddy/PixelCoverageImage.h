////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_IMAGING_PIXELCOVERAGEIMAGE_H
#define CLODDY_API_IMAGING_PIXELCOVERAGEIMAGE_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/PixelCoverage.h"

// Include referenced classes.

#include "Cloddy/CompositeImageOne.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Imaging { class IImage; } } }
namespace Cloddy { namespace API { namespace Imaging { class IImageReader; } } }
namespace Cloddy { namespace API { namespace Imaging { class IImageVisitor; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Imaging { class ImageInfo; } } }

// Declare class ::Cloddy::API::Imaging::PixelCoverageImage.

namespace Cloddy { namespace API { namespace Imaging
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  An Imaging Object Model node that can be used to convert an input image between pixel 
   *         coverage semantics (ie. pixel is point vs.pixel is area).
   * 
   * When converting an image from area to point pixel coverage,the #GetWrapX property can be set 
   * if the input images wraps around the X-axis (which is typically the case for plate caree 
   * projected DEM data and satellite imagery).The leftmost and rightmost columns of the resulting 
   * pixel coverage image will then be equal (since W180 ^=E180).
   */
  class PixelCoverageImage : public CompositeImageOne
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The pixel coverage of the source image.
     * 
     * The default value is PixelCoverage::PixelCoverage_PixelIsArea.
     * 
     * @return The pixel coverage semantic.
     */
    PixelCoverage GetSourcePixelCoverage();
    
    /*!
     * @brief  The pixel coverage of the source image.
     * 
     * The default value is PixelCoverage::PixelCoverage_PixelIsArea.
     * 
     * @param value The pixel coverage semantic.
     */
    void SetSourcePixelCoverage(PixelCoverage value);
    
    /*!
     * @brief  The pixel coverage of the generated image.
     * 
     * The default value is PixelCoverage::PixelCoverage_PixelIsArea.
     * 
     * @return The pixel coverage semantic.
     */
    PixelCoverage GetTargetPixelCoverage();
    
    /*!
     * @brief  The pixel coverage of the generated image.
     * 
     * The default value is PixelCoverage::PixelCoverage_PixelIsArea.
     * 
     * @param value The pixel coverage semantic.
     */
    void SetTargetPixelCoverage(PixelCoverage value);
    
    /*!
     * @brief  Does the input image wrap around the X-axis?
     * 
     * The default value is \c false .
     * 
     * @return \c true  if the input image is wrapped,\c false  if not.
     */
    bool GetWrapX();
    
    /*!
     * @brief  Does the input image wrap around the X-axis?
     * 
     * The default value is \c false .
     * 
     * @param value \c true  if the input image is wrapped,\c false  if not.
     */
    void SetWrapX(bool value);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of PixelCoverageImage.
     */
    PixelCoverageImage();
    
    /*!
     * @brief  Creates a new instance of PixelCoverageImage.
     * 
     * @param sourceImage <b>[not-null]</b>  The source image.
     * @param sourcePixelCoverage The pixel coverage of the source image.
     * @param targetPixelCoverage The pixel coverage of the generated image.
     */
    PixelCoverageImage(IImage* sourceImage, PixelCoverage sourcePixelCoverage, PixelCoverage targetPixelCoverage);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
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
     * @brief  The pixel coverage of the source image.
     */
    PixelCoverage sourcePixelCoverage;
    
    /*!
     * @brief  The pixel coverage of the generated image.
     */
    PixelCoverage targetPixelCoverage;
    
    /*!
     * @brief  Does the input image wrap around the X-axis?
     */
    bool wrapX;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<PixelCoverageImage> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x17AE12BB;
    
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
      if ((ptr = CompositeImageOne::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
