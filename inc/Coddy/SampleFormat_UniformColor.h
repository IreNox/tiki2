////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_SAMPLEFORMATS_SAMPLEFORMAT_UNIFORMCOLOR_H
#define CLODDY_API_HEIGHTMAPS_SAMPLEFORMATS_SAMPLEFORMAT_UNIFORMCOLOR_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/HeightmapLayer.h"

// Include referenced structures.

#include "Cloddy/SampleBitDepth.h"

// Include referenced classes.

#include "Cloddy/SampleFormat.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleFormats { class ISampleEncoder; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Heightmaps { class HeightmapSample; } } }
namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleFormats { class SampleFormat; } } } }
namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::API::Heightmaps::SampleFormats::SampleFormat_UniformColor.

namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleFormats
{
  // Use referenced namespaces.
  
  using namespace Cloddy::API::Heightmaps;
  using namespace CodeX;
  
  // Use referenced classes.
  
  using CodeX::System::ByteBuffer;
  
  /*!
   * @brief  An implementation of the ISampleFormat that uses an uniform diffuse color for all 
   *         vertices.
   */
  class SampleFormat_UniformColor : public SampleFormat
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
    
    virtual void DatasetToHeightmap(ByteBuffer* datasetSample, HeightmapSample* heightmapSample);
    
    virtual void HeightmapToDataset(HeightmapSample* heightmapSample, ByteBuffer* datasetSample);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The wrapped sample format.
     */
    Ptr<ISampleEncoder> sampleEncoder;
    
    /*!
     * @brief  The uniform diffuse color.
     */
    int32 uniformColor;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of SampleFormat_UniformColor.
     * 
     * @param sampleEncoder The sample encoder to wrap.
     * @param uniformColor The uniform color value.
     */
    SampleFormat_UniformColor(ISampleEncoder* sampleEncoder, int32 uniformColor);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<SampleFormat_UniformColor> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x8BA5B3B3;
    
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
