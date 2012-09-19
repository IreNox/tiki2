////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_DATASETS_LODBLOCKPARTITIONING3D_H
#define CLODDY_API_DATASETS_LODBLOCKPARTITIONING3D_H

#include "CodeX/System.h"

// Include referenced structures.

#include "Cloddy/Vec4I.h"

// Declare class ::Cloddy::API::Datasets::LodBlockPartitioning3D.

namespace Cloddy { namespace API { namespace Datasets
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced structures.
  
  using Cloddy::Core::Math::Vectors::Vec4I;
  
  /*!
   * @brief  This class implements a partitioning scheme which is used to rearrange samples in a 
   *         dataset so that loading at runtime can be performed efficiently.
   */
  class LodBlockPartitioning3D : public virtual Object
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
     * @brief  Effective depth of the LOD block (blocks at the boundary may be smaller than the 
     *         block size).
     * 
     * This value is set by the #ForBlock method.
     */
    int32 BlockDepth;
    
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
     * This value is set by the #ForCoords method.
     */
    int32 BlockIdx;
    
    /*!
     * @brief  Absolute X-offset of the top-left corner of the LOD block,in samples.
     * 
     * This value is set by the #ForBlock method.
     */
    int32 BlockOffsetX;
    
    /*!
     * @brief  Absolute Y-offset of the top-left corner of the LOD block,in samples.
     * 
     * This value is set by the #ForBlock method.
     */
    int32 BlockOffsetY;
    
    /*!
     * @brief  Absolute ^Z-offset of the top-left corner of the LOD block,in samples.
     * 
     * This value is set by the #ForBlock method.
     */
    int32 BlockOffsetZ;
    
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
    int32 BlockStride;
    
    /*!
     * @brief  Effective width of the LOD block (blocks at the boundary may be smaller than the 
     *         block size).
     * 
     * This value is set by the #ForBlock method.
     */
    int32 BlockWidth;
    
    /*!
     * @brief  Relative X-coordinate of sample in the LOD block.
     * 
     * This value is set by the #ForCoords method.
     */
    int32 BlockX;
    
    /*!
     * @brief  Relative Y-coordinate of sample in the LOD block.
     * 
     * This value is set by the #ForCoords method.
     */
    int32 BlockY;
    
    /*!
     * @brief  Relative Y-coordinate of sample in the LOD block.
     * 
     * This value is set by the #ForCoords method.
     */
    int32 BlockZ;
    
    /*!
     * @brief  Size of the dataset being partitioned,in samples.
     * 
     * @return <b>[>0]</b>  Size of the dataset,in samples.
     */
    int32 GetSize();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of LodBlockPartitioning3D.
     * 
     * @param size <b>[>0]</b>  The volume size (width,height and depth).
     * @param blockSize <b>[pow2]</b>  Size of a LOD block (both width and height).Must be a power 
     * of two.
     */
    LodBlockPartitioning3D(int32 size, int32 blockSize);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Returns information about a LOD block.
     * 
     * The following fields are used by this method:
     *   - <i>out </i>#BlockOffsetX
     *   - <i>out </i>#BlockOffsetY
     *   - <i>out </i>#BlockStride
     *   - <i>out </i>#BlockWidth
     *   - <i>out </i>#BlockHeight
     * 
     * @param blockIdx <b>[0..#GetBlockCount-1]</b>  The LOD block index.
     */
    void ForBlock(int32 blockIdx);
    
    /*!
     * @brief  Returns the LOD block index and block offsets for the given set of coordinates.
     * 
     * The following fields are used by this method:
     *   - <i>out </i>#BlockIdx
     *   - <i>out </i>#BlockX
     *   - <i>out </i>#BlockY
     *   - <i>out </i>#BlockZ
     * 
     * @param x X-component of input coordinates.
     * @param y Y-component of input coordinates.
     * @param z Z-component of input coordinates.
     */
    void ForCoords(int32 x, int32 y, int32 z);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Number of LOD blocks.
     */
    int32 blockCount;
    
    /*!
     * @brief  Index of first LOD block per LOD level.
     */
    Array<int32> blockFirst;
    
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
     * @brief  Stride value to use for computing the index of a LOD block in its LOD level.
     */
    Array<int32> blockStride;
    
    /*!
     * @brief  Bitmask used to enforce the minimum LOD block size.
     */
    int32 mask;
    
    /*!
     * @brief  Logarithm of base two of #mask+1.
     */
    int32 maskBit;
    
    /*!
     * @brief  The volume size (width,height and depth).
     */
    int32 size;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    static Vec4I Next(int32 ofsX, int32 ofsY, int32 ofsZ, int32 stride);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<LodBlockPartitioning3D> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xFD6F5EBC;
    
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
