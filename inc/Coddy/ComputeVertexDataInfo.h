////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_MESHVISITORS_COMPUTEVERTEXDATAINFO_H
#define CLODDY_API_MESHVISITORS_COMPUTEVERTEXDATAINFO_H

#include "CodeX/System.h"

// Include referenced structures.

#include "Cloddy/Vec3D.h"

// Declare class ::Cloddy::API::MeshVisitors::ComputeVertexDataInfo.

namespace Cloddy { namespace API { namespace MeshVisitors
{
  // Use referenced namespaces.
  
  using namespace CodeX;

  // Use referenced structures.

  using Cloddy::Core::Math::Vectors::Vec3D;
  
  /*!
   * @brief  Represents a vertex data info.
   */
  class ComputeVertexDataInfo : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:

    /*!
     * @brief The computed vertex position in terrain-space.
     */
    Vec3D Position;

    /*!
     * @brief The computed vertex normal in terrain-space.
     */
    Vec3D Normal;

    /*!
     * @brief The computed vertex color.
     */
    int32 Color;

    /*!
     * @brief The computed vertex elevation.
     */
    float64 Elevation;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    ComputeVertexDataInfo();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<ComputeVertexDataInfo> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x26E2CE8B;
    
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
