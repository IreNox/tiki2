////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_SAMPLEFORMATS_SAMPLECONVERTER_H
#define CLODDY_API_HEIGHTMAPS_SAMPLEFORMATS_SAMPLECONVERTER_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/HeightmapLayer.h"
#include "Cloddy/SampleConverterType.h"

// Include referenced structures.

#include "Cloddy/SampleBitDepth.h"

// Include referenced interfaces.

#include "Cloddy/ISampleConverter.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Datasets { namespace Metadata { class IChannelInfo; } } } }
namespace Cloddy { namespace API { namespace Util { namespace Colors { class IColorRamp; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Heightmaps { class HeightmapSample; } } }
namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::API::Heightmaps::SampleFormats::SampleConverter.

namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleFormats
{
  // Use referenced namespaces.
  
  using namespace Cloddy::API::Heightmaps;
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Datasets::Metadata::IChannelInfo;
  using Cloddy::API::Util::Colors::IColorRamp;
  
  // Use referenced classes.
  
  using CodeX::System::ByteBuffer;
  
  /*!
   * @brief  Abstract base class for ISampleConverter implementations.
   */
  class SampleConverter : public virtual ISampleConverter
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual SampleBitDepth GetBitDepth();
    
    virtual int32 GetChannels();
    
    virtual HeightmapLayer GetLayerMask() = 0;
    
    virtual String GetMnemonic() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates an ISampleConverter object for the given built in sample format type.
     * 
     * @param type The sample format type.
     * 
     * @return <b>[not-null]</b>  The ISampleConverter object.
     */
    static Ptr<ISampleConverter> Create(SampleConverterType type);
    
    /*!
     * @brief  Creates a new instance of ISampleConverter.
     * 
     * The returned sample converted sets the heightmap sample diffuse color by reading an unsinged 
     * 8-bit resp. 16-bit color index from the dataset sample and looking it up using the given 
     * color palette.
     * 
     * @param sixteenBits Use 16-bit color indices (\c true )or 8-bit color indices (\c false )?
     * @param colorRamp <b>[not-null]</b>  The IColorRamp to use for generating the color palette.
     * 
     * @return <b>[not-null]</b>  The created ISampleConverter object.
     */
    static Ptr<ISampleConverter> CreateIndexedColor(bool sixteenBits, IColorRamp* colorRamp);
    
    /*!
     * @brief  Creates a new instance of ISampleConverter.
     * 
     * The returned sample converted sets the heightmap sample diffuse color by reading an unsinged 
     * 8-bit resp. 16-bit color index from the dataset sample and looking it up using the given 
     * color palette.
     * 
     * @param sixteenBits Use 16-bit color indices (\c true )or 8-bit color indices (\c false )?
     * @param colorPalette <b>[not-null]</b>  The color palette to use.This array must have at 
     * least 256 entries for 8-bit color indices and at least 65536 entries for 16-bit color 
     * indices.
     * 
     * @return <b>[not-null]</b>  The created ISampleConverter object.
     */
    static Ptr<ISampleConverter> CreateIndexedColor(bool sixteenBits, Array<int32> colorPalette);
    
    virtual void DatasetToHeightmap(ByteBuffer* datasetSample, HeightmapSample* heightmapSample) = 0;
    
    virtual void HeightmapToDataset(HeightmapSample* heightmapSample, ByteBuffer* datasetSample) = 0;
    
    virtual Ptr<IChannelInfo> MetadataInfo();
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Constructors
    // ---------------------------------------------------------------------------------------------
  protected:
    
    /*!
     * @brief  Creates a new instance of SampleConverter.
     * 
     * @param channels <b>[>=0]</b>  The number of dataset channels of the sample format component.
     * @param bitDepth The bit depth of this sample converter.
     */
    SampleConverter(int32 channels, const SampleBitDepth& bitDepth);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The bit depth of this sample converter.
     */
    SampleBitDepth bitDepth;
    
    /*!
     * @brief  The number of dataset channels.
     */
    int32 channels;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<SampleConverter> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x19AA8A78;
    
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
      if ((ptr = ISampleConverter::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } 

#endif
