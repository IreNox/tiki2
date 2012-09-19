////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_PARSING_RULE_MANY_HPP
#define CLODDY_CORE_PARSING_RULE_MANY_HPP

#include "Cloddy/Rule_Many.h"

// Include referenced enumerations.

#include "Cloddy/RulePrecedence.h"

// Include referenced interfaces.

#include "Cloddy/IRule.h"

// Include referenced classes.

#include "CodeX/ErrorInfo.h"
#include "CodeX/InvalidArgumentException.h"
#include "Cloddy/ParserContext.hpp"
#include "Cloddy/RuleBase.hpp"

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
RulePrecedence Rule_Many<T>::GetPrecedence()
{
  return RulePrecedence_Many;
}

// -------------------------------------------------------------------------------------------------
// Public / Methods
// -------------------------------------------------------------------------------------------------

template<class T>
String Rule_Many<T>::ToString()
{
  if (min == 0 && max == 1) return String::Format("%s?", (zstring) (rule->ToStringBraces(this)));
  if (min == 0 && max == 2147483647) return String::Format("%s*", (zstring) (rule->ToStringBraces(this)));
  if (min == 1 && max == 2147483647) return String::Format("%s+", (zstring) (rule->ToStringBraces(this)));
  
  return String::Format("%s{{%d..%d}}", (zstring) (rule->ToStringBraces(this)), min, max);
}

// -------------------------------------------------------------------------------------------------
// Protected / Methods
// -------------------------------------------------------------------------------------------------

template<class T>
bool Rule_Many<T>::DoMatch(ParserContext<T>* context, RulePrecedence precedence)
{
  context->Begin();
  
  for (int32 i = 0; i < min; i++)
  {
    if (rule->Match(context, GetPrecedence())) continue;
    
    context->Rollback();
    context->Mismatch(this);
    
    return false;
  }
  for (int32 i = min; i < max; i++)
  {
    if (rule->Match(context, GetPrecedence())) continue;
    
    context->Commit();
    
    return true;
  }
  
  if (rule->Match(context, GetPrecedence())) 
  {
    context->Rollback();
    context->Mismatch(this);
    
    return false;
  }
  
  context->Commit();
  
  return true;
}

// -------------------------------------------------------------------------------------------------
// Private / Constructors
// -------------------------------------------------------------------------------------------------

template<class T>
Rule_Many<T>::Rule_Many(IRule<T>* rule, int32 min, int32 max)
{
  // Initialize all primitive fields to default values.
  
  this->max = 0;
  this->min = 0;
  
  this->rule = rule;
  this->min = min;
  this->max = max;
}

} } } 

#endif
