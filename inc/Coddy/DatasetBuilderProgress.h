////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_DATASETS_BUILDER_DATASETBUILDERPROGRESS_H
#define CLODDY_API_DATASETS_BUILDER_DATASETBUILDERPROGRESS_H

#include "CodeX/System.h"

// Include referenced structures.

#include "Cloddy/Vec2I.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Datasets { namespace Builder { class IDatasetBlockProvider; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Streams { class IDataStream; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace IO { namespace Files { class Path; } } } }

// Declare class ::Cloddy::API::Datasets::Builder::DatasetBuilderProgress.

namespace Cloddy { namespace API { namespace Datasets { namespace Builder
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced structures.
  
  using Cloddy::Core::Math::Vectors::Vec2I;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::IO::Streams::IDataStream;
  
  // Use referenced classes.
  
  using Cloddy::Core::IO::Files::Path;
  
  /*!
   * @brief  The DatasetBuilderProgress class represents the current state of an incremental 
   *         dataset build operation.
   * 
   * @see IDatasetBlockProvider
   * @see IDatasetBlockFilter
   */
  class DatasetBuilderProgress : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Total number of dataset blocks.
     * 
     * @return <b>[>0]</b>  The number of dataset blocks.
     */
    int32 GetBlockCount();
    
    /*!
     * @brief  Size of a single dataset block,in samples.
     * 
     * @return The block size.
     */
    Vec2I GetBlockSize();
    
    /*!
     * @brief  Size of the whole dataset,in samples.
     * 
     * @return The dataset size.
     */
    Vec2I GetDatasetSize();
    
    /*!
     * @brief  The number of dataset blocks that have already been processed.
     * 
     * @return <b>[0..#GetBlockCount]</b>  The number of finished blocks.
     */
    int32 GetFinishedBlocksCount();
    
    /*!
     * @brief  Size of the dataset grid,in blocks.
     * 
     * @return The grid size.
     */
    Vec2I GetGridSize();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of DatasetBuilderProgress.
     * 
     * @param datasetSize The dataset size (see #GetDatasetSize).
     * @param gridSize The dataset grid size (see #GetGridSize).
     * @param blockSize The dataset block size (see #GetBlockSize).
     */
    DatasetBuilderProgress(const Vec2I& datasetSize, const Vec2I& gridSize, const Vec2I& blockSize);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of DatasetBuilderProgress for the given dataset block 
     *         provider.
     * 
     * @param provider <b>[not-null]</b>  The dataset block provider.
     * 
     * @return <b>[not-null]</b>  The DatasetBuilderProgress object.
     */
    static Ptr<DatasetBuilderProgress> ForProvider(IDatasetBlockProvider* provider);
    
    /*!
     * @brief  Reads dataset build progress information from the given file.
     * 
     * @param filePath <b>[not-null]</b>  The file path.
     * 
     * @return <b>[not-null]</b>  The read progress information.
     */
    static Ptr<DatasetBuilderProgress> Load(Path* filePath);
    
    /*!
     * @brief  Reads dataset build progress information from the given data stream.
     * 
     * @param stream <b>[not-null]</b>  The data stream.
     * 
     * @return <b>[not-null]</b>  The read progress information.
     */
    static Ptr<DatasetBuilderProgress> Load(IDataStream* stream);
    
    /*!
     * @brief  Returns if the given dataset block has already been processed.
     * 
     * @param block The grid coordinates of the dataset block.
     * 
     * @return \c true  if the block has been processed,\c false  if not.
     */
    bool IsFinished(const Vec2I& block);
    
    /*!
     * @brief  Writes dataset build progress information to the given file.
     * 
     * @param filePath <b>[not-null]</b>  The file path.
     */
    void Save(Path* filePath);
    
    /*!
     * @brief  Writes dataset build progress information to the given data stream.
     * 
     * @param stream <b>[not-null]</b>  The data stream.
     */
    void Save(IDataStream* stream);
    
    /*!
     * @brief  Marks the given block as finished.
     * 
     * @param block The grid coordinates.
     * @param finished \c true  to mark the block as finished,\c false  to mark it as unfinished.
     */
    void SetFinished(const Vec2I& block, bool finished);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constants
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Name of the file format used by this class.
     */
    static const String FileFormatName;
    
    /*!
     * @brief  Magic value that identifies persistent dataset build progress information.
     */
    static const int64 Magic = (int64) 0x2B3FFCA9CC9B610FULL;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Size of a single dataset block,in samples.
     */
    Vec2I blockSize;
    
    /*!
     * @brief  Size of the whole dataset,in samples.
     */
    Vec2I datasetSize;
    
    /*!
     * @brief  Row-major matrix that stores a finished flag per dataset block.
     */
    Array<bool> finishedBlocks;
    
    /*!
     * @brief  The number of dataset blocks that have already been processed.
     */
    int32 finishedBlocksCount;
    
    /*!
     * @brief  Size of the dataset grid,in blocks.
     */
    Vec2I gridSize;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of DatasetBuilderProgress.
     * 
     * @param datasetSize The dataset size.
     * @param gridSize The grid size.
     * @param blockSize The block size.
     * @param finishedBlocks Finished blocks.
     * @param finishedBlocksCount Number of finished blocks.
     */
    DatasetBuilderProgress(const Vec2I& datasetSize, const Vec2I& gridSize, const Vec2I& blockSize, Array<bool> finishedBlocks, int32 finishedBlocksCount);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<DatasetBuilderProgress> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xA84FA162;
    
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
      return (void*) 0;
    }
  };
  
} } } } 

#endif
