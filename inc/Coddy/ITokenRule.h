////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_PARSING_ITOKENRULE_H
#define CLODDY_CORE_PARSING_ITOKENRULE_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IRule.h"

// Declare interface ::Cloddy::Core::Parsing::ITokenRule.

namespace Cloddy { namespace Core { namespace Parsing
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Base interface for classes that represent parser token rules that match zero or one 
   *         input tokens.
   * 
   * Additional set semantics can be imposed on token rules.
   */
  template<class T>
  class NO_VTABLE ITokenRule : public virtual IRule<T>
  {
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Returns a token rule that matches an input token iff it would be matched by this 
     *         token rule and the given one.
     * 
     * @param rule <b>[not-null]</b>  The other token rule.
     * 
     * @return <b>[not-null]</b>  The resulting token rule.
     */
    virtual Ptr<ITokenRule<T> > And(ITokenRule<T>* rule) = 0;
    
    /*!
     * @brief  Returns a token rule that matches an input token iff it would be matched by this 
     *         token rule but not by the given one.
     * 
     * @param rule <b>[not-null]</b>  The other token rule.
     * 
     * @return <b>[not-null]</b>  The resulting token rule.
     */
    virtual Ptr<ITokenRule<T> > Except(ITokenRule<T>* rule) = 0;
    
    /*!
     * @brief  Returns a token rule that matches an input token when this rule does not,and 
     *         vice-versa.
     * 
     * @return <b>[not-null]</b>  The resulting token rule.
     */
    virtual Ptr<ITokenRule<T> > Not() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<ITokenRule<T> > ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xD26A8787;
    
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
