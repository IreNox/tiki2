////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_KERNEL_IREFINEMENTPROGRESS_H
#define CLODDY_KERNEL_IREFINEMENTPROGRESS_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/RefinementStatus.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Kernel { class IRefinementCallback; } }

// Declare interface ::Cloddy::Kernel::IRefinementProgress.

namespace Cloddy { namespace Kernel
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  This interface provides information about the progress of CLOD mesh refinement.
   */
  class NO_VTABLE IRefinementProgress : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Shall refinement be paused when it has finished?
     * 
     * When the background refinement has been paused,the application must explicitly resume it by 
     * calling #ResumeRefinement (usually when the visibility criterion parameters have changed).
     * 
     * @return \c true  if refinement shall be paused when it has finished,\c false  to keep 
     * background refinement active even if an optimal mesh structure has been reached.
     */
    virtual bool GetPauseOnFinished() = 0;
    
    /*!
     * @brief  Shall refinement be paused when it has finished?
     * 
     * When the background refinement has been paused,the application must explicitly resume it by 
     * calling #ResumeRefinement (usually when the visibility criterion parameters have changed).
     * 
     * @param value \c true  if refinement shall be paused when it has finished,\c false  to keep 
     * background refinement active even if an optimal mesh structure has been reached.
     */
    virtual void SetPauseOnFinished(bool value) = 0;
    
    /*!
     * @brief  Returns the number of vertices for which computations where still pending during the 
     *         most recent refinement cycle.
     * 
     * @return <b>[>=0]</b>  The number of pending vertices.
     */
    virtual int32 GetPendingVerticesCount() = 0;
    
    /*!
     * @brief  Returns the progress of the refinement,in percent.
     * 
     * A value of \c 100  means that refinement has reached an optimal mesh structure,ie. no more 
     * vertices will be added to or removed from any CLOD meshes.
     * 
     * @return <b>[0..100]</b>  The refinement progress,in percent.
     */
    virtual int32 GetProgressInPercent() = 0;
    
    /*!
     * @brief  Returns the current refinement status.
     * 
     * @return The current refinement status.
     */
    virtual RefinementStatus GetStatus() = 0;
    
    /*!
     * @brief  Returns the number of vertices that have been tested for visibility during the most 
     *         recent refinement cycle.
     * 
     * @return <b>[>=0]</b>  The number of tested vertices.
     */
    virtual int32 GetTestedVerticesCount() = 0;
    
    /*!
     * @brief  Returns the number of vertices that have been activated resp. deactivated (ie. made 
     *         visible or invisible)during the most recent refinement cycle based on the result of 
     *         the visibility test.
     * 
     * @return <b>[>=0]</b>  The number of toggled vertices.
     */
    virtual int32 GetToggledVerticesCount() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Adds the given refinement callback.
     * 
     * @param callback <b>[not-null]</b>  The callback to add.
     */
    virtual void AddRefinementCallback(IRefinementCallback* callback) = 0;
    
    /*!
     * @brief  Removes the given refinement callback.
     * 
     * @param callback <b>[not-null]</b>  The callback to remove.
     */
    virtual void RemoveRefinementCallback(IRefinementCallback* callback) = 0;
    
    /*!
     * @brief  Resumes background refinement.
     * 
     * This method must be called iff #GetPauseOnFinished has been set to \c true  and background 
     * refinement has finished (ie. when #GetStatus is RefinementStatus::RefinementStatus_Paused).
     * Otherwise,refinement will not continue and the mesh structure will remain unchanged,even if 
     * the parameters of the visibility criterion are changed.
     * 
     * If this method is called in other cases it performs no action and silently returns.
     */
    virtual void ResumeRefinement() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IRefinementProgress> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x8A7805C4;
    
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
