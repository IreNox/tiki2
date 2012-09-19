////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_MESHVISITORS_PICKING_H
#define CLODDY_API_MESHVISITORS_PICKING_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/MeshFace.h"

// Include referenced interfaces.

#include "Cloddy/IMeshVisitor.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace VertexData { class IVertexData; } } }
namespace Cloddy { namespace Kernel { class IMesh; } }
namespace Cloddy { namespace Kernel { class IProvider; } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace MeshVisitors { class PointInfo; } } }
namespace Cloddy { namespace API { namespace MeshVisitors { class PointInfoHelper; } } }
namespace Cloddy { namespace Kernel { class Traversal; } }

// Declare class ::Cloddy::API::MeshVisitors::Picking.

namespace Cloddy { namespace API { namespace MeshVisitors
{
  // Use referenced namespaces.
  
  using namespace Cloddy::Kernel;
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::VertexData::IVertexData;
  
  /*!
   * @brief  Performs picking on CLOD meshes.
   * 
   * The Picking class can be used to pick individual points,vertices and/or triangles from a CLOD 
   * mesh.
   * 
   * This class uses an aggregated PointInfoHelper object to compute PointInfo values for picked 
   * points.
   * 
   * The following vertex data semantics are used by this class (\e opt  means that the semantic 
   * will be used if present,\e req  means that the semantic must be present):
   *   - \e req  - Semantic::Position
   *   - \e req  - Semantic::Radius
   */
  class Picking : public virtual IMeshVisitor
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Creates a new instance of Picking.
     */
    Picking();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void BeginFace(MeshFace face);
    
    virtual void BeginMeshAction(IProvider* provider);
    
    virtual void EndFace();
    
    virtual void EndMeshAction();
    
    /*!
     * @brief  Computes the intersection of the given ray with the terrain surface.
     * 
     * @param pointX X-coordinate of ray origin.
     * @param pointY Y-coordinate of ray origin.
     * @param pointZ Z-coordinate of ray origin.
     * @param directionX X-component of ray direction.
     * @param directionY Y-component of ray direction.
     * @param directionZ Z-component of ray direction.
     * @param mesh <b>[not-null]</b>  The CLOD mesh.
     * @param pointInfo <b>[not-null]</b>  The output picking sample.
     * @param pointInfoFlags The PointInfo flags.
     * 
     * @return \c true  if an intersection has been found,\c false  if no intersection has been 
     * found.
     */
    bool Pick(float64 pointX, float64 pointY, float64 pointZ, float64 directionX, float64 directionY, float64 directionZ, IMesh* mesh, PointInfo* pointInfo, int32 pointInfoFlags);
    
    virtual void VisitSector(Traversal* traversal, int32 userData);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Square length of direction vector.
     */
    float64 a;
    
    /*!
     * @brief  X-component of ray direction.
     */
    float64 directionX;
    
    /*!
     * @brief  Y-component of ray direction.
     */
    float64 directionY;
    
    /*!
     * @brief  Z-component of ray direction.
     */
    float64 directionZ;
    
    /*!
     * @brief  The nearest found intersection so far.
     * 
     * <pre>
     *     P = S +  t * V
     *     where
     *     P := Point on picking ray
     *     S := Origin of picking ray
     *     V := Direction of picking ray
     * </pre>
     */
    float64 nearestT;
    
    /*!
     * @brief  The picking sample used to return the result of a picking operation.
     */
    Ptr<PointInfo> pointInfo;
    
    /*!
     * @brief  Helper object used for computing PointInfo values.
     */
    Ptr<PointInfoHelper> pointInfoHelper;
    
    /*!
     * @brief  X-coordinate of ray origin.
     */
    float64 pointX;
    
    /*!
     * @brief  Y-coordinate of ray origin.
     */
    float64 pointY;
    
    /*!
     * @brief  Z-coordinate of ray origin.
     */
    float64 pointZ;
    
    /*!
     * @brief  Vertex positions.
     */
    Ptr<IVertexData> position;
    
    /*!
     * @brief  Bounding sphere radii.
     */
    Ptr<IVertexData> radius;
    
    /*!
     * @brief  This array is used for fetching the vertices of mesh sector.
     */
    Array<int32> vertices;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Intersects the picking ray with the given sphere.
     * 
     * @param x X-coordinate of sphere center,in terrain-space.
     * @param y Y-coordinate of sphere center,in terrain-space.
     * @param z Z-coordinate of sphere center,in terrain-space.
     * @param radius Radius of sphere,in terrain-space.
     * 
     * @return The ray coefficient of the nearest intersection point between the ray and the sphere,
     * <c>3.402823466E+38f</c> if no intersection has been found.
     */
    float64 IntersectSphere(float64 x, float64 y, float64 z, float64 radius);
    
    /*!
     * @brief  Intersects the picking ray with the given triangle.
     * 
     * The fields of #pointInfo are initialized in this method.
     * 
     * @param a Index of first vertex of triangle.
     * @param b Index of second vertex of triangle.
     * @param c Index of third vertex of triangle.
     * 
     * @return \c true  if an intersection has occurred,\c false  if not.
     */
    bool IntersectTriangle(int32 a, int32 b, int32 c);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<Picking> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xC8970ECD;
    
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
      if ((ptr = IMeshVisitor::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
