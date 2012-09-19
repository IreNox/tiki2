////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_TOOLS_INFOTAG_IMAGE_H
#define CLODDY_API_TOOLS_INFOTAG_IMAGE_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/InfoTag.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Tools { class IInfoTagVisitor; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Imaging { class ImageInfo; } } }

// Declare class ::Cloddy::API::Tools::InfoTag_Image.

namespace Cloddy { namespace API { namespace Tools
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced classes.
  
  using Cloddy::API::Imaging::ImageInfo;
  
  class InfoTag_Image : public InfoTag
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The image information object.
     */
    Ptr<ImageInfo> Info;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of InfoTag_Image.
     * 
     * @param info <b>[not-null]</b>  The image info object.
     */
    InfoTag_Image(ImageInfo* info);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void Accept(IInfoTagVisitor* visitor);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<InfoTag_Image> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x68FF04B;
    
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
      if ((ptr = InfoTag::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
