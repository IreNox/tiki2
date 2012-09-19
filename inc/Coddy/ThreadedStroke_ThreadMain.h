////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_BRUSHES_THREADEDSTROKE_THREADMAIN_H
#define CLODDY_API_HEIGHTMAPS_BRUSHES_THREADEDSTROKE_THREADMAIN_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IDirtyRegionCallback.h"
#include "Cloddy/IThreadJoinCallback.h"

// Include referenced classes.

#include "Cloddy/ThreadMainBase.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Brushes { class IStroke; } } } }
namespace Cloddy { namespace API { namespace Heightmaps { class IHeightmap; } } }
namespace Cloddy { namespace Core { namespace Threading { class IThreadContext; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Brushes { class ThreadedStroke; } } } }
namespace CodeX { namespace System { class Monitor; } }

// Declare class ::Cloddy::API::Heightmaps::Brushes::ThreadedStroke_ThreadMain.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Brushes
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Heightmaps::IDirtyRegionCallback;
  using Cloddy::API::Heightmaps::IHeightmap;
  using Cloddy::Core::Threading::IThreadContext;
  using Cloddy::Core::Threading::IThreadJoinCallback;
  
  // Use referenced classes.
  
  using Cloddy::Core::Threading::ThreadMainBase;
  using CodeX::System::Monitor;
  
  /*!
   * @brief  This thread performs the background work for the ThreadedStroke class.
   */
  class ThreadedStroke_ThreadMain : public ThreadMainBase, public virtual IThreadJoinCallback, public virtual IDirtyRegionCallback
  {
    // Declare friend classes.
    
    friend class ThreadedStroke;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual void MarkAsDirty(int32 faceX, int32 faceY, int32 face, int32 width, int32 height);
    
    virtual void Run(IThreadContext* argument);
    
    virtual void WaitingForStop();
    
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
     * @brief  Returns if all background work has finished.
     * 
     * @return \c true  if all background work has finished,\c false  if not.
     */
    bool IsComplete();
    
    /*!
     * @brief  Begin a new stroke?
     */
    bool begin;
    
    Ptr<IThreadContext> context;
    
    /*!
     * @brief  Buffer for dirty regions.
     */
    Array<int32> dirty;
    
    /*!
     * @brief  Current read index for #dirty.
     */
    int32 dirtyReadIdx;
    
    /*!
     * @brief  Number of dirty rectangles current stored in #dirty.
     */
    int32 dirtyReadable;
    
    /*!
     * @brief  The dirty region callback to use.
     */
    Ptr<IDirtyRegionCallback> dirtyRegionCallback;
    
    /*!
     * @brief  Current write index for #dirty.
     */
    int32 dirtyWriteIdx;
    
    /*!
     * @brief  Number of dirty rectangles that can be written to #dirty.
     */
    int32 dirtyWriteable;
    
    /*!
     * @brief  Has the sequence of control points finished?
     */
    bool finished;
    
    /*!
     * @brief  The current heightmap.
     */
    Ptr<IHeightmap> heightmap;
    
    /*!
     * @brief  The monitor object used for synchronization.
     */
    Ptr<Monitor> monitor;
    
    /*!
     * @brief  The number of times the brush has been applied on this stroke (is set after the 
     *         stroke has ended).
     */
    int32 n;
    
    /*!
     * @brief  Stores the control points of the stroke.
     */
    Array<int32> points;
    
    /*!
     * @brief  Current read index for #points.
     */
    int32 pointsReadIdx;
    
    /*!
     * @brief  Number of control points currently stored in #points.
     */
    int32 pointsReadable;
    
    /*!
     * @brief  Current write index for #points.
     */
    int32 pointsWriteIdx;
    
    /*!
     * @brief  Number of control points that can be written to #points.
     */
    int32 pointsWriteable;
    
    /*!
     * @brief  Stores the relative strength values of each control point.
     * 
     * @see #points
     */
    Array<int32> strength;
    
    /*!
     * @brief  The stroke to apply to the heightmap.
     */
    Ptr<IStroke> stroke;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of ThreadedStroke_ThreadMain.
     */
    ThreadedStroke_ThreadMain();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Begins a new stroke.
     * 
     * @param stroke The IStroke to use.
     * @param heightmap The IHeightmap to use.
     * @param dirtyRegionCallback The IDirtyRegionCallback to use.
     */
    void Begin(IStroke* stroke, IHeightmap* heightmap, IDirtyRegionCallback* dirtyRegionCallback);
    
    /*!
     * @brief  Ends the current stroke.
     * 
     * @return The number of times the brush has been applied for the stroke.
     */
    int32 End();
    
    /*!
     * @brief  Finishes the current stroke.
     */
    void Finished();
    
    /*!
     * @brief  Flushes all buffered dirty regions.
     */
    void FlushDirty();
    
    /*!
     * @brief  Adds a new control point to the stroke.
     * 
     * @param x X-coordinate of control point.
     * @param y Y-coordinate of control point.
     * @param z Z-coordinate of control point.
     * @param strength Relative strength of control point.
     */
    void Point(int32 x, int32 y, int32 z, int32 strength);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<ThreadedStroke_ThreadMain> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xBA8EEEF7;
    
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
      if ((ptr = ThreadMainBase::TryCast(typeId)) != 0) return ptr;
      if ((ptr = IThreadJoinCallback::TryCast(typeId)) != 0) return ptr;
      if ((ptr = IDirtyRegionCallback::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } 

#endif
