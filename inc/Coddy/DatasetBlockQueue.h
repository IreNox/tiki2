////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_DATASETS_BUILDER_DATASETBLOCKQUEUE_H
#define CLODDY_API_DATASETS_BUILDER_DATASETBLOCKQUEUE_H

#include "CodeX/System.h"

// Include referenced classes.

#include "CodeX/Disposable.h"

// Forward declare referenced structures.

namespace Cloddy { namespace Core { namespace Math { namespace Vectors { struct Vec2I; } } } }

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Datasets { namespace Builder { class IDatasetBlockProvider; } } } }
namespace Cloddy { namespace Core { namespace Collections { template<class> class IDeque; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Datasets { namespace Builder { class DatasetBlockLoaded; } } } }
namespace Cloddy { namespace API { namespace Datasets { namespace Builder { class DatasetBlockLoadJob; } } } }
namespace Cloddy { namespace API { namespace Datasets { namespace Builder { class DatasetBuilder_Rect_1_0_Incremental; } } } }
namespace CodeX { namespace System { class ByteBuffer; } }
namespace CodeX { namespace System { class Monitor; } }

// Declare class ::Cloddy::API::Datasets::Builder::DatasetBlockQueue.

namespace Cloddy { namespace API { namespace Datasets { namespace Builder
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced structures.
  
  using Cloddy::Core::Math::Vectors::Vec2I;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::Collections::IDeque;
  
  // Use referenced classes.
  
  using CodeX::System::ByteBuffer;
  using CodeX::System::Disposable;
  using CodeX::System::Monitor;
  
  /*!
   * @brief  A queue for dataset block load jobs and loaded dataset block memory images.
   */
  class DatasetBlockQueue : public Disposable
  {
    // Declare friend classes.
    
    friend class DatasetBuilder_Rect_1_0_Incremental;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Pops a loaded dataset block image from the queue.
     * 
     * @return The block image or \c null  if the queue is empty.
     */
    Ptr<DatasetBlockLoaded> PopLoaded();
    
    /*!
     * @brief  Pops a dataset block load job from the queue.
     * 
     * @return The load job or \c null  if the queue has been disposed.
     */
    Ptr<DatasetBlockLoadJob> PopToLoad();
    
    /*!
     * @brief  Pushes a finished (ie. loaded)dataset block image.
     * 
     * @param blockCoords The block coordinates.
     * @param blockData <b>[not-null]</b>  The finished block image.
     */
    void PushLoaded(const Vec2I& blockCoords, ByteBuffer* blockData);
    
    /*!
     * @brief  Pushes a job to load a dataset block image.
     * 
     * @param block The block coordinates.
     */
    void PushToLoad(const Vec2I& block);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
  protected:
    
    virtual void DisposeManaged();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constants
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Number of loaded blocks that can be buffered in the queue.
     */
    static const int32 LoadedBlocksCount = 2;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  The loaded dataset block images.
     */
    Ptr<IDeque<Ref<DatasetBlockLoaded> > > loaded;
    
    /*!
     * @brief  The monitor object.
     */
    Ptr<Monitor> monitor;
    
    /*!
     * @brief  The dataset block provider.
     */
    Ptr<IDatasetBlockProvider> provider;
    
    /*!
     * @brief  The load jobs.
     */
    Ptr<IDeque<Ref<DatasetBlockLoadJob> > > toLoad;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of DatasetBlockQueue.
     * 
     * @param provider The dataset block provider.
     * @param monitor The monitor object to use for synchronization.
     */
    DatasetBlockQueue(IDatasetBlockProvider* provider, Monitor* monitor);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<DatasetBlockQueue> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xA7C44A06;
    
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
      if ((ptr = Disposable::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } 

#endif
