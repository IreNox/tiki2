////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_PARSING_RULEPROXY_HPP
#define CLODDY_CORE_PARSING_RULEPROXY_HPP

#include "Cloddy/RuleProxy.h"

// Include referenced enumerations.

#include "Cloddy/RulePrecedence.h"

// Include referenced interfaces.

#include "Cloddy/IRule.h"

// Include referenced classes.

#include "CodeX/ErrorInfo.h"
#include "CodeX/FailedAssertionException.h"
#include "CodeX/InvalidArgumentException.h"
#include "Cloddy/ParserContext.hpp"
#include "Cloddy/RuleBase.hpp"

namespace Cloddy { namespace Core { namespace Parsing {

// Use referenced namespaces.

using namespace CodeX;

// Use referenced classes.

using CodeX::System::ErrorInfo;
using CodeX::System::FailedAssertionException;
using CodeX::System::InvalidArgumentException;

// -------------------------------------------------------------------------------------------------
// Public / Attributes
// -------------------------------------------------------------------------------------------------

template<class T>
RulePrecedence RuleProxy<T>::GetPrecedence()
{
#ifdef _DEBUG
  AssertHasRule();
#endif
  
  return rule->GetPrecedence();
}

// -------------------------------------------------------------------------------------------------
// Public / Methods
// -------------------------------------------------------------------------------------------------

template<class T>
Ptr<IRule<T> > RuleProxy<T>::Set(IRule<T>* rule)
{
  this->rule = rule;
  
  return this;
}

template<class T>
String RuleProxy<T>::ToString()
{
#ifdef _DEBUG
  AssertHasRule();
#endif
  
  return rule->ToString();
}

// -------------------------------------------------------------------------------------------------
// Protected / Methods
// -------------------------------------------------------------------------------------------------

template<class T>
bool RuleProxy<T>::DoMatch(ParserContext<T>* context, RulePrecedence precedence)
{
#ifdef _DEBUG
  AssertHasRule();
#endif
  
  return rule->Match(context, GetPrecedence());
}

// -------------------------------------------------------------------------------------------------
// Private / Methods
// -------------------------------------------------------------------------------------------------

/*!
 * @brief  Asserts that this mutable rule is not empty.
 */
template<class T>
void RuleProxy<T>::AssertHasRule()
{
  if (rule == null) throw FailedAssertionException::BadState(ZSTRING("RuleProxy.AssertHasRule"), ZSTRING("Rule is empty!"));
}

} } } 

#endif
