////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_PREDICATE_H
#define CLODDY_CORE_COLLECTIONS_PREDICATE_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/PredicateBase.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Collections { template<class> class ICollectionConst; } } }
namespace Cloddy { namespace Core { namespace Collections { template<class> class IEnumerable; } } }
namespace Cloddy { namespace Core { namespace Collections { template<class> class IPredicate; } } }

// Declare class ::Cloddy::Core::Collections::Predicate.

namespace Cloddy { namespace Core { namespace Collections
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  template<class T>
  class Predicate : public PredicateBase<T>
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Returns a predicate that checks if an element is contained in the given set of 
     *         elements.
     * 
     * @param elements <b>[not-null]</b>  The set of element.
     * 
     * @return <b>[not-null]</b>  The predicate.
     */
    static Ptr<IPredicate<T> > In(IEnumerable<T>* elements);
    
    /*!
     * @brief  Returns a predicate that checks if an element is contained in the given set of 
     *         elements.
     * 
     * @param elements <b>[not-null]</b>  The set of element.
     * 
     * @return <b>[not-null]</b>  The predicate.
     */
    static Ptr<IPredicate<T> > In(ICollectionConst<T>* elements);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<Predicate<T> > ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x1257E92B;
    
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
      if ((ptr = PredicateBase<T>::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
