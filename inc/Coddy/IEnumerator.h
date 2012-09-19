////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_IENUMERATOR_H
#define CLODDY_CORE_COLLECTIONS_IENUMERATOR_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "CodeX/IDisposable.h"

// Declare interface ::Cloddy::Core::Collections::IEnumerator.

namespace Cloddy { namespace Core { namespace Collections
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using CodeX::System::IDisposable;
  
  /*!
   * @brief  Base interface for classes that enumerate over the elements of a ICollection.
   */
  template<class T>
  class NO_VTABLE IEnumerator : public virtual IDisposable
  {
    // ---------------------------------------------------------------------------------------------
    // Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Returns the current element of the enumeration.
     * 
     * @return The current element.
     */
    virtual typename T::Out GetCurrent() = 0;
    
    /*!
     * @brief  Returns the zero-based index of the current element in the enumeration.
     * 
     * @return <b>[>0]</b>  The zero-based index of the current element.
     */
    virtual int32 GetIndex() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Advances the enumerator to the next element.
     * 
     * A newly created enumerator is positioned \e before  the first element,so the #Next method 
     * must always be called before querying #GetCurrent.
     * 
     * @return \c true  if the enumerator contains more elements,\c false  if not.
     */
    virtual bool Next() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IEnumerator<T> > ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xF741D6F;
    
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
} } } 

#endif
