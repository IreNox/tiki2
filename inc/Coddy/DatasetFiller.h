////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_DATASETS_DATASETFILLER_H
#define CLODDY_API_DATASETS_DATASETFILLER_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/Operation.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Datafiles { class IDatafile; } } }
namespace Cloddy { namespace API { namespace Util { namespace Progress { class IProgressMonitor; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Datasets { class Dataset_1_0_Cube_Uncompressed; } } }
namespace Cloddy { namespace API { namespace Datasets { class Dataset_1_0_Rect_Uncompressed; } } }
namespace Cloddy { namespace API { namespace Datasets { class Dataset_1_1_Cube_Uncompressed_Sparse; } } }
namespace Cloddy { namespace API { namespace Datasets { class Dataset_1_1_Rect_Uncompressed_Sparse; } } }
namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::API::Datasets::DatasetFiller.

namespace Cloddy { namespace API { namespace Datasets
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Datafiles::IDatafile;
  using Cloddy::API::Util::Progress::IProgressMonitor;
  
  // Use referenced classes.
  
  using Cloddy::API::Util::Progress::Operation;
  using CodeX::System::ByteBuffer;
  
  class DatasetFiller : public Operation
  {
    // Declare friend classes.
    
    friend class Dataset_1_0_Cube_Uncompressed;
    friend class Dataset_1_0_Rect_Uncompressed;
    friend class Dataset_1_1_Cube_Uncompressed_Sparse;
    friend class Dataset_1_1_Rect_Uncompressed_Sparse;
    
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
    
    Ptr<IDatafile> datafile;
    
    int64 datafileOffset;
    
    Ptr<ByteBuffer> sample;
    
    int64 sampleCount;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    DatasetFiller(IDatafile* datafile, int64 datafileOffset, ByteBuffer* sample, int64 sampleCount);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<DatasetFiller> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x8FA96FBF;
    
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
