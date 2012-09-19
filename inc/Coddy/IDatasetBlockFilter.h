////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_DATASETS_BUILDER_IDATASETBLOCKFILTER_H
#define CLODDY_API_DATASETS_BUILDER_IDATASETBLOCKFILTER_H

#include "CodeX/System.h"

// Declare interface ::Cloddy::API::Datasets::Builder::IDatasetBlockFilter.

namespace Cloddy { namespace API { namespace Datasets { namespace Builder
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Base interface for classes that perform filtering on the set of input dataset blocks 
   *         that will be used in an incremental dataset build operation.
   * 
   * A dataset block filter is a predicate that uses the following input (
   * see IDatasetBlockProvider):
   *   - Grid X-coordinate of block.
   *   - Grid Y-coordinate of block.
   *   - Linear indexGrid (row-major)of dataset block.
   */
  class NO_VTABLE IDatasetBlockFilter : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Returns a IDatasetBlockFilter object that accepts dataset block that are accepted by 
     *         this IDatasetBlockFilter instance \b and  the given one (ie. the set intersection).
     * 
     * @param filter <b>[not-null]</b>  The other dataset block filter.
     * 
     * @return <b>[not-null]</b>  The resulting IDatasetBlockFilter object.
     */
    virtual Ptr<IDatasetBlockFilter> And(IDatasetBlockFilter* filter) = 0;
    
    /*!
     * @brief  Determines whether the given dataset block shall be processed or not.
     * 
     * @param index <b>[>=0]</b>  Linear index of dataset block.
     * @param x <b>[>=0]</b>  Grid X-coordinate of dataset block.
     * @param y <b>[>=0]</b>  Grid Y-coordinate of dataset block.
     * 
     * @return \c true  if the dataset block is accepted by this filter,\c false  if it is rejected.
     */
    virtual bool FilterBlock(int32 index, int32 x, int32 y) = 0;
    
    /*!
     * @brief  Returns a IDatasetBlockFilter object that accepts dataset block that are \b not  
     *         accepted by this IDatasetBlockFilter instance (ie. the inverse set).
     * 
     * @return <b>[not-null]</b>  The resulting IDatasetBlockFilter object.
     */
    virtual Ptr<IDatasetBlockFilter> Invert() = 0;
    
    /*!
     * @brief  Returns a IDatasetBlockFilter object that accepts dataset block that are accepted by 
     *         this IDatasetBlockFilter instance \b or  the given one (ie. the set union).
     * 
     * @param filter <b>[not-null]</b>  The other dataset block filter.
     * 
     * @return <b>[not-null]</b>  The resulting IDatasetBlockFilter object.
     */
    virtual Ptr<IDatasetBlockFilter> Or(IDatasetBlockFilter* filter) = 0;
    
    /*!
     * @brief  Returns a IDatasetBlockFilter object that accepts dataset block that are accepted by 
     *         this IDatasetBlockFilter instance <b>but not</b> by the given one (ie. the set 
     *         subtraction).
     * 
     * @param filter <b>[not-null]</b>  The other dataset block filter.
     * 
     * @return <b>[not-null]</b>  The resulting IDatasetBlockFilter object.
     */
    virtual Ptr<IDatasetBlockFilter> WithOut(IDatasetBlockFilter* filter) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IDatasetBlockFilter> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x141DEEA6;
    
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
