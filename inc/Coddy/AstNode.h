////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_PARSING_ASTNODE_H
#define CLODDY_CORE_PARSING_ASTNODE_H

#include "CodeX/System.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Collections { template<class> class IList; } } }
namespace Cloddy { namespace Core { namespace Collections { template<class> class IListConst; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace Collections { template<class> class ArrayList; } } }
namespace Cloddy { namespace Core { namespace Parsing { template<class> class ParserContext; } } }
namespace Cloddy { namespace Core { namespace Parsing { class TokenType; } } }

// Declare class ::Cloddy::Core::Parsing::AstNode.

namespace Cloddy { namespace Core { namespace Parsing
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::Collections::IList;
  using Cloddy::Core::Collections::IListConst;
  
  // Use referenced classes.
  
  using Cloddy::Core::Collections::ArrayList;
  
  /*!
   * @brief  Represents a node of an abstract syntax tree (AST).
   */
  class AstNode : public virtual Object
  {
    // Declare friend classes.
    
    template<class> friend class ParserContext;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constants
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  End end-of-stream marker.
     */
    static const int32 Eof = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Returns the child nodes of this AST node.
     * 
     * @return <b>[not-null]</b>  The child nodes.
     */
    Ptr<IListConst<Ref<AstNode> > > GetChildren();
    
    /*!
     * @brief  Index of last input token that belongs to this AST node (exclusive).
     * 
     * @return <b>[>=0]</b>  The token index.
     */
    int32 GetEnd();
    
    /*!
     * @brief  The parent node or \c null  if this AST node is the root.
     * 
     * @return The parent node.
     */
    Ptr<AstNode> GetParent();
    
    /*!
     * @brief  Index of first input token that belongs to this AST node (inclusive).
     * 
     * @return <b>[>=0]</b>  The token index.
     */
    int32 GetStart();
    
    /*!
     * @brief  The input token type.
     * 
     * The token type value \c -1  is reserved for the end-of-stream marker (see #Eof).
     * 
     * @return <b>[not-null]</b>  The token type.
     */
    Ptr<TokenType> GetType();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Dumps the AST to the standard output.
     */
    void Dump();
    
    /*!
     * @brief  Extracts the range of this AST node from the given string.
     * 
     * The given string must be identical to the parser input (eg. see CharInput).
     * 
     * @param sourceCode <b>[not-null]</b>  The source code string.
     * 
     * @return <b>[not-null]</b>  The AST node range.
     */
    String Extract(String sourceCode);
    
    virtual String ToString();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Zero-length list of AST nodes.
     */
    static const StaticPtr<IListConst<Ref<AstNode> > > EmptyList;
    
    /*!
     * @brief  The list of child nodes.
     */
    Ptr<IList<Ref<AstNode> > > children;
    
    /*!
     * @brief  Index of last input token that belongs to this AST node (exclusive).
     */
    int32 end;
    
    /*!
     * @brief  The parent node or \c null  if this AST node is the root.
     */
    Ptr<AstNode> parent;
    
    /*!
     * @brief  Index of first input token that belongs to this AST node (inclusive).
     */
    int32 start;
    
    /*!
     * @brief  The input token type.
     * 
     * The token type value \c -1  is reserved for the end-of-stream marker (see #Eof).
     */
    Ptr<TokenType> type;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of AstNode.
     * 
     * @param type The node type.
     * @param start Index of first input token that belongs to this AST node (inclusive).
     * @param end Index of last input token that belongs to this AST node (exclusive).
     */
    AstNode(TokenType* type, int32 start, int32 end);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Adds the given AST node as a child to this node.
     * 
     * @param node The child node to add.
     */
    void AddChild(AstNode* node);
    
    void Dump(String prefix);
    
    // ---------------------------------------------------------------------------------------------
    // Static Initializer Functions
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Static initializer function for field EmptyList.
     */
    static Object* StaticInitializer_EmptyList();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<AstNode> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x5E681F3D;
    
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
