////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_SYSTEM_CHARACTERUTIL_H
#define CLODDY_CORE_SYSTEM_CHARACTERUTIL_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/CharacterCategory.h"

// Declare class ::Cloddy::Core::System::CharacterUtil.

namespace Cloddy { namespace Core { namespace System
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Helper class for dealing with unicode characters.
   */
  class CharacterUtil
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Creates a lookup table for mapping character values in the range <c>[0..65535]</c> 
     *         to their corresponding character category.
     * 
     * @return <b>[not-null]</b>  The category lookup table.
     */
    static Array<CharacterCategory> CreateCategoryLookupTable();
    
    /*!
     * @brief  Creates a lookup table for mapping character values in the range <c>[0..65535]</c> 
     *         to their corresponding character category.
     * 
     * @param from Start of character interval,inclusive.
     * @param to <b>[>=from]</b>  End of character interval,inclusive.
     * 
     * @return <b>[not-null]</b>  The category lookup table.
     */
    static Array<CharacterCategory> CreateCategoryLookupTable(wchar_t from, wchar_t to);
    
    /*!
     * @brief  Returns the unicode category of the given character.
     * 
     * @param c The character value.
     * 
     * @return The unicode category.
     */
    static CharacterCategory GetCategory(wchar_t c);
    
    /*!
     * @brief  Checks if the given character belongs to any of the given categories.
     * 
     * @param c The character value.
     * @param categories The character categories.
     * 
     * @return \c true  if \e c  has at least one category given by \e categories ,\c false  if not.
     */
    static bool IsCategory(wchar_t c, CharacterCategory categories);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Unicode character category table (indices).
     */
    static const Array<int16> CategoryIndices;
    
    /*!
     * @brief  Unicode character category table (values).
     */
    static const Array<int32> CategoryValues;
  };
  
} } } 

#endif
