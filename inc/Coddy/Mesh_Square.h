////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_KERNEL_MESH_SQUARE_H
#define CLODDY_KERNEL_MESH_SQUARE_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/BaseGeometry.h"
#include "Cloddy/InitialVertex.h"

// Include referenced classes.

#include "Cloddy/Mesh_Terrain.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Kernel { class IProvider; } }
namespace Cloddy { namespace Kernel { class IRefinementBuffer; } }
namespace Cloddy { namespace Kernel { class IVertexFactory; } }
namespace Cloddy { namespace Kernel { class IVisibilityCriterion; } }

// Forward declare referenced classes.

namespace Cloddy { namespace Kernel { class CloddyKernel; } }
namespace Cloddy { namespace Kernel { class Licence; } }

// Declare class ::Cloddy::Kernel::Mesh_Square.

namespace Cloddy { namespace Kernel
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  A Mesh_Terrain implementation for CLOD meshes that use 
   *         the BaseGeometry::BaseGeometry_Square base geometry.
   */
  class Mesh_Square : public Mesh_Terrain
  {
    // Declare friend classes.
    
    friend class CloddyKernel;
    friend class Licence;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual BaseGeometry GetBaseGeometry();
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
  protected:
    
    virtual void RefineRootVertex(int32 v, int32 l, int32 r, int32 g, int32 a);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The initial vertex IDs.
     */
    static const Array<InitialVertex> Vertices;
    
    /*!
     * @brief  Indices of the initial mesh vertices.
     */
    static Array<int32> indices;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of Mesh_Square.
     * 
     * @param cloddyKernel The Cloddy Kernel instance.
     * @param refinementLevels The number of refinement levels.
     * @param provider The IProvider object of the mesh.
     * @param vertexFactory The vertex factory for this mesh.
     * @param visibilityCriterion The visibility criterion for this mesh.
     */
    Mesh_Square(CloddyKernel* cloddyKernel, int32 refinementLevels, IProvider* provider, IVertexFactory* vertexFactory, IVisibilityCriterion* visibilityCriterion);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void Initialize(IRefinementBuffer* refinementBuffer);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<Mesh_Square> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x19B0E8C8;
    
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
      if ((ptr = Mesh_Terrain::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } 

#endif
