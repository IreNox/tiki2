////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_KERNEL_IREFINEMENTBUFFER_H
#define CLODDY_KERNEL_IREFINEMENTBUFFER_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/InitialVertex.h"

// Include referenced interfaces.

#include "CodeX/IDisposable.h"

// Forward declare referenced classes.

namespace Cloddy { namespace Kernel { class Mesh; } }

// Declare interface ::Cloddy::Kernel::IRefinementBuffer.

namespace Cloddy { namespace Kernel
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using CodeX::System::IDisposable;
  
  /*!
   * @brief  The refinement buffer is responsible for buffering data between the render thread,the 
   *         refinement thread and the compute thread.
   */
  class NO_VTABLE IRefinementBuffer : public virtual IDisposable
  {
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Enqueues the following mesh structure update:add vertex (even,ie. LL-RR).
     * 
     * @param v The vertex to add.
     * @param l The left parent of \e v .
     * @param r The right parent of \e v .
     */
    virtual void AddEven(int32 v, int32 l, int32 r) = 0;
    
    /*!
     * @brief  Enqueues the following mesh structure update:add vertex (odd,ie. LR-RL).
     * 
     * @param v The vertex to add.
     * @param l The left parent of \e v .
     * @param r The right parent of \e v .
     */
    virtual void AddOdd(int32 v, int32 l, int32 r) = 0;
    
    /*!
     * @brief  Marks the beginning of the refinement of the given CLOD mesh.
     * 
     * @param mesh The CLOD mesh.
     */
    virtual void BeginMesh(Mesh* mesh) = 0;
    
    /*!
     * @brief  Stops all background activity of this refinement buffer.
     * 
     * This method is called when this refinement buffer is about to be disposed.
     */
    virtual void Cancel() = 0;
    
    /*!
     * @brief  Enqueues an existing mesh vertex for being computed again.
     * 
     * @param v The vertex to compute.
     * @param l The left parent of \e v .
     * @param r The right parent of \e v .
     * @param g The grand parent of \e v .
     * @param a The ancestor of \e v .
     */
    virtual void ComputeAgain(int32 v, int32 l, int32 r, int32 g, int32 a) = 0;
    
    /*!
     * @brief  Enqueues the computation of a new initial mesh vertex.
     * 
     * @param v The vertex to compute.
     * @param initialVertex The kind of the initial vertex.
     */
    virtual void ComputeNew(int32 v, InitialVertex initialVertex) = 0;
    
    /*!
     * @brief  Enqueues the computation of a new mesh vertex.
     * 
     * @param v The vertex to compute.
     * @param l The left parent of \e v .
     * @param r The right parent of \e v .
     * @param g The grand parent of \e v .
     * @param a The ancestor of \e v .
     */
    virtual void ComputeNew(int32 v, int32 l, int32 r, int32 g, int32 a) = 0;
    
    /*!
     * @brief  Enqueues the following mesh structure update:delete vertex (recursive).
     * 
     * @param v The root vertex.
     */
    virtual void Delete(int32 v) = 0;
    
    /*!
     * @brief  Enqueues the following mesh structure update:delete vertex (even,ie. LL-RR).
     * 
     * @param l Left parent of the deleted vertex.
     * @param r Right parent of the deleted vertex.
     */
    virtual void DeleteEven(int32 l, int32 r) = 0;
    
    /*!
     * @brief  Enqueues the following mesh structure update:delete vertex (odd,ie. LR-RL).
     * 
     * @param l Left parent of the deleted vertex.
     * @param r Right parent of the deleted vertex.
     */
    virtual void DeleteOdd(int32 l, int32 r) = 0;
    
    /*!
     * @brief  Marks the end of the current CLOD mesh refinement.
     */
    virtual void EndMesh() = 0;
    
    /*!
     * @brief  Marks the current CLOD mesh as initialized.
     */
    virtual void MeshInitialized() = 0;
    
    /*!
     * @brief  Enqueues the recomputation of an existing vertex.
     * 
     * @param v The vertex to recompute.
     * @param nl The nearest vertex in direction of the left parent of \e v .
     * @param nr The nearest vertex in direction of the right parent of \e v .
     * @param ng The nearest vertex in direction of the grand parent of \e v .
     * @param na The nearest vertex in direction of the ancestor of \e v .
     */
    virtual void Recompute(int32 v, int32 nl, int32 nr, int32 ng, int32 na) = 0;
    
    /*!
     * @brief  Applies all buffered CLOD mesh updates (mesh structure and vertex data).
     * 
     * @param userData Optional user data object to pass on to IVertexBuffer::LockBuffer.
     * 
     * @return \c true  if mesh updates have been applied,\c false  if the mesh update buffer was 
     * empty.
     */
    virtual bool Update(void* userData) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IRefinementBuffer> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x746F7B91;
    
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
      return (void*) 0;
    }
  };
} } 

#endif
