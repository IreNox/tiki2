////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_VERTEXDATA_SEMANTIC_H
#define CLODDY_API_VERTEXDATA_SEMANTIC_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/TupleType.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace VertexData { class IVertexData; } } }

// Declare class ::Cloddy::API::VertexData::Semantic.

namespace Cloddy { namespace API { namespace VertexData
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Instances of the Semantic class are used as handles for vertex data container 
   *         semantics (vertex position,normal vectors,etc.).
   * 
   * The Semantic class defines default semantic handles for common vertex data containers.
   * Applications are free to instantiate additional semantic handles as needed.
   * 
   * @see IVertexDataCollection
   */
  class Semantic : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Vertex detail data.
     * 
     * Each vertex can have up to sixteen 8-bit detail channels.
     */
    static const StaticPtr<Semantic> Detail;
    
    /*!
     * @brief  Vertex diffuse colors.
     * 
     * The following components in the CloddySDK use this semantic (\e opt  means that the semantic 
     * will be used if present,\e req  means that the semantic must be present):
     *   - \e req  - DefaultErrorMetric
     *   - \e opt  - VertexFactory
     *   - \e req  - ErrorTerm
     */
    static const StaticPtr<Semantic> DiffuseColor;
    
    /*!
     * @brief  Normalized vertex elevation values in the range <c>[0..HeightmapSample.MaxValue]</c>.
     */
    static const StaticPtr<Semantic> Elevation;
    
    /*!
     * @brief  Maximum vertex elevation values per sector in the range [
     *         0..HeightmapSample::MaxValue].
     * 
     * The following components in the CloddySDK use this semantic (\e opt  means that the semantic 
     * will be used if present,\e req  means that the semantic must be present):
     *   - \e opt  - VertexFactory
     *   - \e opt  - FrustumCulling
     */
    static const StaticPtr<Semantic> ElevationMax;
    
    /*!
     * @brief  Minimum vertex elevation values per sector in the range [
     *         0..HeightmapSample::MaxValue].
     * 
     * The following components in the CloddySDK use this semantic (\e opt  means that the semantic 
     * will be used if present,\e req  means that the semantic must be present):
     *   - \e opt  - VertexFactory
     *   - \e opt  - FrustumCulling
     */
    static const StaticPtr<Semantic> ElevationMin;
    
    /*!
     * @brief  A static per-vertex error term.
     */
    static const StaticPtr<Semantic> Error;
    
    /*!
     * @brief  A static per-vertex horizontal error term (ie. along terrain tangent/binormal plane).
     */
    static const StaticPtr<Semantic> ErrorHorizontal;
    
    /*!
     * @brief  A static per-vertex vertical error term (ie. along terrain normal vector).
     */
    static const StaticPtr<Semantic> ErrorVertical;
    
    /*!
     * @brief  Vertex heightmap coordinates.
     * 
     * The following components in the CloddySDK use this semantic (\e opt  means that the semantic 
     * will be used if present,\e req  means that the semantic must be present):
     *   - \e opt  - Computations
     *   - \e req  - MeshDirtyRegionCallback
     *   - \e opt  - PointInfoHelper
     *   - \e req  - VertexFactory
     */
    static const StaticPtr<Semantic> HeightmapCoords;
    
    /*!
     * @brief  Vertex normal vectors.
     * 
     * The following components in the CloddySDK use this semantic (\e opt  means that the semantic 
     * will be used if present,\e req  means that the semantic must be present):
     *   - \e opt  - Computations
     *   - \e req  - DefaultErrorMetric
     *   - \e req  - ErrorTerm
     *   - \e opt  - PointInfoHelper
     */
    static const StaticPtr<Semantic> Normal;
    
    /*!
     * @brief  Vertex positions.
     * 
     * The following components in the CloddySDK use this semantic (\e opt  means that the semantic 
     * will be used if present,\e req  means that the semantic must be present):
     *   - \e req  - CollisionDetection
     *   - \e opt  - Computations
     *   - \e req  - DefaultErrorMetric
     *   - \e req  - DistanceToGround
     *   - \e req  - ErrorTerm
     *   - \e req  - FrustumCulling
     *   - \e req  - Picking
     *   - \e opt  - PointInfoHelper
     *   - \e req  - PositionErrorMetric
     *   - \e req  - RegionErrorMetric
     *   - \e req  - ScreenSpaceVisibilityCriterion
     */
    static const StaticPtr<Semantic> Position;
    
    /*!
     * @brief  Vertex bounding sphere radii.
     * 
     * The following components in the CloddySDK use this semantic (\e opt  means that the semantic 
     * will be used if present,\e req  means that the semantic must be present):
     *   - \e req  - CollisionDetection
     *   - \e opt  - Computations
     *   - \e req  - DefaultErrorMetric
     *   - \e req  - DistanceToGround
     *   - \e req  - ErrorTerm
     *   - \e req  - FrustumCulling
     *   - \e req  - RegionErrorMetric
     *   - \e req  - Picking
     *   - \e opt  - ScreenSpaceVisibilityCriterion
     *   - \e opt  - TerrainSpaceVisibilityCriterion
     */
    static const StaticPtr<Semantic> Radius;
    
    /*!
     * @brief  Vertex tangent vectors along the heightmap space X-axis.
     * 
     * For rectangular heightmaps,these vectors correspond to the usual tangent vectors.
     * 
     * The following components in the CloddySDK use this semantic (\e opt  means that the semantic 
     * will be used if present,\e req  means that the semantic must be present):
     *   - \e opt  - Computations
     *   - \e opt  - PointInfoHelper
     */
    static const StaticPtr<Semantic> TangentX;
    
    /*!
     * @brief  Vertex tangent vectors along the heightmap space Y-axis.
     * 
     * For rectangular heightmaps,these vectors correspond to the usual bitangent resp. binormal 
     * vectors.
     * 
     * The following components in the CloddySDK use this semantic (\e opt  means that the semantic 
     * will be used if present,\e req  means that the semantic must be present):
     *   - \e opt  - Computations
     *   - \e opt  - PointInfoHelper
     */
    static const StaticPtr<Semantic> TangentY;
    
    /*!
     * @brief  Vertex tangent vectors along the heightmap space Z-axis.
     * 
     * These vectors are only used for cubemap heightmaps.In order to avoid distortions at the 
     * edges of the cubemap,it is necessary to combine the tangent vectors for the heightmap space 
     * X-,Y- and Z-axes separately for each cubemap face during rendering.
     * 
     * The following components in the CloddySDK use this semantic (\e opt  means that the semantic 
     * will be used if present,\e req  means that the semantic must be present):
     *   - \e opt  - Computations
     *   - \e opt  - PointInfoHelper
     */
    static const StaticPtr<Semantic> TangentZ;
    
    /*!
     * @brief  Create 64-bit floating point vertex data containers for tuple 
     *         type TupleType::TupleType_Any?
     * 
     * The default value is \c false .
     * 
     * @return \c true  to create double precision data container,\c false  to create single 
     * precision ones.
     * 
     * @see #CreateVertexData
     * @see TupleType
     */
    static bool GetUseDoubleForAny();
    
    /*!
     * @brief  Create 64-bit floating point vertex data containers for tuple 
     *         type TupleType::TupleType_Any?
     * 
     * The default value is \c false .
     * 
     * @param value \c true  to create double precision data container,\c false  to create single 
     * precision ones.
     * 
     * @see #CreateVertexData
     * @see TupleType
     */
    static void SetUseDoubleForAny(bool value);
    
    /*!
     * @brief  The ID of this semantic object.
     * 
     * @return <b>[0..255]</b>  The unique identifier of this semantic object.
     */
    int32 GetId();
    
    /*!
     * @brief  The name of this vertex data container semantic.
     * 
     * @return <b>[not-null]</b>  The semantic name.
     */
    String GetName();
    
    /*!
     * @brief  The tuple size.
     * 
     * @return <b>[1..4]</b>  The tuple size.
     */
    int32 GetTupleSize();
    
    /*!
     * @brief  The tuple element type.
     * 
     * @return The tuple type.
     */
    TupleType GetTupleType();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of Semantic.
     * 
     * The maximum number of Semantic objects that may be created is \c 256 .
     * 
     * @param name <b>[not-null]</b>  The name of the semantic object.
     * @param tupleSize <b>[1..4]</b>  The tuple size.
     * @param tupleType The tuple type.
     */
    Semantic(String name, int32 tupleSize, TupleType tupleType);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new vertex data container for this semantic.
     * 
     * When TupleType is TupleType::TupleType_Any,the created IVertexData object will use the 
     * type TupleType::TupleType_Float.
     * 
     * @param capacity <b>[>0]</b>  The capacity of the container,in vertices.
     * 
     * @return <b>[not-null]</b>  The created container.
     */
    Ptr<IVertexData> CreateVertexData(int32 capacity);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The ID of the next semantic object.
     */
    static int32 nextId;
    
    /*!
     * @brief  Create 64-bit floating point vertex data containers for tuple 
     *         type TupleType::TupleType_Any?
     */
    static bool useDoubleForAny;
    
    /*!
     * @brief  The name of this vertex data container semantic.
     */
    String name;
    
    /*!
     * @brief  The ID of this semantic object.
     */
    int32 semanticId;
    
    /*!
     * @brief  The tuple size.
     */
    int32 tupleSize;
    
    /*!
     * @brief  The tuple element type.
     */
    TupleType tupleType;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Asserts that the maximum number of Semantic object has not been reached yet.
     */
    static void AssertValidId();
    
    // ---------------------------------------------------------------------------------------------
    // Static Initializer Functions
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Static initializer function for field Detail.
     */
    static Object* StaticInitializer_Detail();
    
    /*!
     * @brief Static initializer function for field DiffuseColor.
     */
    static Object* StaticInitializer_DiffuseColor();
    
    /*!
     * @brief Static initializer function for field Elevation.
     */
    static Object* StaticInitializer_Elevation();
    
    /*!
     * @brief Static initializer function for field ElevationMax.
     */
    static Object* StaticInitializer_ElevationMax();
    
    /*!
     * @brief Static initializer function for field ElevationMin.
     */
    static Object* StaticInitializer_ElevationMin();
    
    /*!
     * @brief Static initializer function for field Error.
     */
    static Object* StaticInitializer_Error();
    
    /*!
     * @brief Static initializer function for field ErrorHorizontal.
     */
    static Object* StaticInitializer_ErrorHorizontal();
    
    /*!
     * @brief Static initializer function for field ErrorVertical.
     */
    static Object* StaticInitializer_ErrorVertical();
    
    /*!
     * @brief Static initializer function for field HeightmapCoords.
     */
    static Object* StaticInitializer_HeightmapCoords();
    
    /*!
     * @brief Static initializer function for field Normal.
     */
    static Object* StaticInitializer_Normal();
    
    /*!
     * @brief Static initializer function for field Position.
     */
    static Object* StaticInitializer_Position();
    
    /*!
     * @brief Static initializer function for field Radius.
     */
    static Object* StaticInitializer_Radius();
    
    /*!
     * @brief Static initializer function for field TangentX.
     */
    static Object* StaticInitializer_TangentX();
    
    /*!
     * @brief Static initializer function for field TangentY.
     */
    static Object* StaticInitializer_TangentY();
    
    /*!
     * @brief Static initializer function for field TangentZ.
     */
    static Object* StaticInitializer_TangentZ();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<Semantic> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x5B4FDF24;
    
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
  
} } } 

#endif
