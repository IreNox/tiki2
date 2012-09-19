////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_ENUMERABLE_APPEND_H
#define CLODDY_CORE_COLLECTIONS_ENUMERABLE_APPEND_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/EnumerableBase.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Collections { template<class> class IEnumerable; } } }
namespace Cloddy { namespace Core { namespace Collections { template<class> class IEnumerator; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace Collections { template<class> class EnumerableBase; } } }

// Declare class ::Cloddy::Core::Collections::Enumerable_Append.

namespace Cloddy { namespace Core { namespace Collections
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  template<class T>
  class Enumerable_Append : public EnumerableBase<T>
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
    
    Ptr<IEnumerable<T> > first;
    
    Ptr<IEnumerable<T> > second;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    Enumerable_Append(IEnumerable<T>* first, IEnumerable<T>* second);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<Enumerable_Append<T> > ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x93B56DC1;
    
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
