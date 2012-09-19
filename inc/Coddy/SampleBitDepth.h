////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_SAMPLEFORMATS_SAMPLEBITDEPTH_H
#define CLODDY_API_HEIGHTMAPS_SAMPLEFORMATS_SAMPLEBITDEPTH_H

#include "CodeX/System.h"

// Declare class ::Cloddy::API::Heightmaps::SampleFormats::SampleBitDepth.

namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleFormats
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Stores information about the bit depths of a heightmap resp. a heightmap sample format.
   */
  struct SampleBitDepth : StructType
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  A sample bit depth of zero.
     */
    static const SampleBitDepth Empty;
    
    /*!
     * @brief  The number of bits used to encode a color channel value.
     */
    int32 ColorBits;
    
    /*!
     * @brief  The number of bits used to encode detail values.
     */
    int32 DetailBits;
    
    /*!
     * @brief  The number of bits used to encode an axis component of a displacement vector.
     */
    int32 DisplacementBits;
    
    /*!
     * @brief  The number of bits used to encode elevation values.
     */
    int32 ElevationBits;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of SampleBitDepth.
     * 
     * @param elevationBits <b>[>=0]</b>  The number of bits used to encode elevation values.
     * @param colorBits <b>[>=0]</b>  The number of bits used to encode a color channel value.
     * @param displacementBits <b>[>=0]</b>  The number of bits used to encode an axis component of 
     * a displacement vector.
     * @param detailBits <b>[>=0]</b>  The number of bits used to encode a single detail channel 
     * value.
     */
    SampleBitDepth(int32 elevationBits, int32 colorBits, int32 displacementBits, int32 detailBits);
    
    SampleBitDepth();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Returns the maximum sample bit depth of this bit depth and the given one.
     * 
     * @param other The bit depth.
     * 
     * @return The resulting bit depth.
     */
    SampleBitDepth Max(const SampleBitDepth& other) const;
    
    // ---------------------------------------------------------------------------------------------
    //  Copy constructor and copy assignment operator
    // ---------------------------------------------------------------------------------------------
  public:
    
    SampleBitDepth(const SampleBitDepth& other);
    
    SampleBitDepth& operator=(const SampleBitDepth& other);
  };
  
} } } } 

#endif
