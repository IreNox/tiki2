////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_DATASETS_DATASETDECOMPRESSOR_1_0_H
#define CLODDY_API_DATASETS_DATASETDECOMPRESSOR_1_0_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/Operation.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Datasets { class IDataset; } } }
namespace Cloddy { namespace API { namespace Util { namespace Progress { class IProgressMonitor; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Datasets { class Dataset_1_0_Cube_Compressed; } } }
namespace Cloddy { namespace API { namespace Datasets { class Dataset_1_0_Cube_Uncompressed; } } }
namespace Cloddy { namespace API { namespace Datasets { class Dataset_1_0_Rect_Compressed; } } }
namespace Cloddy { namespace API { namespace Datasets { class Dataset_1_0_Rect_Uncompressed; } } }
namespace Cloddy { namespace Core { namespace IO { namespace Files { class Path; } } } }

// Declare class ::Cloddy::API::Datasets::DatasetDecompressor_1_0.

namespace Cloddy { namespace API { namespace Datasets
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Util::Progress::IProgressMonitor;
  
  // Use referenced classes.
  
  using Cloddy::API::Util::Progress::Operation;
  using Cloddy::Core::IO::Files::Path;
  
  /*!
   * @brief  An implementation of the IOperation interface that decompressed a dataset of version 1.
   *         0 
   */
  class DatasetDecompressor_1_0 : public Operation
  {
    // Declare friend classes.
    
    friend class Dataset_1_0_Cube_Compressed;
    friend class Dataset_1_0_Cube_Uncompressed;
    friend class Dataset_1_0_Rect_Compressed;
    friend class Dataset_1_0_Rect_Uncompressed;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual String GetName();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void Prepare(IProgressMonitor* progressMonitor);
    
    virtual void Run(IProgressMonitor* argument);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
  protected:
    
    virtual void DisposeManaged();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The input dataset.
     */
    Ptr<IDataset> inputDataset;
    
    /*!
     * @brief  The file path to the output dataset.
     */
    Ptr<Path> outputDatasetFilePath;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of DatasetDecompressor_1_0.
     * 
     * @param inputDataset The input dataset.
     * @param outputDatasetFilePath The file path to the output dataset.
     */
    DatasetDecompressor_1_0(IDataset* inputDataset, Path* outputDatasetFilePath);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Decompresses a dataset that uses a square as base geometry.
     * 
     * @param outputDataset The output dataset.
     * @param progressMonitor The progress monitor.
     */
    void DecompressCube(IDataset* outputDataset, IProgressMonitor* progressMonitor);
    
    /*!
     * @brief  Decompresses a dataset that uses a square as base geometry.
     * 
     * @param outputDataset The output dataset.
     * @param progressMonitor The progress monitor.
     */
    void DecompressRect(IDataset* outputDataset, IProgressMonitor* progressMonitor);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<DatasetDecompressor_1_0> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x4B29CDAA;
    
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
  
} } } 

#endif
