////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_IMAGING_NORMALIZEIMAGE_H
#define CLODDY_API_IMAGING_NORMALIZEIMAGE_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/CompositeImageOne.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Imaging { class IImage; } } }
namespace Cloddy { namespace API { namespace Imaging { class IImageReader; } } }
namespace Cloddy { namespace API { namespace Imaging { class IImageVisitor; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Imaging { class ImageInfo; } } }

// Declare class ::Cloddy::API::Imaging::NormalizeImage.

namespace Cloddy { namespace API { namespace Imaging
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  An Imaging Object Model node that can be used to normalized the range of sample values 
   *         of an input image.
   */
  class NormalizeImage : public CompositeImageOne
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Upper pixel sample value bound.
     * 
     * @return The upper value bound to use for normalization.
     */
    float32 GetMaximum();
    
    /*!
     * @brief  Upper pixel sample value bound.
     * 
     * @param value The upper value bound to use for normalization.
     */
    void SetMaximum(float32 value);
    
    /*!
     * @brief  Lower pixel sample value bound.
     * 
     * @return The lower value bound to use for normalization.
     */
    float32 GetMinimum();
    
    /*!
     * @brief  Lower pixel sample value bound.
     * 
     * @param value The lower value bound to use for normalization.
     */
    void SetMinimum(float32 value);
    
    /*!
     * @brief  The elevation value that represents no data (will be set to zero elevation).
     * 
     * @return The special no data elevation value.
     */
    float32 GetNoData();
    
    /*!
     * @brief  The elevation value that represents no data (will be set to zero elevation).
     * 
     * @param value The special no data elevation value.
     */
    void SetNoData(float32 value);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of NormalizeImage.
     */
    NormalizeImage();
    
    /*!
     * @brief  Creates a new instance of NormalizeImage.
     * 
     * @param sourceImage <b>[not-null]</b>  The source image.
     * @param min Lower value bound for normalization.
     * @param max Upper value bound for normalization.
     */
    NormalizeImage(IImage* sourceImage, float32 min, float32 max);
    
    /*!
     * @brief  Creates a new instance of NormalizeImage.
     * 
     * @param sourceImage <b>[not-null]</b>  The source image.
     * @param min Lower value bound for normalization.
     * @param max Upper value bound for normalization.
     * @param noData The pixel sample value that represents missing data (will be set to zero 
     * elevation).
     */
    NormalizeImage(IImage* sourceImage, float32 min, float32 max, float32 noData);
    
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
     * @brief  Upper pixel sample value bound.
     */
    float32 maximum;
    
    /*!
     * @brief  Lower pixel sample value bound.
     */
    float32 minimum;
    
    /*!
     * @brief  Zero elevation value.
     */
    float32 noData;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<NormalizeImage> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xB0AD5DAC;
    
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
