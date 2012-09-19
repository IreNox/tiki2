////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_VERTEXDATA_IVERTEXDATACOLLECTION_H
#define CLODDY_API_VERTEXDATA_IVERTEXDATACOLLECTION_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/ICapacity.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace VertexData { class IVertexData; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace VertexData { class Semantic; } } }

// Declare interface ::Cloddy::API::VertexData::IVertexDataCollection.

namespace Cloddy { namespace API { namespace VertexData
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Kernel::ICapacity;
  
  /*!
   * @brief  Base interface for classes that contain vertex data containers.
   * 
   * The application must provide an IVertexDataCollection object for each CLOD mesh by adding 
   * a ComponentIdsApi::Req_VertexDataCollection component to the meshes IProvider object.
   * 
   * @see Semantic
   */
  class NO_VTABLE IVertexDataCollection : public virtual ICapacity
  {
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Creates a new vertex data container for the given semantic.
     * 
     * If the Semantic::GetTupleType of \e semantic  is TupleType::TupleType_Any,a 32-bit floating 
     * point vertex data container will be created by default (see TupleType::TupleType_Float).To 
     * override this behaviour,create a custom IVertexData container and set it via #SetVertexData.
     * 
     * @param semantic <b>[not-null]</b>  The semantic.
     */
    virtual void CreateVertexData(Semantic* semantic) = 0;
    
    /*!
     * @brief  Returns the vertex data container for the given semantic.
     * 
     * @param semantic <b>[not-null]</b>  The semantic.
     * 
     * @return The vertex data container or \c null  if no container exists for the given semantic.
     */
    virtual Ptr<IVertexData> GetVertexData(Semantic* semantic) = 0;
    
    /*!
     * @brief  Sets the vertex data container for the given semantic.
     * 
     * @param semantic <b>[not-null]</b>  The semantic.
     * @param vertexData The vertex data container or \c null .
     */
    virtual void SetVertexData(Semantic* semantic, IVertexData* vertexData) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IVertexDataCollection> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x68AA2B0B;
    
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
      if ((ptr = ICapacity::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
} } } 

#endif
