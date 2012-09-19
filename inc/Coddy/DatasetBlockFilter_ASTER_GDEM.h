////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_DATASETS_BUILDER_DEM_DATASETBLOCKFILTER_ASTER_GDEM_H
#define CLODDY_API_DATASETS_BUILDER_DEM_DATASETBLOCKFILTER_ASTER_GDEM_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/DatasetBlockFilter.h"

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Datasets { namespace Builder { namespace DEM { class DatasetBlockProvider_ASTER_GDEM; } } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Files { class Path; } } } }

// Declare class ::Cloddy::API::Datasets::Builder::DEM::DatasetBlockFilter_ASTER_GDEM.

namespace Cloddy { namespace API { namespace Datasets { namespace Builder { namespace DEM
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced classes.
  
  using Cloddy::API::Datasets::Builder::DatasetBlockFilter;
  using Cloddy::Core::IO::Files::Path;
  
  class DatasetBlockFilter_ASTER_GDEM : public DatasetBlockFilter
  {
    // Declare friend classes.
    
    friend class DatasetBlockProvider_ASTER_GDEM;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual bool FilterBlock(int32 index, int32 x, int32 y);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Path to the directory that contains the ASTER GDEM granule files.
     */
    Ptr<Path> granulesDir;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of DatasetBlockFilter_ASTER_GDEM.
     * 
     * @param granulesDir Path to the directory that contains the ASTER GDEM granule files.
     */
    DatasetBlockFilter_ASTER_GDEM(Path* granulesDir);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<DatasetBlockFilter_ASTER_GDEM> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xA05A5869;
    
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
  
} } } } } 

#endif
