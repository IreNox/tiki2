////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_MESHVISITORS_DISTANCETOGROUND_H
#define CLODDY_API_MESHVISITORS_DISTANCETOGROUND_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/MeshFace.h"

// Include referenced interfaces.

#include "Cloddy/IMeshVisitor.h"

// Include referenced structures.

#include "Cloddy/Vec3D.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace VertexData { class IVertexData; } } }
namespace Cloddy { namespace Kernel { class IMesh; } }
namespace Cloddy { namespace Kernel { class IProvider; } }

// Forward declare referenced classes.

namespace Cloddy { namespace Kernel { class Traversal; } }
namespace Cloddy { namespace Core { namespace Math { namespace Vectors { struct Vec3D; } } } }

// Declare class ::Cloddy::API::MeshVisitors::DistanceToGround.

namespace Cloddy { namespace API { namespace MeshVisitors
{
  // Use referenced namespaces.
  
  using namespace Cloddy::Kernel;
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::VertexData::IVertexData;

  // Use referenced structures.

  using Cloddy::Core::Math::Vectors::Vec3D;
  
  /*!
   * @brief  Computes the nearest distance from the specified point in terrain-space to the terrain 
   *         surface of the traversed CLOD mesh sectors.
   * 
   * The following vertex data semantics are used by this class (\e opt  means that the semantic 
   * will be used if present,\e req  means that the semantic must be present):
   *   - \e req  - Semantic::Position
   *   - \e req  - Semantic::Radius
   */
  class DistanceToGround : public virtual IMeshVisitor
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual void BeginFace(MeshFace face);
    
    virtual void BeginMeshAction(IProvider* provider);

    /*!
     * @brief  Computes the nearest distance from the given position in terrain-space to the specified 
     *         CLOD mesh.
     * 
     * @param position A position in terrain-space.
     * @param mesh The CLOD mesh.
     * 
     * @return The nearest distance to the terrain surface,in terrain-space.
     */
    float64 ComputeNearestDistance(Vec3D& position, IMesh* mesh);
    
    /*!
     * @brief  Computes the nearest distance from the given position in terrain-space to the specified 
     *         CLOD mesh.
     * 
     * @param pointX X-coordinate of the position in terrain-space.
     * @param pointY Y-coordinate of the position in terrain-space.
     * @param pointZ Z-coordinate of the position in terrain-space.
     * @param mesh The CLOD mesh.
     * 
     * @return The nearest distance to the terrain surface,in terrain-space.
     */
    float64 ComputeNearestDistance(float64 pointX, float64 pointY, float64 pointZ, IMesh* mesh);

    /*!
     * @brief  Computes the nearest position from the given position in terrain-space to the specified 
     *         CLOD mesh.
     * 
     * @param position A position in terrain-space.
     * @param mesh The CLOD mesh.
     * 
     * @return The nearest position to the terrain surface,in terrain-space.
     */
    Vec3D ComputeNearestPosition(Vec3D& position, IMesh* mesh);

    /*!
     * @brief  Computes the nearest position from the given position in terrain-space to the specified 
     *         CLOD mesh.
     * 
     * @param pointX X-coordinate of the position in terrain-space.
     * @param pointY Y-coordinate of the position in terrain-space.
     * @param pointZ Z-coordinate of the position in terrain-space.
     * @param mesh The CLOD mesh.
     * 
     * @return The nearest position to the terrain surface,in terrain-space.
     */
    Vec3D ComputeNearestPosition(float64 pointX, float64 pointY, float64 pointZ, IMesh* mesh);
    
    virtual void EndFace();
    
    virtual void EndMeshAction();
    
    virtual void VisitSector(Traversal* traversal, int32 userData);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:

    /*!
     * @brief  The position in terrain-space from which to calculate the nearest distance and nearest 
     *         position to the terrain surface.
     */     
    Vec3D position;

    /*!
     * @brief  The current nearest position.
     */
    Vec3D nearestPosition;

    /*!
     * @brief  The current nearest distance.
     */
    float64 nearestDistance;
    
    /*!
     * @brief  Vertices position container.
     */
    Ptr<IVertexData> verticesPositionContainer;
    
    /*!
     * @brief  Vertices bounding sphere radii container.
     */
    Ptr<IVertexData> verticesRadiusContainer;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
  public:
    
    DistanceToGround();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<DistanceToGround> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x5AD73BCD;
    
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
