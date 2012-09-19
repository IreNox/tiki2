////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_DATASETS_BUILDER_DATASETBUILDER_RECT_1_0_INCREMENTAL_H
#define CLODDY_API_DATASETS_BUILDER_DATASETBUILDER_RECT_1_0_INCREMENTAL_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/DatasetBuilder2.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Datafiles { class IDatafile; } } }
namespace Cloddy { namespace API { namespace Datasets { namespace Builder { class IDatasetBlockFilter; } } } }
namespace Cloddy { namespace API { namespace Datasets { namespace Builder { class IDatasetBlockProvider; } } } }
namespace Cloddy { namespace API { namespace Datasets { class IDataset; } } }
namespace Cloddy { namespace API { namespace Util { namespace Progress { class IProgressMonitor; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Datasets { namespace Builder { class DatasetBuilder2; } } } }
namespace Cloddy { namespace API { namespace Datasets { namespace Builder { class DatasetBuilderProgress; } } } }

// Declare class ::Cloddy::API::Datasets::Builder::DatasetBuilder_Rect_1_0_Incremental.

namespace Cloddy { namespace API { namespace Datasets { namespace Builder
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Datafiles::IDatafile;
  using Cloddy::API::Datasets::IDataset;
  using Cloddy::API::Util::Progress::IProgressMonitor;
  
  class DatasetBuilder_Rect_1_0_Incremental : public DatasetBuilder2
  {
    // Declare friend classes.
    
    friend class DatasetBuilder2;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual void Prepare(IProgressMonitor* progressMonitor);
    
    virtual void Run(IProgressMonitor* argument);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
  protected:
    
    virtual void DisposeManaged();
    
    virtual void DisposeManagedChildren();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The dataset block data provider.
     */
    Ptr<IDatasetBlockProvider> blockProvider;
    
    /*!
     * @brief  The dataset being updated.
     */
    Ptr<IDataset> dataset;
    
    /*!
     * @brief  The dataset block filter to use.
     */
    Ptr<IDatasetBlockFilter> filter;
    
    /*!
     * @brief  Dataset build progress information.
     */
    Ptr<DatasetBuilderProgress> progress;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of DatasetBuilder_Rect_1_0_Incremental.
     * 
     * @param blockProvider The dataset block provider to use.
     * @param datafile The output datafile.
     * @param progress The dataset build progress object.
     * @param filter The dataset block filter to use.
     */
    DatasetBuilder_Rect_1_0_Incremental(IDatasetBlockProvider* blockProvider, IDatafile* datafile, DatasetBuilderProgress* progress, IDatasetBlockFilter* filter);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Computes a space filling curve which depicts the order in which the dataset blocks 
     *         will be processed.
     * 
     * @return An dataset block processing order,as XY tuples.
     */
    Array<int32> ComputeSpaceFillingCurve();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<DatasetBuilder_Rect_1_0_Incremental> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x13FDE238;
    
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
      if ((ptr = DatasetBuilder2::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } 

#endif
