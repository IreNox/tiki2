////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_PARSING_TOKENRULE_NOT_HPP
#define CLODDY_CORE_PARSING_TOKENRULE_NOT_HPP

#include "Cloddy/TokenRule_Not.h"

// Include referenced enumerations.

#include "Cloddy/RulePrecedence.h"

// Include referenced interfaces.

#include "Cloddy/IRule.h"
#include "Cloddy/ITokenRule.h"

// Include referenced classes.

#include "CodeX/ErrorInfo.h"
#include "CodeX/InvalidArgumentException.h"
#include "Cloddy/ParserContext.hpp"
#include "Cloddy/TokenRuleBase.hpp"

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
bool TokenRule_Not<T>::IsTerminal()
{
  return true;
}

template<class T>
RulePrecedence TokenRule_Not<T>::GetPrecedence()
{
  return RulePrecedence_Terminal;
}

// -------------------------------------------------------------------------------------------------
// Protected / Methods
// -------------------------------------------------------------------------------------------------

template<class T>
bool TokenRule_Not<T>::DoMatch(ParserContext<T>* context, RulePrecedence precedence)
{
  context->Begin();
  
  if (rule->Match(context, GetPrecedence())) 
  {
    context->Rollback();
    context->Mismatch(this);
    
    return false;
  }
  
  context->Consume(1);
  context->Commit();
  
  return true;
}

// -------------------------------------------------------------------------------------------------
// Private / Constructors
// -------------------------------------------------------------------------------------------------

template<class T>
TokenRule_Not<T>::TokenRule_Not(ITokenRule<T>* rule)
{
  this->rule = rule;
}

} } } 

#endif
