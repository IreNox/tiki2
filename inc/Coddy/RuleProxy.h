////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_PARSING_RULEPROXY_H
#define CLODDY_CORE_PARSING_RULEPROXY_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/RulePrecedence.h"

// Include referenced classes.

#include "Cloddy/RuleBase.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Parsing { template<class> class IRule; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace Parsing { template<class> class ParserContext; } } }

// Declare class ::Cloddy::Core::Parsing::RuleProxy.

namespace Cloddy { namespace Core { namespace Parsing
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  template<class T>
  class RuleProxy : public RuleBase<T>
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual RulePrecedence GetPrecedence();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    Ptr<IRule<T> > Set(IRule<T>* rule);
    
    virtual String ToString();
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
  protected:
    
    virtual bool DoMatch(ParserContext<T>* context, RulePrecedence precedence);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    Ptr<IRule<T> > rule;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Asserts that this mutable rule is not empty.
     */
    void AssertHasRule();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<RuleProxy<T> > ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x90C09FC9;
    
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
      if ((ptr = RuleBase<T>::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
