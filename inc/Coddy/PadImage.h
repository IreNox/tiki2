////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_IMAGING_PADIMAGE_H
#define CLODDY_API_IMAGING_PADIMAGE_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/CompositeImageOne.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Imaging { class IImage; } } }
namespace Cloddy { namespace API { namespace Imaging { class IImageReader; } } }
namespace Cloddy { namespace API { namespace Imaging { class IImageVisitor; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Imaging { class ImageInfo; } } }

// Declare class ::Cloddy::API::Imaging::PadImage.

namespace Cloddy { namespace API { namespace Imaging
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  An Imaging Object Model node that can be used to pad an input image by duplicating its 
   *         border pixels.
   * 
   * For example,an input image...
   * <pre>
   *      +---+---+---+---+
   *      | 0 | 1 | 2 | 3 |
   *      +---+---+---+---+   width  := 4
   *      | 4 | 5 | 6 | 7 |   height := 3
   *      +---+---+---+---+
   *      | 8 | 9 | A | B |
   *      +---+---+---+---+
   * </pre>
   * ...will be padded to (assuming a pad width of one):
   * <pre>
   *      +---+---+---+---+---+---+
   *      | 0 | 0 | 1 | 2 | 3 | 3 |
   *      +---+---+---+---+---+---+
   *      | 0 | 0 | 1 | 2 | 3 | 3 |
   *      +---+---+---+---+---+---+   width  := 6
   *      | 4 | 4 | 5 | 6 | 7 | 7 |   height := 5
   *      +---+---+---+---+---+---+
   *      | 8 | 8 | 9 | A | B | B |
   *      +---+---+---+---+---+---+
   *      | 8 | 8 | 9 | A | B | B |
   *      +---+---+---+---+---+---+
   * </pre>
   * 
   * Padding is necessary for scaling certain DEM products (eg. SRTM or ASTER GDEM)while keeping 
   * the georeferencing properties intact.The ASTER GDEM product for example provides one pixel for 
   * each arc-second latitude/longitude pair on a near-global scale.The resolution is thus:
   * <pre>
   *      resolution = 1px/?
   *      width  = (W180?0'0'' - E180?0'0'' + 1) / resolution = 1.296.001px
   *      height = (S90?0'0''  - N90?0'0''  + 1) / resolution =   648.000px
   * </pre>
   * Downscaling can then be performed by padding the global image using a pad width of one and 
   * scaling it by <c>1/3</c>.The resulting resolution will then be:
   *   -# 1.296.001 by 648.000
   *   -#  432.001 by 216.001
   *   -#  144.001 by 72.001
   *   -#  48.001 by 24.001
   *   -#  16.001 by 8.001
   */
  class PadImage : public CompositeImageOne
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Width of the padded region,in pixels.
     * 
     * @return <b>[>=0]</b>  The padded region width.
     */
    int32 GetPadWidth();
    
    /*!
     * @brief  Width of the padded region,in pixels.
     * 
     * @param value <b>[>=0]</b>  The padded region width.
     */
    void SetPadWidth(int32 value);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of PadImage.
     */
    PadImage();
    
    /*!
     * @brief  Creates a new instance of PadImage.
     * 
     * @param sourceImage <b>[not-null]</b>  The source image.
     * @param padWidth <b>[>=0]</b>  The pad width.
     */
    PadImage(IImage* sourceImage, int32 padWidth);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void Accept(IImageVisitor* visitor, Object* userData);
    
    virtual Ptr<IImage> Pad(int32 padWidth);
    
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
     * @brief  Width of the padded region,in pixels.
     */
    int32 padWidth;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<PadImage> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x43E4CF32;
    
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
