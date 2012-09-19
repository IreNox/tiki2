////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_SAMPLEFORMATS_SAMPLEFORMAT_COMPOSITEONE_H
#define CLODDY_API_HEIGHTMAPS_SAMPLEFORMATS_SAMPLEFORMAT_COMPOSITEONE_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/HeightmapLayer.h"

// Include referenced structures.

#include "Cloddy/SampleBitDepth.h"

// Include referenced classes.

#include "Cloddy/SampleFormat.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Datasets { namespace Metadata { class IChannelInfo; } } } }
namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleFormats { class ISampleConverter; } } } }
namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleFormats { class ISampleFormat; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Heightmaps { class HeightmapSample; } } }
namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleFormats { class SampleFormat; } } } }
namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::API::Heightmaps::SampleFormats::SampleFormat_CompositeOne.

namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleFormats
{
  // Use referenced namespaces.
  
  using namespace Cloddy::API::Heightmaps;
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Datasets::Metadata::IChannelInfo;
  
  // Use referenced classes.
  
  using CodeX::System::ByteBuffer;
  
  /*!
   * @brief  This class wraps a ISampleConverter into a ISampleFormat.
   */
  class SampleFormat_CompositeOne : public SampleFormat
  {
    // Declare friend classes.
    
    friend class SampleFormat;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual SampleBitDepth GetBitDepth();
    
    virtual int32 GetChannels();
    
    virtual HeightmapLayer GetLayerMask();
    
    virtual String GetMnemonic();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual Ptr<ISampleFormat> Append(ISampleConverter* component);
    
    virtual void DatasetToHeightmap(ByteBuffer* datasetSample, HeightmapSample* heightmapSample);
    
    virtual void HeightmapToDataset(HeightmapSample* heightmapSample, ByteBuffer* datasetSample);
    
    virtual Array<Ptr<IChannelInfo> > MetadataInfo();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The wrapped ISampleConverter object.
     */
    Ptr<ISampleConverter> component;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of SampleFormat_CompositeOne.
     * 
     * @param component The sample format component.
     */
    SampleFormat_CompositeOne(ISampleConverter* component);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<SampleFormat_CompositeOne> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x9B0F9C97;
    
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
      if ((ptr = SampleFormat::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } 

#endif
