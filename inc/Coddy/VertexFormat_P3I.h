////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_VERTEXFACTORIES_VERTEXFORMATS_VERTEXFORMAT_P3I_H
#define CLODDY_API_VERTEXFACTORIES_VERTEXFORMATS_VERTEXFORMAT_P3I_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/VertexFormat.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace VertexData { class IVertexData; } } }
namespace Cloddy { namespace API { namespace VertexData { class IVertexDataCollection; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace VertexData { class Semantic; } } }
namespace Cloddy { namespace API { namespace VertexFactories { namespace VertexFormats { class FixedRange; } } } }
namespace Cloddy { namespace API { namespace VertexFactories { namespace VertexFormats { class VertexFormat; } } } }
namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::API::VertexFactories::VertexFormats::VertexFormat_P3I.

namespace Cloddy { namespace API { namespace VertexFactories { namespace VertexFormats
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::VertexData::IVertexData;
  using Cloddy::API::VertexData::IVertexDataCollection;
  
  // Use referenced classes.
  
  using Cloddy::API::VertexData::Semantic;
  using CodeX::System::ByteBuffer;
  
  class VertexFormat_P3I : public VertexFormat
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
     * @brief  Vertex positions.
     */
    Ptr<IVertexData> position;
    
    /*!
     * @brief  The fixed coordinate range.
     */
    Ptr<FixedRange> range;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of VertexFormat_P3I.
     * 
     * @param range The fixed coordinate range.
     */
    VertexFormat_P3I(FixedRange* range);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<VertexFormat_P3I> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x76FC80CC;
    
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
