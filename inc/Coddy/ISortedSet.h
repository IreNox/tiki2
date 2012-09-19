////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_ISORTEDSET_H
#define CLODDY_CORE_COLLECTIONS_ISORTEDSET_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/ISet.h"
#include "Cloddy/ISortedSetConst.h"

// Declare interface ::Cloddy::Core::Collections::ISortedSet.

namespace Cloddy { namespace Core { namespace Collections
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Base interface for mutable sets that store their elements in order.
   */
  template<class T>
  class NO_VTABLE ISortedSet : public virtual ISet<T>, public virtual ISortedSetConst<T>
  {
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Counts the values in this set that lie within the given range.
     * 
     * @param from Start of range,inclusive.
     * @param to End of range,exclusive.
     * 
     * @return <b>[not-null]</b>  The values in the range.
     */
    virtual int32 CountValuesInRange(typename T::In from, typename T::In to) = 0;
    
    /*!
     * @brief  Returns the values in this set that lie within the given range.
     * 
     * @param from Start of range,inclusive.
     * @param to End of range,exclusive.
     * 
     * @return <b>[>=0]</b>  The number of values in the given range.
     */
    virtual Array<typename T::Out> GetValuesInRange(typename T::In from, typename T::In to) = 0;
    
    /*!
     * @brief  Removes the maximum element from this set.
     * 
     * @return The removed element.
     */
    virtual typename T::Out RemoveMaximum() = 0;
    
    /*!
     * @brief  Removes the minimum element from this set.
     * 
     * @return The removed element.
     */
    virtual typename T::Out RemoveMinimum() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<ISortedSet<T> > ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xC707FDBA;
    
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
      if ((ptr = ISet<T>::TryCast(typeId)) != 0) return ptr;
      if ((ptr = ISortedSetConst<T>::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
} } } 

#endif
