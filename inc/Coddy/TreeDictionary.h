////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_TREEDICTIONARY_H
#define CLODDY_CORE_COLLECTIONS_TREEDICTIONARY_H

#include "CodeX/System.h"

// Include referenced structures.

#include "Cloddy/DictionaryEntry.h"

// Include referenced interfaces.

#include "Cloddy/ISortedDictionary.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Collections { template<class> class ICollectionConst; } } }
namespace Cloddy { namespace Core { namespace Collections { template<class> class ISetConst; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace Collections { template<class, class> class TreeDictionary_Entries; } } }
namespace Cloddy { namespace Core { namespace Collections { template<class, class> class TreeDictionary_Keys; } } }
namespace Cloddy { namespace Core { namespace Collections { template<class, class> class TreeDictionary_Values; } } }

// Declare class ::Cloddy::Core::Collections::TreeDictionary.

namespace Cloddy { namespace Core { namespace Collections
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  An implementation of the IDictionary interface that uses a balanced binary tree for 
   *         storing the dictionary mappings.
   * 
   * A TreeDictionary container has the following performance characteristics:
   * <pre>
   *     Add:       O(logn)
   *     Clear:     O(1)
   *     Contains:  O(logn)
   *     Remove:    O(logn)
   *     n := number of elements in the container.
   * </pre>
   */
  template<class TKey, class TValue>
  class TreeDictionary : public virtual ISortedDictionary<TKey, TValue>
  {
    // Declare friend classes.
    
    template<class, class> friend class TreeDictionary_Entries;
    template<class, class> friend class TreeDictionary_Keys;
    template<class, class> friend class TreeDictionary_Values;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual int32 GetCount();
    
    virtual Ptr<ISetConst<Val<DictionaryEntry<TKey, TValue> > > > GetEntries();
    
    virtual Ptr<ISetConst<TKey> > GetKeys();
    
    virtual DictionaryEntry<TKey, TValue> GetMaximumEntry();
    
    virtual typename TKey::Out GetMaximumKey();
    
    virtual DictionaryEntry<TKey, TValue> GetMinimumEntry();
    
    virtual typename TKey::Out GetMinimumKey();
    
    virtual Ptr<ICollectionConst<TValue> > GetValues();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of TreeDictionary.
     */
    TreeDictionary();
    
    /*!
     * @brief  Creates a new instance of TreeDictionary.
     * 
     * @param initialCapacity <b>[>=0]</b>  The initial capacity of the dictionary,in mapped values.
     */
    TreeDictionary(int32 initialCapacity);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void Clear();
    
    virtual bool Contains(typename TKey::In key);
    
    virtual typename TValue::Out Get(typename TKey::In key, typename TValue::In defaultValue);
    
    virtual typename TValue::Out Put(typename TKey::In key, typename TValue::In value);
    
    virtual typename TValue::Out Remove(typename TKey::In key);
    
    virtual DictionaryEntry<TKey, TValue> RemoveMaximumEntry();
    
    virtual typename TKey::Out RemoveMaximumKey();
    
    virtual DictionaryEntry<TKey, TValue> RemoveMinimumEntry();
    
    virtual typename TKey::Out RemoveMinimumKey();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The current capacity of this set.
     */
    int32 capacity;
    
    /*!
     * @brief  The descendant count per tree node.
     */
    Array<int32> count;
    
    /*!
     * @brief  Head node of linked list of free nodes.
     */
    int32 free;
    
    /*!
     * @brief  The key values per tree node.
     */
    Array<typename TKey::Out> keys;
    
    /*!
     * @brief  Left child pointer per tree node.
     */
    Array<int32> left;
    
    /*!
     * @brief  Right child pointer per tree node.
     */
    Array<int32> right;
    
    /*!
     * @brief  The root node of the tree.
     */
    int32 root;
    
    /*!
     * @brief  The mapped values per tree node.
     */
    Array<typename TValue::Out> values;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  (Re-)balances the given tree node.
     * 
     * @param n The tree node to balance (left child of \e p ).
     * @param p The parent of \e n .
     */
    void Balance_L(int32 n, int32 p);
    
    /*!
     * @brief  (Re-)balances the given tree node.
     * 
     * @param n The tree node to balance (right child of \e p ).
     * @param p The parent of \e n .
     */
    void Balance_R(int32 n, int32 p);
    
    /*!
     * @brief  (Re-)balances the tree root node.
     */
    void Balance_X();
    
    /*!
     * @brief  Returns the number of nodes in the given subtree.
     * 
     * @param n Root of the subtree.
     * 
     * @return The number of nodes in the subtree.
     */
    int32 CountNodes(int32 n);
    
    /*!
     * @brief  Creates a new tree node.
     * 
     * @param key The node key.
     * 
     * @return The index of the created tree node.
     */
    int32 CreateNode(typename TKey::In key);
    
    /*!
     * @brief  Searches the given value and deletes,starting at the given node.
     * 
     * @param n The tree node (left child of \e p ).
     * @param p The parent of \e n .
     * @param key The value to delete.
     * 
     * @return \c true  if the value has been deleted,\c false  if it is not contained in the tree.
     */
    int32 Delete_L(int32 n, int32 p, typename TKey::In key);
    
    /*!
     * @brief  Searches the given value and deletes,starting at the given node.
     * 
     * @param n The tree node (right child of \e p ).
     * @param p The parent of \e n .
     * @param key The value to delete.
     * 
     * @return \c true  if the value has been deleted,\c false  if it is not contained in the tree.
     */
    int32 Delete_R(int32 n, int32 p, typename TKey::In key);
    
    /*!
     * @brief  Searches the given value and deletes,starting from the root node.
     * 
     * @param key The value to delete.
     * 
     * @return \c true  if the value has been deleted,\c false  if it is not contained in the tree.
     */
    int32 Delete_X(typename TKey::In key);
    
    /*!
     * @brief  Ensures that the set has at least the given capacity.
     * 
     * @param newCapacity The minimum required capacity.
     */
    void EnsureCapacity(int32 newCapacity);
    
    /*!
     * @brief  Performs a binary search for the given value.
     * 
     * @param n The current node.
     * @param key The value to find.
     * 
     * @return \c true  if the value has been found,\c false  if not.
     */
    int32 FindKey(int32 n, typename TKey::In key);
    
    /*!
     * @brief  Performs a brute-force search for the given value.
     * 
     * @param n The current node.
     * @param value The value to find.
     * 
     * @return \c true  if the value has been found,\c false  if not.
     */
    bool FindValue(int32 n, typename TValue::In value);
    
    /*!
     * @brief  Inserts the given value into the tree.
     * 
     * @param n Left child of \e p  or \c null .
     * @param p Left child of \e g .
     * @param g Grand parent of \e n .
     * @param key The key to insert.
     * 
     * @return \c true  if the value has been inserted,\c false  if it is already contained in the 
     * tree.
     */
    int32 Insert_LL(int32 n, int32 p, int32 g, typename TKey::In key);
    
    /*!
     * @brief  Inserts the given value into the tree.
     * 
     * @param n Right child of \e p  or \c null .
     * @param p Left child of \e g .
     * @param g Grand parent of \e n .
     * @param key The key to insert.
     * 
     * @return \c true  if the value has been inserted,\c false  if it is already contained in the 
     * tree.
     */
    int32 Insert_LR(int32 n, int32 p, int32 g, typename TKey::In key);
    
    /*!
     * @brief  Inserts the given value into the tree.
     * 
     * @param n Left child of \e p  or \c null .
     * @param p Right child of \e g .
     * @param g Grand parent of \e n .
     * @param key The key to insert.
     * 
     * @return \c true  if the value has been inserted,\c false  if it is already contained in the 
     * tree.
     */
    int32 Insert_RL(int32 n, int32 p, int32 g, typename TKey::In key);
    
    /*!
     * @brief  Inserts the given value into the tree.
     * 
     * @param n Right child of \e p  or \c null .
     * @param p Right child of \e g .
     * @param g Grand parent of \e n .
     * @param key The value to insert.
     * 
     * @return \c true  if the value has been inserted,\c false  if it is already contained in the 
     * tree.
     */
    int32 Insert_RR(int32 n, int32 p, int32 g, typename TKey::In key);
    
    /*!
     * @brief  Inserts the given value into the tree.
     * 
     * @param n Left child of #root or \c null .
     * @param key The key to insert.
     * 
     * @return \c true  if the value has been inserted,\c false  if it is already contained in the 
     * tree.
     */
    int32 Insert_XL(int32 n, typename TKey::In key);
    
    /*!
     * @brief  Inserts the given value into the tree.
     * 
     * @param n Right child of #root or \c null .
     * @param key The key to insert.
     * 
     * @return \c true  if the value has been inserted,\c false  if it is already contained in the 
     * tree.
     */
    int32 Insert_XR(int32 n, typename TKey::In key);
    
    /*!
     * @brief  Pushes the given storage node to the free list.
     * 
     * @param n The storage node to push.
     */
    void PushFree(int32 n);
    
    /*!
     * @brief  Removes the given node from the tree.
     * 
     * @param n The node to remove (left child of \e p ).
     * @param p The parent of \e n .
     */
    void Remove_L(int32 n, int32 p);
    
    /*!
     * @brief  Removes the given node from the tree.
     * 
     * @param n The node to remove (right child of \e p ).
     * @param p The parent of \e n .
     */
    void Remove_R(int32 n, int32 p);
    
    /*!
     * @brief  Removes the root node from the tree.
     */
    void Remove_X();
    
    /*!
     * @brief  Updates the node counters for a left rotation on the given node.
     * 
     * <pre>
     *     .          +---+                           +---+        
     *     .     .----| # |----.                 .----| R |
     *     .     |    +---+    |                 |    +---+
     *     .     V             V                 V              
     *     .   +---+         +---+             +---+       
     *     .   | L |    .----| R |  =>    .----| # |----.  
     *     .   +---+    |    +---+        |    +---+    |  
     *     .            V                 V             V          
     *     .          +---+             +---+         +---+        
     *     .          | C |             | L |         | C |        
     *     .          +---+             +---+         +---+        
     *     .   
     *     .   # := The given tree node.
     *     .   L := Left child of # (may exist).
     *     .   R := Right child of # (must exist). 
     *     .   C := Left child of R (may exist).
     * </pre>
     * 
     * @param n The tree node.
     */
    void RotateCount_L(int32 n);
    
    /*!
     * @brief  Updates the node counters for a right rotation on the given node.
     * 
     * <pre>
     *     .          +---+             +---+        
     *     .     .----| # |----.        | L |----.
     *     .     |    +---+    |        +---+    |
     *     .     V             V                 V  
     *     .   +---+         +---+             +---+       
     *     .   | L |----.    | R |  =>    .----| # |----.  
     *     .   +---+    |    +---+        |    +---+    |  
     *     .            V                 V             V          
     *     .          +---+             +---+         +---+        
     *     .          | C |             | C |         | R |        
     *     .          +---+             +---+         +---+        
     *     .   
     *     .   # := The given tree node.
     *     .   L := Left child of # (must exist).
     *     .   R := Right child of # (may exist). 
     *     .   C := Right child of L (may exist).
     * </pre>
     * 
     * @param n The tree node.
     */
    void RotateCount_R(int32 n);
    
    /*!
     * @brief  Performs a left rotation on the given node.
     * 
     * <pre>
     *     .                 +---+                           +---+  
     *     .            .----| P |                      .----| P |  
     *     .            |    +---+                      |    +---+ 
     *     .            V                               V          
     *     .          +---+                           +---+        
     *     .     .----| N |----.                 .----| R |
     *     .     |    +---+    |                 |    +---+
     *     .     V             V    =>           V              
     *     .   +---+         +---+             +---+       
     *     .   | L |    .----| R |        .----| N |----.  
     *     .   +---+    |    +---+        |    +---+    |  
     *     .            V                 V             V          
     *     .          +---+             +---+         +---+        
     *     .          | C |             | L |         | C |        
     *     .          +---+             +---+         +---+        
     *     .   
     *     .   P := Parent of N.
     *     .   N := Left child of P (the given node).
     *     .   L := Left child of N (may exist).
     *     .   R := Right child of N (must exist). 
     *     .   C := Left child of R (may exist).
     * </pre>
     * 
     * @param n Left child of \e p .
     * @param p Parent of \e n .
     */
    void Rotate_LL(int32 n, int32 p);
    
    /*!
     * @brief  Performs a right rotation on the given node.
     * 
     * <pre>
     *     .                 +---+             +---+  
     *     .            .----| P |        .----| P |  
     *     .            |    +---+        |    +---+ 
     *     .            V                 V          
     *     .          +---+             +---+        
     *     .     .----| N |----.        | L |----.
     *     .     |    +---+    |        +---+    |
     *     .     V             V    =>           V  
     *     .   +---+         +---+             +---+       
     *     .   | L |----.    | R |        .----| N |----.  
     *     .   +---+    |    +---+        |    +---+    |  
     *     .            V                 V             V          
     *     .          +---+             +---+         +---+        
     *     .          | C |             | C |         | R |        
     *     .          +---+             +---+         +---+        
     *     .   
     *     .   P := Parent of N.
     *     .   N := Left child of P (the given node).
     *     .   L := Left child of N (must exist).
     *     .   R := Right child of N (may exist). 
     *     .   C := Right child of L (may exist).
     * </pre>
     * 
     * @param n Left child of \e p .
     * @param p Parent of \e n .
     */
    void Rotate_LR(int32 n, int32 p);
    
    /*!
     * @brief  Performs a left rotation on the given node.
     * 
     * <pre>
     *     .   +---+                           +---+  
     *     .   | P |----.                      | P |----.
     *     .   +---+    |                      +---+    |
     *     .            V                               V          
     *     .          +---+                           +---+        
     *     .     .----| N |----.                 .----| R |
     *     .     |    +---+    |                 |    +---+
     *     .     V             V    =>           V              
     *     .   +---+         +---+             +---+       
     *     .   | L |    .----| R |        .----| N |----.  
     *     .   +---+    |    +---+        |    +---+    |  
     *     .            V                 V             V          
     *     .          +---+             +---+         +---+        
     *     .          | C |             | L |         | C |        
     *     .          +---+             +---+         +---+        
     *     .   
     *     .   P := Parent of N.
     *     .   N := Right child of P (the given node).
     *     .   L := Left child of N (may exist).
     *     .   R := Right child of N (must exist). 
     *     .   C := Left child of R (may exist).
     * </pre>
     * 
     * @param n Right child of \e p .
     * @param p Parent of \e n .
     */
    void Rotate_RL(int32 n, int32 p);
    
    /*!
     * @brief  Performs a right rotation on the given node.
     * 
     * <pre>
     *     .   +---+                    +---+  
     *     .   | P |----.               | P |----.
     *     .   +---+    |               +---+    |
     *     .            V                        V          
     *     .          +---+                    +---+        
     *     .     .----| N |----.               | L |----.
     *     .     |    +---+    |               +---+    |
     *     .     V             V    =>                  V  
     *     .   +---+         +---+                    +---+       
     *     .   | L |----.    | R |               .----| N |----.  
     *     .   +---+    |    +---+               |    +---+    |  
     *     .            V                        V             V          
     *     .          +---+                    +---+         +---+        
     *     .          | C |                    | C |         | R |        
     *     .          +---+                    +---+         +---+        
     *     .   
     *     .   P := Parent of N.
     *     .   N := Right child of P (the given node).
     *     .   L := Left child of N (must exist).
     *     .   R := Right child of N (may exist). 
     *     .   C := Right child of L (may exist).
     * </pre>
     * 
     * @param n Right child of \e p .
     * @param p Parent of \e n .
     */
    void Rotate_RR(int32 n, int32 p);
    
    /*!
     * @brief  Performs a left rotation on the tree root node.
     * 
     * <pre>
     *     .          +---+                           +---+        
     *     .     .----| N |----.                 .----| R |
     *     .     |    +---+    |                 |    +---+
     *     .     V             V                 V              
     *     .   +---+         +---+             +---+       
     *     .   | L |    .----| R |  =>    .----| N |----.  
     *     .   +---+    |    +---+        |    +---+    |  
     *     .            V                 V             V          
     *     .          +---+             +---+         +---+        
     *     .          | C |             | L |         | C |        
     *     .          +---+             +---+         +---+        
     *     .   
     *     .   N := Tree root node.
     *     .   L := Left child of N (may exist).
     *     .   R := Right child of N (must exist). 
     *     .   C := Left child of R (may exist).
     * </pre>
     */
    void Rotate_XL();
    
    /*!
     * @brief  Performs a right rotation on the tree root node.
     * 
     * <pre>
     *     .          +---+             +---+        
     *     .     .----| N |----.        | L |----.
     *     .     |    +---+    |        +---+    |
     *     .     V             V                 V  
     *     .   +---+         +---+             +---+       
     *     .   | L |----.    | R |  =>    .----| N |----.  
     *     .   +---+    |    +---+        |    +---+    |  
     *     .            V                 V             V          
     *     .          +---+             +---+         +---+        
     *     .          | C |             | C |         | R |        
     *     .          +---+             +---+         +---+        
     *     .   
     *     .   N := Tree root node.
     *     .   L := Left child of N (must exist).
     *     .   R := Right child of N (may exist). 
     *     .   C := Right child of L (may exist).
     * </pre>
     */
    void Rotate_XR();
    
    /*!
     * @brief  Performs an inorder traversal of the tree and writes the node values into \e array .
     * 
     * @param array The output array.
     * @param node The current node.
     * @param index The current array index.
     * 
     * @return The resulting array index.
     */
    int32 ToEntriesArray(Array<DictionaryEntry<TKey, TValue> > array, int32 node, int32 index);
    
    /*!
     * @brief  Performs an inorder traversal of the tree and writes the node values into \e array .
     * 
     * @param array The output array.
     * @param node The current node.
     * @param index The current array index.
     * 
     * @return The resulting array index.
     */
    int32 ToKeysArray(Array<typename TKey::Out> array, int32 node, int32 index);
    
    /*!
     * @brief  Performs an inorder traversal of the tree and writes the node values into \e array .
     * 
     * @param array The output array.
     * @param node The current node.
     * @param index The current array index.
     * 
     * @return The resulting array index.
     */
    int32 ToValuesArray(Array<typename TValue::Out> array, int32 node, int32 index);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<TreeDictionary<TKey, TValue> > ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xE4FD0FD0;
    
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
      if ((ptr = ISortedDictionary<TKey, TValue>::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
