////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_KERNEL_MESHLIST_H
#define CLODDY_KERNEL_MESHLIST_H

#include "CodeX/System.h"

// Forward declare referenced classes.

namespace Cloddy { namespace Kernel { class CloddyKernel; } }
namespace Cloddy { namespace Kernel { class Mesh; } }

// Declare class ::Cloddy::Kernel::MeshList.

namespace Cloddy { namespace Kernel
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  A single linked list of Mesh_Terrain objects.
   */
  class MeshList : public virtual Object
  {
    // Declare friend classes.
    
    friend class CloddyKernel;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Number of meshes in the list.
     * 
     * @return <b>[>=0]</b>  The number of meshes in the list.
     */
    int32 GetCount();
    
    /*!
     * @brief  The head node or \c null  if the list is empty.
     * 
     * @return The head node or \c null .
     */
    Ptr<Mesh> GetHead();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Adds the given mesh to the list.
     * 
     * @param mesh <b>[not-null]</b>  The mesh to add.
     */
    void Add(Mesh* mesh);
    
    /*!
     * @brief  Returns all meshes from this list.
     * 
     * @return The former head node or \c null  if the list was already empty.
     */
    Ptr<Mesh> Clear();
    
    /*!
     * @brief  Moves all meshes in the given list to this one.
     * 
     * @param list <b>[not-null]</b>  The source list.
     */
    void MoveToThis(MeshList* list);
    
    /*!
     * @brief  Removes the given mesh from the list.
     * 
     * @param mesh <b>[not-null]</b>  The mesh to remove.
     */
    void Remove(Mesh* mesh);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Number of meshes in the list.
     */
    int32 count;
    
    /*!
     * @brief  The head node or \c null  if the list is empty.
     */
    Ptr<Mesh> head;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Removes all meshes from this list that are tagged for being recycled (
     *         see Mesh::needRecycle)and moves them to the given list.
     * 
     * @param meshesToRecycle The output list.
     */
    void RemoveToRecycle(MeshList* meshesToRecycle);
    
    /*!
     * @brief  Calls Mesh::ConcurrentUnlock (in any case)and IDisposable::Dispose (
     *         iff Mesh::needRecycle is \c false )on each mesh in the list.
     */
    void UnlockAndDisposeAll();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
  public:
    
    MeshList();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<MeshList> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x3D5525AA;
    
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
