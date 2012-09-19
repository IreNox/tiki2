////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_PARSING_CHARINPUT_H
#define CLODDY_CORE_PARSING_CHARINPUT_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/ITokenInput.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace IO { namespace Streams { class IDataStream; } } } }

// Declare class ::Cloddy::Core::Parsing::CharInput.

namespace Cloddy { namespace Core { namespace Parsing
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::IO::Streams::IDataStream;
  
  /*!
   * @brief  An input token source of \c char  values.
   */
  class CharInput : public virtual ITokenInput<Prm<wchar_t> >
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual int32 GetCount();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of CharInput.
     * 
     * The given stream is fully read into memory by this method.
     * 
     * @param stream <b>[not-null]</b>  The input stream of ascii characters which is to be 
     * interpreted as the sequence of input tokens.
     * 
     * @return <b>[not-null]</b>  The token input object.
     */
    static Ptr<CharInput> FromAsciiStream(IDataStream* stream);
    
    /*!
     * @brief  Creates a new instance of CharInput.
     * 
     * The given character array is used as is,no copying is performed.
     * 
     * @param input <b>[not-null]</b>  The input token array.
     * @param inputOffset <b>[>=0]</b>  Offset into \e input  to first input token.
     * @param inputLength <b>[>=0]</b>  Length of input token array,starting at \e inputOffset .
     * 
     * @return <b>[not-null]</b>  The token input object.
     */
    static Ptr<CharInput> FromChars(Array<wchar_t> input, int32 inputOffset, int32 inputLength);
    
    /*!
     * @brief  Creates a new instance of CharInput.
     * 
     * @param input <b>[not-null]</b>  The input string that represents the sequence of input 
     * tokens.
     * 
     * @return <b>[not-null]</b>  The token input object.
     */
    static Ptr<ITokenInput<Prm<wchar_t> > > FromString(String input);
    
    virtual wchar_t TokenAt(int32 index);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The input tokens.
     */
    Array<wchar_t> tokens;
    
    /*!
     * @brief  Length of token array,starting at #tokensOffset.
     */
    int32 tokensLength;
    
    /*!
     * @brief  Offset into #tokens to first input token.
     */
    int32 tokensOffset;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of CharInput.
     * 
     * @param tokens The input tokens.
     * @param tokensOffset Offset into \e tokens .
     * @param tokensLength Number of input tokens,starting at \e tokensOffset .
     */
    CharInput(Array<wchar_t> tokens, int32 tokensOffset, int32 tokensLength);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<CharInput> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xFF563955;
    
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
      if ((ptr = ITokenInput<Prm<wchar_t> >::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
