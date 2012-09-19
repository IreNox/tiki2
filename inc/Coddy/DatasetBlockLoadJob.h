////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_DATASETS_BUILDER_DATASETBLOCKLOADJOB_H
#define CLODDY_API_DATASETS_BUILDER_DATASETBLOCKLOADJOB_H

#include "CodeX/System.h"

// Include referenced structures.

#include "Cloddy/Vec2I.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Datasets { namespace Builder { class IDatasetBlockProvider; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Datasets { namespace Builder { class DatasetBlockQueue; } } } }

// Declare class ::Cloddy::API::Datasets::Builder::DatasetBlockLoadJob.

namespace Cloddy { namespace API { namespace Datasets { namespace Builder
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced structures.
  
  using Cloddy::Core::Math::Vectors::Vec2I;
  
  /*!
   * @brief  Represents a job for loading a dataset block image.
   */
  class DatasetBlockLoadJob : public virtual Object
  {
    // Declare friend classes.
    
    friend class DatasetBlockQueue;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The block coordinates of the dataset block image to load.
     */
    Vec2I BlockCoords;
    
    /*!
     * @brief  The dataset block provider.
     */
    Ptr<IDatasetBlockProvider> Provider;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Creates a new instance of DatasetBlockLoadJob.
     * 
     * @param provider The dataset block provider.
     * @param blockCoords The block coordinates of the dataset block image to load.
     */
    DatasetBlockLoadJob(IDatasetBlockProvider* provider, const Vec2I& blockCoords);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<DatasetBlockLoadJob> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x3A204DBE;
    
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
