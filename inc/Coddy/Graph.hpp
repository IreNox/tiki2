////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_GRAPH_HPP
#define CLODDY_CORE_COLLECTIONS_GRAPH_HPP

#include "Cloddy/Graph.h"

// Include referenced interfaces.

#include "Cloddy/ICollectionConst.h"
#include "Cloddy/IDictionary.h"
#include "Cloddy/IEnumerable.h"
#include "Cloddy/IEnumerator.h"
#include "Cloddy/IList.h"
#include "Cloddy/ISet.h"
#include "Cloddy/ISetConst.h"
#include "Cloddy/ISortedSet.h"

// Include referenced classes.

#include "CodeX/ErrorInfo.h"
#include "Cloddy/HashDictionary.hpp"
#include "Cloddy/HashSet.hpp"
#include "CodeX/InvalidArgumentException.h"
#include "Cloddy/TreeSet.hpp"

namespace Cloddy { namespace Core { namespace Collections {

// Use referenced namespaces.

using namespace CodeX;

// Use referenced classes.

using CodeX::System::ErrorInfo;
using CodeX::System::InvalidArgumentException;

// -------------------------------------------------------------------------------------------------
// Public / Attributes
// -------------------------------------------------------------------------------------------------

/*!
 * @brief  Returns all sinks in the graph.
 * 
 * A sink is a graph node that has no outgoing links.
 * 
 * @return <b>[not-null]</b>  The sinks.
 */
template<class TNode>
Array<typename TNode::Out> Graph<TNode>::GetSinks()
{
  if (sinksArray == null) 
  {
    int32 idx;
    
    sinksArray = Array<typename TNode::Out>(sinks->GetCount());
    idx = 0;
    
    for (Ptr<IEnumerator<Prm<int32> > > it = sinks->GetEnumerator(); it->Next(); )
      sinksArray[idx++] = idToNode->Get(it->GetCurrent(), TNode::Default());
  }
  
  return sinksArray;
}

/*!
 * @brief  Returns all sources in the graph.
 * 
 * A source is a graph node that has no incoming links.
 * 
 * @return <b>[not-null]</b>  The sources.
 */
template<class TNode>
Array<typename TNode::Out> Graph<TNode>::GetSources()
{
  if (sourcesArray == null) 
  {
    int32 idx;
    
    sourcesArray = Array<typename TNode::Out>(sources->GetCount());
    idx = 0;
    
    for (Ptr<IEnumerator<Prm<int32> > > it = sources->GetEnumerator(); it->Next(); )
      sourcesArray[idx++] = idToNode->Get(it->GetCurrent(), TNode::Default());
  }
  
  return sourcesArray;
}

// -------------------------------------------------------------------------------------------------
// Public / Constructors
// -------------------------------------------------------------------------------------------------

template<class TNode>
Graph<TNode>::Graph()
{
  links = new HashDictionary<Prm<int64>, Prm<int32> >(12);
  nodeToId = new HashDictionary<TNode, Prm<int32> >(12);
  sinks = new HashSet<Prm<int32> >(12);
  sourceToTarget = new TreeSet<Prm<int64> >(12);
  sources = new HashSet<Prm<int32> >(12);
  targetToSource = new TreeSet<Prm<int64> >(12);
}

// -------------------------------------------------------------------------------------------------
// Public / Methods
// -------------------------------------------------------------------------------------------------

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
template<class TNode>
bool Graph<TNode>::AddLink(typename TNode::In source, typename TNode::In target)
{
  return AddLink(source, target, 1);
}

/*!
 * @brief  Adds a link to the graph.
 * 
 * @param source The source node.
 * @param target The target node.
 * @param weight <b>[>0]</b>  The link weight.
 * 
 * @return \c true  if the graph has changed,\c false  if it has not.
 */
template<class TNode>
bool Graph<TNode>::AddLink(typename TNode::In source, typename TNode::In target, int32 weight)
{
#ifdef _DEBUG
  if (weight <= 0) throw InvalidArgumentException::Greater(ZSTRING("Graph.AddLink"), ZSTRING("weight"), 0);
#endif
  
  int32 targetId;
  
  // The target node can no longer be a source.
  
  if (sources->Remove(targetId = IdNew(target))) sourcesArray = null;
  
  // Add link.
  
  return links->Put(Key(IdNew(source), targetId), weight) != weight;
}

/*!
 * @brief  Adds a node to the graph.
 * 
 * @param node The node to add.
 * 
 * @return \c true  if the graph has changed,\c false  if it has not.
 */
template<class TNode>
bool Graph<TNode>::AddNode(typename TNode::In node)
{
  if (nodeToId->Get(node, -1) == -1) 
  {
    int32 nodeId;
    
    nodeToId->Put(node, nodeId = nodeToId->GetCount());
    
    // New nodes are always sources and sinks.
    
    sources->Add(nodeId);
    sinks->Add(nodeId);
    
    sourcesArray = null;
    sinksArray = null;
    
    return true;
  }
  
  return false;
}

/*!
 * @brief  Removes a links from this graph.
 * 
 * @param source The source node.
 * @param target The target node.
 * 
 * @return \c true  if the graph has changed,\c false  if it has not.
 */
template<class TNode>
bool Graph<TNode>::RemoveLink(typename TNode::In source, typename TNode::In target)
{
  int32 sourceId;
  int32 targetId;
  
  if ((sourceId = Id(source)) == -1) return false;
  if ((targetId = Id(target)) == -1) return false;
  
  return links->Remove(Key(sourceId, targetId)) != 0;
}

/*!
 * @brief  Removes a node from the graph.
 * 
 * @param node The node to remove.
 * 
 * @return \c true  if the graph has changed,\c false  if it has not.
 */
template<class TNode>
bool Graph<TNode>::RemoveNode(typename TNode::In node)
{
  int32 nodeId;
  int64 from;
  int64 to;
  Array<int64> values;
  
  if ((nodeId = Id(node)) == -1) return false;
  
  from = Key(nodeId, 0);
  to = from + (int64) 0x100000000ULL;
  values = sourceToTarget->GetValuesInRange(from, to);
  
  for (int32 i = 0; i < values.Length(); i++)
    links->Remove(values[i]);
  
  targetToSource->GetValuesInRange(from, to);
  
  return true;
}

// -------------------------------------------------------------------------------------------------
// Private / Methods
// -------------------------------------------------------------------------------------------------

/*!
 * @brief  Computes the key for the given link.
 * 
 * @param sourceId ID of source node of link.
 * @param targetId ID of target node of link.
 * 
 * @return The link key.
 */
template<class TNode>
int64 Graph<TNode>::Key(int32 sourceId, int32 targetId)
{
  return (int64) sourceId << 32 | targetId & (int64) 0xFFFFFFFFULL;
}

/*!
 * @brief  Returns the ID of the given graph node.
 * 
 * @param node The graph node.
 * 
 * @return The node ID or \c -1 .
 */
template<class TNode>
int32 Graph<TNode>::Id(typename TNode::In node)
{
  return nodeToId->Get(node, -1);
}

/*!
 * @brief  Returns the ID of the given graph node,allocating a new one if necessary.
 * 
 * @param node The graph node.
 * 
 * @return The node ID.
 */
template<class TNode>
int32 Graph<TNode>::IdNew(typename TNode::In node)
{
  int32 nodeId;
  
  if ((nodeId = nodeToId->Get(node, -1)) == -1) 
  {
    nodeToId->Put(node, nodeId = nodeToId->GetCount());
    
    // New nodes are always sources and sinks.
    
    sources->Add(nodeId);
    sinks->Add(nodeId);
  }
  
  return nodeId;
}

} } } 

#endif
