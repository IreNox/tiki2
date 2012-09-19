////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_GEOMETRIES_GEOMETRY_FLIPZ_H
#define CLODDY_API_GEOMETRIES_GEOMETRY_FLIPZ_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/Handedness.h"

// Include referenced classes.

#include "Cloddy/GeometryBase.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Geometries { class IGeometry; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Geometries { class GeometryBase; } } }
namespace Cloddy { namespace API { namespace Geometries { class GeometrySample; } } }

// Declare class ::Cloddy::API::Geometries::Geometry_FlipZ.

namespace Cloddy { namespace API { namespace Geometries
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  An implementation of the IGeometry interface that flips the output of an 
   *         aggregated IGeometry object around the terrain-space Z-axis.
   */
  class Geometry_FlipZ : public GeometryBase
  {
    // Declare friend classes.
    
    friend class GeometryBase;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual float64 GetBoundingSphereRadius();
    
    virtual Handedness GetHandedness();
    
    virtual float64 GetMaximumDisplacement();
    
    virtual void SetMaximumDisplacement(float64 value);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void ComputeHeightmapCoordinatesAndElevation(GeometrySample* sample);
    
    virtual void ComputeVertexPosition(GeometrySample* sample);
    
    virtual Ptr<IGeometry> ToHandedness(Handedness handedness);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The original geometry.
     */
    Ptr<IGeometry> geometry;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of Geometry_FlipZ.
     * 
     * @param geometry The original geometry.
     */
    Geometry_FlipZ(IGeometry* geometry);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<Geometry_FlipZ> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xE5E9322;
    
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
      if ((ptr = GeometryBase::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
