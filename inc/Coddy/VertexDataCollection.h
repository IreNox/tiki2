////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_VERTEXDATA_VERTEXDATACOLLECTION_H
#define CLODDY_API_VERTEXDATA_VERTEXDATACOLLECTION_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IVertexDataCollection.h"

// Include referenced classes.

#include "Cloddy/CapacityBase.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace VertexData { class IVertexData; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace VertexData { class Semantic; } } }

// Declare class ::Cloddy::API::VertexData::VertexDataCollection.

namespace Cloddy { namespace API { namespace VertexData
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced classes.
  
  using Cloddy::Kernel::CapacityBase;
  
  /*!
   * @brief  Default implementation of the IVertexDataCollection interface.
   */
  class VertexDataCollection : public CapacityBase, public virtual IVertexDataCollection
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Creates a new instance of VertexDataCollection.
     * 
     * @param capacity <b>[>0]</b>  The capacity of each vertex data container in this collection,
     * in vertices.
     */
    VertexDataCollection(int32 capacity);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void CreateVertexData(Semantic* semantic);
    
    virtual Ptr<IVertexData> GetVertexData(Semantic* semantic);
    
    virtual void SetVertexData(Semantic* semantic, IVertexData* vertexData);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Array of contained vertex data containers.
     * 
     * This array is indexed with the unique semantic IDs (see Semantic::GetId).
     */
    Array<Ptr<IVertexData> > vertexDatas;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<VertexDataCollection> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x2BA4DAB2;
    
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
      if ((ptr = CapacityBase::TryCast(typeId)) != 0) return ptr;
      if ((ptr = IVertexDataCollection::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
