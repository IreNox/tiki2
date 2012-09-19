////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_SAMPLEFORMATS_ISAMPLECONVERTER_H
#define CLODDY_API_HEIGHTMAPS_SAMPLEFORMATS_ISAMPLECONVERTER_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/ISampleEncoder.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Datasets { namespace Metadata { class IChannelInfo; } } } }

// Declare interface ::Cloddy::API::Heightmaps::SampleFormats::ISampleConverter.

namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleFormats
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Datasets::Metadata::IChannelInfo;
  
  /*!
   * @brief  Base interface for classes that transcodes dataset samples into heightmap samples and 
   *         vice versa.
   * 
   * Dataset samples store one or more channels;each dataset channel consist of 8-bits resp. one 
   * byte.
   * 
   * Heightmap samples contain data such as elevation,diffuse color and displacement values.See 
   * the HeightmapSample for detailed information.
   */
  class NO_VTABLE ISampleConverter : public virtual ISampleEncoder
  {
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Returns an IChannelInfo object that describes this sample converter.
     * 
     * The returned IChannelInfo object can be stored as metadata with a dataset.
     * 
     * @return The IChannelInfo object or \c null  if this sample converter cannot be described.
     */
    virtual Ptr<IChannelInfo> MetadataInfo() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<ISampleConverter> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x6B23064F;
    
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
      if ((ptr = ISampleEncoder::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
} } } } 

#endif
