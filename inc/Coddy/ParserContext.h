////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_PARSING_PARSERCONTEXT_H
#define CLODDY_CORE_PARSING_PARSERCONTEXT_H

#include "CodeX/System.h"

// Include referenced classes.

#include "CodeX/Disposable.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Collections { template<class> class IDeque; } } }
namespace Cloddy { namespace Core { namespace Collections { template<class> class IList; } } }
namespace Cloddy { namespace Core { namespace Parsing { template<class> class IRule; } } }
namespace Cloddy { namespace Core { namespace Parsing { template<class> class ISyntaxErrorCallback; } } }
namespace Cloddy { namespace Core { namespace Parsing { template<class> class ITokenInput; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace Parsing { class AstNode; } } }
namespace Cloddy { namespace Core { namespace Parsing { template<class> class Rule_Add; } } }
namespace Cloddy { namespace Core { namespace Parsing { template<class> class Rule_Ast; } } }
namespace Cloddy { namespace Core { namespace Parsing { template<class> class Rule_AstIfLeft; } } }
namespace Cloddy { namespace Core { namespace Parsing { template<class> class Rule_AstIfRight; } } }
namespace Cloddy { namespace Core { namespace Parsing { template<class> class Rule_Many; } } }
namespace Cloddy { namespace Core { namespace Parsing { class Rule_NoneOf; } } }
namespace Cloddy { namespace Core { namespace Parsing { class Rule_OneOf; } } }
namespace Cloddy { namespace Core { namespace Parsing { template<class> class Rule_Or; } } }
namespace Cloddy { namespace Core { namespace Parsing { class Rule_Range; } } }
namespace Cloddy { namespace Core { namespace Parsing { class Rule_Token; } } }
namespace Cloddy { namespace Core { namespace Parsing { template<class> class RuleBase; } } }
namespace Cloddy { namespace Core { namespace Parsing { template<class> class TokenRule_And; } } }
namespace Cloddy { namespace Core { namespace Parsing { template<class> class TokenRule_Except; } } }
namespace Cloddy { namespace Core { namespace Parsing { template<class> class TokenRule_Not; } } }
namespace Cloddy { namespace Core { namespace Parsing { class TokenType; } } }

// Declare class ::Cloddy::Core::Parsing::ParserContext.

namespace Cloddy { namespace Core { namespace Parsing
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::Collections::IDeque;
  using Cloddy::Core::Collections::IList;
  
  // Use referenced classes.
  
  using CodeX::System::Disposable;
  
  template<class T>
  class ParserContext : public Disposable
  {
    // Declare friend classes.
    
    template<class> friend class Rule_Add;
    template<class> friend class Rule_Ast;
    template<class> friend class Rule_AstIfLeft;
    template<class> friend class Rule_AstIfRight;
    template<class> friend class Rule_Many;
    friend class Rule_NoneOf;
    friend class Rule_OneOf;
    template<class> friend class Rule_Or;
    friend class Rule_Range;
    friend class Rule_Token;
    template<class> friend class RuleBase;
    template<class> friend class TokenRule_And;
    template<class> friend class TokenRule_Except;
    template<class> friend class TokenRule_Not;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Has the end of the input token sequence been reached?
     * 
     * @return \c true  if there are no more input tokens following the current position,\c false  
     * if at least one more token will follow.
     */
    bool IsEof();
    
    int64 GetMatchesNonTerminal();
    
    int64 GetMatchesTerminal();
    
    /*!
     * @brief  Returns the current position.
     * 
     * @return <b>[>=0]</b>  The current position.
     */
    int32 GetPosition();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of ParserContext.
     * 
     * @param input <b>[not-null]</b>  The input tokens.
     * @param syntaxErrorCallback Optional callback for syntax errors.
     */
    ParserContext(ITokenInput<T>* input, ISyntaxErrorCallback<T>* syntaxErrorCallback);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    void Begin();
    
    void Commit();
    
    /*!
     * @brief  Consumes the next \e n  input tokens and advances the position accordingly.
     * 
     * @param n Number of input tokens to consume.
     */
    void Consume(int32 n);
    
    Ptr<AstNode> CreateAst();
    
    /*!
     * @brief  Peeks a token relative to the current position without modifying the current 
     *         position.
     * 
     * If the resulting token offset lies outside the valid range,the default value of the token 
     * type will be returned.
     * 
     * @param offset The relative offset.
     * 
     * @return The token.
     */
    typename T::Out Peek(int32 offset);
    
    void Rollback();
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
  protected:
    
    virtual void DisposeManaged();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constants
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Begins a new frame on the AST output command stack.
     */
    static const int32 CommandBegin = 1;
    
    /*!
     * @brief  Commits the current frame on the AST output command stack.
     */
    static const int32 CommandCommit = 2;
    
    /*!
     * @brief  Creates a new AST node.
     */
    static const int32 CommandCreate = 3;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
    
    Ptr<IDeque<Prm<int32> > > errorPosition;
    
    Ptr<IDeque<Ref<IRule<T> > > > errorRule;
    
    /*!
     * @brief  The input tokens.
     */
    Ptr<ITokenInput<T> > input;
    
    /*!
     * @brief  Number of input tokens.
     */
    int32 inputCount;
    
    /*!
     * @brief  The last position.
     */
    int32 inputLast;
    
    /*!
     * @brief  The current position.
     */
    int32 inputPosition;
    
    /*!
     * @brief  Position stack for input tokens.
     */
    Ptr<IDeque<Prm<int32> > > inputStack;
    
    int64 matchesNonTerminal;
    
    int64 matchesTerminal;
    
    /*!
     * @brief  The list of output AST commands.
     */
    Ptr<IList<Prm<int32> > > output;
    
    /*!
     * @brief  Position stack for output tokens.
     */
    Ptr<IDeque<Prm<int32> > > outputStack;
    
    /*!
     * @brief  The callback for syntax errors.
     */
    Ptr<ISyntaxErrorCallback<T> > syntaxErrorCallback;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Asserts that the position stack is not empty.
     */
    void AssertStackNotEmpty();
    
    int32 CreateAst(int32 index, IList<Ref<AstNode> >* nodes);
    
    void Increment(IRule<T>* rule);
    
    void Mismatch(IRule<T>* rule);
    
    void Push(TokenType* type, int32 start, int32 end);
    
    void RuleFailed(IRule<T>* rule);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<ParserContext<T> > ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x34C8A4D3;
    
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
      if ((ptr = Disposable::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
