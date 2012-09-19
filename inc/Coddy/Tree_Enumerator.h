////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_TREE_ENUMERATOR_H
#define CLODDY_CORE_COLLECTIONS_TREE_ENUMERATOR_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/EnumeratorBase.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Collections { template<class> class IDeque; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace Collections { template<class, class> class TreeDictionary_Keys; } } }
namespace Cloddy { namespace Core { namespace Collections { template<class, class> class TreeDictionary_Values; } } }
namespace Cloddy { namespace Core { namespace Collections { template<class> class TreeSet; } } }

// Declare class ::Cloddy::Core::Collections::Tree_Enumerator.

namespace Cloddy { namespace Core { namespace Collections
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  template<class T>
  class Tree_Enumerator : public EnumeratorBase<T>
  {
    // Declare friend classes.
    
    template<class, class> friend class TreeDictionary_Keys;
    template<class, class> friend class TreeDictionary_Values;
    template<class> friend class TreeSet;
    
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
     * @brief  Index of current tree node.
     */
    int32 current;
    
    /*!
     * @brief  Left child nodes.
     */
    Array<int32> left;
    
    /*!
     * @brief  Index of next tree node.
     */
    int32 next;
    
    /*!
     * @brief  Right child nodes.
     */
    Array<int32> right;
    
    /*!
     * @brief  The traversal stack.
     */
    Ptr<IDeque<Prm<int32> > > stack;
    
    /*!
     * @brief  The node values.
     */
    Array<typename T::Out> values;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of Tree_Enumerator.
     * 
     * @param root The root node.
     * @param left Left child nodes.
     * @param right Right child nodes.
     * @param values The node values.
     */
    Tree_Enumerator(int32 root, Array<int32> left, Array<int32> right, Array<typename T::Out> values);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<Tree_Enumerator<T> > ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x8FAC2FB;
    
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
