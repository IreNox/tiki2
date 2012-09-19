////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_IMAGING_NORMALIZEIMAGEREADER_H
#define CLODDY_API_IMAGING_NORMALIZEIMAGEREADER_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/ImageReaderBase.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Imaging { class IImageReader; } } }
namespace Cloddy { namespace Core { namespace IO { namespace Streams { class IDataStream; } } } }

// Declare class ::Cloddy::API::Imaging::NormalizeImageReader.

namespace Cloddy { namespace API { namespace Imaging
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::IO::Streams::IDataStream;
  
  /*!
   * @brief  Abstract base class for IImageReader implementations that performs normalization of 
   *         sample values while reading image data.
   */
  class NormalizeImageReader : public ImageReaderBase
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual bool CanNormalize();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual Ptr<IImageReader> Normalize(float32 min, float32 max, float32 noData);
    
    /*!
     * @brief  Translates the given sample value to <c>[0..65535]</c>.The translated sample value 
     *         is clamped to the output range.
     * 
     * @param sampleValue The sample value.
     * 
     * @return <b>[0..65535]</b>  The translated sample value.
     */
    int32 TranslateFloatSampleValue16(float32 sampleValue);
    
    /*!
     * @brief  Translates the given sample value to <c>[0..255]</c>.The translated sample value is 
     *         clamped to the output range.
     * 
     * @param sampleValue The sample value.
     * 
     * @return <b>[0..255]</b>  The translated sample value.
     */
    int32 TranslateFloatSampleValue8(float32 sampleValue);
    
    /*!
     * @brief  Translates the given sample value to <c>[0..65535]</c>.The translated sample value 
     *         is clamped to the output range.
     * 
     * @param sampleValue The sample value.
     * 
     * @return <b>[0..65535]</b>  The translated sample value.
     */
    int32 TranslateIntSampleValue16(int32 sampleValue);
    
    /*!
     * @brief  Translates the given sample value from to <c>[0..255]</c>.The translated sample 
     *         value is clamped to the output range.
     * 
     * @param sampleValue The sample value.
     * 
     * @return <b>[0..255]</b>  The translated sample value.
     */
    int32 TranslateIntSampleValue8(int32 sampleValue);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Attributes
    // ---------------------------------------------------------------------------------------------
  protected:
    
    /*!
     * @brief  Depicts the binary sample format code of the image data.
     * 
     * Setting this property will reset the normalization value range according to the following 
     * table:
     * <pre>
     *     .    sample    | channel   |               | default     | default    
     *     .    bit-depth | bit-depth | sample format | min value   | max value  
     *     .   -----------+-----------+---------------+-------------+-----------
     *     .    8-bit     | 8-bit     | unsigned int  | 0           | 255
     *     .    16-bit    | 16-bit    | unsigned int  | 0           | 65535
     *     .    8-bit     | 8-bit     | signed int    | -128        | 127
     *     .    16-bit    | 16-bit    | signed int    | -32768      | 32767
     *     .    32-bit    | 16-bit    | float         | -10000      | 10000
     *     .   
     *     .   sample bit-depth  := Bit-depth of the pixel sample values (as found in image file)
     *     .   channel bit-depth := Bit-depth of the pixel channel values (as returned by image 
     *     .                        reader)
     * </pre>
     * The value of the sample format code can be interpreted as follows:
     * <pre>
     *     .   -2 := 16-bit signed integer
     *     .   -1 := 8-bit  signed integer
     *     .    0  := 32-bit floating point
     *     .    1  := 8-bit  unsigned integer
     *     .    2  := 16-bit unsigned integer
     * </pre>
     * 
     * @param value The sample format code.
     */
    void SetSampleFormat(int32 value);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Reads the next sample from the image data and returns it as a 16-bit unsigned 
     *         integer.
     * 
     * @param stream The IDataStream to read from.
     * 
     * @return <b>[0..65535]</b>  The sample value.
     */
    int32 ReadSample16(IDataStream* stream);
    
    /*!
     * @brief  Reads the next sample from the image data and returns it as an 8-bit unsigned 
     *         integer.
     * 
     * @param stream The IDataStream to read from.
     * 
     * @return <b>[0..255]</b>  The sample value.
     */
    int32 ReadSample8(IDataStream* stream);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Depicts the binary sample format of the raw image data.
     * 
     * <pre>
     *     -2 := 16-bit signed integer
     *     -1 := 8-bit  signed integer
     *     0  := 32-bit floating point
     *     1  := 8-bit  unsigned integer
     *     2  := 16-bit unsigned integer
     * </pre>
     */
    int32 sampleFormat;
    
    /*!
     * @brief  The sample value that represents no data.
     */
    float32 sampleNoDataFloat;
    
    /*!
     * @brief  The sample value that represents no data.
     */
    int32 sampleNoDataInt;
    
    /*!
     * @brief  The minimum sample value.
     */
    float32 sampleValueMinFloat;
    
    /*!
     * @brief  The minimum sample value (integer precision).
     */
    int32 sampleValueMinInt;
    
    /*!
     * @brief  Width of the sample value range (integer precision).
     */
    int32 sampleValueRangeInt;
    
    /*!
     * @brief  Scale factor for scaling to 16-bit unsigned integer range.
     */
    float32 sampleValueScale16Float;
    
    /*!
     * @brief  Scale factor for scaling to 8-bit unsigned integer range.
     */
    float32 sampleValueScale8Float;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
  public:
    
    NormalizeImageReader();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<NormalizeImageReader> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x1EF085AD;
    
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
      if ((ptr = ImageReaderBase::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
