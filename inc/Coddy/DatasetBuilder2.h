////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_DATASETS_BUILDER_DATASETBUILDER2_H
#define CLODDY_API_DATASETS_BUILDER_DATASETBUILDER2_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/Operation.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Datafiles { class IDatafile; } } }
namespace Cloddy { namespace API { namespace Datasets { namespace Builder { class IDatasetBlockFilter; } } } }
namespace Cloddy { namespace API { namespace Datasets { namespace Builder { class IDatasetBlockProvider; } } } }
namespace Cloddy { namespace API { namespace Util { namespace Progress { class IOperation; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Datasets { namespace Builder { class DatasetBuilderProgress; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Files { class Path; } } } }

// Declare class ::Cloddy::API::Datasets::Builder::DatasetBuilder2.

namespace Cloddy { namespace API { namespace Datasets { namespace Builder
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Datafiles::IDatafile;
  using Cloddy::API::Util::Progress::IOperation;
  
  // Use referenced classes.
  
  using Cloddy::API::Util::Progress::Operation;
  using Cloddy::Core::IO::Files::Path;
  
  class DatasetBuilder2 : public Operation
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual String GetName();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Builds a rectangular dataset from the given IDatasetBlockProvider.
     * 
     * The file depicted by \e datasetFile  will be opened iff it exists,otherwise a new file will 
     * be created.
     * 
     * The provided DatasetBuilderProgress object can be used to resume a previous dataset build 
     * operation.During a build operation,the progress object is updated.When the operation has 
     * finished resp. is cancelled (see IOperation::Cancel),the progress object can be serialized 
     * to a file or stream (see DatasetBuilderProgress::Save(Path*) 
     * and DatasetBuilderProgress::Save(IDataStream*)).Later,the progress object can be loaded and 
     * passed to this method in order to resume the operation.
     * 
     * @param blockProvider <b>[not-null]</b>  The dataset block data provider.
     * @param datasetFile <b>[not-null]</b>  The dataset file.
     * @param progress <b>[not-null]</b>  The dataset build progress information object to use.
     * @param filter Optional dataset block filter to use.
     * 
     * @return <b>[not-null]</b>  An IOperation that performs the actual work.
     */
    static Ptr<IOperation> BuildRectIncremental(IDatasetBlockProvider* blockProvider, Path* datasetFile, DatasetBuilderProgress* progress, IDatasetBlockFilter* filter);
    
    /*!
     * @brief  Builds a rectangular dataset from the given IDatasetBlockProvider.
     * 
     * The provided DatasetBuilderProgress object can be used to resume a previous dataset build 
     * operation.During a build operation,the progress object is updated.When the operation has 
     * finished resp. is cancelled (see IOperation::Cancel),the progress object can be serialized 
     * to a file or stream (see DatasetBuilderProgress::Save(Path*) 
     * and DatasetBuilderProgress::Save(IDataStream*)).Later,the progress object can be loaded and 
     * passed to this method in order to resume the operation.
     * 
     * @param blockProvider <b>[not-null]</b>  The dataset block data provider.
     * @param datasetFile <b>[not-null]</b>  The dataset file.
     * @param progress <b>[not-null]</b>  The dataset build progress information object to use.
     * @param filter Optional dataset block filter to use.
     * 
     * @return <b>[not-null]</b>  An IOperation that performs the actual work.
     */
    static Ptr<IOperation> BuildRectIncremental(IDatasetBlockProvider* blockProvider, IDatafile* datasetFile, DatasetBuilderProgress* progress, IDatasetBlockFilter* filter);
    
    /*!
     * @brief  Update progress.
     * 
     * @param progress <b>[not-null]</b>  The progress data.
     * @param finishedBlocks <b>[>=0]</b>  The number of finished blocks.
     */
    static void UpdateProgress(DatasetBuilderProgress* progress, int32 finishedBlocks);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<DatasetBuilder2> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xB4999683;
    
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
      if ((ptr = Operation::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } 

#endif
