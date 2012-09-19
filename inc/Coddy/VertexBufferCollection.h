////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_KERNEL_VERTEXBUFFERCOLLECTION_H
#define CLODDY_KERNEL_VERTEXBUFFERCOLLECTION_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IVertexBufferCollection.h"

// Include referenced classes.

#include "CodeX/Disposable.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Collections { template<class> class IList; } } }
namespace Cloddy { namespace Kernel { class IVertexBuffer; } }

// Declare class ::Cloddy::Kernel::VertexBufferCollection.

namespace Cloddy { namespace Kernel
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::Collections::IList;
  
  // Use referenced classes.
  
  using CodeX::System::Disposable;
  
  /*!
   * @brief  A collection of IVertexBuffer instances.
   * 
   * During CLOD mesh refinement,vertex data is produced by an IVertexFactory object and then 
   * stored in one or more vertex buffers (typically on the GPU).Each vertex buffer will receive 
   * the same data.In most cases,only one vertex buffer will be needed;however,when performing 
   * stereoscopic rendering via multiply GPUs,multiple vertex buffers may be necessary.
   */
  class VertexBufferCollection : public Disposable, public virtual IVertexBufferCollection
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual int32 GetCapacity();
    
    virtual int32 GetCount();
    
    virtual int32 GetVertexSize();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of VertexBufferCollection.
     */
    VertexBufferCollection();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new IVertexBufferCollection instance that contains no vertex buffers.
     * 
     * The #Empty method can be used when it is not necessary to generate GPU vertex data (eg. when 
     * exporting triangle meshes from a CLOD mesh during a preprocessing step).
     * 
     * @param capacity The capacity of the vertex buffer collection.
     * @param vertexSize The vertex size of the vertex buffer collection,in bytes.
     * 
     * @return <b>[not-null]</b>  The created IVertexBufferCollection object.
     */
    static Ptr<IVertexBufferCollection> Empty(int32 capacity, int32 vertexSize);
    
    /*!
     * @brief  Wraps the given IVertexBuffer object in a VertexBufferCollection.
     * 
     * @param vertexBuffer <b>[not-null]</b>  The vertex buffer to wrap.
     * 
     * @return <b>[not-null]</b>  The VertexBufferCollection object.
     */
    static Ptr<IVertexBufferCollection> Wrap(IVertexBuffer* vertexBuffer);
    
    /*!
     * @brief  Wraps the given IVertexBuffer objects in a VertexBufferCollection.
     * 
     * @param vertexBuffers <b>[not-null]</b>  The vertex buffers to wrap.
     * 
     * @return <b>[not-null]</b>  The VertexBufferCollection object.
     */
    static Ptr<IVertexBufferCollection> Wrap(Array<Ptr<IVertexBuffer> > vertexBuffers);
    
    /*!
     * @brief  Adds a IVertexBuffer to this collection.
     * 
     * It is not allowed to add a vertex buffer to a collection \e after  it has been used to 
     * create a CloddyKernel instance.
     * 
     * @param vertexBuffer <b>[not-null]</b>  The vertex buffer to add.
     */
    void Add(IVertexBuffer* vertexBuffer);
    
    virtual Ptr<IVertexBuffer> Get(int32 index);
    
    /*!
     * @brief  Removes a IVertexBuffer from this collection.
     * 
     * @param vertexBuffer <b>[not-null]</b>  The vertex buffer to remove.
     */
    void Remove(IVertexBuffer* vertexBuffer);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
  protected:
    
    virtual void DisposeManaged();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The capacity of this vertex buffer collection,in vertices.
     */
    int32 capacity;
    
    /*!
     * @brief  The list of vertex buffers.
     */
    Ptr<IList<Ref<IVertexBuffer> > > vertexBuffers;
    
    /*!
     * @brief  The size of a single vertex,in bytes.
     */
    int32 vertexSize;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<VertexBufferCollection> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xFCA0D8FF;
    
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
      if ((ptr = Disposable::TryCast(typeId)) != 0) return ptr;
      if ((ptr = IVertexBufferCollection::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } 

#endif
