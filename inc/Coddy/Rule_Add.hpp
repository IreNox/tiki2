////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_PARSING_RULE_ADD_HPP
#define CLODDY_CORE_PARSING_RULE_ADD_HPP

#include "Cloddy/Rule_Add.h"

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
RulePrecedence Rule_Add<T>::GetPrecedence()
{
  return RulePrecedence_Sequence;
}

// -------------------------------------------------------------------------------------------------
// Public / Methods
// -------------------------------------------------------------------------------------------------

template<class T>
String Rule_Add<T>::ToString()
{
  return String::Format("%s %s", (zstring) (first->ToStringBraces(this)), (zstring) (second->ToStringBraces(this)));
}

// -------------------------------------------------------------------------------------------------
// Protected / Methods
// -------------------------------------------------------------------------------------------------

template<class T>
bool Rule_Add<T>::DoMatch(ParserContext<T>* context, RulePrecedence precedence)
{
  context->Begin();
  
  if (!first->Match(context, GetPrecedence())) 
  {
    context->Rollback();
    
    if (precedence != GetPrecedence()) context->Mismatch(this);
    
    return false;
  }
  if (!second->Match(context, GetPrecedence())) 
  {
    context->Rollback();
    
    if (precedence != GetPrecedence()) context->Mismatch(this);
    
    return false;
  }
  
  context->Commit();
  
  return true;
}

// -------------------------------------------------------------------------------------------------
// Private / Constructors
// -------------------------------------------------------------------------------------------------

/*!
 * @brief  Creates a new instance of Rule_Add.
 * 
 * @param first The first rule.
 * @param second The second rule.
 */
template<class T>
Rule_Add<T>::Rule_Add(IRule<T>* first, IRule<T>* second)
{
  this->first = first;
  this->second = second;
}

} } } 

#endif
