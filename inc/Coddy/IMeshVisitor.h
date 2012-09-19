////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_KERNEL_IMESHVISITOR_H
#define CLODDY_KERNEL_IMESHVISITOR_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/MeshFace.h"

// Include referenced interfaces.

#include "Cloddy/IMeshCallback.h"

// Forward declare referenced classes.

namespace Cloddy { namespace Kernel { class Traversal; } }

// Declare interface ::Cloddy::Kernel::IMeshVisitor.

namespace Cloddy { namespace Kernel
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Base interface for classes that implement a CLOD mesh traversal 
   *         via Mesh_Terrain::TraverseSectors.
   */
  class NO_VTABLE IMeshVisitor : public virtual IMeshCallback
  {
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  This method is called each time a mesh face is about to be traversed.
     * 
     * @param face The mesh face that is about to be traversed.
     */
    virtual void BeginFace(MeshFace face) = 0;
    
    /*!
     * @brief  This method is called when the traversal of a mesh face has finished.
     */
    virtual void EndFace() = 0;
    
    /*!
     * @brief  Visits a sector of the mesh.
     * 
     * Implementing methods may call the Traversal::VisitSubsectors to continue the traversal.
     * 
     * @param traversal The Traversal object that represents the current CLOD mesh traversal.
     * @param userData Optional user data to pass down during mesh traversal.
     */
    virtual void VisitSector(Traversal* traversal, int32 userData) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IMeshVisitor> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xC72AEF5F;
    
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
      if ((ptr = IMeshCallback::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
} } 

#endif
