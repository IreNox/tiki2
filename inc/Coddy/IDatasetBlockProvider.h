////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_DATASETS_BUILDER_IDATASETBLOCKPROVIDER_H
#define CLODDY_API_DATASETS_BUILDER_IDATASETBLOCKPROVIDER_H

#include "CodeX/System.h"

// Include referenced structures.

#include "Cloddy/Vec2I.h"

// Include referenced interfaces.

#include "CodeX/IDisposable.h"

// Forward declare referenced classes.

namespace CodeX { namespace System { class ByteBuffer; } }

// Declare interface ::Cloddy::API::Datasets::Builder::IDatasetBlockProvider.

namespace Cloddy { namespace API { namespace Datasets { namespace Builder
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced structures.
  
  using Cloddy::Core::Math::Vectors::Vec2I;
  
  // Use referenced interfaces.
  
  using CodeX::System::IDisposable;
  
  // Use referenced classes.
  
  using CodeX::System::ByteBuffer;
  
  /*!
   * @brief  Base interface for classes that provide gridded sample data for a rectangular dataset.
   * 
   * An IDatasetBlockProvider instance provides equally sized blocks of data.The whole dataset is 
   * partitioned into a grid:
   * <pre>
   *     .         GridSize.X (here: 5)
   *     .      *-----*-----*-----*-----*
   *     .   
   *     .   +-----+-----+-----+-----+-----+    
   *     .   | 0,0 | 1,0 | 2,0 | 3,0 | 4,0 |   *
   *     .   |  0  |  1  |  2  |  3  |  4  |   |
   *     .   +-----+-----+-----+-----+-----+   |
   *     .   | 0,1 | 1,1 | 2,1 | 3,1 | 4,1 |   *
   *     .   |  5  |  6  |  7  |  8  |  9  |   |
   *     .   +-----+-----+-----+-----+-----+   | GridSize.Y (here: 4)
   *     .   | 0,2 | 1,2 | 2,2 | 3,2 | 4,2 |   *
   *     .   | 10  | 11  | 12  | 13  | 14  |   |
   *     .   +-----+-----+-----+-----+-----+   |
   *     .   | 0,3 | 1,3 | 2,3 | 3,3 | 4,3 |   *
   *     .   | 15  | 16  | 17  | 18  | 19  |    
   *     .   +-----+-----+-----+-----+-----+    
   *     .    
   *     .         *******
   *     .   BlockSize.X (here: 6)
   *     .
   *     .   +-----+   
   *     .   | X,Y |   X,Y := Grid X- and Y-coordinates of dataset block.  
   *     .   | IDX |   IDX := Linear index (row-major) of dataset block.
   *     .   +-----+
   * </pre>
   */
  class NO_VTABLE IDatasetBlockProvider : public virtual IDisposable
  {
    // ---------------------------------------------------------------------------------------------
    // Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The number of dataset blocks in the grid.
     * 
     * @return <b>[>0]</b>  The number of dataset blocks.
     */
    virtual int32 GetBlockCount() = 0;
    
    /*!
     * @brief  Size of a single dataset block.
     * 
     * @return The block size.
     */
    virtual Vec2I GetBlockSize() = 0;
    
    /*!
     * @brief  The number of dataset channels.
     * 
     * @return <b>[>0]</b>  The number of dataset channels.
     */
    virtual int32 GetChannels() = 0;
    
    /*!
     * @brief  Size of the whole dataset,in samples 
     * 
     * The dataset size may be larger than the grid size multiplied with the block size.In this 
     * case,the additional pixels are appended to the right and bottom edges of the rightmost resp. 
     * bottommost grid blocks.
     * 
     * @return The dataset size.
     */
    virtual Vec2I GetDatasetSize() = 0;
    
    /*!
     * @brief  Size of the dataset grid.
     * 
     * @return The grid size.
     */
    virtual Vec2I GetGridSize() = 0;
    
    /*!
     * @brief  Returns the maximum block size.
     * 
     * @return The maximum block size.
     */
    virtual Vec2I GetMaximumBlockSize() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Returns the data of a dataset block.
     * 
     * @param block Grid coordinates of the dataset block.
     * @param buffer <b>[not-null]</b>  Output buffer for dataset block data (must have at 
     * least #GetBlockSize bytes remaining).
     */
    virtual void GetBlock(const Vec2I& block, ByteBuffer* buffer) = 0;
    
    /*!
     * @brief  Computes the effective block size of the given dataset block.
     * 
     * Blocks at the right and bottom edges of the grid may be smaller than indicated 
     * by #GetBlockSize.The effective block size will report a smaller size in these cases.
     * 
     * @param block Grid coordinates of the dataset block.
     * 
     * @return The effective block size.
     */
    virtual Vec2I GetEffectiveBlockSize(const Vec2I& block) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IDatasetBlockProvider> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x7A6DA56D;
    
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
      if ((ptr = IDisposable::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
} } } } 

#endif
