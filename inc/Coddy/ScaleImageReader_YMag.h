////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_IMAGING_SCALEIMAGEREADER_YMAG_H
#define CLODDY_API_IMAGING_SCALEIMAGEREADER_YMAG_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/ScaleImageReader.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Imaging { class IImageReader; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Imaging { class ImageReaderBase; } } }
namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::API::Imaging::ScaleImageReader_YMag.

namespace Cloddy { namespace API { namespace Imaging
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced classes.
  
  using CodeX::System::ByteBuffer;
  
  /*!
   * @brief  An IImageReader implementation that applies a cubic magnification filter along the 
   *         Y-axis.
   */
  class ScaleImageReader_YMag : public ScaleImageReader
  {
    // Declare friend classes.
    
    friend class ImageReaderBase;
    
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
     * @brief  The running discrete fraction.
     */
    int32 fraction;
    
    /*!
     * @brief  Index of current scanline in #sourceScanlines.
     */
    int32 sourceScanlineIdx;
    
    /*!
     * @brief  Holds four consecutive scanlines for interpolation.
     */
    Array<Ptr<ByteBuffer> > sourceScanlines;
    
    /*!
     * @brief  The fraction threshold.
     */
    int32 threshold;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of ScaleImageReader_YMag.
     * 
     * @param imageReader The source image reader.
     * @param height Height of the scaled image.
     */
    ScaleImageReader_YMag(IImageReader* imageReader, int32 height);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<ScaleImageReader_YMag> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x80F561D5;
    
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
      if ((ptr = ScaleImageReader::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
