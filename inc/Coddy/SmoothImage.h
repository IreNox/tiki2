////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_IMAGING_SMOOTHIMAGE_H
#define CLODDY_API_IMAGING_SMOOTHIMAGE_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/CompositeImageOne.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Imaging { class IImage; } } }
namespace Cloddy { namespace API { namespace Imaging { class IImageReader; } } }
namespace Cloddy { namespace API { namespace Imaging { class IImageVisitor; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Imaging { class ImageInfo; } } }

// Declare class ::Cloddy::API::Imaging::SmoothImage.

namespace Cloddy { namespace API { namespace Imaging
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  An Imaging Object Model node that can be used to smooth an input image while 
   *         preserving edges and contours.
   * 
   * Image smoothing is useful for removing high frequency noise from DEM data and satellite 
   * imagery.
   */
  class SmoothImage : public CompositeImageOne
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The strength of the smoothing effect.
     * 
     * The default value is \c 3 .
     * 
     * @return <b>[1..10]</b>  The strength of the smoothing effect.
     */
    int32 GetStrength();
    
    /*!
     * @brief  The strength of the smoothing effect.
     * 
     * The default value is \c 3 .
     * 
     * @param value <b>[1..10]</b>  The strength of the smoothing effect.
     */
    void SetStrength(int32 value);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of SmoothImage.
     */
    SmoothImage();
    
    /*!
     * @brief  Creates a new instance of SmoothImage.
     * 
     * @param sourceImage <b>[not-null]</b>  The source image.
     * @param strength <b>[1..10]</b>  The strength of the smoothing effect.
     */
    SmoothImage(IImage* sourceImage, int32 strength);
    
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
     * @brief  The overall strength of the smoothing effect.
     */
    int32 strength;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<SmoothImage> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x9505A94B;
    
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
