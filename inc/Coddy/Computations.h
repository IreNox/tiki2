////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_VERTEXFACTORIES_COMPUTATIONS_H
#define CLODDY_API_VERTEXFACTORIES_COMPUTATIONS_H

#include "CodeX/System.h"

// Include referenced structures.

#include "Cloddy/Vec3I.h"

// Include referenced interfaces.

#include "Cloddy/IMeshCallback.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Geometries { class IGeometry; } } }
namespace Cloddy { namespace API { namespace Heightmaps { class IHeightmap; } } }
namespace Cloddy { namespace API { namespace VertexData { class IVertexData; } } }
namespace Cloddy { namespace Kernel { class IProvider; } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Geometries { class GeometrySample; } } }
namespace Cloddy { namespace API { namespace Heightmaps { class HeightmapSample; } } }
namespace Cloddy { namespace API { namespace VertexData { class Float3; } } }
namespace Cloddy { namespace API { namespace VertexData { class Int1; } } }
namespace Cloddy { namespace API { namespace VertexData { class Int2; } } }
namespace Cloddy { namespace API { namespace VertexData { class Int4; } } }
namespace Cloddy { namespace API { namespace VertexFactories { class Computations_VertexHierarchyCallback; } } }
namespace Cloddy { namespace Kernel { class CommandBuffer; } }

// Declare class ::Cloddy::API::VertexFactories::Computations.

namespace Cloddy { namespace API { namespace VertexFactories
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced structures.
  
  using Cloddy::Core::Math::Vectors::Vec3I;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Geometries::IGeometry;
  using Cloddy::API::Heightmaps::IHeightmap;
  using Cloddy::API::VertexData::IVertexData;
  using Cloddy::Kernel::IMeshCallback;
  using Cloddy::Kernel::IProvider;
  
  // Use referenced classes.
  
  using Cloddy::API::Geometries::GeometrySample;
  using Cloddy::API::Heightmaps::HeightmapSample;
  using Cloddy::API::VertexData::Float3;
  using Cloddy::API::VertexData::Int1;
  using Cloddy::API::VertexData::Int2;
  using Cloddy::API::VertexData::Int4;
  using Cloddy::Kernel::CommandBuffer;
  
  /*!
   * @brief  This is a helper class that implements computations that are common 
   *         between IVertexFactory implementations.
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
   *   - \e opt  - Semantic::Radius
   *   - \e opt  - Semantic::TangentX
   *   - \e opt  - Semantic::TangentY
   *   - \e opt  - Semantic::TangentZ
   * 
   * @see VertexFactory
   */
  class Computations : public virtual IMeshCallback
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Creates a new instance of Computations.
     */
    Computations();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void BeginMeshAction(IProvider* provider);
    
    /*!
     * @brief  Computes adjacency data for the vertices in the given command buffer..
     * 
     * @param commandBuffer The command buffer.
     * 
     * @see CommandBuffer::ComputeAdjacencyData
     */
    void ComputeAdjacencyData(CommandBuffer* commandBuffer);
    
    /*!
     * @brief  Computes the heightmap coordinates for the current vertex in the given command 
     *         buffer.
     * 
     * @param commandBuffer <b>[not-null]</b>  The command buffer.
     * 
     * @return <b>[not-null]</b>  The computed heightmap coordinates.
     */
    Vec3I ComputeHeightmapCoordinates(CommandBuffer* commandBuffer);
    
    /*!
     * @brief  Computes vertex data for the vertices in the given command buffer.
     * 
     * @param commandBuffer The command buffer.
     * @param hx Heightmap X-coordinate of the vertex.
     * @param hy Heightmap Y-coordinate of the vertex.
     * @param hz Heightmap Z-coordinate of the vertex.
     * @param heightmapSample The heightmap sample of the vertex.
     * 
     * @see CommandBuffer::ComputeVertexData
     */
    void ComputeVertexData(CommandBuffer* commandBuffer, int32 hx, int32 hy, int32 hz, HeightmapSample* heightmapSample);
    
    virtual void EndMeshAction();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Radius of the bounding sphere of the current meshes geometry.
     */
    float64 boundingSphereRadius;
    
    /*!
     * @brief  Can compute detail channel values?
     */
    bool computeDetail;
    
    /*!
     * @brief  Can compute vertex displacement?
     */
    bool computeDisplacement;
    
    /*!
     * @brief  Store elevation values?
     */
    bool computeElevation;
    
    /*!
     * @brief  Compute maximum elevation values?
     */
    bool computeElevationMax;
    
    /*!
     * @brief  Compute minimium elevation values?
     */
    bool computeElevationMin;
    
    /*!
     * @brief  Can compute heightmap coordinates?
     */
    bool computeHeightmapCoords;
    
    /*!
     * @brief  Can compute normal vectors?
     */
    bool computeNormal;
    
    /*!
     * @brief  Can compute vertex positions?
     */
    bool computePosition;
    
    /*!
     * @brief  Can compute vertex bounding sphere radii?
     */
    bool computeRadius;
    
    /*!
     * @brief  Can compute tangent vectors along heightmap space X-axis?
     */
    bool computeTangentX;
    
    /*!
     * @brief  Can compute tangent vectors along heightmap space Y-axis?
     */
    bool computeTangentY;
    
    /*!
     * @brief  Can compute tangent vectors along heightmap space Z-axis?
     */
    bool computeTangentZ;
    
    /*!
     * @brief  Vertex data container for detail channel values.
     */
    Ptr<Int4> detail;
    
    Ptr<Int1> elevation;
    
    /*!
     * @brief  Vertex data container for maximum elevation values per sector.
     */
    Ptr<Int1> elevationMax;
    
    /*!
     * @brief  Vertex data container for minimum elevation values per sector.
     */
    Ptr<Int1> elevationMin;
    
    /*!
     * @brief  Need to flip computed normal vectors?
     */
    bool flipNormals;
    
    /*!
     * @brief  The geometry of the current mesh.
     */
    Ptr<IGeometry> geometry;
    
    /*!
     * @brief  The data container for accessing the geometry of the current mesh.
     */
    Ptr<GeometrySample> geometrySample;
    
    /*!
     * @brief  The current heightmap.
     */
    Ptr<IHeightmap> heightmap;
    
    /*!
     * @brief  The vertex data container for heightmap coordinates.
     */
    Ptr<Int2> heightmapCoords;
    
    /*!
     * @brief  The vertex data container for normal vectors.
     */
    Ptr<Float3> normal;
    
    /*!
     * @brief  The vertex data container for vertex positions.
     */
    Ptr<IVertexData> position;
    
    /*!
     * @brief  The vertex data container for vertex bounding sphere radii.
     */
    Ptr<IVertexData> radius;
    
    /*!
     * @brief  The vertex data container for tangent vectors along heightmap space X-axis.
     */
    Ptr<Float3> tangentX;
    
    /*!
     * @brief  The vertex data container for bitangent vectors along heightmap space Y-axis.
     */
    Ptr<Float3> tangentY;
    
    /*!
     * @brief  The vertex data container for bitangent vectors along heightmap space Z-axis.
     */
    Ptr<Float3> tangentZ;
    
    /*!
     * @brief  Scale factor for displacement values of current mesh.
     */
    float64 terrainDisplacement;
    
    Ptr<Computations_VertexHierarchyCallback> vertexHierarchyCallback;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Computes the weight for mixing tangent vectors.
     * 
     * @param a First heightmap coordinate value.
     * @param b Second heightmap coordinate value.
     * 
     * @return The tangent vector weight.
     */
    static float64 ComputeTangentWeight(int32 a, int32 b);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<Computations> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xDFC3AA4E;
    
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
      if ((ptr = IMeshCallback::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
