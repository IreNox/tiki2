////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_DATASETS_ILODBLOCK2DCALLBACK_H
#define CLODDY_API_DATASETS_ILODBLOCK2DCALLBACK_H

#include "CodeX/System.h"

// Declare interface ::Cloddy::API::Datasets::ILodBlock2DCallback.

namespace Cloddy { namespace API { namespace Datasets
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Callback for processing 2D LOD blocks that intersect a given rectangular processing 
   *         region.
   * 
   * @see LodBlockPartitioning2D::ProcessBlocksInField
   */
  class NO_VTABLE ILodBlock2DCallback : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Processes a single LOD block.
     * 
     * @param blockIdx The LOD block index.
     * @param blockX Absolute X-offset of the top-left corner of the LOD block,in samples.
     * @param blockY Absolute Y-offset of the top-left corner of the LOD block,in samples.
     * @param blockStep Distance between adjacent LOD block samples.
     * @param blockSubX1 Minimum X-coordinate (inclusive)of intersection LOD block subrectangle.
     * @param blockSubY1 Minimum X-coordinate (inclusive)of intersection LOD block subrectangle.
     * @param blockSubX2 Maximum X-coordinate (exclusive)of intersection LOD block subrectangle.
     * @param blockSubY2 Maximum X-coordinate (exclusive)of intersection LOD block subrectangle.
     * @param blockSubStep Distance between block samples in subrectangle.
     */
    virtual void ProcessLodBlock(int32 blockIdx, int32 blockX, int32 blockY, int32 blockStep, int32 blockSubX1, int32 blockSubY1, int32 blockSubX2, int32 blockSubY2, int32 blockSubStep) = 0;
    
    /*!
     * @brief  Begins to process a series of LOD blocks.
     * 
     * @param face The cubemap face.
     * @param width Width of the dataset being partitioned,in samples.
     * @param height Height of the dataset being partitioned,in samples.
     * @param blockSize Size of a LOD block (both width and height).Must be a power of two.
     * @param blockCount Total number of LOD blocks.
     */
    virtual void ProcessLodBlockBegin(int32 face, int32 width, int32 height, int32 blockSize, int32 blockCount) = 0;
    
    /*!
     * @brief  Ends to process a series of LOD blocks.
     */
    virtual void ProcessLodBlockEnd() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<ILodBlock2DCallback> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x2FA843D5;
    
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
