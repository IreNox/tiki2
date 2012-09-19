////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_GEOMETRIES_GEOMETRYBASE_H
#define CLODDY_API_GEOMETRIES_GEOMETRYBASE_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/Handedness.h"

// Include referenced interfaces.

#include "Cloddy/IGeometry.h"

// Forward declare referenced structures.

namespace Cloddy { namespace Core { namespace Math { namespace Vectors { struct Mat4D; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Geometries { class GeometrySample; } } }

// Declare class ::Cloddy::API::Geometries::GeometryBase.

namespace Cloddy { namespace API { namespace Geometries
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced structures.
  
  using Cloddy::Core::Math::Vectors::Mat4D;
  
  /*!
   * @brief  Abstract base class for IGeometry implementations.
   */
  class GeometryBase : public virtual IGeometry
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual float64 GetBoundingSphereRadius() = 0;
    
    virtual Handedness GetHandedness() = 0;
    
    virtual float64 GetMaximumDisplacement() = 0;
    
    virtual void SetMaximumDisplacement(float64 value) = 0;
    
    virtual int32 GetSize();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void ComputeHeightmapCoordinatesAndElevation(GeometrySample* sample) = 0;
    
    virtual void ComputeVertexPosition(GeometrySample* sample) = 0;
    
    virtual Ptr<IGeometry> ToHandedness(Handedness handedness);
    
    virtual Ptr<IGeometry> Transform(const Mat4D& matrix);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Constructors
    // ---------------------------------------------------------------------------------------------
  protected:
    
    /*!
     * @brief  Creates a new instance of GeometryBase.
     * 
     * @param size <b>[pow2+1]</b>  The internal map size.
     */
    GeometryBase(int32 size);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The internal map size.
     */
    int32 size;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<GeometryBase> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x818FC6FF;
    
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
      if ((ptr = IGeometry::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
