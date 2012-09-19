////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_SAMPLEFORMATS_SAMPLEFORMAT_H
#define CLODDY_API_HEIGHTMAPS_SAMPLEFORMATS_SAMPLEFORMAT_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/HeightmapLayer.h"
#include "Cloddy/SampleConverterType.h"

// Include referenced structures.

#include "Cloddy/SampleBitDepth.h"

// Include referenced interfaces.

#include "Cloddy/ISampleFormat.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Datasets { namespace Metadata { class IChannelInfo; } } } }
namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleFormats { class ISampleConverter; } } } }
namespace Cloddy { namespace API { namespace Util { namespace Colors { class IColorRamp; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Heightmaps { class HeightmapSample; } } }
namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::API::Heightmaps::SampleFormats::SampleFormat.

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
   * @brief  Represents a dataset sample format.
   */
  class SampleFormat : public virtual ISampleFormat
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Returns a new sample format:16-bit 565 RGB color values.
     * 
     * @return <b>[not-null]</b>  The new sample format object.
     */
    static Ptr<ISampleFormat> GetC16();
    
    /*!
     * @brief  Returns a new sample format:24-bit RGB color values.
     * 
     * @return <b>[not-null]</b>  The new sample format object.
     */
    static Ptr<ISampleFormat> GetC24();
    
    /*!
     * @brief  Returns a new sample format:32-bit ARGB color values.
     * 
     * @return <b>[not-null]</b>  The new sample format object.
     */
    static Ptr<ISampleFormat> GetC32();
    
    /*!
     * @brief  Returns a new sample format:8-bit grayscale color values.
     * 
     * @return <b>[not-null]</b>  The new sample format object.
     */
    static Ptr<ISampleFormat> GetC8();
    
    /*!
     * @brief  Returns a new sample format:16-bit elevation values.
     * 
     * @return <b>[not-null]</b>  The new sample format object.
     */
    static Ptr<ISampleFormat> GetE16();
    
    /*!
     * @brief  Returns a new sample format:16-bit elevation values and 24-bit RGB color values.
     * 
     * @return <b>[not-null]</b>  The new sample format object.
     */
    static Ptr<ISampleFormat> GetE16C24();
    
    /*!
     * @brief  Returns a new sample format:16-bit elevation values and 32-bit ARGB color values.
     * 
     * @return <b>[not-null]</b>  The new sample format object.
     */
    static Ptr<ISampleFormat> GetE16C32();
    
    /*!
     * @brief  Returns a new sample format:24-bit elevation values.
     * 
     * @return <b>[not-null]</b>  The new sample format object.
     */
    static Ptr<ISampleFormat> GetE24();
    
    /*!
     * @brief  Returns a new sample format:24-bit elevation values and 24-bit RGB color values.
     * 
     * @return <b>[not-null]</b>  The new sample format object.
     */
    static Ptr<ISampleFormat> GetE24C24();
    
    /*!
     * @brief  Returns a new sample format:24-bit elevation values and 32-bit ARGB color values.
     * 
     * @return <b>[not-null]</b>  The new sample format object.
     */
    static Ptr<ISampleFormat> GetE24C32();
    
    /*!
     * @brief  Returns a new sample format:8-bit elevation values.
     * 
     * @return <b>[not-null]</b>  The new sample format object.
     */
    static Ptr<ISampleFormat> GetE8();
    
    /*!
     * @brief  Returns a new sample format:8-bit elevation values and 24-bit RGB color values.
     * 
     * @return <b>[not-null]</b>  The new sample format object.
     */
    static Ptr<ISampleFormat> GetE8C24();
    
    /*!
     * @brief  Returns a new sample format:8-bit elevation values and 32-bit ARGB color values.
     * 
     * @return <b>[not-null]</b>  The new sample format object.
     */
    static Ptr<ISampleFormat> GetE8C32();
    
    virtual SampleBitDepth GetBitDepth() = 0;
    
    virtual int32 GetChannels() = 0;
    
    virtual HeightmapLayer GetLayerMask() = 0;
    
    virtual String GetMnemonic() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of ISampleFormat.
     * 
     * @param sampleConverter The built in sample converter to use.
     * 
     * @return <b>[not-null]</b>  The ISampleFormat instance.
     */
    static Ptr<ISampleFormat> Create(SampleConverterType sampleConverter);
    
    /*!
     * @brief  Creates a new instance of ISampleFormat.
     * 
     * @param sampleConverter <b>[not-null]</b>  The sample converter to use.
     * 
     * @return <b>[not-null]</b>  The ISampleFormat instance.
     */
    static Ptr<ISampleFormat> Create(ISampleConverter* sampleConverter);
    
    /*!
     * @brief  Creates a new instance of ISampleFormat from the given mnemonic tag.
     * 
     * @param mnemonic <b>[not-null]</b>  The mnemonic tag.
     * 
     * @return <b>[not-null]</b>  The created ISampleFormat instance.
     */
    static Ptr<ISampleFormat> FromMnemonic(String mnemonic);
    
    virtual Ptr<ISampleFormat> Append(SampleConverterType sampleConverter);
    
    virtual Ptr<ISampleFormat> Append(ISampleConverter* component);
    
    virtual void DatasetToHeightmap(ByteBuffer* datasetSample, HeightmapSample* heightmapSample) = 0;
    
    virtual void HeightmapToDataset(HeightmapSample* heightmapSample, ByteBuffer* datasetSample) = 0;
    
    virtual Ptr<ISampleFormat> MakeOpaque();
    
    virtual Array<Ptr<IChannelInfo> > MetadataInfo();
    
    virtual Ptr<ISampleFormat> UseColorRamp(IColorRamp* colorRamp);
    
    virtual Ptr<ISampleFormat> UseColorRamp(IColorRamp* colorRamp, float64 from, float64 to);
    
    virtual Ptr<ISampleFormat> UseUniformColor(int32 color);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<SampleFormat> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x22B32B25;
    
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
      if ((ptr = ISampleFormat::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } 

#endif
