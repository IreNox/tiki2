////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_PARSING_RULEBASE_H
#define CLODDY_CORE_PARSING_RULEBASE_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/RulePrecedence.h"

// Include referenced interfaces.

#include "Cloddy/IRule.h"

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace Parsing { template<class> class ParserContext; } } }
namespace Cloddy { namespace Core { namespace Parsing { class TokenType; } } }

// Declare class ::Cloddy::Core::Parsing::RuleBase.

namespace Cloddy { namespace Core { namespace Parsing
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  template<class T>
  class RuleBase : public virtual IRule<T>
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual bool IsTerminal();
    
    virtual RulePrecedence GetPrecedence() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual Ptr<IRule<T> > Add(IRule<T>* rule);
    
    virtual Ptr<IRule<T> > Ast(String tokenType);
    
    virtual Ptr<IRule<T> > Ast(TokenType* tokenType);
    
    virtual Ptr<IRule<T> > AstIfLeft(IRule<T>* rule, String tokenType);
    
    virtual Ptr<IRule<T> > AstIfLeft(IRule<T>* rule, TokenType* tokenType);
    
    virtual Ptr<IRule<T> > AstIfRight(IRule<T>* rule, String tokenType);
    
    virtual Ptr<IRule<T> > AstIfRight(IRule<T>* rule, TokenType* tokenType);
    
    virtual Ptr<IRule<T> > Compile();
    
    virtual Ptr<IRule<T> > Many(int32 minOccurs, int32 maxOccurs);
    
    virtual bool Match(ParserContext<T>* context, RulePrecedence precedence);
    
    virtual Ptr<IRule<T> > OneOrMore();
    
    virtual Ptr<IRule<T> > Or(IRule<T>* rule);
    
    virtual String ToStringBraces(IRule<T>* outer);
    
    virtual String ToStringBraces(RulePrecedence outer);
    
    virtual Ptr<IRule<T> > ZeroOrMore();
    
    virtual Ptr<IRule<T> > ZeroOrOne();
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
  protected:
    
    virtual bool DoMatch(ParserContext<T>* context, RulePrecedence precedence) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<RuleBase<T> > ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x246C33B4;
    
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
      void* ptr;
      if ((ptr = IRule<T>::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
