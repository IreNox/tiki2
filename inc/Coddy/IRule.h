////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_PARSING_IRULE_H
#define CLODDY_CORE_PARSING_IRULE_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/RulePrecedence.h"

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace Parsing { template<class> class ParserContext; } } }
namespace Cloddy { namespace Core { namespace Parsing { class TokenType; } } }

// Declare interface ::Cloddy::Core::Parsing::IRule.

namespace Cloddy { namespace Core { namespace Parsing
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Base interface for classes that represent parser rules that match zero or more input 
   *         tokens.
   */
  template<class T>
  class NO_VTABLE IRule : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Is this a terminal rule?
     * 
     * @return \c true  if this rule is terminal,\c false  if it is not.
     */
    virtual bool IsTerminal() = 0;
    
    /*!
     * @brief  Returns the precedence of this rule.
     * 
     * @return The rule precedence.
     */
    virtual RulePrecedence GetPrecedence() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Appends the given rule to this one.
     * 
     * @param rule <b>[not-null]</b>  The rule to append.
     * 
     * @return <b>[not-null]</b>  The resulting rule.
     */
    virtual Ptr<IRule<T> > Add(IRule<T>* rule) = 0;
    
    /*!
     * @brief  Returns a rule that creates an AST node upon match.
     * 
     * @param tokenType <b>[not-null]</b>  The token type.
     * 
     * @return <b>[not-null]</b>  The resulting rule.
     */
    virtual Ptr<IRule<T> > Ast(String tokenType) = 0;
    
    /*!
     * @brief  Returns a rule that creates an AST node upon match.
     * 
     * @param tokenType <b>[not-null]</b>  The token type.
     * 
     * @return <b>[not-null]</b>  The resulting rule.
     */
    virtual Ptr<IRule<T> > Ast(TokenType* tokenType) = 0;
    
    /*!
     * @brief  Creates an AST node from this rule and the given one if this rule is matched.
     * 
     * @param rule <b>[not-null]</b>  The other rule.
     * @param tokenType <b>[not-empty]</b>  The token type.
     * 
     * @return <b>[not-null]</b>  The resulting rule.
     */
    virtual Ptr<IRule<T> > AstIfLeft(IRule<T>* rule, String tokenType) = 0;
    
    /*!
     * @brief  Creates an AST node from this rule and the given one if this rule is matched.
     * 
     * @param rule <b>[not-null]</b>  The other rule.
     * @param tokenType <b>[not-null]</b>  The token type.
     * 
     * @return <b>[not-null]</b>  The resulting rule.
     */
    virtual Ptr<IRule<T> > AstIfLeft(IRule<T>* rule, TokenType* tokenType) = 0;
    
    /*!
     * @brief  Creates an AST node from this rule and the given one if the latter rule is matched.
     * 
     * @param rule <b>[not-null]</b>  The other rule.
     * @param tokenType <b>[not-empty]</b>  The token type.
     * 
     * @return <b>[not-null]</b>  The resulting rule.
     */
    virtual Ptr<IRule<T> > AstIfRight(IRule<T>* rule, String tokenType) = 0;
    
    /*!
     * @brief  Creates an AST node from this rule and the given one if the latter is matched.
     * 
     * @param rule <b>[not-null]</b>  The other rule.
     * @param tokenType <b>[not-null]</b>  The token type.
     * 
     * @return <b>[not-null]</b>  The resulting rule.
     */
    virtual Ptr<IRule<T> > AstIfRight(IRule<T>* rule, TokenType* tokenType) = 0;
    
    /*!
     * @brief  Compiles this rule into an optimized representation.
     * 
     * @return <b>[not-null]</b>  The compiled rule.
     */
    virtual Ptr<IRule<T> > Compile() = 0;
    
    /*!
     * @brief  Returns a rule that matches this rule \c n  times,where \c n  lies in the range 
     *         <c>[minOccurs..maxOccurs]</c>.
     * 
     * @param minOccurs <b>[>=0]</b>  Minimum number of allowed occurences.
     * @param maxOccurs <b>[>=minOccurs]</b>  Maximum number of allowed occurences.
     * 
     * @return <b>[not-null]</b>  The resulting rule.
     */
    virtual Ptr<IRule<T> > Many(int32 minOccurs, int32 maxOccurs) = 0;
    
    /*!
     * @brief  Tries to match the given input tokens.
     * 
     * @param context <b>[not-null]</b>  The parser context object to use.
     * @param precedence The precedence of the outer rule.
     * 
     * @return \c true  if the rule has successfully matched all input tokens,\c false  if the rule 
     * could not be matched.
     */
    virtual bool Match(ParserContext<T>* context, RulePrecedence precedence) = 0;
    
    /*!
     * @brief  Returns a rule that matches this rule one or more times.
     * 
     * @return <b>[not-null]</b>  The resulting rule.
     */
    virtual Ptr<IRule<T> > OneOrMore() = 0;
    
    /*!
     * @brief  Returns a rule that matches either this rule or the given one.
     * 
     * @param rule <b>[not-null]</b>  The rule.
     * 
     * @return <b>[not-null]</b>  The resulting rule.
     */
    virtual Ptr<IRule<T> > Or(IRule<T>* rule) = 0;
    
    /*!
     * @brief  Returns the string representation of this rule.
     * 
     * The string representation will be wrapped in braces if necessary regarding to the outer rule 
     * precedence.
     * 
     * @param outer The precedence of the outer rule.
     * 
     * @return <b>[not-null]</b>  The string representation.
     */
    virtual String ToStringBraces(RulePrecedence outer) = 0;
    
    /*!
     * @brief  Returns the string representation of this rule.
     * 
     * The string representation will be wrapped in braces if necessary regarding to the outer rule 
     * precedence.
     * 
     * @param outer <b>[not-null]</b>  The outer rule.
     * 
     * @return <b>[not-null]</b>  The string representation.
     */
    virtual String ToStringBraces(IRule<T>* outer) = 0;
    
    /*!
     * @brief  Returns a rule that matches this rule zero or more times.
     * 
     * @return <b>[not-null]</b>  The resulting rule.
     */
    virtual Ptr<IRule<T> > ZeroOrMore() = 0;
    
    /*!
     * @brief  Returns a rule that matches this rule zero times or one time.
     * 
     * @return <b>[not-null]</b>  The resulting rule.
     */
    virtual Ptr<IRule<T> > ZeroOrOne() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IRule<T> > ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x5AB248BC;
    
    /*!
     * @brief Tries to cast this object to the given type.
     *
     * @param typeId The ID of the type to cast to.
     *
     * @return The result of the type cast. Can be \c 0 if the requested cast is an invalid 
     *         downcast.
     */
    protected: virtual void* TryCast(int typeId)
    {
      if (typeId == TypeId) return (void*) this;
      return (void*) 0;
    }
  };
} } } 

#endif
