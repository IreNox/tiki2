////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_IMAGING_CLIPIMAGE_H
#define CLODDY_API_IMAGING_CLIPIMAGE_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/CompositeImageOne.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Imaging { class IImage; } } }
namespace Cloddy { namespace API { namespace Imaging { class IImageReader; } } }
namespace Cloddy { namespace API { namespace Imaging { class IImageVisitor; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Imaging { class ImageInfo; } } }

// Declare class ::Cloddy::API::Imaging::ClipImage.

namespace Cloddy { namespace API { namespace Imaging
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  The ClipImage class is an image descriptor that represents a subregion of a given 
   *         source image.
   */
  class ClipImage : public CompositeImageOne
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Height of clip rectangle.
     * 
     * @return <b>[>0]</b>  Height of the clip rectangle,in pixels.
     */
    int32 GetHeight();
    
    /*!
     * @brief  Height of clip rectangle.
     * 
     * @param value <b>[>0]</b>  Height of the clip rectangle,in pixels.
     */
    void SetHeight(int32 value);
    
    /*!
     * @brief  Width of clip rectangle.
     * 
     * @return <b>[>0]</b>  Width of the clip rectangle,in pixels.
     */
    int32 GetWidth();
    
    /*!
     * @brief  Width of clip rectangle.
     * 
     * @param value <b>[>0]</b>  Width of the clip rectangle,in pixels.
     */
    void SetWidth(int32 value);
    
    /*!
     * @brief  X-coordinate of top-left corner of clip rectangle.
     * 
     * @return <b>[>=0]</b>  X-coordinate of top-left corner.
     */
    int32 GetX();
    
    /*!
     * @brief  X-coordinate of top-left corner of clip rectangle.
     * 
     * @param value <b>[>=0]</b>  X-coordinate of top-left corner.
     */
    void SetX(int32 value);
    
    /*!
     * @brief  Y-coordinate of top-left corner of clip rectangle.
     * 
     * @return <b>[>=0]</b>  Y-coordinate of top-left corner.
     */
    int32 GetY();
    
    /*!
     * @brief  Y-coordinate of top-left corner of clip rectangle.
     * 
     * @param value <b>[>=0]</b>  Y-coordinate of top-left corner.
     */
    void SetY(int32 value);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of ClipImage.
     */
    ClipImage();
    
    /*!
     * @brief  Creates a new instance of ClipImage.
     * 
     * @param sourceImage <b>[not-null]</b>  The source image.
     * @param x <b>[>=0]</b>  X-coordinate of top-left corner of clip rectangle.
     * @param y <b>[>=0]</b>  Y-coordinate of top-left corner of clip rectangle.
     * @param width <b>[>0]</b>  Width of clip rectangle.
     * @param height <b>[>0]</b>  Height of clip rectangle.
     */
    ClipImage(IImage* sourceImage, int32 x, int32 y, int32 width, int32 height);
    
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
     * @brief  Height of clip rectangle.
     */
    int32 height;
    
    /*!
     * @brief  Width of clip rectangle.
     */
    int32 width;
    
    /*!
     * @brief  X-coordinate of top-left corner of clip rectangle.
     */
    int32 x;
    
    /*!
     * @brief  Y-coordinate of top-left corner of clip rectangle.
     */
    int32 y;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<ClipImage> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x5309F92F;
    
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
