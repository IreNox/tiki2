////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_PARSING_RULE_NONEOF_H
#define CLODDY_CORE_PARSING_RULE_NONEOF_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/RulePrecedence.h"

// Include referenced classes.

#include "Cloddy/TokenRuleBase.hpp"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Collections { template<class> class ISetConst; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace Parsing { template<class> class ParserContext; } } }
namespace Cloddy { namespace Core { namespace Parsing { class Rule; } } }

// Declare class ::Cloddy::Core::Parsing::Rule_NoneOf.

namespace Cloddy { namespace Core { namespace Parsing
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::Collections::ISetConst;
  
  class Rule_NoneOf : public TokenRuleBase<Prm<wchar_t> >
  {
    // Declare friend classes.
    
    friend class Rule;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual bool IsTerminal();
    
    virtual RulePrecedence GetPrecedence();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual String ToString();
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
  protected:
    
    virtual bool DoMatch(ParserContext<Prm<wchar_t> >* context, RulePrecedence precedence);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The set of characters to match.
     */
    Ptr<ISetConst<Prm<wchar_t> > > chars;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    Rule_NoneOf(ISetConst<Prm<wchar_t> >* chars);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<Rule_NoneOf> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x308EA6CD;
    
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
      if ((ptr = TokenRuleBase<Prm<wchar_t> >::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
