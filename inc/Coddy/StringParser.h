////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_PARSING_STRINGPARSER_H
#define CLODDY_CORE_PARSING_STRINGPARSER_H

#include "CodeX/System.h"

// Declare class ::Cloddy::Core::Parsing::StringParser.

namespace Cloddy { namespace Core { namespace Parsing
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Helper class for performing simple parsing tasks for strings.
   */
  class StringParser : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Has the end of input been reached?
     * 
     * @return \c true  if the end of input has been reached,\c false  if not.
     */
    bool IsEof();
    
    /*!
     * @brief  Returns the number of remaining characters in the input string.
     * 
     * @return <b>[>=0]</b>  The number of remaining characters.
     */
    String GetRemaining();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Returns wether the given character code represents a whitespace or not.
     * 
     * @param c The character code.
     * 
     * @return \c true  if \e c  is a whitespace,\c false  if it is not.
     */
    static bool IsWhitespace(int32 c);
    
    /*!
     * @brief  Decrements the parse position.
     * 
     * @return <b>[not-null]</b>  this
     */
    Ptr<StringParser> Back();
    
    /*!
     * @brief  Begins to parse the given input text.
     * 
     * @param text <b>[not-null]</b>  The input text.
     * 
     * @return <b>[not-null]</b>  this
     */
    Ptr<StringParser> Begin(String text);
    
    /*!
     * @brief  Consume the next \e n  input characters.
     * 
     * @param n <b>[>=0]</b>  The number of input characters to consume.
     * 
     * @return <b>[not-null]</b>  this
     */
    Ptr<StringParser> Consume(int32 n);
    
    /*!
     * @brief  Does the given character match the input that follows?
     * 
     * The current parse position is not modified by this method.
     * 
     * @param c The character.
     * 
     * @return \c true  if the following input matches,\c false  if not.
     */
    bool Follows(int32 c);
    
    /*!
     * @brief  Does the given string match the input that follows?
     * 
     * The current parse position is not modified by this method.
     * 
     * @param s <b>[not-null]</b>  The string.
     * 
     * @return \c true  if the following input matches,\c false  if not.
     */
    bool Follows(String s);
    
    /*!
     * @brief  Peeks at the following input character.
     * 
     * @param idx <b>[>=0]</b>  Index of character to peek,relative to current parse position.
     * 
     * @return The character or \c -1  if the end of the input data has been reached.
     */
    int32 LookAhead(int32 idx);
    
    /*!
     * @brief  Reads the next character from the current line and increments the parse position.
     * 
     * @return The next character or \c -1  if the end of the input data has been reached.
     */
    int32 Next();
    
    /*!
     * @brief  Parses a floating point number.
     * 
     * <pre>
     *     float := '-'? digit+ ('.' digit+ ( ('e' | 'E') digit+ )? )?
     *     digit := '0'..'9'
     * </pre>
     * 
     * @return The number value.
     */
    float64 ParseFloat();
    
    /*!
     * @brief  Parses an integer number.
     * 
     * <pre>
     *     integer := '-'? digit+
     *     digit   := '0'..'9'
     * </pre>
     * 
     * @return The number value.
     */
    int64 ParseInteger();
    
    /*!
     * @brief  Skips all coming non whitespaces.
     * 
     * @return <b>[not-null]</b>  this
     */
    Ptr<StringParser> SkipNonWhitespace();
    
    /*!
     * @brief  Skips all coming whitespaces.
     * 
     * @return <b>[not-null]</b>  this
     */
    Ptr<StringParser> SkipWhitespace();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The line that is currently being parsed.
     */
    String text;
    
    /*!
     * @brief  Length of the input,in characters.
     */
    int32 textLength;
    
    /*!
     * @brief  Current parse offset into #text.
     */
    int32 textOffset;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Asserts that the current text offset does not point at the first character.
     */
    void AssertNotAtStart();
    
    /*!
     * @brief  Parses the fraction of a floating point number.
     * 
     * @return The fraction value.
     */
    float64 ParseFraction();
    
    /*!
     * @brief  Parses the optional exponential scale part of a floating-point number.
     * 
     * @return The parsed exponential scale or \c 1 .
     */
    float64 ParseScale();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
  public:
    
    StringParser();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<StringParser> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x7BA75BF9;
    
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
