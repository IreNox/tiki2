////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_KERNEL_REFINEMENTPROGRESS_H
#define CLODDY_KERNEL_REFINEMENTPROGRESS_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/RefinementStatus.h"

// Include referenced interfaces.

#include "Cloddy/IRefinementProgress.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Collections { template<class> class IList; } } }
namespace Cloddy { namespace Kernel { class IRefinementCallback; } }

// Forward declare referenced classes.

namespace Cloddy { namespace Kernel { class Mesh; } }
namespace Cloddy { namespace Kernel { class RefinementProgressValues; } }

// Declare class ::Cloddy::Kernel::RefinementProgress.

namespace Cloddy { namespace Kernel
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::Collections::IList;
  
  /*!
   * @brief  Default implementation of the IRefinementProgress interface.
   */
  class RefinementProgress : public virtual IRefinementProgress
  {
    // Declare friend classes.
    
    friend class Mesh;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual bool GetPauseOnFinished();
    
    virtual void SetPauseOnFinished(bool value);
    
    virtual int32 GetPendingVerticesCount();
    
    virtual int32 GetProgressInPercent();
    
    virtual RefinementStatus GetStatus();
    
    virtual int32 GetTestedVerticesCount();
    
    virtual int32 GetToggledVerticesCount();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void AddRefinementCallback(IRefinementCallback* callback);
    
    virtual void RemoveRefinementCallback(IRefinementCallback* callback);
    
    virtual void ResumeRefinement();
    
    /*!
     * @brief  Updates the refinement progress.
     * 
     * @param source <b>[not-null]</b>  The source object to use for invoking callbacks.
     * @param values <b>[not-null]</b>  The new refinement progress values.
     */
    void SetProgress(IRefinementProgress* source, RefinementProgressValues* values);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Pause refinement when finished?
     */
    bool pauseOnFinished;
    
    /*!
     * @brief  The number of vertices for which computations where still pending during the most 
     *         recent refinement cycle.
     */
    int32 pendingVerticesCount;
    
    /*!
     * @brief  The progress of the refinement,in percent.
     */
    int32 progressInPercent;
    
    /*!
     * @brief  The current list of registered refinement callbacks.
     */
    Ptr<IList<Ref<IRefinementCallback> > > refinementCallbacks;
    
    /*!
     * @brief  The current refinement status value.
     */
    RefinementStatus status;
    
    /*!
     * @brief  The number of vertices that have been tested for visibility during the most recent 
     *         refinement cycle.
     */
    int32 testedVerticesCount;
    
    /*!
     * @brief  The number of vertices that have been activated resp. deactivated (ie. made visible 
     *         or invisible)during the most recent refinement cycle based on the result of the 
     *         visibility test.
     */
    int32 toggledVerticesCount;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of RefinementProgress.
     */
    RefinementProgress();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Invokes the IRefinementCallback::RefinementFinished method on each registered 
     *         callback.
     * 
     * @param source The source object to use.
     */
    void FireRefinementFinished(IRefinementProgress* source);
    
    /*!
     * @brief  Invokes the IRefinementCallback::RefinementStarted method on each registered 
     *         callback.
     * 
     * @param source The source object to use.
     */
    void FireRefinementStarted(IRefinementProgress* source);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<RefinementProgress> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xE272BE0D;
    
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
      if ((ptr = IRefinementProgress::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } 

#endif
