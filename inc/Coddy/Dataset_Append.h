////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_DATASETS_DATASET_APPEND_H
#define CLODDY_API_DATASETS_DATASET_APPEND_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/DatasetBase.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Datasets { class IDataset; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Datasets { class DatasetBase; } } }
namespace Cloddy { namespace API { namespace Datasets { namespace Metadata { class DatasetMetadata; } } } }
namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::API::Datasets::Dataset_Append.

namespace Cloddy { namespace API { namespace Datasets
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced classes.
  
  using Cloddy::API::Datasets::Metadata::DatasetMetadata;
  using CodeX::System::ByteBuffer;
  
  class Dataset_Append : public DatasetBase
  {
    // Declare friend classes.
    
    friend class DatasetBase;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual int32 GetChannels();
    
    virtual bool IsMutable();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void Begin();
    
    virtual void End();
    
    virtual void Flush();
    
    virtual void FlushMetadata();
    
    virtual Ptr<ByteBuffer> Get(int32 x, int32 y);
    
    virtual Ptr<ByteBuffer> Get(int32 x, int32 y, int32 z);
    
    virtual Ptr<ByteBuffer> Set(int32 x, int32 y);
    
    virtual Ptr<ByteBuffer> Set(int32 x, int32 y, int32 z);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
  protected:
    
    virtual void DisposeManaged();
    
    virtual void DisposeManagedChildren();
    
    virtual Ptr<DatasetMetadata> LoadMetadata();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The buffer for getting dataset samples.
     */
    Ptr<ByteBuffer> buffer;
    
    /*!
     * @brief  Current buffer for setting a dataset sample.
     */
    Ptr<ByteBuffer> bufferFirst;
    
    /*!
     * @brief  Current buffer for setting a dataset sample.
     */
    Ptr<ByteBuffer> bufferSecond;
    
    /*!
     * @brief  First aggregated dataset.
     */
    Ptr<IDataset> first;
    
    /*!
     * @brief  Second aggregated dataset.
     */
    Ptr<IDataset> second;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of Dataset_Append.
     * 
     * @param first The first dataset.
     * @param second The second dataset.
     */
    Dataset_Append(IDataset* first, IDataset* second);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    void FlushSet();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<Dataset_Append> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xD6AB624C;
    
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
      if ((ptr = DatasetBase::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
