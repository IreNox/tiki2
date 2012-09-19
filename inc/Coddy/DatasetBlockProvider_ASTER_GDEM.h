////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_DATASETS_BUILDER_DEM_DATASETBLOCKPROVIDER_ASTER_GDEM_H
#define CLODDY_API_DATASETS_BUILDER_DEM_DATASETBLOCKPROVIDER_ASTER_GDEM_H

#include "CodeX/System.h"

// Include referenced structures.

#include "Cloddy/Vec2I.h"

// Include referenced classes.

#include "Cloddy/DatasetBlockProvider.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Datasets { namespace Builder { class IDatasetBlockFilter; } } } }
namespace Cloddy { namespace API { namespace Datasets { class IDataset; } } }
namespace Cloddy { namespace API { namespace Imaging { class IImage; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Datasets { namespace Builder { namespace DEM { class DatasetBlockFilter_ASTER_GDEM; } } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Files { class Path; } } } }
namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::API::Datasets::Builder::DEM::DatasetBlockProvider_ASTER_GDEM.

namespace Cloddy { namespace API { namespace Datasets { namespace Builder { namespace DEM
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced structures.
  
  using Cloddy::Core::Math::Vectors::Vec2I;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Datasets::Builder::IDatasetBlockFilter;
  using Cloddy::API::Datasets::IDataset;
  using Cloddy::API::Imaging::IImage;
  
  // Use referenced classes.
  
  using Cloddy::API::Datasets::Builder::DatasetBlockProvider;
  using Cloddy::Core::IO::Files::Path;
  using CodeX::System::ByteBuffer;
  
  /*!
   * @brief  An IDatasetBlockProvider implementation for the ASTER GDEM dataset (see http://www.
   *         gdem.aster.ersdac.or.jp.
   * 
   * An imported Cloddy dataset for ASTER GDEM will have the following georefencing properties:
   * <pre>
   *     Dataset XY        | Latitude | Longitude |
   *     ------------------+----------+-----------+
   *     0, 0              | N90      | W180      |
   *     width-1, 0        | N90      | E180      |
   *     0, height-1       | S90      | W180      |
   *     width-1, height-1 | S90      | E180      |
   * </pre>
   */
  class DatasetBlockProvider_ASTER_GDEM : public DatasetBlockProvider
  {
    // Declare friend classes.
    
    friend class DatasetBlockFilter_ASTER_GDEM;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual Vec2I GetBlockSize();
    
    virtual int32 GetChannels();
    
    virtual Vec2I GetDatasetSize();
    
    /*!
     * @brief  Returns an IDatasetBlockFilter object that filters out all dataset blocks for which 
     *         the granule data file is missing.
     * 
     * @return <b>[not-null]</b>  The dataset block filter.
     */
    Ptr<IDatasetBlockFilter> GetExistingBlocksFilter();
    
    virtual Vec2I GetGridSize();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of DatasetBlockProvider_ASTER_GDEM.
     * 
     * @param granulesDir <b>[not-null]</b>  Path to the directory that contains the ASTER GDEM 
     * granule files.
     * @param srtm3Path <b>[not-null]</b>  Path to the combined SRTM3 Cloddy dataset.
     * @param oceanMaskPath <b>[not-null]</b>  Path to the ocean mask file.
     */
    DatasetBlockProvider_ASTER_GDEM(Path* granulesDir, Path* srtm3Path, Path* oceanMaskPath);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Returns the local granule ID for the given dataset block.
     * 
     * @param block Grid coordinates of the dataset block.
     * 
     * @return <b>[not-null]</b>  The granule ID.
     */
    static String GetGranuleId(const Vec2I& block);
    
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
     * @brief  Size of the SRTM3 dataset.
     */
    static const Vec2I Srtm3Size;
    
    Ptr<IDatasetBlockFilter> existingBlocksFilter;
    
    /*!
     * @brief  Path to the directory that contains the ASTER GDEM granule files.
     */
    Ptr<Path> granulesDir;
    
    /*!
     * @brief  Path to the ocean mask dataset file.
     */
    Ptr<Path> oceanMaskPath;
    
    /*!
     * @brief  The SRTM3 dataset.
     */
    Ptr<IDataset> srtm3;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    static String GetZipEntryNameForGranule(const Vec2I& block, bool demOrNum);
    
    static String GetZipFileNameForGranule(const Vec2I& block);
    
    Ptr<IImage> GetAsterTile(const Vec2I& block, const Vec2I& blockSize);
    
    Ptr<IImage> GetBlendTile(const Vec2I& block, const Vec2I& blockSize);
    
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
     * @brief  Returns the interpolated SRTM3 tile for the given dataset block.
     * 
     * @param block The block coordinates.
     * @param blockSize The block size.
     * 
     * @return <b>[not-null]</b>  The block tile image.
     */
    Ptr<IImage> GetSrtm3Tile(const Vec2I& block, const Vec2I& blockSize);
    
    /*!
     * @brief  Returns a tile of the SRTM3 dataset.
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
    Ptr<IImage> GetSrtm3Tile(int32 x1, int32 y1, int32 x2, int32 y2);
    
    Ptr<IImage> GetTile(const Vec2I& block);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<DatasetBlockProvider_ASTER_GDEM> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x401E2C6;
    
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
