////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_IMAGING_COMPOSITEIMAGEONE_H
#define CLODDY_API_IMAGING_COMPOSITEIMAGEONE_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/CompositeImage.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Imaging { class IImage; } } }

// Declare class ::Cloddy::API::Imaging::CompositeImageOne.

namespace Cloddy { namespace API { namespace Imaging
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Abstract base class for IImage implementations that read a single source image and 
   *         perform image operations on it.
   */
  class CompositeImageOne : public CompositeImage
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The source image.
     * 
     * @return <b>[not-null]</b>  The source image.
     */
    Ptr<IImage> GetSourceImage();
    
    /*!
     * @brief  The source image.
     * 
     * @param value <b>[not-null]</b>  The source image.
     */
    void SetSourceImage(IImage* value);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void Validate();
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Attributes
    // ---------------------------------------------------------------------------------------------
  protected:
    
    virtual int32 GetSourceImageCount();
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of CompositeImageOne.
     */
    CompositeImageOne();
    
    /*!
     * @brief  Creates a new instance of CompositeImageOne.
     * 
     * @param sourceImage <b>[not-null]</b>  The source image.
     */
    CompositeImageOne(IImage* sourceImage);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual Ptr<IImage> GetSourceImageAt(int32 index);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The source image.
     */
    Ptr<IImage> sourceImage;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<CompositeImageOne> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x18AB2E5C;
    
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
