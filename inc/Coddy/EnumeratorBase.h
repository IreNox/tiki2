////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_ENUMERATORBASE_H
#define CLODDY_CORE_COLLECTIONS_ENUMERATORBASE_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IEnumerator.h"

// Include referenced classes.

#include "CodeX/Disposable.h"

// Declare class ::Cloddy::Core::Collections::EnumeratorBase.

namespace Cloddy { namespace Core { namespace Collections
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced classes.
  
  using CodeX::System::Disposable;
  
  template<class T>
  class EnumeratorBase : public Disposable, public virtual IEnumerator<T>
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual typename T::Out GetCurrent() = 0;
    
    virtual int32 GetIndex();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual bool Next();
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Constructors
    // ---------------------------------------------------------------------------------------------
  protected:
    
    /*!
     * @brief  Creates a new instance of EnumeratorBase.
     */
    EnumeratorBase();
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void DisposeManaged();
    
    virtual bool DoNext() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Zero-based index of current element.
     */
    int32 index;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<EnumeratorBase<T> > ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xF48CB8E3;
    
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
      if ((ptr = IEnumerator<T>::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
