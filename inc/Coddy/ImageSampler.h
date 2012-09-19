////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_IMAGING_IMAGESAMPLER_H
#define CLODDY_API_IMAGING_IMAGESAMPLER_H

#include "CodeX/System.h"

// Include referenced classes.

#include "CodeX/Disposable.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Imaging { class IImage; } } }
namespace Cloddy { namespace API { namespace Imaging { class IImageReader; } } }

// Declare class ::Cloddy::API::Imaging::ImageSampler.

namespace Cloddy { namespace API { namespace Imaging
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced classes.
  
  using CodeX::System::Disposable;
  
  /*!
   * @brief  Base interface for classes that sample image data using some kind of interpolation.
   */
  class ImageSampler : public Disposable
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Creates a new instance of ImageSampler for the given image.
     * 
     * @param image <b>[not-null]</b>  The image.
     * 
     * @return <b>[not-null]</b>  The image sampler.
     */
    static Ptr<ImageSampler> For(IImage* image);
    
    /*!
     * @brief  Creates a new instance of ImageSampler for the given image.
     * 
     * @param reader <b>[not-null]</b>  The image.
     * 
     * @return <b>[not-null]</b>  The image sampler.
     */
    static Ptr<ImageSampler> For(IImageReader* reader);
    
    /*!
     * @brief  Samples a pixel from the image.
     * 
     * @param u X-coordinate of pixel to sample,in the range <c>[0..1]</c>.
     * @param v Y-coordinate of pixel to sample,in the range <c>[0..1]</c>.
     * 
     * @return The samples pixel value.
     */
    int32 SamplePixel(float64 u, float64 v);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
  protected:
    
    virtual void DisposeManaged();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    int32 height;
    
    Array<int32> pixels;
    
    int32 width;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    ImageSampler(Array<int32> pixels, int32 width, int32 height);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<ImageSampler> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xE9D74DA9;
    
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
      if ((ptr = Disposable::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
