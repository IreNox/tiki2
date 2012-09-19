////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_DATASETS_BUILDER_DATASETBLOCKFILTER_GRIDREGION_H
#define CLODDY_API_DATASETS_BUILDER_DATASETBLOCKFILTER_GRIDREGION_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/DatasetBlockFilter.h"

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Datasets { namespace Builder { class DatasetBlockFilter; } } } }

// Declare class ::Cloddy::API::Datasets::Builder::DatasetBlockFilter_GridRegion.

namespace Cloddy { namespace API { namespace Datasets { namespace Builder
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  class DatasetBlockFilter_GridRegion : public DatasetBlockFilter
  {
    // Declare friend classes.
    
    friend class DatasetBlockFilter;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual bool FilterBlock(int32 index, int32 x, int32 y);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    int32 x1;
    
    int32 x2;
    
    int32 y1;
    
    int32 y2;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    DatasetBlockFilter_GridRegion(int32 x1, int32 y1, int32 x2, int32 y2);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<DatasetBlockFilter_GridRegion> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xA1FAA1DE;
    
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
      if ((ptr = DatasetBlockFilter::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } 

#endif
