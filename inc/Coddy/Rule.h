////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_PARSING_RULE_H
#define CLODDY_CORE_PARSING_RULE_H

#include "CodeX/System.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Collections { template<class> class ISetConst; } } }
namespace Cloddy { namespace Core { namespace Parsing { template<class> class IRule; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace Parsing { class AstNode; } } }

// Declare class ::Cloddy::Core::Parsing::Rule.

namespace Cloddy { namespace Core { namespace Parsing
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::Collections::ISetConst;
  
  class Rule
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Returns a rule that matches all characters except the given ones.
     * 
     * @param chars <b>[not-empty]</b>  The characters.
     * 
     * @return <b>[not-null]</b>  The rule.
     */
    static Ptr<IRule<Prm<wchar_t> > > NoneOf(String chars);
    
    /*!
     * @brief  Returns a rule that matches all characters except the given ones.
     * 
     * @param chars <b>[not-empty]</b>  The characters.
     * 
     * @return <b>[not-null]</b>  The rule.
     */
    static Ptr<IRule<Prm<wchar_t> > > NoneOf(ISetConst<Prm<wchar_t> >* chars);
    
    /*!
     * @brief  Returns a rule that matches one of the given characters.
     * 
     * @param chars <b>[not-empty]</b>  The characters.
     * 
     * @return <b>[not-null]</b>  The rule.
     */
    static Ptr<IRule<Prm<wchar_t> > > OneOf(String chars);
    
    /*!
     * @brief  Returns a rule that matches one of the given characters.
     * 
     * @param chars <b>[not-empty]</b>  The characters.
     * 
     * @return <b>[not-null]</b>  The rule.
     */
    static Ptr<IRule<Prm<wchar_t> > > OneOf(ISetConst<Prm<wchar_t> >* chars);
    
    /*!
     * @brief  Parses the given code using the specified rule.
     * 
     * @param code <b>[not-null]</b>  The code to parse.
     * @param rule <b>[not-null]</b>  The rule to use.
     * 
     * @return The parsed AST or \c null  if the given rule cannot match the specified input.
     */
    static Ptr<AstNode> Parse(String code, IRule<Prm<wchar_t> >* rule);
    
    /*!
     * @brief  Returns a rule that matches one character in the given range.
     * 
     * @param from First character of range,inclusive.
     * @param to <b>[>=from]</b>  Last character of range,inclusive.
     * 
     * @return <b>[not-null]</b>  The rule.
     */
    static Ptr<IRule<Prm<wchar_t> > > Range(wchar_t from, wchar_t to);
    
    /*!
     * @brief  Returns a rule that matches the given string token.
     * 
     * @param token <b>[not-empty]</b>  The string token.
     * 
     * @return <b>[not-null]</b>  The rule.
     */
    static Ptr<IRule<Prm<wchar_t> > > Token(String token);
    
    /*!
     * @brief  Wraps the given rule in the specified start and end tags.
     * 
     * @param rule <b>[not-null]</b>  The rule to wrap.
     * @param start <b>[not-empty]</b>  The start tag.
     * @param end <b>[not-empty]</b>  The end tag.
     * 
     * @return <b>[not-null]</b>  The rule.
     */
    static Ptr<IRule<Prm<wchar_t> > > Wrap(IRule<Prm<wchar_t> >* rule, String start, String end);
  };
  
} } } 

#endif
