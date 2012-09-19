////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_PARSING_TOKENRULE_AND_HPP
#define CLODDY_CORE_PARSING_TOKENRULE_AND_HPP

#include "Cloddy/TokenRule_And.h"

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
bool TokenRule_And<T>::IsTerminal()
{
  return true;
}

template<class T>
RulePrecedence TokenRule_And<T>::GetPrecedence()
{
  return RulePrecedence_Terminal;
}

// -------------------------------------------------------------------------------------------------
// Protected / Methods
// -------------------------------------------------------------------------------------------------

template<class T>
bool TokenRule_And<T>::DoMatch(ParserContext<T>* context, RulePrecedence precedence)
{
  context->Begin();
  
  if (first->Match(context, GetPrecedence()) && second->Match(context, GetPrecedence())) 
  {
    context->Commit();
    
    return true;
  }
  
  context->Rollback();
  context->Mismatch(this);
  
  return false;
}

// -------------------------------------------------------------------------------------------------
// Private / Constructors
// -------------------------------------------------------------------------------------------------

template<class T>
TokenRule_And<T>::TokenRule_And(ITokenRule<T>* first, ITokenRule<T>* second)
{
  this->first = first;
  this->second = second;
}

} } } 

#endif
