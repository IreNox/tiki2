////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_DATASETS_METADATA_ICHANNELINFOVISITOR_H
#define CLODDY_API_DATASETS_METADATA_ICHANNELINFOVISITOR_H

#include "CodeX/System.h"

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Datasets { namespace Metadata { class ColorChannelInfo; } } } }
namespace Cloddy { namespace API { namespace Datasets { namespace Metadata { class DetailChannelInfo; } } } }
namespace Cloddy { namespace API { namespace Datasets { namespace Metadata { class DisplacementChannelInfo; } } } }
namespace Cloddy { namespace API { namespace Datasets { namespace Metadata { class ElevationChannelInfo; } } } }

// Declare interface ::Cloddy::API::Datasets::Metadata::IChannelInfoVisitor.

namespace Cloddy { namespace API { namespace Datasets { namespace Metadata
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Visitor interface for IChannelInfos.
   */
  class NO_VTABLE IChannelInfoVisitor : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Visits the given IChannelInfo object.
     * 
     * @param info <b>[not-null]</b>  The channel info object.
     * @param userData Optional user data.
     */
    virtual void Visit(ColorChannelInfo* info, Object* userData) = 0;
    
    /*!
     * @brief  Visits the given IChannelInfo object.
     * 
     * @param info <b>[not-null]</b>  The channel info object.
     * @param userData Optional user data.
     */
    virtual void Visit(DetailChannelInfo* info, Object* userData) = 0;
    
    /*!
     * @brief  Visits the given IChannelInfo object.
     * 
     * @param info <b>[not-null]</b>  The channel info object.
     * @param userData Optional user data.
     */
    virtual void Visit(DisplacementChannelInfo* info, Object* userData) = 0;
    
    /*!
     * @brief  Visits the given IChannelInfo object.
     * 
     * @param info <b>[not-null]</b>  The channel info object.
     * @param userData Optional user data.
     */
    virtual void Visit(ElevationChannelInfo* info, Object* userData) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IChannelInfoVisitor> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xE4DEB08E;
    
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
      return (void*) 0;
    }
  };
} } } } 

#endif
