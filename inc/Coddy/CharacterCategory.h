////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_SYSTEM_CHARACTERCATEGORY_H
#define CLODDY_CORE_SYSTEM_CHARACTERCATEGORY_H

#include "CodeX/System.h"

// Declare enumeration ::Cloddy::Core::System::CharacterCategory.

namespace Cloddy { namespace Core { namespace System
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Enumeration of unicode categories.
   */
  enum CharacterCategory
  {
    /*!
     * @brief  No category.
     */
    CharacterCategory_None = 0,
    
    /*!
     * @brief  Unicode character category:Letter (<c>L*</c>).
     */
    CharacterCategory_Letter = 31,
    
    /*!
     * @brief  Unicode character category:Letter,uppercase (\c Lu ).
     */
    CharacterCategory_LetterUppercase = 1,
    
    /*!
     * @brief  Unicode character category:Letter,lowercase (\c Ll ).
     */
    CharacterCategory_LetterLowercase = 2,
    
    /*!
     * @brief  Unicode character category:Letter,titlecase (\c Lt ).
     */
    CharacterCategory_LetterTitlecase = 4,
    
    /*!
     * @brief  Unicode character category:Letter,modifier (\c Lm ).
     */
    CharacterCategory_LetterModifier = 8,
    
    /*!
     * @brief  Unicode character category:Letter,other (\c Lo ).
     */
    CharacterCategory_LetterOther = 16,
    
    /*!
     * @brief  Unicode character category:Mark (<c>M*</c>).
     */
    CharacterCategory_Mark = 224,
    
    /*!
     * @brief  Unicode character category:Mark,non-spacing (\c Mn ).
     */
    CharacterCategory_MarkNonSpacing = 32,
    
    /*!
     * @brief  Unicode character category:Mark,space combining (\c Mc ).
     */
    CharacterCategory_MarkSpacingCombining = 64,
    
    /*!
     * @brief  Unicode character category:Mark,enclosing (\c Me ).
     */
    CharacterCategory_MarkEnclosing = 128,
    
    /*!
     * @brief  Unicode character category:Number (<c>N*</c>).
     */
    CharacterCategory_Number = 1792,
    
    /*!
     * @brief  Unicode character category:Number,decimal digit (\c Nd ).
     */
    CharacterCategory_NumberDecimalDigit = 256,
    
    /*!
     * @brief  Unicode character category:Number,letter (\c Nl ).
     */
    CharacterCategory_NumberLetter = 512,
    
    /*!
     * @brief  Unicode character category:Number,other (\c No ).
     */
    CharacterCategory_NumberOther = 1024,
    
    /*!
     * @brief  Unicode character category:Separator (<c>Z*</c>).
     */
    CharacterCategory_Separator = 14336,
    
    /*!
     * @brief  Unicode character category:Separator,space (\c Zs ).
     */
    CharacterCategory_SeparatorSpace = 2048,
    
    /*!
     * @brief  Unicode character category:Separator,line (\c Zl ).
     */
    CharacterCategory_SeparatorLine = 4096,
    
    /*!
     * @brief  Unicode character category:Separator,paragraph (\c Zp ).
     */
    CharacterCategory_SeparatorParagraph = 8192,
    
    /*!
     * @brief  Unicode character category:Other (<c>C*</c>).
     */
    CharacterCategory_Other = 507904,
    
    /*!
     * @brief  Unicode character category:Other,control (\c Cc ).
     */
    CharacterCategory_OtherControl = 16384,
    
    /*!
     * @brief  Unicode character category:Other,format (\c Cf ).
     */
    CharacterCategory_OtherFormat = 32768,
    
    /*!
     * @brief  Unicode character category:Other,surrogate (\c Cs ).
     */
    CharacterCategory_OtherSurrogate = 65536,
    
    /*!
     * @brief  Unicode character category:Other,private use (\c Co ).
     */
    CharacterCategory_OtherPrivateUse = 131072,
    
    /*!
     * @brief  Unicode character category:Other,not assigned (\c Cn ).
     */
    CharacterCategory_OtherNotAssigned = 262144,
    
    /*!
     * @brief  Unicode character category:Punctuation (<c>P*</c>).
     */
    CharacterCategory_Puntuation = 66584576,
    
    /*!
     * @brief  Unicode character category:Punctuation,connector (\c Pc ).
     */
    CharacterCategory_PunctuationConnector = 524288,
    
    /*!
     * @brief  Unicode character category:Punctuation,dash (\c Pd ).
     */
    CharacterCategory_PunctuationDash = 1048576,
    
    /*!
     * @brief  Unicode character category:Punctuation,open (\c Ps ).
     */
    CharacterCategory_PunctuationOpen = 2097152,
    
    /*!
     * @brief  Unicode character category:Punctuation,close (\c Pe ).
     */
    CharacterCategory_PunctuationClose = 4194304,
    
    /*!
     * @brief  Unicode character category:Punctuation,initial quote (\c Pi ).
     */
    CharacterCategory_PunctuationInitialQuote = 8388608,
    
    /*!
     * @brief  Unicode character category:Punctuation,final quote (\c Pf ).
     */
    CharacterCategory_PunctuationFinalQuote = 16777216,
    
    /*!
     * @brief  Unicode character category:Punctuation,other (\c Po ).
     */
    CharacterCategory_PunctuationOther = 33554432,
    
    /*!
     * @brief  Unicode character categoriy:Symbol (<c>S*</c>).
     */
    CharacterCategory_Symbol = 1006632960,
    
    /*!
     * @brief  Unicode character category:Symbol,math (\c Sm ).
     */
    CharacterCategory_SymbolMath = 67108864,
    
    /*!
     * @brief  Unicode character category:Symbol,currency (\c Sc ).
     */
    CharacterCategory_SymbolCurrency = 134217728,
    
    /*!
     * @brief  Unicode character category:Symbol,modifier (\c Sk ).
     */
    CharacterCategory_SymbolModifier = 268435456,
    
    /*!
     * @brief  Unicode character category:Symbol,other (\c So ).
     */
    CharacterCategory_SymbolOther = 536870912,
    
    /*!
     * @brief  Unicode character categories:#CharacterCategory_Letter 
     *         and #CharacterCategory_NumberDecimalDigit.
     */
    CharacterCategory_LetterOrDigit = 287,
    
    /*!
     * @brief  Unicode character categories:#CharacterCategory_Separator 
     *         and #CharacterCategory_OtherControl.
     */
    CharacterCategory_Whitespace = 30720
  };
  
  static inline CharacterCategory operator|=(CharacterCategory a, CharacterCategory b)
  {
    return (CharacterCategory) ((int32) a | (int32) b);
  }
  
  static inline CharacterCategory operator&=(CharacterCategory a, CharacterCategory b)
  {
    return (CharacterCategory) ((int32) a & (int32) b);
  }
  
  static inline CharacterCategory operator^=(CharacterCategory a, CharacterCategory b)
  {
    return (CharacterCategory) ((int32) a ^ (int32) b);
  }
} } } 

#endif
