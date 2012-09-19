////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_IMAGING_IIMAGE_H
#define CLODDY_API_IMAGING_IIMAGE_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IImageOp.h"
#include "Cloddy/ISerializable.h"
#include "Cloddy/IUserData.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Imaging { class IImageReader; } } }
namespace Cloddy { namespace API { namespace Imaging { class IImageVisitor; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Imaging { class ImageInfo; } } }

// Declare interface ::Cloddy::API::Imaging::IImage.

namespace Cloddy { namespace API { namespace Imaging
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::IO::Serialization::ISerializable;
  using Cloddy::Kernel::IUserData;
  
  /*!
   * @brief  The IImage interface is the basis of the Imaging Object Model.
   * 
   * The Imaging Object Model can be used to generate image data from a variety of different input 
   * sources using transformations.All transformations,conversions,etc. are performed on-the-fly 
   * while an image is being read,scanline after scanline.This allows efficient processing of 
   * extremely large images,since buffers and temporary storage space is only necessary for a 
   * couple of scanlines.
   */
  class NO_VTABLE IImage : public virtual IImageOp<Ref<IImage> >, public virtual IUserData, public virtual ISerializable
  {
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Accepts the given visitor object.
     * 
     * @param visitor <b>[not-null]</b>  The visitor object.
     */
    virtual void Accept(IImageVisitor* visitor) = 0;
    
    /*!
     * @brief  Accepts the given visitor object.
     * 
     * @param visitor <b>[not-null]</b>  The visitor object.
     * @param userData Optional user data to pass to the visitor object.
     */
    virtual void Accept(IImageVisitor* visitor, Object* userData) = 0;
    
    /*!
     * @brief  Creates an IImageReader object that reads the image data of this image.
     * 
     * The user data object set for this image descriptor (see IUserData::GetUserData)will be 
     * passed on to the created IImageReader.
     * 
     * @return <b>[not-null]</b>  The IImageReader object.
     * 
     * @exception CoreException If the image descriptor is incomplete.
     */
    virtual Ptr<IImageReader> ReadImage() = 0;
    
    /*!
     * @brief  Returns information about the image.
     * 
     * @return <b>[not-null]</b>  An ImageInfo object that holds information about the image.
     * 
     * @exception CoreException If the image descriptor is incomplete.
     */
    virtual Ptr<ImageInfo> ReadImageInfo() = 0;
    
    /*!
     * @brief  Validates this image descriptor.
     * 
     * @exception CoreException If the validation fails.
     */
    virtual void Validate() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IImage> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xCFA04B20;
    
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
      if ((ptr = IImageOp<Ref<IImage> >::TryCast(typeId)) != 0) return ptr;
      if ((ptr = IUserData::TryCast(typeId)) != 0) return ptr;
      if ((ptr = ISerializable::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
} } } 

#endif
