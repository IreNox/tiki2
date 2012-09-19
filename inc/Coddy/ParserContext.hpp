////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_PARSING_PARSERCONTEXT_HPP
#define CLODDY_CORE_PARSING_PARSERCONTEXT_HPP

#include "Cloddy/ParserContext.h"

// Include referenced interfaces.

#include "Cloddy/IDeque.h"
#include "Cloddy/IEnumerable.h"
#include "Cloddy/IEnumerator.h"
#include "Cloddy/IList.h"
#include "Cloddy/IListConst.h"
#include "Cloddy/IRule.h"
#include "Cloddy/ISet.h"
#include "Cloddy/ISyntaxErrorCallback.h"
#include "Cloddy/ITokenInput.h"

// Include referenced classes.

#include "Cloddy/ArrayDeque.hpp"
#include "Cloddy/ArrayList.hpp"
#include "Cloddy/AstNode.h"
#include "CodeX/CoreException.h"
#include "CodeX/ErrorInfo.h"
#include "CodeX/FailedAssertionException.h"
#include "CodeX/InvalidArgumentException.h"
#include "Cloddy/TokenType.h"

namespace Cloddy { namespace Core { namespace Parsing {

// Use referenced namespaces.

using namespace CodeX;

// Use referenced interfaces.

using Cloddy::Core::Collections::IDeque;
using Cloddy::Core::Collections::IEnumerable;
using Cloddy::Core::Collections::IEnumerator;
using Cloddy::Core::Collections::IList;
using Cloddy::Core::Collections::IListConst;
using Cloddy::Core::Collections::ISet;

// Use referenced classes.

using Cloddy::Core::Collections::ArrayDeque;
using Cloddy::Core::Collections::ArrayList;
using CodeX::System::CoreException;
using CodeX::System::Disposable;
using CodeX::System::ErrorInfo;
using CodeX::System::FailedAssertionException;
using CodeX::System::InvalidArgumentException;

// -------------------------------------------------------------------------------------------------
// Public / Attributes
// -------------------------------------------------------------------------------------------------

/*!
 * @brief  Has the end of the input token sequence been reached?
 * 
 * @return \c true  if there are no more input tokens following the current position,\c false  if 
 * at least one more token will follow.
 */
template<class T>
bool ParserContext<T>::IsEof()
{
  return inputPosition == inputCount;
}

template<class T>
int64 ParserContext<T>::GetMatchesNonTerminal()
{
  return matchesNonTerminal;
}

template<class T>
int64 ParserContext<T>::GetMatchesTerminal()
{
  return matchesTerminal;
}

/*!
 * @brief  Returns the current position.
 * 
 * @return <b>[>=0]</b>  The current position.
 */
template<class T>
int32 ParserContext<T>::GetPosition()
{
  return inputPosition;
}

// -------------------------------------------------------------------------------------------------
// Public / Constructors
// -------------------------------------------------------------------------------------------------

/*!
 * @brief  Creates a new instance of ParserContext.
 * 
 * @param input <b>[not-null]</b>  The input tokens.
 * @param syntaxErrorCallback Optional callback for syntax errors.
 */
template<class T>
ParserContext<T>::ParserContext(ITokenInput<T>* input, ISyntaxErrorCallback<T>* syntaxErrorCallback)
{
  // Initialize all primitive fields to default values.
  
  this->inputCount = 0;
  this->inputLast = 0;
  this->inputPosition = 0;
  this->matchesNonTerminal = 0LL;
  this->matchesTerminal = 0LL;
  
#ifdef _DEBUG
  if (input == null) throw InvalidArgumentException::NotNull(ZSTRING("ParserContext.ParserContext"), ZSTRING("input"));
#endif
  
  try
  {
    this->input = input;
    this->syntaxErrorCallback = syntaxErrorCallback;
    inputLast = input->GetCount() - 1;
    inputCount = input->GetCount();
    inputStack = new ArrayDeque<Prm<int32> >();
    output = new ArrayList<Prm<int32> >();
    outputStack = new ArrayDeque<Prm<int32> >();
    errorRule = new ArrayDeque<Ref<IRule<T> > >();
    errorPosition = new ArrayDeque<Prm<int32> >();
  }
  catch (...)
  {
    this->Dispose();
    
    throw ;
  }
}

// -------------------------------------------------------------------------------------------------
// Public / Methods
// -------------------------------------------------------------------------------------------------

template<class T>
void ParserContext<T>::Begin()
{
  inputStack->PushLast(inputPosition);
  outputStack->PushLast(output->GetCount());
  output->Add(CommandBegin);
}

template<class T>
void ParserContext<T>::Commit()
{
#ifdef _DEBUG
  AssertStackNotEmpty();
#endif
  
  int32 oldPosition;
  
  oldPosition = inputStack->PopLast();
  
  outputStack->PopLast();
  output->Add(CommandCommit);
  
  // Clear rule mismatch stack if the committed rule has consumed at least one input token.
  
  if (oldPosition < inputPosition) 
  {
    while (errorPosition->GetCount() > 0 && errorPosition->PeekLast() <= inputPosition)
    {
      errorRule->PopLast();
      errorPosition->PopLast();
    }
  }
}

/*!
 * @brief  Consumes the next \e n  input tokens and advances the position accordingly.
 * 
 * @param n Number of input tokens to consume.
 */
template<class T>
void ParserContext<T>::Consume(int32 n)
{
  inputPosition += n;
  
  if (inputPosition > inputCount) inputPosition = inputCount;
}

template<class T>
Ptr<AstNode> ParserContext<T>::CreateAst()
{
  Ptr<IList<Ref<AstNode> > > nodes;
  
  // Console.Out.WriteLine("MatchesTerminal    = {0}", MatchesTerminal);
  // Console.Out.WriteLine("MatchesNonTerminal = {0}", MatchesNonTerminal);
  // Console.Out.WriteLine("Errors:");
  // while (errorPosition.Count > 0)
  // {
  // int pos;
  // IRule<T> rule;
  // pos = errorPosition.PopLast();
  // rule = errorRule.PopLast();
  // Console.Out.WriteLine(pos + " : " + rule);
  // }
  // if (!IsEof)
  // Console.Out.WriteLine(inputPosition + " : no viable alternative");
  
  nodes = new ArrayList<Ref<AstNode> >();
  
  CreateAst(0, nodes);
  
  return nodes->GetCount() == 1 ? nodes->GetAt(0) : null;
}

/*!
 * @brief  Peeks a token relative to the current position without modifying the current position.
 * 
 * If the resulting token offset lies outside the valid range,the default value of the token type 
 * will be returned.
 * 
 * @param offset The relative offset.
 * 
 * @return The token.
 */
template<class T>
typename T::Out ParserContext<T>::Peek(int32 offset)
{
  offset += inputPosition;
  
  if (offset < 0 || offset > inputLast) return T::Default();
  
  return input->TokenAt(offset);
}

template<class T>
void ParserContext<T>::Rollback()
{
  int32 last;
  
#ifdef _DEBUG
  AssertStackNotEmpty();
#endif
  
  inputPosition = inputStack->PopLast();
  last = outputStack->PopLast();
  
  output->RemoveRange(last, output->GetCount() - last);
}

// -------------------------------------------------------------------------------------------------
// Protected / Methods
// -------------------------------------------------------------------------------------------------

template<class T>
void ParserContext<T>::DisposeManaged()
{
  output = null;
  input = null;
  inputStack = null;
  outputStack = null;
  syntaxErrorCallback = null;
  errorPosition = null;
  errorRule = null;
  
  Disposable::DisposeManaged();
}

// -------------------------------------------------------------------------------------------------
// Private / Methods
// -------------------------------------------------------------------------------------------------

/*!
 * @brief  Asserts that the position stack is not empty.
 */
template<class T>
void ParserContext<T>::AssertStackNotEmpty()
{
  if (outputStack->GetCount() == 0) throw FailedAssertionException::BadState(ZSTRING("ParserContext.AssertStackNotEmpty"), ZSTRING("Position stack is empty!"));
}

template<class T>
int32 ParserContext<T>::CreateAst(int32 index, IList<Ref<AstNode> >* nodes)
{
  int32 firstNode;
  
  firstNode = 0;
  
  while (index < output->GetCount())
  {
    Ptr<AstNode> node;
    int32 cmd;
    Ptr<TokenType> tokenType;
    int32 start;
    int32 end;
    
    cmd = output->GetAt(index++);
    
    switch (cmd)
    {
      case CommandBegin:
        firstNode = nodes->GetCount();
        index = CreateAst(index, nodes);
        
        continue;
      
      case CommandCommit:
        return index;
      
      case CommandCreate:
        break;
      
      default:
        throw CoreException::UnknownEnum(ZSTRING("ParserContext.CreateAst"), ZSTRING("Command"), cmd);
    }
    
    // Create new AST node.
    
    tokenType = TokenType::FromId(output->GetAt(index++));
    start = output->GetAt(index++);
    end = output->GetAt(index++);
    node = new AstNode(tokenType, start, end);
    
    // Collect child AST nodes.
    
    for (int32 i = firstNode; i < nodes->GetCount(); i++)
      node->AddChild(nodes->GetAt(i));
    
    nodes->RemoveRange(firstNode, nodes->GetCount() - firstNode);
    
    // Add new AST node to list.
    
    nodes->Add(node);
  }
  
  return index;
}

template<class T>
void ParserContext<T>::Increment(IRule<T>* rule)
{
  if (rule->IsTerminal()) matchesTerminal++;
  else matchesNonTerminal++;
}

template<class T>
void ParserContext<T>::Mismatch(IRule<T>* rule)
{
  errorPosition->PushLast(inputPosition);
  errorRule->PushLast(rule);
}

template<class T>
void ParserContext<T>::Push(TokenType* type, int32 start, int32 end)
{
  output->Add(CommandCreate);
  output->Add(type->Id);
  output->Add(start);
  output->Add(end);
}

template<class T>
void ParserContext<T>::RuleFailed(IRule<T>* rule)
{
}

} } } 

#endif
