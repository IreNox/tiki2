////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_PARSING_TOKENRULE_NOT_H
#define CLODDY_CORE_PARSING_TOKENRULE_NOT_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/RulePrecedence.h"

// Include referenced classes.

#include "Cloddy/TokenRuleBase.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Parsing { template<class> class ITokenRule; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace Parsing { template<class> class ParserContext; } } }
namespace Cloddy { namespace Core { namespace Parsing { template<class> class TokenRuleBase; } } }

// Declare class ::Cloddy::Core::Parsing::TokenRule_Not.

namespace Cloddy { namespace Core { namespace Parsing
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  template<class T>
  class TokenRule_Not : public TokenRuleBase<T>
  {
    // Declare friend classes.
    
    template<class> friend class TokenRuleBase;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual bool IsTerminal();
    
    virtual RulePrecedence GetPrecedence();
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
  protected:
    
    virtual bool DoMatch(ParserContext<T>* context, RulePrecedence precedence);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    Ptr<ITokenRule<T> > rule;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    TokenRule_Not(ITokenRule<T>* rule);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<TokenRule_Not<T> > ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x5EC37398;
    
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
      if ((ptr = TokenRuleBase<T>::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
