////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_IO_FILES_PATHGRAMMAR_H
#define CLODDY_CORE_IO_FILES_PATHGRAMMAR_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/ISyntaxErrorCallback.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Parsing { template<class> class IRule; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace IO { namespace Files { class Path; } } } }
namespace Cloddy { namespace Core { namespace Parsing { class AstNode; } } }
namespace Cloddy { namespace Core { namespace Parsing { class TokenType; } } }

// Declare class ::Cloddy::Core::IO::Files::PathGrammar.

namespace Cloddy { namespace Core { namespace IO { namespace Files
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::Parsing::IRule;
  using Cloddy::Core::Parsing::ISyntaxErrorCallback;
  
  // Use referenced classes.
  
  using Cloddy::Core::Parsing::AstNode;
  using Cloddy::Core::Parsing::TokenType;
  
  /*!
   * @brief  Helper class for parsing path strings into Path objects.
   */
  class PathGrammar : public virtual ISyntaxErrorCallback<Prm<wchar_t> >
  {
    // Declare friend classes.
    
    friend class Path;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Singleton instance of PathGrammar.
     */
    static const StaticPtr<PathGrammar> Instance;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The rule for parsing a path.
     */
    Ptr<IRule<Prm<wchar_t> > > path;
    
    Ptr<TokenType> tokenAbsolute;
    
    Ptr<TokenType> tokenName;
    
    Ptr<TokenType> tokenPath;
    
    Ptr<TokenType> tokenRoot;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of PathGrammar.
     */
    PathGrammar();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Parses the given path.
     * 
     * @param path The path to parsed.
     * 
     * @return The resulting AST or \c null  if an errors has occured.
     */
    Ptr<AstNode> Parse(String path);
    
    // ---------------------------------------------------------------------------------------------
    // Static Initializer Functions
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Static initializer function for field Instance.
     */
    static Object* StaticInitializer_Instance();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<PathGrammar> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x4DA7951E;
    
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
      if ((ptr = ISyntaxErrorCallback<Prm<wchar_t> >::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } 

#endif
