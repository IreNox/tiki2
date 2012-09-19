////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_SAMPLEFORMATS_ISAMPLEENCODER_H
#define CLODDY_API_HEIGHTMAPS_SAMPLEFORMATS_ISAMPLEENCODER_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/HeightmapLayer.h"

// Include referenced structures.

#include "Cloddy/SampleBitDepth.h"

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Heightmaps { class HeightmapSample; } } }
namespace CodeX { namespace System { class ByteBuffer; } }

// Declare interface ::Cloddy::API::Heightmaps::SampleFormats::ISampleEncoder.

namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleFormats
{
  // Use referenced namespaces.
  
  using namespace Cloddy::API::Heightmaps;
  using namespace CodeX;
  
  // Use referenced classes.
  
  using CodeX::System::ByteBuffer;
  
  class NO_VTABLE ISampleEncoder : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Returns the bit depth of this sample converter per heightmap layer.
     * 
     * @return The sample bit depth.
     */
    virtual SampleBitDepth GetBitDepth() = 0;
    
    /*!
     * @brief  The number of dataset channels.
     * 
     * @return <b>[>0]</b>  The number of channels.
     */
    virtual int32 GetChannels() = 0;
    
    /*!
     * @brief  Returns the heightmap layer mask of this sample converter.
     * 
     * @return The heightmap layer mask.
     */
    virtual HeightmapLayer GetLayerMask() = 0;
    
    /*!
     * @brief  Returns a mnemonic string that describes the layout of this sample converter,eg. 
     *         \c E16  for 16-bit elevation values.
     * 
     * Each <c>?</c> character in a sample converter mnemonic string means that one dataset channel 
     * serves an application specific purpose.
     * 
     * @return <b>[not-null]</b>  The mnemonic string.
     */
    virtual String GetMnemonic() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Converts the given dataset sample into a heightmap sample.
     * 
     * @param datasetSample Pointer to first byte of dataset sample.
     * @param heightmapSample The heightmap sample.
     */
    virtual void DatasetToHeightmap(ByteBuffer* datasetSample, HeightmapSample* heightmapSample) = 0;
    
    /*!
     * @brief  Converts the given heightmap sample into dataset sample.
     * 
     * @param heightmapSample The heightmap sample.
     * @param datasetSample Pointer to first byte of dataset sample.
     */
    virtual void HeightmapToDataset(HeightmapSample* heightmapSample, ByteBuffer* datasetSample) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<ISampleEncoder> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x62C4B5A3;
    
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
