////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_IMAGING_DATASETIMAGEREADER_H
#define CLODDY_API_IMAGING_DATASETIMAGEREADER_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/PixelFormat.h"

// Include referenced classes.

#include "Cloddy/ImageReaderBase.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Datasets { class IDataset; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Imaging { class DatasetImage; } } }
namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::API::Imaging::DatasetImageReader.

namespace Cloddy { namespace API { namespace Imaging
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Datasets::IDataset;
  
  // Use referenced classes.
  
  using CodeX::System::ByteBuffer;
  
  /*!
   * @brief  An IImageReader implementation that interprets the samples of a dataset as image 
   *         pixels and reads the resulting image.
   */
  class DatasetImageReader : public ImageReaderBase
  {
    // Declare friend classes.
    
    friend class DatasetImage;
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
  protected:
    
    virtual void DisposeManaged();
    
    virtual void DisposeManagedChildren();
    
    virtual void DoReadScanline(int32 scanlineY, ByteBuffer* scanline);
    
    virtual void DoSkipScanlines(int32 count);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Index of first channel of dataset to read.
     */
    int32 channel;
    
    /*!
     * @brief  The dataset.
     */
    Ptr<IDataset> dataset;
    
    /*!
     * @brief  The cubemap face from which to extract the image.
     */
    int32 face;
    
    /*!
     * @brief  X-coordinate of top-left corner of rectangle to read.
     */
    int32 faceX;
    
    /*!
     * @brief  Y-coordinate of top-left corner of rectangle to read.
     */
    int32 faceY;
    
    /*!
     * @brief  The dataset sample stride.
     */
    int32 stride;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of DatasetImageReader.
     * 
     * @param dataset The dataset.
     * @param channel Offset of first dataset channel to read.
     * @param face The cubemap face.
     * @param faceX X-coordinate of top-left corner of rectangle to read.
     * @param faceY Y-coordinate of top-left corner of rectangle to read.
     * @param width Width of rectangle to read.
     * @param height Height of rectangle to read.
     * @param stride The dataset sample stride.
     * @param pixelFormat The pixel format.
     */
    DatasetImageReader(IDataset* dataset, int32 channel, int32 face, int32 faceX, int32 faceY, int32 width, int32 height, int32 stride, PixelFormat pixelFormat);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<DatasetImageReader> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x86739C5E;
    
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
