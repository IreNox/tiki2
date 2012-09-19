////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_IMAGING_SMOOTHIMAGEREADER_H
#define CLODDY_API_IMAGING_SMOOTHIMAGEREADER_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/ImageReaderBase.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Imaging { class IImageReader; } } }
namespace Cloddy { namespace API { namespace Util { namespace Colors { class IColorDistanceMetric; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Imaging { class ImageReaderBase; } } }
namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::API::Imaging::SmoothImageReader.

namespace Cloddy { namespace API { namespace Imaging
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Util::Colors::IColorDistanceMetric;
  
  // Use referenced classes.
  
  using CodeX::System::ByteBuffer;
  
  /*!
   * @brief  An IImageReader implementation that reads a SmoothImage.
   */
  class SmoothImageReader : public ImageReaderBase
  {
    // Declare friend classes.
    
    friend class ImageReaderBase;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual Ptr<IImageReader> Normalize(float32 min, float32 max, float32 noData);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
  protected:
    
    virtual void DisposeManaged();
    
    virtual void DoReadScanline(int32 scanlineY, ByteBuffer* scanline);
    
    virtual void DoSkipScanlines(int32 count);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The kernel size (both width and height).
     */
    int32 kernelSize;
    
    /*!
     * @brief  The kernel size,divided by two.
     */
    int32 kernelSizeHalf;
    
    /*!
     * @brief  Precomputed distance weights of each kernel sample.
     */
    Array<float32> kernelWeights;
    
    /*!
     * @brief  Size of the precomputed distance weights matrix.
     */
    int32 kernelWeightsSize;
    
    /*!
     * @brief  The color distance metric used for edge preservation.
     */
    Ptr<IColorDistanceMetric> metric;
    
    /*!
     * @brief  The source image reader.
     */
    Ptr<IImageReader> source;
    
    /*!
     * @brief  Index of the scanline buffer in #sourceScanlines that will be filled next.
     * 
     * @see #ReadSourceScanline
     * @see #DuplicateSourceScanline
     */
    int32 sourceScanlineIndex;
    
    /*!
     * @brief  Buffers for source images scanlines.
     */
    Array<Ptr<ByteBuffer> > sourceScanlines;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of SmoothImageReader.
     * 
     * @param source The source image reader.
     * @param kernelSize The kernel size (both width and height).
     * @param metric The color distance metric to use.
     */
    SmoothImageReader(IImageReader* source, int32 kernelSize, IColorDistanceMetric* metric);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Duplicates the most recently read source image scanline and shifts the kernel.
     */
    void DuplicateSourceScanline();
    
    /*!
     * @brief  Reads the next source image scanline and shifts the kernel.
     * 
     * When all scanlines of the source image have been read,this method duplicates the lowermost 
     * scanline of the source image.
     */
    void ReadSourceScanline();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<SmoothImageReader> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x52CCA0E4;
    
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
