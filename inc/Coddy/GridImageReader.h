////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_IMAGING_GRIDIMAGEREADER_H
#define CLODDY_API_IMAGING_GRIDIMAGEREADER_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/PixelFormat.h"

// Include referenced classes.

#include "Cloddy/CompositeImageReader.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Imaging { class IImage; } } }
namespace Cloddy { namespace API { namespace Imaging { class IImageReader; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Imaging { class GridImage; } } }
namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::API::Imaging::GridImageReader.

namespace Cloddy { namespace API { namespace Imaging
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced classes.
  
  using CodeX::System::ByteBuffer;
  
  /*!
   * @brief  An IImageReader implementation that reads the tile images of a GridImage as a 
   *         contiguous image.
   */
  class GridImageReader : public CompositeImageReader
  {
    // Declare friend classes.
    
    friend class GridImage;
    
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
     * @brief  Grid cell height,in pixels.
     */
    int32 cellHeight;
    
    /*!
     * @brief  Grid cell width,in pixels.
     */
    int32 cellWidth;
    
    /*!
     * @brief  Number of grid columns.
     */
    int32 columns;
    
    /*!
     * @brief  Index of grid row that is currently being read.
     */
    int32 currentRow;
    
    /*!
     * @brief  The IImageReader objects for the tile images being read.
     */
    Array<Ptr<IImageReader> > imageReaders;
    
    /*!
     * @brief  Amount of overlap between adjacent grid cells,in pixels.
     */
    int32 overlap;
    
    /*!
     * @brief  Number of grid rows.
     */
    int32 rows;
    
    /*!
     * @brief  The IImage descriptors of the tile images.
     */
    Array<Ptr<IImage> > tileImages;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of GridImageReader.
     * 
     * @param rows Number of grid rows.
     * @param columns Number of grid columns.
     * @param cellWidth Width of grid cells,in pixels.
     * @param cellHeight Height of grid cells,in pixels.
     * @param overlap Amount of overlap between adjacent grid cells,in pixels.
     * @param pixelFormat The pixel format of the grid image.
     * @param tileImages The tile images for the grid cells.
     */
    GridImageReader(int32 rows, int32 columns, int32 cellWidth, int32 cellHeight, int32 overlap, PixelFormat pixelFormat, Array<Ptr<IImage> > tileImages);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<GridImageReader> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x7DAFC2A6;
    
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
      if ((ptr = CompositeImageReader::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
