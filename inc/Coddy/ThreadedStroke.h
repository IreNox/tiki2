////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_BRUSHES_THREADEDSTROKE_H
#define CLODDY_API_HEIGHTMAPS_BRUSHES_THREADEDSTROKE_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/Stroke.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Brushes { class IStroke; } } } }
namespace Cloddy { namespace API { namespace Heightmaps { class IDirtyRegionCallback; } } }
namespace Cloddy { namespace API { namespace Heightmaps { class IHeightmap; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Brushes { class Stroke; } } } }
namespace Cloddy { namespace API { namespace Heightmaps { namespace Brushes { class ThreadedStroke_ThreadMain; } } } }
namespace Cloddy { namespace Core { namespace Threading { class Thread; } } }

// Declare class ::Cloddy::API::Heightmaps::Brushes::ThreadedStroke.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Brushes
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Heightmaps::IDirtyRegionCallback;
  using Cloddy::API::Heightmaps::IHeightmap;
  
  // Use referenced classes.
  
  using Cloddy::Core::Threading::Thread;
  
  /*!
   * @brief  An IStroke implementation that defers heightmap access and brush application to a 
   *         background thread.
   * 
   * When stroke painting is performed from within the render or UI thread,it is beneficial to use 
   * this class in order to avoid lags and interruptions that would be annoying to the user.
   */
  class ThreadedStroke : public Stroke
  {
    // Declare friend classes.
    
    friend class Stroke;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual bool IsComplete();
    
    virtual int32 GetOverlap();
    
    virtual void SetOverlap(int32 value);
    
    /*!
     * @brief  The stroke that is used for painting on the heightmap.
     * 
     * All calls made to this object through the IStroke interface will be delegated to the given 
     * stroke in a background thread.
     * 
     * The ThreadedStroke class ensures that the wrapped stroke object is not invoked from more 
     * than two threads at the same time.ie. the wrapped stroke need not be thread-safe.
     * 
     * @return <b>[not-null]</b>  The stroke.
     */
    Ptr<IStroke> GetStroke();
    
    /*!
     * @brief  The stroke that is used for painting on the heightmap.
     * 
     * All calls made to this object through the IStroke interface will be delegated to the given 
     * stroke in a background thread.
     * 
     * The ThreadedStroke class ensures that the wrapped stroke object is not invoked from more 
     * than two threads at the same time.ie. the wrapped stroke need not be thread-safe.
     * 
     * @param value <b>[not-null]</b>  The stroke.
     */
    void SetStroke(IStroke* value);
    
    virtual Ptr<IStroke> GetThreaded();
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
  protected:
    
    virtual void DisposeManaged();
    
    virtual void DisposeManagedChildren();
    
    virtual void DoBegin(IHeightmap* heightmap, IDirtyRegionCallback* dirtyRegionCallback);
    
    virtual int32 DoEnd();
    
    virtual void DoFinished();
    
    virtual void DoFlush();
    
    virtual void DoPoint(int32 x, int32 y, int32 z, int32 strength);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The stroke that is applied in a separate thread.
     */
    Ptr<IStroke> stroke;
    
    /*!
     * @brief  The background thread.
     */
    Ptr<Thread> thread;
    
    /*!
     * @brief  The worker object that performs stroke painting in a separate thread.
     */
    Ptr<ThreadedStroke_ThreadMain> threadMain;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of ThreadedStroke.
     * 
     * @param stroke The stroke to apply in a separate thread.
     */
    ThreadedStroke(IStroke* stroke);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<ThreadedStroke> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x1F7F8805;
    
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
      if ((ptr = Stroke::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } 

#endif
