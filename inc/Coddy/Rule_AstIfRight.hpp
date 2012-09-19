////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_PARSING_RULE_ASTIFRIGHT_HPP
#define CLODDY_CORE_PARSING_RULE_ASTIFRIGHT_HPP

#include "Cloddy/Rule_AstIfRight.h"

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
RulePrecedence Rule_AstIfRight<T>::GetPrecedence()
{
  return RulePrecedence_Alternative;
}

// -------------------------------------------------------------------------------------------------
// Public / Methods
// -------------------------------------------------------------------------------------------------

template<class T>
String Rule_AstIfRight<T>::ToString()
{
  return String::Format("%s | %s", (zstring) (left->ToStringBraces(this)), (zstring) (tokenType->Name));
}

// -------------------------------------------------------------------------------------------------
// Protected / Methods
// -------------------------------------------------------------------------------------------------

template<class T>
bool Rule_AstIfRight<T>::DoMatch(ParserContext<T>* context, RulePrecedence precedence)
{
  int32 start;
  
  start = context->GetPosition();
  
  context->Begin();
  
  if (left->Match(context, GetPrecedence())) 
  {
    if (right->Match(context, GetPrecedence())) context->Push(tokenType, start, context->GetPosition());
    
    context->Commit();
    
    return true;
  }
  
  context->Rollback();
  
  if (precedence != GetPrecedence()) context->Mismatch(this);
  
  return false;
}

// -------------------------------------------------------------------------------------------------
// Private / Constructors
// -------------------------------------------------------------------------------------------------

template<class T>
Rule_AstIfRight<T>::Rule_AstIfRight(IRule<T>* left, IRule<T>* right, TokenType* tokenType)
{
  this->left = left;
  this->right = right;
  this->tokenType = tokenType;
}

} } } 

#endif
