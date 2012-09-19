////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_VERTEXFACTORIES_VERTEXFACTORY_H
#define CLODDY_API_VERTEXFACTORIES_VERTEXFACTORY_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IVertexFactory.h"

// Include referenced classes.

#include "CodeX/Disposable.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Heightmaps { class IHeightmap; } } }
namespace Cloddy { namespace API { namespace VertexData { class IVertexDataCollection; } } }
namespace Cloddy { namespace API { namespace VertexFactories { namespace VertexFormats { class IVertexFormat; } } } }
namespace Cloddy { namespace Kernel { class IProvider; } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Heightmaps { class HeightmapSample; } } }
namespace Cloddy { namespace API { namespace VertexData { class Int1; } } }
namespace Cloddy { namespace API { namespace VertexData { class Int2; } } }
namespace Cloddy { namespace API { namespace VertexFactories { class Computations; } } }
namespace Cloddy { namespace Kernel { class CommandBuffer; } }

// Declare class ::Cloddy::API::VertexFactories::VertexFactory.

namespace Cloddy { namespace API { namespace VertexFactories
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Heightmaps::IHeightmap;
  using Cloddy::API::VertexData::IVertexDataCollection;
  using Cloddy::API::VertexFactories::VertexFormats::IVertexFormat;
  using Cloddy::Kernel::IProvider;
  using Cloddy::Kernel::IVertexFactory;
  
  // Use referenced classes.
  
  using Cloddy::API::Heightmaps::HeightmapSample;
  using Cloddy::API::VertexData::Int1;
  using Cloddy::API::VertexData::Int2;
  using Cloddy::Kernel::CommandBuffer;
  using CodeX::System::Disposable;
  
  /*!
   * @brief  Abstract base class for default vertex factory implementations.
   * 
   * The following computations are performed by this class:
   *   - \b HeightmapCoords :Heightmap coordinates for new vertices.
   *   - <b>Preloading:</b>:Preloading of heightmap samples for improved performance.
   *   - \b Position :Vertex positions in terrain-space.
   *   - \b Normal :Vertex normal vectors in terrain-space.
   *   - \b Tangent :Vertex tangent vectors in terrain-space.
   *   - \b Radius :Vertex bounding sphere radii in terrain-space.
   *   - \b Displacement :Per-vertex displacement in terrain-space.
   * The following list shows which vertex data containers are needed for each computations:
   *   - \b HeightmapCoords :Semantic::HeightmapCoords
   *   - \b Preloading :Semantic::HeightmapCoords
   *   - \b Position :Semantic::Position
   *   - \b Normal :Semantic::Position,Semantic::Normal
   *   - 
   *   \b Tangent :Semantic::Position,Semantic::HeightmapCoords,Semantic::TangentX,Semantic::TangentY 
   *   and Semantic::TangentZ
   *   - \b Radius :Semantic::Position,Semantic::Radius
   *   - \b Displacement :Semantic::Position
   * If a vertex data container prerequisite is not met,the dependent computations will not be 
   * performed.
   * 
   * The following vertex data semantics are used by this class (\e opt  means that the semantic 
   * will be used if present,\e req  means that the semantic must be present):
   *   - \e opt  - Semantic::HeightmapCoords
   *   - \e opt  - Semantic::Position
   *   - \e opt  - Semantic::Normal
   *   - \e opt  - Semantic::DiffuseColor
   *   - \e opt  - Semantic::Radius
   *   - \e opt  - Semantic::TangentX
   *   - \e opt  - Semantic::TangentY
   *   - \e opt  - Semantic::TangentZ
   * 
   * @see ComponentIdsApi
   */
  class VertexFactory : public Disposable, public virtual IVertexFactory
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Creates a new instance of VertexFactory.
     */
    VertexFactory();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methodss
    // ---------------------------------------------------------------------------------------------
    
    virtual bool BeginCompute(CommandBuffer* commandBuffer);
    
    virtual void BeginMeshAction(IProvider* provider);
    
    virtual void EndCompute(CommandBuffer* commandBuffer);
    
    virtual void EndMeshAction();
    
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
     * @brief  Helper object for performing common computations.
     */
    Ptr<Computations> computations;
    
    /*!
     * @brief  Holds heightmap diffuse colors.
     */
    Ptr<Int1> diffuse;
    
    /*!
     * @brief  The current IHeightmap object.
     */
    Ptr<IHeightmap> heightmap;
    
    /*!
     * @brief  Data container for heightmap coordinates.
     */
    Ptr<Int2> heightmapCoords;
    
    /*!
     * @brief  Width of #heightmap (see IMap::GetWidth).
     */
    int32 heightmapHeight;
    
    /*!
     * @brief  The HeightmapSample object used to access heightmaps.
     */
    Ptr<HeightmapSample> heightmapSample;
    
    /*!
     * @brief  Size of #heightmap (see IMap::GetSize).
     */
    int32 heightmapSize;
    
    /*!
     * @brief  Height of #heightmap (see IMap::GetHeight).
     */
    int32 heightmapWidth;
    
    /*!
     * @brief  The application vertex data containers 
     */
    Ptr<IVertexDataCollection> vertexDataCollection;
    
    /*!
     * @brief  The current vertex layout.
     */
    Ptr<IVertexFormat> vertexFormat;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<VertexFactory> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x7F44D04A;
    
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
      if ((ptr = IVertexFactory::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
