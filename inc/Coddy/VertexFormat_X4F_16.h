////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_VERTEXFACTORIES_VERTEXFORMATS_VERTEXFORMAT_X4F_16_H
#define CLODDY_API_VERTEXFACTORIES_VERTEXFORMATS_VERTEXFORMAT_X4F_16_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/VertexFormat.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace VertexData { class IVertexDataCollection; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace VertexData { class Int4; } } }
namespace Cloddy { namespace API { namespace VertexData { class Semantic; } } }
namespace Cloddy { namespace API { namespace VertexFactories { namespace VertexFormats { class VertexFormat; } } } }
namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::API::VertexFactories::VertexFormats::VertexFormat_X4F_16.

namespace Cloddy { namespace API { namespace VertexFactories { namespace VertexFormats
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::VertexData::IVertexDataCollection;
  
  // Use referenced classes.
  
  using Cloddy::API::VertexData::Int4;
  using Cloddy::API::VertexData::Semantic;
  using CodeX::System::ByteBuffer;
  
  class VertexFormat_X4F_16 : public VertexFormat
  {
    // Declare friend classes.
    
    friend class VertexFormat;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual void SetVertexData(IVertexDataCollection* vertexDataCollection);
    
    virtual bool UsesSemantic(Semantic* semantic);
    
    virtual void WriteVertex(int32 vertex, ByteBuffer* buffer);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The vertex data container that holds the detail channel values per vertex.
     */
    Ptr<Int4> detail;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of VertexFormat_X4F_16.
     */
    VertexFormat_X4F_16();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<VertexFormat_X4F_16> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x6CAB587C;
    
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
      if ((ptr = VertexFormat::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } 

#endif
