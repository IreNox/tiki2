////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_KERNEL_TRAVERSAL_H
#define CLODDY_KERNEL_TRAVERSAL_H

#include "CodeX/System.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Kernel { class IMeshVisitor; } }

// Declare class ::Cloddy::Kernel::Traversal.

namespace Cloddy { namespace Kernel
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Base interface for classes that traverse a hierarchical CLOD mesh.
   */
  class Traversal : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Index of center vertex of parent of cector being visited or CloddyKernel::Void for 
     *         root sectors.
     */
    int32 Parent;
    
    /*!
     * @brief  Index of center vertex of sector being visited or CloddyKernel::Void for leaf 
     *         sectors.
     */
    int32 Vertex;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Returns the vertices of this mesh sector as a triangle fan.
     * 
     * The triangles of the returned triangle fan are oriented in counter-clockwise direction.
     * 
     * @param vertices <b>[not-null]</b>  The vertex indices will be stored here.
     * 
     * @return <b>[3..10]</b>  The number of emitted vertices.
     */
    virtual int32 GetVertices(Array<int32> vertices) = 0;
    
    /*!
     * @brief  Performs mesh triangulation for the mesh sector currently being visited.
     */
    virtual void Triangulate() = 0;
    
    /*!
     * @brief  Visits all subsectors of the current mesh sector.
     * 
     * @param meshVisitor <b>[not-null]</b>  The IMeshVisitor to use for visiting the subsectors.
     * @param userData Optional user data to pass down during mesh traversal.
     */
    virtual void VisitSubsectors(IMeshVisitor* meshVisitor, int32 userData) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    Traversal();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<Traversal> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x14D3D439;
    
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
  
} } 

#endif
