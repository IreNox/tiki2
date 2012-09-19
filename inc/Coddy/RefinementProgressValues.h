////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_KERNEL_REFINEMENTPROGRESSVALUES_H
#define CLODDY_KERNEL_REFINEMENTPROGRESSVALUES_H

#include "CodeX/System.h"

// Declare class ::Cloddy::Kernel::RefinementProgressValues.

namespace Cloddy { namespace Kernel
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Helper object for dealing with refinement progress values.
   */
  class RefinementProgressValues : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Returns the number of vertices for which computations where still pending during the 
     *         most recent refinement cycle.
     * 
     * @return <b>[>=0]</b>  The number of pending vertices.
     */
    int32 GetPendingVerticesCount();
    
    /*!
     * @brief  Returns the number of vertices for which computations where still pending during the 
     *         most recent refinement cycle.
     * 
     * @param value <b>[>=0]</b>  The number of pending vertices.
     */
    void SetPendingVerticesCount(int32 value);
    
    /*!
     * @brief  Returns the progress of the refinement,in percent.
     * 
     * @return <b>[0..100]</b>  The refinement progress,in percent.
     */
    int32 GetProgressInPercent();
    
    /*!
     * @brief  The number of vertices that have been tested for visibility during the most recent 
     *         refinement cycle.
     * 
     * @return <b>[>=0]</b>  The vertex count.
     */
    int32 GetTestedVerticesCount();
    
    /*!
     * @brief  The number of vertices that have been tested for visibility during the most recent 
     *         refinement cycle.
     * 
     * @param value <b>[>=0]</b>  The vertex count.
     */
    void SetTestedVerticesCount(int32 value);
    
    /*!
     * @brief  The number of vertices that have been activated resp. deactivated (ie. made visible 
     *         or invisible)during the most recent refinement cycle based on the result of the 
     *         visibility test.
     * 
     * @return <b>[>=0]</b>  The vertex count.
     */
    int32 GetToggledVerticesCount();
    
    /*!
     * @brief  The number of vertices that have been activated resp. deactivated (ie. made visible 
     *         or invisible)during the most recent refinement cycle based on the result of the 
     *         visibility test.
     * 
     * @param value <b>[>=0]</b>  The vertex count.
     */
    void SetToggledVerticesCount(int32 value);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Adds the given refinement progress values to this RefinementProgressValues object.
     * 
     * @param values <b>[not-null]</b>  The RefinementProgressValues to add.
     */
    void Add(RefinementProgressValues* values);
    
    /*!
     * @brief  Clears all refinement progress values.
     */
    void Clear();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The number of vertices for which computations where still pending during the most 
     *         recent refinement cycle.
     */
    int32 pendingVerticesCount;
    
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
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
  public:
    
    RefinementProgressValues();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<RefinementProgressValues> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x2AD2B9F5;
    
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
