////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_PARSING_RULE_AST_HPP
#define CLODDY_CORE_PARSING_RULE_AST_HPP

#include "Cloddy/Rule_Ast.h"

// Include referenced enumerations.

#include "Cloddy/RulePrecedence.h"

// Include referenced interfaces.

#include "Cloddy/IRule.h"

// Include referenced classes.

#include "CodeX/ErrorInfo.h"
#include "CodeX/InvalidArgumentException.h"
#include "Cloddy/ParserContext.hpp"
#include "Cloddy/RuleBase.hpp"
#include "Cloddy/TokenType.h"

namespace Cloddy { namespace Core { namespace Parsing {

// Use referenced namespaces.

using namespace CodeX;

// Use referenced classes.

using CodeX::System::ErrorInfo;
using CodeX::System::InvalidArgumentException;

// -------------------------------------------------------------------------------------------------
// Public / Attributes
// -------------------------------------------------------------------------------------------------

template<class T>
RulePrecedence Rule_Ast<T>::GetPrecedence()
{
  return RulePrecedence_Name;
}

// -------------------------------------------------------------------------------------------------
// Public / Methods
// -------------------------------------------------------------------------------------------------

template<class T>
String Rule_Ast<T>::ToString()
{
  return tokenType->Name;
}

// -------------------------------------------------------------------------------------------------
// Protected / Methods
// -------------------------------------------------------------------------------------------------

template<class T>
bool Rule_Ast<T>::DoMatch(ParserContext<T>* context, RulePrecedence precedence)
{
  int32 start;
  
  start = context->GetPosition();
  
  if (rule->Match(context, GetPrecedence())) 
  {
    context->Push(tokenType, start, context->GetPosition());
    
    return true;
  }
  if (precedence != GetPrecedence()) context->Mismatch(this);
  
  return false;
}

// -------------------------------------------------------------------------------------------------
// Private / Constructors
// -------------------------------------------------------------------------------------------------

template<class T>
Rule_Ast<T>::Rule_Ast(IRule<T>* rule, TokenType* tokenType)
{
  this->rule = rule;
  this->tokenType = tokenType;
}

} } } 

#endif
