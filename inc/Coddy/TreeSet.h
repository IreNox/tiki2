////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_TREESET_H
#define CLODDY_CORE_COLLECTIONS_TREESET_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/ISortedSet.h"

// Include referenced classes.

#include "Cloddy/CollectionBase.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Collections { template<class> class IEnumerator; } } }
namespace Cloddy { namespace Core { namespace Collections { template<class> class IList; } } }

// Declare class ::Cloddy::Core::Collections::TreeSet.

namespace Cloddy { namespace Core { namespace Collections
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  An implementation of the ISet interface that uses a balanced binary tree for storing 
   *         the set elements.
   * 
   * A TreeSet container has the following performance characteristics:
   * <pre>
   *     Add:       O(logn)
   *     Clear:     O(1)
   *     Contains:  O(logn)
   *     Remove:    O(logn)
   *     n := number of elements in the container.
   * </pre>
   */
  template<class T>
  class TreeSet : public CollectionBase<T>, public virtual ISortedSet<T>
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual int32 GetCount();
    
    virtual Ptr<IEnumerator<T> > GetEnumerator();
    
    virtual typename T::Out GetMaximum();
    
    virtual typename T::Out GetMinimum();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of TreeSet.
     */
    TreeSet();
    
    /*!
     * @brief  Creates a new instance of TreeSet.
     * 
     * @param initialCapacity <b>[>=0]</b>  The initial capacity of the set,in values.
     */
    TreeSet(int32 initialCapacity);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual bool Add(typename T::In element);
    
    virtual void Clear();
    
    virtual bool Contains(typename T::In element);
    
    virtual int32 CountValuesInRange(typename T::In from, typename T::In to);
    
    virtual Array<typename T::Out> GetValuesInRange(typename T::In from, typename T::In to);
    
    virtual bool Remove(typename T::In element);
    
    virtual typename T::Out RemoveMaximum();
    
    virtual typename T::Out RemoveMinimum();
    
    virtual Array<typename T::Out> ToArrayCopy(Array<typename T::Out> array, int32 offset);
    
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
     * @brief  The long value per tree node.
     */
    Array<typename T::Out> values;
    
    /*!
     * @brief  A compact array that holds all set elements,in ascending order.
     */
    Array<typename T::Out> valuesArray;
    
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
    
    int32 CountValuesInRange(int32 node, typename T::In from, typename T::In to);
    
    /*!
     * @brief  Creates a new tree node.
     * 
     * @param value The node value.
     * 
     * @return The index of the created tree node.
     */
    int32 CreateNode(typename T::In value);
    
    /*!
     * @brief  Searches the given value and deletes,starting at the given node.
     * 
     * @param n The tree node (left child of \e p ).
     * @param p The parent of \e n .
     * @param value The value to delete.
     * 
     * @return \c true  if the value has been deleted,\c false  if it is not contained in the tree.
     */
    bool Delete_L(int32 n, int32 p, typename T::In value);
    
    /*!
     * @brief  Searches the given value and deletes,starting at the given node.
     * 
     * @param n The tree node (right child of \e p ).
     * @param p The parent of \e n .
     * @param value The value to delete.
     * 
     * @return \c true  if the value has been deleted,\c false  if it is not contained in the tree.
     */
    bool Delete_R(int32 n, int32 p, typename T::In value);
    
    /*!
     * @brief  Searches the given value and deletes,starting from the root node.
     * 
     * @param value The value to delete.
     * 
     * @return \c true  if the value has been deleted,\c false  if it is not contained in the tree.
     */
    bool Delete_X(typename T::In value);
    
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
     * @param value The value to find.
     * 
     * @return \c true  if the value has been found,\c false  if not.
     */
    bool Find(int32 n, typename T::In value);
    
    void GetValuesInRange(int32 node, typename T::In from, typename T::In to, IList<T>* list);
    
    /*!
     * @brief  Inserts the given value into the tree.
     * 
     * @param n Left child of \e p  or \c null .
     * @param p Left child of \e g .
     * @param g Grand parent of \e n .
     * @param value The value to insert.
     * 
     * @return \c true  if the value has been inserted,\c false  if it is already contained in the 
     * tree.
     */
    bool Insert_LL(int32 n, int32 p, int32 g, typename T::In value);
    
    /*!
     * @brief  Inserts the given value into the tree.
     * 
     * @param n Right child of \e p  or \c null .
     * @param p Left child of \e g .
     * @param g Grand parent of \e n .
     * @param value The value to insert.
     * 
     * @return \c true  if the value has been inserted,\c false  if it is already contained in the 
     * tree.
     */
    bool Insert_LR(int32 n, int32 p, int32 g, typename T::In value);
    
    /*!
     * @brief  Inserts the given value into the tree.
     * 
     * @param n Left child of \e p  or \c null .
     * @param p Right child of \e g .
     * @param g Grand parent of \e n .
     * @param value The value to insert.
     * 
     * @return \c true  if the value has been inserted,\c false  if it is already contained in the 
     * tree.
     */
    bool Insert_RL(int32 n, int32 p, int32 g, typename T::In value);
    
    /*!
     * @brief  Inserts the given value into the tree.
     * 
     * @param n Right child of \e p  or \c null .
     * @param p Right child of \e g .
     * @param g Grand parent of \e n .
     * @param value The value to insert.
     * 
     * @return \c true  if the value has been inserted,\c false  if it is already contained in the 
     * tree.
     */
    bool Insert_RR(int32 n, int32 p, int32 g, typename T::In value);
    
    /*!
     * @brief  Inserts the given value into the tree.
     * 
     * @param n Left child of #root or \c null .
     * @param value The value to insert.
     * 
     * @return \c true  if the value has been inserted,\c false  if it is already contained in the 
     * tree.
     */
    bool Insert_XL(int32 n, typename T::In value);
    
    /*!
     * @brief  Inserts the given value into the tree.
     * 
     * @param n Right child of #root or \c null .
     * @param value The value to insert.
     * 
     * @return \c true  if the value has been inserted,\c false  if it is already contained in the 
     * tree.
     */
    bool Insert_XR(int32 n, typename T::In value);
    
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
     * @brief  Performs an inorder traversal of the tree and writes the node values 
     *         into #valuesArray.
     * 
     * @param node The current node.
     * @param index The current array index.
     * 
     * @return The resulting array index.
     */
    int32 ToArrayInternal(int32 node, int32 index);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<TreeSet<T> > ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x3E5A174;
    
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
      if ((ptr = CollectionBase<T>::TryCast(typeId)) != 0) return ptr;
      if ((ptr = ISortedSet<T>::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
