////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_IMAGING_CLAMPIMAGE_H
#define CLODDY_API_IMAGING_CLAMPIMAGE_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/CompositeImageOne.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Imaging { class IImage; } } }
namespace Cloddy { namespace API { namespace Imaging { class IImageReader; } } }
namespace Cloddy { namespace API { namespace Imaging { class IImageVisitor; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Imaging { class ImageInfo; } } }

// Declare class ::Cloddy::API::Imaging::ClampImage.

namespace Cloddy { namespace API { namespace Imaging
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  The ClampImage class is an image descriptor that clamps color channel values to a 
   *         given range.
   */
  class ClampImage : public CompositeImageOne
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The maximum color channel value,inclusive.
     * 
     * @return The maximum value.
     */
    int32 GetMaximum();
    
    /*!
     * @brief  The maximum color channel value,inclusive.
     * 
     * @param value The maximum value.
     */
    void SetMaximum(int32 value);
    
    /*!
     * @brief  The minimum color channel value,inclusive.
     * 
     * @return The minimum value.
     */
    int32 GetMinimum();
    
    /*!
     * @brief  The minimum color channel value,inclusive.
     * 
     * @param value The minimum value.
     */
    void SetMinimum(int32 value);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of ClampImage.
     */
    ClampImage();
    
    /*!
     * @brief  Creates a new instance of ClampImage.
     * 
     * @param sourceImage <b>[not-null]</b>  The source image.
     * @param minimum The minimum color channel value,inclusive.
     * @param maximum The maximum color channel value,inclusive.
     */
    ClampImage(IImage* sourceImage, int32 minimum, int32 maximum);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void Accept(IImageVisitor* visitor, Object* userData);
    
    virtual Ptr<IImage> Clamp(int32 minimum, int32 maximum);
    
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
     * @brief  The maximum color channel value,inclusive.
     */
    int32 maximum;
    
    /*!
     * @brief  The minimum color channel value,inclusive.
     */
    int32 minimum;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<ClampImage> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x66BE4F88;
    
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
