////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_IMAGING_GRIDIMAGE_H
#define CLODDY_API_IMAGING_GRIDIMAGE_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/PixelFormat.h"

// Include referenced classes.

#include "Cloddy/CompositeImage.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Imaging { class IImage; } } }
namespace Cloddy { namespace API { namespace Imaging { class IImageReader; } } }
namespace Cloddy { namespace API { namespace Imaging { class IImageVisitor; } } }
namespace Cloddy { namespace Core { namespace Collections { template<class> class IList; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Imaging { class ImageInfo; } } }

// Declare class ::Cloddy::API::Imaging::GridImage.

namespace Cloddy { namespace API { namespace Imaging
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::Collections::IList;
  
  /*!
   * @brief  An Imaging Object Model node that can be used to combine multiple images into one big 
   *         image.
   * 
   * A GridImage defines a virtual canvas which is divided into a regular grid.An input tile image 
   * is placed into each cell of that grid.The resulting image contains the image data of the 
   * entire virtual canvas.
   * <pre>
   *    .          col    col    col    col    col
   *    .          0      1      2      3      4
   *    .          +------+------+------+------+------+
   *    .          |      |      |      |      |      |
   *    .    row 0 |   0  |   1  |   2  |   3  |   4  |
   *    .          |      |      |      |      |      |
   *    .          +------+------+------+------+------+
   *    .          |      |      |      |      |      |
   *    .    row 1 |   5  |   6  |   7  |   8  |   9  |
   *    .          |      |      |      |      |      |
   *    .          +------+------+------+------+------+
   *    .          |      |      |      |      |      |
   *    .    row 2 |  10  |  11  |  12  |  13  |  14  |
   *    .          |      |      |      |      |      |
   *    .          +------+------+------+------+------+
   *    .    
   *    .    rows    := 3
   *    .    columns := 5
   *    .    # tiles := 15
   * </pre>
   * An optional #GetOverlap value can be specified.This value depicts by how many pixels adjacent 
   * grid cells shall overlap.Overlap is usually required for tiled datasets where the first and 
   * last rows resp. columns of adjacent tiles contain the same pixels.
   */
  class GridImage : public CompositeImage
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Height of a single grid cell,in pixels.
     * 
     * @return <b>[>=0]</b>  The cell height.
     */
    int32 GetCellHeight();
    
    /*!
     * @brief  Width of a single grid cell,in pixels.
     * 
     * @return <b>[>=0]</b>  The cell width.
     */
    int32 GetCellWidth();
    
    /*!
     * @brief  Number of columns in the grid.
     * 
     * @return <b>[>0]</b>  The number of columns.
     */
    int32 GetColumns();
    
    /*!
     * @brief  Number of columns in the grid.
     * 
     * @param value <b>[>0]</b>  The number of columns.
     */
    void SetColumns(int32 value);
    
    /*!
     * @brief  Height of the grid image,in pixels.
     * 
     * @return <b>[>=0]</b>  Height of the grid image,in pixels.
     */
    int32 GetHeight();
    
    /*!
     * @brief  The amount of overlap between adjacent grid cells,in pixels.
     * 
     * @return <b>[>=0]</b>  The amount of overlap,in pixels.
     */
    int32 GetOverlap();
    
    /*!
     * @brief  The amount of overlap between adjacent grid cells,in pixels.
     * 
     * @param value <b>[>=0]</b>  The amount of overlap,in pixels.
     */
    void SetOverlap(int32 value);
    
    /*!
     * @brief  The pixel format of the grid image.
     * 
     * If set to PixelFormat::PixelFormat_UnknownPixelFormat,the pixel format of the returned image 
     * will be determined from the pixel formats of the tile images (
     * see ImageUtil::GetCombinedPixelFormat).
     * 
     * @return The pixel format of the grid image.
     */
    PixelFormat GetPixelFormat();
    
    /*!
     * @brief  The pixel format of the grid image.
     * 
     * If set to PixelFormat::PixelFormat_UnknownPixelFormat,the pixel format of the returned image 
     * will be determined from the pixel formats of the tile images (
     * see ImageUtil::GetCombinedPixelFormat).
     * 
     * @param value The pixel format of the grid image.
     */
    void SetPixelFormat(PixelFormat value);
    
    /*!
     * @brief  Number of rows in the grid.
     * 
     * @return <b>[>0]</b>  The number of rows.
     */
    int32 GetRows();
    
    /*!
     * @brief  Number of rows in the grid.
     * 
     * @param value <b>[>0]</b>  The number of rows.
     */
    void SetRows(int32 value);
    
    /*!
     * @brief  Returns the number of tile images in the grid.
     * 
     * @return <b>[>=0]</b>  The number of tile images.
     */
    int32 GetTileImageCount();
    
    /*!
     * @brief  Width of the grid image,in pixels.
     * 
     * @return <b>[>=0]</b>  Width of the grid image,in pixels.
     */
    int32 GetWidth();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of GridImage.
     */
    GridImage();
    
    /*!
     * @brief  Creates a new instance of GridImage.
     * 
     * @param rows <b>[>0]</b>  Number of grid rows.
     * @param columns <b>[>0]</b>  Number of grid columns.
     */
    GridImage(int32 rows, int32 columns);
    
    /*!
     * @brief  Creates a new instance of GridImage.
     * 
     * @param rows <b>[>0]</b>  Number of grid rows.
     * @param columns <b>[>0]</b>  Number of grid columns.
     * @param overlap <b>[>=0]</b>  The amount of overlap between adjacent grid cells,in pixels.
     * @param pixelFormat The pixel format of the grid image.If set 
     * to PixelFormat::PixelFormat_UnknownPixelFormat,the pixel format of the grid image will be 
     * deferred from the pixel formats of the tile images.
     */
    GridImage(int32 rows, int32 columns, int32 overlap, PixelFormat pixelFormat);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void Accept(IImageVisitor* visitor, Object* userData);
    
    /*!
     * @brief  Adds a tile image to the grid.
     * 
     * The sequence in which the tile image have been added to the grid determines the grid cell in 
     * which each of them will be placed.Given the zero-based index \c i  of a tile image in the 
     * sequence,the coordinates of its grid cell then are:
     * <pre>
     *     x := i % columns
     *     y := i / columns
     * </pre>
     * 
     * @param tileImage <b>[not-null]</b>  The tile image to add.
     * 
     * @return <b>[not-null]</b>  this
     */
    Ptr<GridImage> AddTileImage(IImage* tileImage);
    
    /*!
     * @brief  Removes all tile images from the grid.
     * 
     * @return <b>[not-null]</b>  this
     */
    Ptr<GridImage> Clear();
    
    /*!
     * @brief  Returns the \e index -th tile image.
     * 
     * @param index <b>[0..#GetTileImageCount-1]</b>  Index of the tile image to return.
     * 
     * @return <b>[not-null]</b>  The IImage object that represents the tile image.
     */
    Ptr<IImage> GetTileImage(int32 index);
    
    /*!
     * @brief  Removes a tile images from the grid.
     * 
     * @param tileImage <b>[not-null]</b>  The tile image to remove.
     * 
     * @return <b>[not-null]</b>  this
     */
    Ptr<GridImage> RemoveTileImage(IImage* tileImage);
    
    virtual void Validate();
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Attributes
    // ---------------------------------------------------------------------------------------------
  protected:
    
    virtual int32 GetSourceImageCount();
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual Ptr<IImageReader> DoReadImage();
    
    virtual Ptr<ImageInfo> DoReadImageInfo();
    
    virtual Ptr<IImage> GetSourceImageAt(int32 index);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Height of a single grid cell,in pixels.
     */
    int32 cellHeight;
    
    /*!
     * @brief  Width of a single grid cell,in pixels.
     */
    int32 cellWidth;
    
    /*!
     * @brief  Number of columns in the grid.
     */
    int32 columns;
    
    /*!
     * @brief  Holds the images for the grid cells,in row-major order.
     */
    Ptr<IList<Ref<IImage> > > images;
    
    /*!
     * @brief  The amount of overlapped between adjacent grid cells,in pixels.
     */
    int32 overlap;
    
    /*!
     * @brief  The pixel format of the grid.
     */
    PixelFormat pixelFormat;
    
    /*!
     * @brief  Number of rows in the grid.
     */
    int32 rows;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Computes the cell width and cell height.
     */
    void ComputeCellWidthAndCellHeight();
    
    /*!
     * @brief  Returns the pixel format to use for the grid image.
     * 
     * @return The PixelFormat.
     */
    PixelFormat ComputePixelFormat();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<GridImage> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xF77EB1D1;
    
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
      if ((ptr = CompositeImage::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
