////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_IMAGING_IMAGEBASE_H
#define CLODDY_API_IMAGING_IMAGEBASE_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/PixelCoverage.h"
#include "Cloddy/PixelFormat.h"

// Include referenced interfaces.

#include "Cloddy/IImage.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Imaging { class IImageReader; } } }
namespace Cloddy { namespace API { namespace Imaging { class IImageVisitor; } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class ISerializable; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class ISerialTypeInfo; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Imaging { class ImageInfo; } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class Serializer; } } } }

// Declare class ::Cloddy::API::Imaging::ImageBase.

namespace Cloddy { namespace API { namespace Imaging
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::IO::Serialization::ISerializable;
  using Cloddy::Core::IO::Serialization::ISerialTypeInfo;
  
  // Use referenced classes.
  
  using Cloddy::Core::IO::Serialization::Serializer;
  
  /*!
   * @brief  Abstract base class for IImage implementations.
   */
  class ImageBase : public virtual IImage
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual bool CanNormalize();
    
    virtual Ptr<ISerialTypeInfo> GetSerialType();
    
    virtual int32 GetSerialVersion();
    
    virtual void* GetUserData();
    
    virtual void SetUserData(void* value);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void Accept(IImageVisitor* visitor, Object* userData) = 0;
    
    virtual void Accept(IImageVisitor* visitor);
    
    virtual Ptr<IImage> Blend(IImage* image, IImage* alpha);
    
    virtual Ptr<IImage> Clamp(int32 minimum, int32 maximum);
    
    virtual Ptr<IImage> Clip(int32 x, int32 y, int32 width, int32 height);
    
    virtual Ptr<IImage> Convert(PixelFormat pixelFormat);
    
    virtual Ptr<ISerializable> Deserialize(int32 serialVersion, Serializer* data);
    
    virtual Ptr<IImage> Normalize(float32 min, float32 max, float32 noData);
    
    virtual Ptr<IImage> Pad(int32 padWidth);
    
    virtual Ptr<IImageReader> ReadImage();
    
    virtual Ptr<ImageInfo> ReadImageInfo();
    
    virtual Ptr<IImage> Scale(int32 width, int32 height);
    
    virtual void Serialize(Serializer* data);
    
    virtual Ptr<IImage> Smooth(int32 strength);
    
    virtual Ptr<IImage> ToPixelCoverage(PixelCoverage source, PixelCoverage target);
    
    virtual Ptr<IImage> ToPixelCoverage(PixelCoverage source, PixelCoverage target, bool wrapX);
    
    virtual void Validate();
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Constructors
    // ---------------------------------------------------------------------------------------------
  protected:
    
    /*!
     * @brief  Creates a new instance of ImageBase.
     */
    ImageBase();
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Reads the image data.
     * 
     * This method is called after the #Validate method has been called.
     * 
     * @return <b>[not-null]</b>  The IImageReader object.
     */
    virtual Ptr<IImageReader> DoReadImage() = 0;
    
    /*!
     * @brief  Returns information about the image data.
     * 
     * This method is called after the #Validate method has been called.
     * 
     * @return <b>[not-null]</b>  The ImageInfo object.
     */
    virtual Ptr<ImageInfo> DoReadImageInfo() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The user data object.
     */
    void* userData;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<ImageBase> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x24111788;
    
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
      if ((ptr = IImage::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
