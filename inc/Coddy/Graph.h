////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_GRAPH_H
#define CLODDY_CORE_COLLECTIONS_GRAPH_H

#include "CodeX/System.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Collections { template<class, class> class IDictionary; } } }
namespace Cloddy { namespace Core { namespace Collections { template<class> class ISet; } } }
namespace Cloddy { namespace Core { namespace Collections { template<class> class ISortedSet; } } }

// Declare class ::Cloddy::Core::Collections::Graph.

namespace Cloddy { namespace Core { namespace Collections
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  A directed graph.
   */
  template<class TNode>
  class Graph : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Returns all sinks in the graph.
     * 
     * A sink is a graph node that has no outgoing links.
     * 
     * @return <b>[not-null]</b>  The sinks.
     */
    Array<typename TNode::Out> GetSinks();
    
    /*!
     * @brief  Returns all sources in the graph.
     * 
     * A source is a graph node that has no incoming links.
     * 
     * @return <b>[not-null]</b>  The sources.
     */
    Array<typename TNode::Out> GetSources();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    Graph();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Adds a link to the graph.
     * 
     * The link will have a weight of \c 1 .
     * 
     * @param source The source node.
     * @param target The target node.
     * 
     * @return \c true  if the graph has changed,\c false  if it has not.
     */
    bool AddLink(typename TNode::In source, typename TNode::In target);
    
    /*!
     * @brief  Adds a link to the graph.
     * 
     * @param source The source node.
     * @param target The target node.
     * @param weight <b>[>0]</b>  The link weight.
     * 
     * @return \c true  if the graph has changed,\c false  if it has not.
     */
    bool AddLink(typename TNode::In source, typename TNode::In target, int32 weight);
    
    /*!
     * @brief  Adds a node to the graph.
     * 
     * @param node The node to add.
     * 
     * @return \c true  if the graph has changed,\c false  if it has not.
     */
    bool AddNode(typename TNode::In node);
    
    /*!
     * @brief  Removes a links from this graph.
     * 
     * @param source The source node.
     * @param target The target node.
     * 
     * @return \c true  if the graph has changed,\c false  if it has not.
     */
    bool RemoveLink(typename TNode::In source, typename TNode::In target);
    
    /*!
     * @brief  Removes a node from the graph.
     * 
     * @param node The node to remove.
     * 
     * @return \c true  if the graph has changed,\c false  if it has not.
     */
    bool RemoveNode(typename TNode::In node);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    Ptr<IDictionary<Prm<int32>, TNode> > idToNode;
    
    /*!
     * @brief  Mapping from node IDs pairs to link weights.
     */
    Ptr<IDictionary<Prm<int64>, Prm<int32> > > links;
    
    /*!
     * @brief  Mapping from node objects to node IDs.
     */
    Ptr<IDictionary<TNode, Prm<int32> > > nodeToId;
    
    /*!
     * @brief  Set of IDs for nodes that have no outgoing links.
     */
    Ptr<ISet<Prm<int32> > > sinks;
    
    Array<typename TNode::Out> sinksArray;
    
    Ptr<ISortedSet<Prm<int64> > > sourceToTarget;
    
    /*!
     * @brief  Set of IDs for nodes that have no incoming links.
     */
    Ptr<ISet<Prm<int32> > > sources;
    
    Array<typename TNode::Out> sourcesArray;
    
    Ptr<ISortedSet<Prm<int64> > > targetToSource;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Computes the key for the given link.
     * 
     * @param sourceId ID of source node of link.
     * @param targetId ID of target node of link.
     * 
     * @return The link key.
     */
    static int64 Key(int32 sourceId, int32 targetId);
    
    /*!
     * @brief  Returns the ID of the given graph node.
     * 
     * @param node The graph node.
     * 
     * @return The node ID or \c -1 .
     */
    int32 Id(typename TNode::In node);
    
    /*!
     * @brief  Returns the ID of the given graph node,allocating a new one if necessary.
     * 
     * @param node The graph node.
     * 
     * @return The node ID.
     */
    int32 IdNew(typename TNode::In node);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<Graph<TNode> > ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xF4AEF49C;
    
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
      return (void*) 0;
    }
  };
  
} } } 

#endif
