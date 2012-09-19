////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_DATASETS_BUILDER_DATASETBLOCKLOADED_H
#define CLODDY_API_DATASETS_BUILDER_DATASETBLOCKLOADED_H

#include "CodeX/System.h"

// Include referenced structures.

#include "Cloddy/Vec2I.h"

// Include referenced classes.

#include "CodeX/Disposable.h"

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Datasets { namespace Builder { class DatasetBlockQueue; } } } }
namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::API::Datasets::Builder::DatasetBlockLoaded.

namespace Cloddy { namespace API { namespace Datasets { namespace Builder
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced structures.
  
  using Cloddy::Core::Math::Vectors::Vec2I;
  
  // Use referenced classes.
  
  using CodeX::System::ByteBuffer;
  using CodeX::System::Disposable;
  
  /*!
   * @brief  Represents a loaded dataset block image.
   */
  class DatasetBlockLoaded : public Disposable
  {
    // Declare friend classes.
    
    friend class DatasetBlockQueue;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The block coordinates of the loaded dataset block image.
     */
    Vec2I BlockCoords;
    
    /*!
     * @brief  The loaded dataset block.
     * 
     * @return <b>[not-null]</b>  The block data.
     */
    Ptr<ByteBuffer> GetBlockData();
    
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
     * @brief  The loaded dataset block.
     */
    Ptr<ByteBuffer> blockData;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of DatasetBlockLoaded.
     * 
     * @param blockCoords The block coordinates of the loaded dataset block image.
     * @param blockData The loaded dataset block.
     */
    DatasetBlockLoaded(const Vec2I& blockCoords, ByteBuffer* blockData);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<DatasetBlockLoaded> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x60E50726;
    
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
