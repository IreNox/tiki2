////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_VERTEXFACTORIES_VERTEXFORMATS_VERTEXFORMAT_G3F_H
#define CLODDY_API_VERTEXFACTORIES_VERTEXFORMATS_VERTEXFORMAT_G3F_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/VertexFormat.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace VertexData { class IVertexDataCollection; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace VertexData { class Float3; } } }
namespace Cloddy { namespace API { namespace VertexData { class Int3; } } }
namespace Cloddy { namespace API { namespace VertexData { class Semantic; } } }
namespace Cloddy { namespace API { namespace VertexFactories { namespace VertexFormats { class VertexFormat; } } } }
namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::API::VertexFactories::VertexFormats::VertexFormat_G3F.

namespace Cloddy { namespace API { namespace VertexFactories { namespace VertexFormats
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::VertexData::IVertexDataCollection;
  
  // Use referenced classes.
  
  using Cloddy::API::VertexData::Float3;
  using Cloddy::API::VertexData::Int3;
  using Cloddy::API::VertexData::Semantic;
  using CodeX::System::ByteBuffer;
  
  class VertexFormat_G3F : public VertexFormat
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
     * @brief  Heightmap coordinates.
     */
    Ptr<Int3> heightmapCoords;
    
    /*!
     * @brief  Maximum heightmap coordinate value.
     */
    int32 maxHeightmapCoord;
    
    /*!
     * @brief  Tangent vectors along heightmap X-axis.
     */
    Ptr<Float3> tangentX;
    
    /*!
     * @brief  Tangent vectors along heightmap Y-axis.
     */
    Ptr<Float3> tangentY;
    
    /*!
     * @brief  Tangent vectors along heightmap Z-axis.
     */
    Ptr<Float3> tangentZ;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of VertexFormat_G3F.
     * 
     * @param maxHeightmapCoord Maximum heightmap coordinate value.
     */
    VertexFormat_G3F(int32 maxHeightmapCoord);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<VertexFormat_G3F> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x76FC7F24;
    
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
