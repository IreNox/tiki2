////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_MESHVISITORS_COLLISIONDETECTION_H
#define CLODDY_API_MESHVISITORS_COLLISIONDETECTION_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/MeshFace.h"

// Include referenced interfaces.

#include "Cloddy/IMeshVisitor.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace MeshVisitors { class ICollisionShape; } } }
namespace Cloddy { namespace API { namespace VertexData { class IVertexData; } } }
namespace Cloddy { namespace Kernel { class IMesh; } }
namespace Cloddy { namespace Kernel { class IProvider; } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace MeshVisitors { class ContactPointInfo; } } }
namespace Cloddy { namespace API { namespace MeshVisitors { class PointInfoHelper; } } }
namespace Cloddy { namespace Kernel { class Traversal; } }

// Declare class ::Cloddy::API::MeshVisitors::CollisionDetection.

namespace Cloddy { namespace API { namespace MeshVisitors
{
  // Use referenced namespaces.
  
  using namespace Cloddy::Kernel;
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::VertexData::IVertexData;
  
  /*!
   * @brief  Performs collision detection between CLOD meshes and collision shapes.
   * 
   * This class uses an aggregated PointInfoHelper object to compute PointInfo values for found 
   * contact points.
   * 
   * The following vertex data semantics are used by this class (\e opt  means that the semantic 
   * will be used if present,\e req  means that the semantic must be present):
   *   - \e req  - Semantic::Position
   *   - \e req  - Semantic::Radius
   */
  class CollisionDetection : public virtual IMeshVisitor
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Returns the number of contact points that have been generated during the last 
     *         collision detection run.
     * 
     * @return <b>[>=0]</b>  The number of generated contact points.
     * 
     * @see #Collide
     */
    int32 GetContactPointCount();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of CollisionDetection.
     */
    CollisionDetection();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void BeginFace(MeshFace face);
    
    virtual void BeginMeshAction(IProvider* provider);
    
    /*!
     * @brief  Performs collision detection between the given CLOD and triangle mesh.
     * 
     * @param clodMesh <b>[not-null]</b>  The CLOD mesh.
     * @param collisionShape <b>[not-null]</b>  The collision shape.
     * @param maxContactPointCount <b>[>=0]</b>  Maximum number of contact point to return.
     * @param pointInfoFlags The PointInfo flags.
     * 
     * @return \c true  if at least one contact point has been generated,\c false  if there are no 
     * contact points (ie. no collision has occurred).
     * 
     * @see #GetContactPointCount
     */
    bool Collide(IMesh* clodMesh, ICollisionShape* collisionShape, int32 maxContactPointCount, int32 pointInfoFlags);
    
    virtual void EndFace();
    
    virtual void EndMeshAction();
    
    /*!
     * @brief  Returns a contact point.
     * 
     * @param index <b>[0..#GetContactPointCount-1]</b>  Index of contact point to return.
     * 
     * @return <b>[not-null]</b>  The contact point.
     */
    Ptr<ContactPointInfo> GetContactPoint(int32 index);
    
    virtual void VisitSector(Traversal* traversal, int32 userData);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  X-coordinate of collision shape center.
     */
    float64 centerX;
    
    /*!
     * @brief  Y-coordinate of collision shape center.
     */
    float64 centerY;
    
    /*!
     * @brief  Z-coordinate of collision shape center.
     */
    float64 centerZ;
    
    /*!
     * @brief  The collision shape.
     */
    Ptr<ICollisionShape> collisionShape;
    
    /*!
     * @brief  Number of valid contact points in #contactPoints.
     */
    int32 contactPointCount;
    
    /*!
     * @brief  Buffer for contact points.
     */
    Array<Ptr<ContactPointInfo> > contactPoints;
    
    /*!
     * @brief  Collision detection has finished because the maximum number of contact points has 
     *         been reached?
     */
    bool finished;
    
    /*!
     * @brief  Helper object used for computing PointInfo values.
     */
    Ptr<PointInfoHelper> pointInfoHelper;
    
    /*!
     * @brief  Vertex positions.
     */
    Ptr<IVertexData> position;
    
    /*!
     * @brief  Vertex bounding sphere radii.
     */
    Ptr<IVertexData> radius;
    
    /*!
     * @brief  Bounding sphere radius of collision shape.
     */
    float32 shapeRadius;
    
    /*!
     * @brief  Square value of #shapeRadius.
     */
    float32 shapeRadiusSqr;
    
    /*!
     * @brief  This array is used for fetching the triangles of a CLOD mesh.
     */
    Array<int32> vertices;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<CollisionDetection> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xAA5457FD;
    
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
