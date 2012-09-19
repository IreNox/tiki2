////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_IMAGING_PIXELCOVERAGEIMAGEREADER_AREA_H
#define CLODDY_API_IMAGING_PIXELCOVERAGEIMAGEREADER_AREA_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/ImageReaderBase.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Imaging { class IImageReader; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Imaging { class ImageReaderBase; } } }
namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::API::Imaging::PixelCoverageImageReader_Area.

namespace Cloddy { namespace API { namespace Imaging
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced classes.
  
  using CodeX::System::ByteBuffer;
  
  /*!
   * @brief  An implementation of the IImageReader interface that transforms an input image that 
   *         has a PixelCoverage::PixelCoverage_PixelIsPoint semantic into an image that has 
   *         a PixelCoverage::PixelCoverage_PixelIsArea semantic.
   */
  class PixelCoverageImageReader_Area : public ImageReaderBase
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
     * @brief  Index of current source scanline in #sourceScanlines.
     */
    int32 current;
    
    /*!
     * @brief  Need to read the source scanline?
     */
    bool needPrevious;
    
    /*!
     * @brief  Index of previous source scanline in #sourceScanlines.
     */
    int32 previous;
    
    /*!
     * @brief  The source image reader.
     */
    Ptr<IImageReader> sourceImageReader;
    
    /*!
     * @brief  Buffers for current and previous source image scanlines.
     */
    Array<Ptr<ByteBuffer> > sourceScanlines;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    PixelCoverageImageReader_Area(IImageReader* sourceImageReader);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<PixelCoverageImageReader_Area> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x3671C78;
    
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
