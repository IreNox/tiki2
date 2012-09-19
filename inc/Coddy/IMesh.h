////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_KERNEL_IMESH_H
#define CLODDY_KERNEL_IMESH_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/BaseGeometry.h"
#include "Cloddy/MeshFace.h"

// Include referenced interfaces.

#include "CodeX/IDisposable.h"
#include "Cloddy/IRefinementProgress.h"
#include "Cloddy/IUserData.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Kernel { class IMeshVisitor; } }
namespace Cloddy { namespace Kernel { class IProvider; } }
namespace Cloddy { namespace Kernel { class IVertexFactory; } }
namespace Cloddy { namespace Kernel { class IVisibilityCriterion; } }

// Forward declare referenced classes.

namespace Cloddy { namespace Kernel { class CloddyKernel; } }

// Declare interface ::Cloddy::Kernel::IMesh.

namespace Cloddy { namespace Kernel
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using CodeX::System::IDisposable;
  
  /*!
   * @brief  Base interface for CLOD meshes.
   */
  class NO_VTABLE IMesh : public virtual IDisposable, public virtual IRefinementProgress, public virtual IUserData
  {
    // ---------------------------------------------------------------------------------------------
    // Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The base geometry of this CLOD mesh.
     * 
     * @return The base geometry.
     */
    virtual BaseGeometry GetBaseGeometry() = 0;
    
    /*!
     * @brief  Return the #GetKernel which this CLOD mesh belongs to.
     * 
     * @return <b>[not-null]</b>  The #GetKernel instance.
     */
    virtual Ptr<CloddyKernel> GetKernel() = 0;
    
    /*!
     * @brief  The component IProvider of this CLOD mesh.
     * 
     * @return <b>[not-null]</b>  The IProvider instance.
     */
    virtual Ptr<IProvider> GetProvider() = 0;
    
    /*!
     * @brief  The IVertexFactory this CLOD mesh uses.
     * 
     * @return <b>[not-null]</b>  The IVertexFactory instance.
     */
    virtual Ptr<IVertexFactory> GetVertexFactory() = 0;
    
    /*!
     * @brief  The IVisibilityCriterion this CLOD mesh uses.
     * 
     * @return <b>[not-null]</b>  The IVisibilityCriterion.
     */
    virtual Ptr<IVisibilityCriterion> GetVisibilityCriterion() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Traverses the root sectors of the given mesh faces.
     * 
     * @param meshFace The mesh face to traverse.
     * @param visitor <b>[not-null]</b>  The sector visitor object to use.
     * @param userData Optional user data to pass to sector visitor.
     */
    virtual void TraverseSectors(MeshFace meshFace, IMeshVisitor* visitor, int32 userData) = 0;
    
    /*!
     * @brief  Triangulates the given mesh face.
     * 
     * A triangle strip is generated that reflects the current mesh structure of this CLOD mesh.The 
     * strip is divided into chunks (see CloddyKernelOptions::GetTriangleStripChunkSize),and each 
     * triangle strip chunk is forwarded to the application via the current ITriangulationCallback 
     * object (see CloddyKernel::BeginTriangulation).
     * 
     * The generated triangle strip chunks can be used for immediate rendering.The application can 
     * of course choose to buffer the chunks,which is more efficient for multi-pass rendering (
     * triangulation is only performed once per frame,and not once per pass).
     * 
     * @param meshFace The mesh face to triangulate.
     */
    virtual void Triangulate(MeshFace meshFace) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IMesh> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x4C93A95F;
    
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
      if ((ptr = IDisposable::TryCast(typeId)) != 0) return ptr;
      if ((ptr = IRefinementProgress::TryCast(typeId)) != 0) return ptr;
      if ((ptr = IUserData::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
} } 

#endif
