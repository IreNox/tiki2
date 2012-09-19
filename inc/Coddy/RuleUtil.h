////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_PARSING_RULEUTIL_H
#define CLODDY_CORE_PARSING_RULEUTIL_H

#include "CodeX/System.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Collections { template<class> class ISet; } } }

// Declare class ::Cloddy::Core::Parsing::RuleUtil.

namespace Cloddy { namespace Core { namespace Parsing
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::Collections::ISet;
  
  /*!
   * @brief  Helper class for dealing with parser rules.
   */
  class RuleUtil
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Returns a set that contains all the characters found in the given string.
     * 
     * @param s The input string.
     * @param chars The set to use or \c null .
     * 
     * @return The set of characters.
     */
    static Ptr<ISet<Prm<wchar_t> > > ToCharSet(String s, ISet<Prm<wchar_t> >* chars);
  };
  
} } } 

#endif
