////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_KERNEL_MESH_VOLUME_H
#define CLODDY_KERNEL_MESH_VOLUME_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/BaseGeometry.h"
#include "Cloddy/MeshFace.h"

// Include referenced classes.

#include "Cloddy/Mesh.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Kernel { class IMeshVisitor; } }
namespace Cloddy { namespace Kernel { class IProvider; } }
namespace Cloddy { namespace Kernel { class IRefinementBuffer; } }
namespace Cloddy { namespace Kernel { class IVertexFactory; } }
namespace Cloddy { namespace Kernel { class IVisibilityCriterion; } }

// Forward declare referenced classes.

namespace Cloddy { namespace Kernel { class CloddyKernel; } }

// Declare class ::Cloddy::Kernel::Mesh_Volume.

namespace Cloddy { namespace Kernel
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  class Mesh_Volume : public Mesh
  {
    // Declare friend classes.
    
    friend class CloddyKernel;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual BaseGeometry GetBaseGeometry();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void TraverseSectors(MeshFace meshFace, IMeshVisitor* visitor, int32 userData);
    
    virtual void Triangulate(MeshFace meshFace);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
  protected:
    
    virtual void DisposeManaged();
    
    virtual void RefineVertices();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    Array<int32> black;
    
    Array<int32> blue;
    
    Array<int32> cyan;
    
    Array<int32> green;
    
    Array<int32> magenta;
    
    Array<int32> red;
    
    Array<int32> white;
    
    Array<int32> yellow;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of Mesh_Volume.
     * 
     * @param kernel The Cloddy Kernel instance.
     * @param refinementLevels The number of refinement levels.
     * @param provider The IProvider object of the mesh.
     * @param vertexFactory The vertex factory for this mesh.
     * @param visibilityCriterion The visibility criterion for this mesh.
     */
    Mesh_Volume(CloddyKernel* kernel, int32 refinementLevels, IProvider* provider, IVertexFactory* vertexFactory, IVisibilityCriterion* visibilityCriterion);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void Initialize(IRefinementBuffer* refinementBuffer);
    
    virtual void Recycle();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<Mesh_Volume> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xA39F8739;
    
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
      if ((ptr = Mesh::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } 

#endif
