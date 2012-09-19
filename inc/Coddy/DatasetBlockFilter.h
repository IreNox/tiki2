////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_DATASETS_BUILDER_DATASETBLOCKFILTER_H
#define CLODDY_API_DATASETS_BUILDER_DATASETBLOCKFILTER_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IDatasetBlockFilter.h"

// Declare class ::Cloddy::API::Datasets::Builder::DatasetBlockFilter.

namespace Cloddy { namespace API { namespace Datasets { namespace Builder
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  class DatasetBlockFilter : public virtual IDatasetBlockFilter
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Creates a new instance of IDatasetBlockFilter that accepts dataset blocks that lie 
     *         within the given block grid region.
     * 
     * @param x <b>[>=0]</b>  X-coordinate of top-left block in region.
     * @param y <b>[>=0]</b>  Y-coordinate of top-left block in region.
     * @param width <b>[>=0]</b>  Width of block grid region.
     * @param height <b>[>=0]</b>  Height of block grid region.
     * 
     * @return <b>[not-null]</b>  The created IDatasetBlockFilter object.
     */
    static Ptr<IDatasetBlockFilter> GridRegion(int32 x, int32 y, int32 width, int32 height);
    
    /*!
     * @brief  Creates a new instance of IDatasetBlockFilter that accepts dataset blocks within a 
     *         given block index range.
     * 
     * @param firstIndex <b>[>=0]</b>  Index of first dataset block in range.
     * @param blockCount <b>[>=0]</b>  Total number of dataset blocks in range.
     * 
     * @return <b>[not-null]</b>  The created IDatasetBlockFilter object.
     */
    static Ptr<IDatasetBlockFilter> IndexRange(int32 firstIndex, int32 blockCount);
    
    virtual Ptr<IDatasetBlockFilter> And(IDatasetBlockFilter* filter);
    
    virtual Ptr<IDatasetBlockFilter> Invert();
    
    virtual Ptr<IDatasetBlockFilter> Or(IDatasetBlockFilter* filter);
    
    virtual bool FilterBlock(int32 index, int32 x, int32 y) = 0;
    
    virtual Ptr<IDatasetBlockFilter> WithOut(IDatasetBlockFilter* filter);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<DatasetBlockFilter> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xF5151BC5;
    
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
      if ((ptr = IDatasetBlockFilter::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } 

#endif
