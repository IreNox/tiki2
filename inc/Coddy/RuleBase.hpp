////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_PARSING_RULEBASE_HPP
#define CLODDY_CORE_PARSING_RULEBASE_HPP

#include "Cloddy/RuleBase.h"

// Include referenced enumerations.

#include "Cloddy/RulePrecedence.h"

// Include referenced interfaces.

#include "Cloddy/IList.h"
#include "Cloddy/IRule.h"

// Include referenced classes.

#include "CodeX/ErrorInfo.h"
#include "CodeX/InvalidArgumentException.h"
#include "Cloddy/ParserContext.hpp"
#include "Cloddy/Rule_Add.hpp"
#include "Cloddy/Rule_Ast.hpp"
#include "Cloddy/Rule_AstIfLeft.hpp"
#include "Cloddy/Rule_AstIfRight.hpp"
#include "Cloddy/Rule_Many.hpp"
#include "Cloddy/Rule_Or.hpp"
#include "Cloddy/TokenType.h"

namespace Cloddy { namespace Core { namespace Parsing {

// Use referenced namespaces.

using namespace CodeX;

// Use referenced interfaces.

using Cloddy::Core::Collections::IList;

// Use referenced classes.

using CodeX::System::ErrorInfo;
using CodeX::System::InvalidArgumentException;

// -------------------------------------------------------------------------------------------------
// Public / Attributes
// -------------------------------------------------------------------------------------------------

template<class T>
bool RuleBase<T>::IsTerminal()
{
  return false;
}

// -------------------------------------------------------------------------------------------------
// Public / Methods
// -------------------------------------------------------------------------------------------------

template<class T>
Ptr<IRule<T> > RuleBase<T>::Add(IRule<T>* rule)
{
#ifdef _DEBUG
  if (rule == null) throw InvalidArgumentException::NotNull(ZSTRING("RuleBase.Add"), ZSTRING("rule"));
#endif
  
  return new Rule_Add<T>(this, rule);
}

template<class T>
Ptr<IRule<T> > RuleBase<T>::Ast(String tokenType)
{
#ifdef _DEBUG
  if (tokenType == null) throw InvalidArgumentException::NotNull(ZSTRING("RuleBase.Ast"), ZSTRING("tokenType"));
#endif
  
  Ptr<TokenType> type;
  
  type = new TokenType(tokenType);
  
  return Ast(type);
}

template<class T>
Ptr<IRule<T> > RuleBase<T>::Ast(TokenType* tokenType)
{
#ifdef _DEBUG
  if (tokenType == null) throw InvalidArgumentException::NotNull(ZSTRING("RuleBase.Ast"), ZSTRING("tokenType"));
#endif
  
  return new Rule_Ast<T>(this, tokenType);
}

template<class T>
Ptr<IRule<T> > RuleBase<T>::AstIfLeft(IRule<T>* rule, String tokenType)
{
#ifdef _DEBUG
  if (rule == null) throw InvalidArgumentException::NotNull(ZSTRING("RuleBase.AstIfLeft"), ZSTRING("rule"));
  if (tokenType == null || tokenType.Length() == 0) throw InvalidArgumentException::NotEmpty(ZSTRING("RuleBase.AstIfLeft"), ZSTRING("tokenType"));
#endif
  
  Ptr<TokenType> type;
  
  type = new TokenType(tokenType);
  
  return AstIfLeft(rule, type);
}

template<class T>
Ptr<IRule<T> > RuleBase<T>::AstIfLeft(IRule<T>* rule, TokenType* tokenType)
{
#ifdef _DEBUG
  if (rule == null) throw InvalidArgumentException::NotNull(ZSTRING("RuleBase.AstIfLeft"), ZSTRING("rule"));
  if (tokenType == null) throw InvalidArgumentException::NotNull(ZSTRING("RuleBase.AstIfLeft"), ZSTRING("tokenType"));
#endif
  
  return new Rule_AstIfLeft<T>(this, rule, tokenType);
}

template<class T>
Ptr<IRule<T> > RuleBase<T>::AstIfRight(IRule<T>* rule, String tokenType)
{
#ifdef _DEBUG
  if (rule == null) throw InvalidArgumentException::NotNull(ZSTRING("RuleBase.AstIfRight"), ZSTRING("rule"));
  if (tokenType == null || tokenType.Length() == 0) throw InvalidArgumentException::NotEmpty(ZSTRING("RuleBase.AstIfRight"), ZSTRING("tokenType"));
#endif
  
  Ptr<TokenType> type;
  
  type = new TokenType(tokenType);
  
  return AstIfRight(rule, type);
}

template<class T>
Ptr<IRule<T> > RuleBase<T>::AstIfRight(IRule<T>* rule, TokenType* tokenType)
{
#ifdef _DEBUG
  if (rule == null) throw InvalidArgumentException::NotNull(ZSTRING("RuleBase.AstIfRight"), ZSTRING("rule"));
  if (tokenType == null) throw InvalidArgumentException::NotNull(ZSTRING("RuleBase.AstIfRight"), ZSTRING("tokenType"));
#endif
  
  return new Rule_AstIfRight<T>(this, rule, tokenType);
}

template<class T>
Ptr<IRule<T> > RuleBase<T>::Compile()
{
  // TODO: Implement!
  
  return this;
}

template<class T>
Ptr<IRule<T> > RuleBase<T>::Many(int32 minOccurs, int32 maxOccurs)
{
#ifdef _DEBUG
  if (minOccurs < 0) throw InvalidArgumentException::GreaterEqual(ZSTRING("RuleBase.Many"), ZSTRING("minOccurs"), 0);
  if (maxOccurs < minOccurs) throw InvalidArgumentException::GreaterEqual(ZSTRING("RuleBase.Many"), ZSTRING("maxOccurs"), minOccurs);
#endif
  
  return new Rule_Many<T>(this, minOccurs, maxOccurs);
}

template<class T>
bool RuleBase<T>::Match(ParserContext<T>* context, RulePrecedence precedence)
{
#ifdef _DEBUG
  if (context == null) throw InvalidArgumentException::NotNull(ZSTRING("RuleBase.Match"), ZSTRING("context"));
#endif
  
  context->Increment(this);
  
  return DoMatch(context, precedence);
}

template<class T>
Ptr<IRule<T> > RuleBase<T>::OneOrMore()
{
  return Many(1, 2147483647);
}

template<class T>
Ptr<IRule<T> > RuleBase<T>::Or(IRule<T>* rule)
{
#ifdef _DEBUG
  if (rule == null) throw InvalidArgumentException::NotNull(ZSTRING("RuleBase.Or"), ZSTRING("rule"));
#endif
  
  return new Rule_Or<T>(this, rule);
}

template<class T>
String RuleBase<T>::ToStringBraces(IRule<T>* outer)
{
#ifdef _DEBUG
  if (outer == null) throw InvalidArgumentException::NotNull(ZSTRING("RuleBase.ToStringBraces"), ZSTRING("outer"));
#endif
  
  return ToStringBraces(outer->GetPrecedence());
}

template<class T>
String RuleBase<T>::ToStringBraces(RulePrecedence outer)
{
  if (GetPrecedence() > outer) return String::Format("(%s)", (zstring) (this->ToString()));
  
  return this->ToString();
}

template<class T>
Ptr<IRule<T> > RuleBase<T>::ZeroOrMore()
{
  return Many(0, 2147483647);
}

template<class T>
Ptr<IRule<T> > RuleBase<T>::ZeroOrOne()
{
  return Many(0, 1);
}

} } } 

#endif
