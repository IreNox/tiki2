////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_DATASETS_BUILDER_DEM_ASTERBLENDIMAGE_H
#define CLODDY_API_DATASETS_BUILDER_DEM_ASTERBLENDIMAGE_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/ImageBase.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Imaging { class IImage; } } }
namespace Cloddy { namespace API { namespace Imaging { class IImageReader; } } }
namespace Cloddy { namespace API { namespace Imaging { class IImageVisitor; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Datasets { namespace Builder { namespace DEM { class DatasetBlockProvider_ASTER_GDEM; } } } } }
namespace Cloddy { namespace API { namespace Imaging { class ImageInfo; } } }

// Declare class ::Cloddy::API::Datasets::Builder::DEM::AsterBlendImage.

namespace Cloddy { namespace API { namespace Datasets { namespace Builder { namespace DEM
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Imaging::IImage;
  using Cloddy::API::Imaging::IImageReader;
  using Cloddy::API::Imaging::IImageVisitor;
  
  // Use referenced classes.
  
  using Cloddy::API::Imaging::ImageBase;
  using Cloddy::API::Imaging::ImageInfo;
  
  class AsterBlendImage : public ImageBase
  {
    // Declare friend classes.
    
    friend class DatasetBlockProvider_ASTER_GDEM;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
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
    
    Ptr<IImage> num;
    
    Ptr<IImage> ocean;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    AsterBlendImage(IImage* num, IImage* ocean);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<AsterBlendImage> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x72AB796F;
    
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
      if ((ptr = ImageBase::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } } 

#endif
