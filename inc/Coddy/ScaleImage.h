////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_IMAGING_SCALEIMAGE_H
#define CLODDY_API_IMAGING_SCALEIMAGE_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/CompositeImageOne.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Imaging { class IImage; } } }
namespace Cloddy { namespace API { namespace Imaging { class IImageReader; } } }
namespace Cloddy { namespace API { namespace Imaging { class IImageVisitor; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Imaging { class ImageInfo; } } }

// Declare class ::Cloddy::API::Imaging::ScaleImage.

namespace Cloddy { namespace API { namespace Imaging
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  An Imaging Object Model node that can be used to rescale another image on-the-fly.
   */
  class ScaleImage : public CompositeImageOne
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Height of scaled image,in pixels.
     * 
     * @return <b>[>0]</b>  Height of scaled image.
     */
    int32 GetHeight();
    
    /*!
     * @brief  Height of scaled image,in pixels.
     * 
     * @param value <b>[>0]</b>  Height of scaled image.
     */
    void SetHeight(int32 value);
    
    /*!
     * @brief  Width of scaled image,in pixels.
     * 
     * @return <b>[>0]</b>  Width of scaled image.
     */
    int32 GetWidth();
    
    /*!
     * @brief  Width of scaled image,in pixels.
     * 
     * @param value <b>[>0]</b>  Width of scaled image.
     */
    void SetWidth(int32 value);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of ScaleImage.
     */
    ScaleImage();
    
    /*!
     * @brief  Creates a new instance of ScaleImage.
     * 
     * @param sourceImage <b>[not-null]</b>  The source image.
     * @param width <b>[>0]</b>  Width of scaled image.
     * @param height <b>[>0]</b>  Height of scaled image.
     */
    ScaleImage(IImage* sourceImage, int32 width, int32 height);
    
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
     * @brief  Height of scaled image,in pixels.
     */
    int32 height;
    
    /*!
     * @brief  Width of scaled image,in pixels.
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
    public: typedef Ptr<ScaleImage> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xF64E6525;
    
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
