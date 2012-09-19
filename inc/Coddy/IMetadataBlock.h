////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_DATASETS_METADATA_IMETADATABLOCK_H
#define CLODDY_API_DATASETS_METADATA_IMETADATABLOCK_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/ISerializable.h"

// Declare interface ::Cloddy::API::Datasets::Metadata::IMetadataBlock.

namespace Cloddy { namespace API { namespace Datasets { namespace Metadata
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::IO::Serialization::ISerializable;
  
  /*!
   * @brief  Base interface for metadata blocks that can be stored along with IDatasets.
   * 
   * @see DatasetMetadata
   */
  class NO_VTABLE IMetadataBlock : public virtual ISerializable
  {
    // ---------------------------------------------------------------------------------------------
    // Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The unique ID token of this metadata block.
     * 
     * Metadata block IDs are four-character codes (eg. 'ELEV')of 7-bit ASCII characters.
     * 
     * @return <b>[not-null]</b>  The ID token.
     */
    virtual String GetId() = 0;
    
    /*!
     * @brief  Human-readable name of this metadata block.
     * 
     * @return <b>[not-null]</b>  The name.
     */
    virtual String GetName() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IMetadataBlock> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x5F487A3B;
    
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
      if ((ptr = ISerializable::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
} } } } 

#endif
