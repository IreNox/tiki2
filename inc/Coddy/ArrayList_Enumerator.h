////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_ARRAYLIST_ENUMERATOR_H
#define CLODDY_CORE_COLLECTIONS_ARRAYLIST_ENUMERATOR_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/EnumeratorBase.h"

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace Collections { template<class> class ArrayList; } } }
namespace Cloddy { namespace Core { namespace Collections { template<class> class ArrayList_Wrap; } } }

// Declare class ::Cloddy::Core::Collections::ArrayList_Enumerator.

namespace Cloddy { namespace Core { namespace Collections
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  An IEnumerator implementation for ArrayList objects.
   */
  template<class T>
  class ArrayList_Enumerator : public EnumeratorBase<T>
  {
    // Declare friend classes.
    
    template<class> friend class ArrayList;
    template<class> friend class ArrayList_Wrap;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual typename T::Out GetCurrent();
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
  protected:
    
    virtual void DisposeManaged();
    
    virtual bool DoNext();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Index of current element.
     */
    int32 current;
    
    /*!
     * @brief  The list elements.
     */
    Array<typename T::Out> elements;
    
    /*!
     * @brief  Index of last element.
     */
    int32 last;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of ArrayList_Enumerator.
     * 
     * @param elements Total number of elements.
     * @param count Total number of elements.
     */
    ArrayList_Enumerator(Array<typename T::Out> elements, int32 count);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<ArrayList_Enumerator<T> > ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xCB2D4B8;
    
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
      if ((ptr = EnumeratorBase<T>::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
