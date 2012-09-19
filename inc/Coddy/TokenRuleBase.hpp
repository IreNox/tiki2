////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_PARSING_TOKENRULEBASE_HPP
#define CLODDY_CORE_PARSING_TOKENRULEBASE_HPP

#include "Cloddy/TokenRuleBase.h"

// Include referenced enumerations.

#include "Cloddy/RulePrecedence.h"

// Include referenced interfaces.

#include "Cloddy/IRule.h"
#include "Cloddy/ITokenRule.h"

// Include referenced classes.

#include "CodeX/ErrorInfo.h"
#include "CodeX/InvalidArgumentException.h"
#include "Cloddy/RuleBase.hpp"
#include "Cloddy/TokenRule_And.hpp"
#include "Cloddy/TokenRule_Except.hpp"
#include "Cloddy/TokenRule_Not.hpp"

namespace Cloddy { namespace Core { namespace Parsing {

// Use referenced namespaces.

using namespace CodeX;

// Use referenced classes.

using CodeX::System::ErrorInfo;
using CodeX::System::InvalidArgumentException;

// -------------------------------------------------------------------------------------------------
// Public / Methods
// -------------------------------------------------------------------------------------------------

template<class T>
Ptr<ITokenRule<T> > TokenRuleBase<T>::And(ITokenRule<T>* rule)
{
#ifdef _DEBUG
  if (rule == null) throw InvalidArgumentException::NotNull(ZSTRING("TokenRuleBase.And"), ZSTRING("rule"));
#endif
  
  return new TokenRule_And<T>(this, rule);
}

template<class T>
Ptr<ITokenRule<T> > TokenRuleBase<T>::Except(ITokenRule<T>* rule)
{
#ifdef _DEBUG
  if (rule == null) throw InvalidArgumentException::NotNull(ZSTRING("TokenRuleBase.Except"), ZSTRING("rule"));
#endif
  
  return new TokenRule_Except<T>(this, rule);
}

template<class T>
Ptr<ITokenRule<T> > TokenRuleBase<T>::Not()
{
  return new TokenRule_Not<T>(this);
}

} } } 

#endif
