////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_ENUMERABLE_SELECT_H
#define CLODDY_CORE_COLLECTIONS_ENUMERABLE_SELECT_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/EnumerableBase.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Collections { template<class> class IEnumerable; } } }
namespace Cloddy { namespace Core { namespace Collections { template<class> class IEnumerator; } } }
namespace Cloddy { namespace Core { namespace Collections { template<class> class IPredicate; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace Collections { template<class> class EnumerableBase; } } }

// Declare class ::Cloddy::Core::Collections::Enumerable_Select.

namespace Cloddy { namespace Core { namespace Collections
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  template<class T>
  class Enumerable_Select : public EnumerableBase<T>
  {
    // Declare friend classes.
    
    template<class> friend class EnumerableBase;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual Ptr<IEnumerator<T> > GetEnumerator();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    Ptr<IEnumerable<T> > enumerable;
    
    Ptr<IPredicate<T> > predicate;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    Enumerable_Select(IEnumerable<T>* enumerable, IPredicate<T>* predicate);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<Enumerable_Select<T> > ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x4120FE17;
    
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
      if ((ptr = EnumerableBase<T>::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
