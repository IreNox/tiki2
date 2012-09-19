////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_DATASETS_LODBLOCKPARTITIONING2D_H
#define CLODDY_API_DATASETS_LODBLOCKPARTITIONING2D_H

#include "CodeX/System.h"

// Forward declare referenced structures.

namespace Cloddy { namespace API { namespace Util { struct MapField; } } }

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Datasets { class ILodBlock2DCallback; } } }
namespace Cloddy { namespace Core { namespace Collections { template<class> class ICollection; } } }
namespace Cloddy { namespace Core { namespace Collections { template<class> class ISet; } } }

// Declare class ::Cloddy::API::Datasets::LodBlockPartitioning2D.

namespace Cloddy { namespace API { namespace Datasets
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced structures.
  
  using Cloddy::API::Util::MapField;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::Collections::ICollection;
  using Cloddy::Core::Collections::ISet;
  
  /*!
   * @brief  This class implements a partitioning scheme which is used to rearrange samples in a 
   *         dataset so that loading at runtime can be performed efficiently.
   * 
   * //TODO:Extend BlockIdx to 64-bit!
   */
  class LodBlockPartitioning2D : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Total number of LOD blocks.
     * 
     * @return <b>[>0]</b>  Number of LOD blocks.
     */
    int32 GetBlockCount();
    
    /*!
     * @brief  Effective height of the LOD block (blocks at the boundary may be smaller than the 
     *         block size).
     * 
     * This value is set by the #ForBlock method.
     */
    int32 BlockHeight;
    
    /*!
     * @brief  Index of LOD block that contains the sample at the input coordinates.
     * 
     * This value is set by the #ForCoords(int32,int32) method.
     */
    int32 BlockIdx;
    
    /*!
     * @brief  Size of a LOD block (both width and height).
     * 
     * The block size is always a power of two.
     * 
     * @return <b>[pow2]</b>  LOD block size,in samples.
     */
    int32 GetBlockSize();
    
    /*!
     * @brief  Distance between adjacent LOD block samples.
     * 
     * This value is set by the #ForBlock method.
     */
    int32 BlockStep;
    
    /*!
     * @brief  Distance between adjacent samples in the LOD block (ie. LOD block index \c 0 ).
     * 
     * @return <b>[pow2]</b>  The block stride.
     */
    int32 GetBlockStepZero();
    
    /*!
     * @brief  Relative X-coordinate of sample in the LOD block.
     * 
     * This value is set by the #ForCoords(int32,int32) method.
     */
    int32 BlockSubX;
    
    /*!
     * @brief  Relative Y-coordinate of sample in the LOD block.
     * 
     * This value is set by the #ForCoords(int32,int32) method.
     */
    int32 BlockSubY;
    
    /*!
     * @brief  Effective width of the LOD block (blocks at the boundary may be smaller than the 
     *         block size).
     * 
     * This value is set by the #ForBlock method.
     */
    int32 BlockWidth;
    
    /*!
     * @brief  Absolute X-offset of the top-left corner of the LOD block,in samples.
     * 
     * This value is set by the #ForBlock method.
     */
    int32 BlockX;
    
    /*!
     * @brief  Absolute Y-offset of the top-left corner of the LOD block,in samples.
     * 
     * This value is set by the #ForBlock method.
     */
    int32 BlockY;
    
    /*!
     * @brief  Height of the dataset being partitioned,in samples.
     * 
     * @return <b>[>0]</b>  Height of the dataset,in samples.
     */
    int32 GetDatasetHeight();
    
    /*!
     * @brief  Width of the dataset being partitioned,in samples.
     * 
     * @return <b>[>0]</b>  Width of the dataset,in samples.
     */
    int32 GetDatasetWidth();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of this class.
     * 
     * @param datasetWidth Width of the dataset being partitioned,in samples.
     * @param datasetHeight Height of the dataset being partitioned,in samples.
     * @param blockSize Size of a LOD block (both width and height).Must be a power of two.
     */
    LodBlockPartitioning2D(int32 datasetWidth, int32 datasetHeight, int32 blockSize);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of LodBlockPartitioning2D for a compressed dataset.
     * 
     * @param width <b>[>0]</b>  Width of the dataset,in samples.
     * @param height <b>[>0]</b>  Height of the dataset,in samples.
     * @param channels <b>[>0]</b>  Number of dataset channels.
     * 
     * @return <b>[not-null]</b>  The created LodBlockPartitioning2D object.
     */
    static Ptr<LodBlockPartitioning2D> ForCompressed(int32 width, int32 height, int32 channels);
    
    /*!
     * @brief  Creates a new instance of LodBlockPartitioning2D for a sparse dataset.
     * 
     * @param width <b>[>0]</b>  Width of the dataset,in samples.
     * @param height <b>[>0]</b>  Height of the dataset,in samples.
     * 
     * @return <b>[not-null]</b>  The created LodBlockPartitioning2D object.
     */
    static Ptr<LodBlockPartitioning2D> ForSparse(int32 width, int32 height);
    
    /*!
     * @brief  Creates a new instance of LodBlockPartitioning2D for an uncompressed dataset.
     * 
     * @param width <b>[>0]</b>  Width of the dataset,in samples.
     * @param height <b>[>0]</b>  Height of the dataset,in samples.
     * 
     * @return <b>[not-null]</b>  The created LodBlockPartitioning2D object.
     */
    static Ptr<LodBlockPartitioning2D> ForUncompressed(int32 width, int32 height);
    
    /*!
     * @brief  Returns information about a LOD block.
     * 
     * The following fields are used by this method:
     *   - <i>out </i>#BlockX
     *   - <i>out </i>#BlockY
     *   - <i>out </i>#BlockStep
     *   - <i>out </i>#BlockWidth
     *   - <i>out </i>#BlockHeight
     * 
     * @param blockIdx <b>[0..#GetBlockCount-1]</b>  The LOD block index.
     */
    void ForBlock(int32 blockIdx);
    
    /*!
     * @brief  Determines all LOD blocks that intersect with the given rectangle and adds their 
     *         block indices to \e blockIndices .
     * 
     * The following fields are modified by this method and contain undefined values after this 
     * method returns.
     *   - <i>out </i>#BlockIdx
     *   - <i>out </i>#BlockSubX
     *   - <i>out </i>#BlockSubY
     *   - <i>out </i>#BlockX
     *   - <i>out </i>#BlockY
     *   - <i>out </i>#BlockStep
     *   - <i>out </i>#BlockWidth
     *   - <i>out </i>#BlockHeight
     * 
     * @param x1 X-coordinate of top-left corner of rectangle.
     * @param y1 Y-coordinate of top-left corner of rectangle.
     * @param x2 X-coordinate of bottom-right corner of rectangle.
     * @param y2 Y-coordinate of bottom-right corner of rectangle.
     * @param blockIndexOffset Offset value to add to found LOD block indices before adding them 
     * to \e blockIndices .
     * @param blockIndices <b>[not-null]</b>  Output set for found LOD block indices.
     */
    void ForCoords(int32 x1, int32 y1, int32 x2, int32 y2, int32 blockIndexOffset, ISet<Prm<int32> >* blockIndices);
    
    /*!
     * @brief  Returns the LOD block index and block offsets for the given set of coordinates.
     * 
     * The following fields are used by this method:
     *   - <i>out </i>#BlockIdx
     *   - <i>out </i>#BlockSubX
     *   - <i>out </i>#BlockSubY
     * 
     * @param x X-component of input coordinates.
     * @param y Y-component of input coordinates.
     */
    void ForCoords(int32 x, int32 y);
    
    /*!
     * @brief  Processes all LOD blocks that intersect the given sample field by invoking the given 
     *         callback for them.
     * 
     * @param field The map field.
     * @param callback <b>[not-null]</b>  The processor callback to use.
     */
    void ProcessBlocksInField(const MapField& field, ILodBlock2DCallback* callback);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Number of LOD blocks.
     */
    int32 blockCount;
    
    /*!
     * @brief  Size of a LOD block (both width and height).
     * 
     * The block size is always a power of two.
     */
    int32 blockSize;
    
    /*!
     * @brief  Is equal to #blockSize - 1.
     */
    int32 blockSizeMask;
    
    /*!
     * @brief  Logarithm of base two of #blockSize.
     */
    int32 blockSizeShift;
    
    /*!
     * @brief  Height of the dataset being partitioned,in samples.
     */
    int32 datasetHeight;
    
    /*!
     * @brief  Width of the dataset being partitioned,in samples.
     */
    int32 datasetWidth;
    
    /*!
     * @brief  Number of LOD levels.
     */
    int32 levelCount;
    
    /*!
     * @brief  Index of first LOD block per LOD level.
     */
    Array<int32> levelFirst;
    
    /*!
     * @brief  Offset along dataset X-axis per LOD level.
     */
    Array<int32> levelOffsetX;
    
    /*!
     * @brief  Offset along dataset X-axis per LOD level.
     */
    Array<int32> levelOffsetY;
    
    /*!
     * @brief  Step value for each LOD level.
     */
    Array<int32> levelStep;
    
    /*!
     * @brief  Stride value to use for computing the index of a LOD block in its LOD level.
     */
    Array<int32> levelStride;
    
    /*!
     * @brief  Bitmask used to enforce the minimum LOD block size.
     */
    int32 mask;
    
    /*!
     * @brief  Logarithm of base two of:#mask+1.
     */
    int32 maskBit;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Computes the number of LOD block necessary for a LodBlockPartitioning2D object of 
     *         the given dimensions.
     * 
     * @param width Width of the dataset being partitioned,in samples.
     * @param height Height of the dataset being partitioned,in samples.
     * @param blockSize Size of a LOD block (both width and height).
     * 
     * @return The number of LOD blocks.
     */
    static int32 ComputeBlockCount(int32 width, int32 height, int32 blockSize);
    
    /*!
     * @brief  Recursively finds LOD blocks that intersect with the current sample field.
     * 
     * @param x1 X-coordinate of top-left sample in field.
     * @param y1 Y-coordinate of top-left sample in field.
     * @param x2 X-coordinate of bottom sample in field.
     * @param y2 Y-coordinate of bottom-right sample in field.
     * @param blockIndexOffset LOD block index offset value.
     * @param blockIndices Output set for found LOD block indices.
     * @param stepX Step of sample field along X-axis,in samples.
     * @param stepY Step of sample field along Y-axis,in samples.
     */
    void ForCoords(int32 x1, int32 y1, int32 x2, int32 y2, int32 blockIndexOffset, ICollection<Prm<int32> >* blockIndices, int32 stepX, int32 stepY);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<LodBlockPartitioning2D> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xFD6F5EBB;
    
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
  
} } } 

#endif
