////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_PARSING_RULEPRECEDENCE_H
#define CLODDY_CORE_PARSING_RULEPRECEDENCE_H

#include "CodeX/System.h"

// Declare enumeration ::Cloddy::Core::Parsing::RulePrecedence.

namespace Cloddy { namespace Core { namespace Parsing
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Enumeration of rule precedence values.
   */
  enum RulePrecedence
  {
    /*!
     * @brief  A terminal rule.
     */
    RulePrecedence_Terminal = 0,
    
    /*!
     * @brief  A named rule.
     */
    RulePrecedence_Name = 1,
    
    /*!
     * @brief  A repeat rule.
     */
    RulePrecedence_Many = 2,
    
    /*!
     * @brief  A sequence rule.
     */
    RulePrecedence_Sequence = 3,
    
    /*!
     * @brief  An alternative rule.
     */
    RulePrecedence_Alternative = 4,
    
    /*!
     * @brief  No rule.
     */
    RulePrecedence_None = 5
  };
  
} } } 

#endif
