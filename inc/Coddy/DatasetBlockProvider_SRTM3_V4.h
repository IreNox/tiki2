////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_DATASETS_BUILDER_DEM_DATASETBLOCKPROVIDER_SRTM3_V4_H
#define CLODDY_API_DATASETS_BUILDER_DEM_DATASETBLOCKPROVIDER_SRTM3_V4_H

#include "CodeX/System.h"

// Include referenced structures.

#include "Cloddy/Vec2I.h"

// Include referenced classes.

#include "Cloddy/DatasetBlockProvider.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Datasets { class IDataset; } } }
namespace Cloddy { namespace API { namespace Imaging { class IImage; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace IO { namespace Files { class Path; } } } }
namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::API::Datasets::Builder::DEM::DatasetBlockProvider_SRTM3_V4.

namespace Cloddy { namespace API { namespace Datasets { namespace Builder { namespace DEM
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced structures.
  
  using Cloddy::Core::Math::Vectors::Vec2I;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Datasets::IDataset;
  using Cloddy::API::Imaging::IImage;
  
  // Use referenced classes.
  
  using Cloddy::API::Datasets::Builder::DatasetBlockProvider;
  using Cloddy::Core::IO::Files::Path;
  using CodeX::System::ByteBuffer;
  
  /*!
   * @brief  An IDatasetBlockProvider implementation for SRTM3 v4 dataset (see http://srtm.csi.
   *         cgiar.org/).
   * 
   * In order to provide data for the whole globe,the north- and south-most regions need to be 
   * filled with alternative data since these regions or not covered by the SRTM3 v4 dataset.
   * Alternative data is taken from a combined SRTM30/GTOPO30 Cloddy dataset (size 43201 by 21601).
   * The raw data for SRTM30 and GTOPO30 can be downloaded here:http://www.src.com/datasets/
   * datasets_terrain.html.
   * 
   * The SRTM3 v4 input data is normalized using the value range -11000 to 11000.In order to 
   * produce correct results,the combined SRTM30/GTOPO30 Cloddy dataset must have been created 
   * using the same normalization parameters.
   */
  class DatasetBlockProvider_SRTM3_V4 : public DatasetBlockProvider
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual Vec2I GetBlockSize();
    
    virtual int32 GetChannels();
    
    virtual Vec2I GetDatasetSize();
    
    virtual Vec2I GetGridSize();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of DatasetBlockProvider_SRTM3_V4.
     * 
     * @param srtm3Dir <b>[not-null]</b>  Path to the directory that holds the SRTM3 v4 zipped data 
     * files.
     * @param srtm30Path <b>[not-null]</b>  Path to the combined SRTM30/GTOOP30 Cloddy dataset.
     * @param oceanMaskPath <b>[not-null]</b>  Path to the ocean mask file.
     */
    DatasetBlockProvider_SRTM3_V4(Path* srtm3Dir, Path* srtm30Path, Path* oceanMaskPath);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
  protected:
    
    virtual void DisposeManaged();
    
    virtual void DoGetBlock(const Vec2I& block, ByteBuffer* buffer);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constants
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Maximum DEM elevation value,
     */
    static const float32 MaxValue;
    
    /*!
     * @brief  Minimum DEM elevation value.
     */
    static const float32 MinValue;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Size of the ocean mask image.
     */
    static const Vec2I OceanMaskSize;
    
    /*!
     * @brief  Size of the SRTM30 image.
     */
    static const Vec2I Srtm30Size;
    
    /*!
     * @brief  Path to the ocean mask dataset file.
     */
    Ptr<Path> oceanMaskPath;
    
    /*!
     * @brief  The SRTM30 dataset.
     */
    Ptr<IDataset> srtm30;
    
    /*!
     * @brief  The data directory of the SRTM3 v4 files.
     */
    Ptr<Path> srtm3Dir;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Returns a tile of the ocean mask image.
     * 
     * Automatic wrapping is performed along the X-axis.
     * 
     * @param x1 X-coordinate of top-left corner of image.
     * @param y1 Y-coordinate of top-left corner of image.
     * @param x2 X-coordinate of bottom-right corner of image.
     * @param y2 Y-coordinate of bottom-right corner of image.
     * 
     * @return The tile image.
     */
    Ptr<IImage> GetOceanMaskTile(int32 x1, int32 y1, int32 x2, int32 y2);
    
    /*!
     * @brief  Returns the ocean mask tile for the given dataset block.
     * 
     * @param block The block coordinates.
     * @param blockSize The block size.
     * 
     * @return The block tile image.
     */
    Ptr<IImage> GetOceanMaskTile(const Vec2I& block, const Vec2I& blockSize);
    
    /*!
     * @brief  Returns a tile of the SRTM30 dataset.
     * 
     * Automatic wrapping is performed along the X-axis.
     * 
     * @param x1 X-coordinate of top-left corner of image.
     * @param y1 Y-coordinate of top-left corner of image.
     * @param x2 X-coordinate of bottom-right corner of image.
     * @param y2 Y-coordinate of bottom-right corner of image.
     * 
     * @return The tile image.
     */
    Ptr<IImage> GetSrtm30Tile(int32 x1, int32 y1, int32 x2, int32 y2);
    
    /*!
     * @brief  Returns the interpolated SRTM30 tile for the given dataset block.
     * 
     * @param block The block coordinates.
     * @param blockSize The block size.
     * 
     * @return <b>[not-null]</b>  The block tile image.
     */
    Ptr<IImage> GetSrtm30Tile(const Vec2I& block, const Vec2I& blockSize);
    
    /*!
     * @brief  Returns the SRTM3 tile for the given dataset block.
     * 
     * @param block The block coordinates.
     * @param blockSize The block size.
     * 
     * @return The block tile image or \c null  if there is no available SRTM3 tile.
     */
    Ptr<IImage> GetSrtm3Tile(const Vec2I& block, const Vec2I& blockSize);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<DatasetBlockProvider_SRTM3_V4> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xC440E0B3;
    
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
      if ((ptr = DatasetBlockProvider::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } } 

#endif
