////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_TOOLS_SWAPBLOCK_H
#define CLODDY_API_TOOLS_SWAPBLOCK_H

#include "CodeX/System.h"

// Include referenced structures.

#include "Cloddy/Vec2I.h"
#include "Cloddy/Vec3I.h"

// Declare class ::Cloddy::API::Tools::SwapBlock.

namespace Cloddy { namespace API { namespace Tools
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced structures.
  
  using Cloddy::Core::Math::Vectors::Vec2I;
  using Cloddy::Core::Math::Vectors::Vec3I;
  
  struct SwapBlock : StructType
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Cubemap face coordinates of the first block.
     */
    Vec3I First;
    
    /*!
     * @brief  Cubemap face coordinates of the second block.
     */
    Vec3I Second;
    
    /*!
     * @brief  Size of the block,in dataset samples.
     */
    Vec2I Size;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of SwapBlock.
     * 
     * @param size Size of the block,in dataset samples.
     * @param first Cubemap face coordinates of the first block.
     * @param second Cubemap face coordinates of the second block.
     */
    SwapBlock(const Vec2I& size, const Vec3I& first, const Vec3I& second);
    
    SwapBlock();
    
    // ---------------------------------------------------------------------------------------------
    //  Copy constructor and copy assignment operator
    // ---------------------------------------------------------------------------------------------
  public:
    
    SwapBlock(const SwapBlock& other);
    
    SwapBlock& operator=(const SwapBlock& other);
  };
  
} } } 

#endif
