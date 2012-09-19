////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_SAMPLEFORMATS_SAMPLECONVERTER_I8_H
#define CLODDY_API_HEIGHTMAPS_SAMPLEFORMATS_SAMPLECONVERTER_I8_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/HeightmapLayer.h"

// Include referenced structures.

#include "Cloddy/SampleBitDepth.h"

// Include referenced classes.

#include "Cloddy/SampleConverter.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Datasets { namespace Metadata { class IChannelInfo; } } } }
namespace Cloddy { namespace API { namespace Util { namespace Colors { class IColorDistanceMetric; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Heightmaps { class HeightmapSample; } } }
namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleFormats { class SampleConverter; } } } }
namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::API::Heightmaps::SampleFormats::SampleConverter_I8.

namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleFormats
{
  // Use referenced namespaces.
  
  using namespace Cloddy::API::Heightmaps;
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Datasets::Metadata::IChannelInfo;
  using Cloddy::API::Util::Colors::IColorDistanceMetric;
  
  // Use referenced classes.
  
  using CodeX::System::ByteBuffer;
  
  /*!
   * @brief  A sample format component for indexed diffuse color values stored in a single dataset 
   *         channel (ie. 8 bits).
   * 
   * The actual color value is derieved from the unsigned input value by using a color palette.
   */
  class SampleConverter_I8 : public SampleConverter
  {
    // Declare friend classes.
    
    friend class SampleConverter;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual HeightmapLayer GetLayerMask();
    
    virtual String GetMnemonic();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void DatasetToHeightmap(ByteBuffer* datasetSample, HeightmapSample* heightmapSample);
    
    virtual void HeightmapToDataset(HeightmapSample* heightmapSample, ByteBuffer* datasetSample);
    
    virtual Ptr<IChannelInfo> MetadataInfo();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The color distance metric to use.
     */
    Ptr<IColorDistanceMetric> colorDistanceMetric;
    
    /*!
     * @brief  The color palette of this sample converter.
     */
    Array<int32> colorPalette;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of SampleConverter_I8.
     * 
     * @param colorPalette The color palette to use.
     * @param colorDistanceMetric The color distance metric to use.
     */
    SampleConverter_I8(Array<int32> colorPalette, IColorDistanceMetric* colorDistanceMetric);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<SampleConverter_I8> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x669AD688;
    
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
      if ((ptr = SampleConverter::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } 

#endif
