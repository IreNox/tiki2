////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_KERNEL_COMPONENTIDSKERNEL_H
#define CLODDY_KERNEL_COMPONENTIDSKERNEL_H

#include "CodeX/System.h"

// Declare class ::Cloddy::Kernel::ComponentIdsKernel.

namespace Cloddy { namespace Kernel
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  This class defines component ID constants for the components that exist in the 
   *         CloddyKernel.
   * 
   * For each component used in the CloddyKernel,a component ID is declared as a static constant in 
   * this class.A component ID is a unique 64-bit integer value.
   * 
   * Component ID constants that start with \c Req_  indicate mandatory components which must 
   * always be specified when creating a CLOD mesh.Constants starting with \c Opt_  are only needed 
   * under certain circumstances;see the respective source documentation for details.
   * 
   * The following list contains some unused component IDs which can be used for additional 
   * components defined by the application:
   * <pre>
   *       0x2E11C5F1C28BA4C0
   *       0x394EEF4B0E8C0975
   *       0x395A9E6B0650D2CE
   *       0x3DE79046B7D844FA
   *       0x45C2735E4482BBB9
   *       0x4F06EA1000765F02
   *       0x51AA3C02BBE2DB70
   *       0x53307A50C58E42CB
   *       0x543EB75B5891D65A
   *       0x5BD226BF093D0AEE
   *       0x5D5680705A0D7152
   *       0x619F4A709601933C
   *       0x6721EEE07C08354D
   *       0x68965B0D0E4BC570
   *       0x6A53F2C00A9C7E61
   *       0x70254BA52829F8E6
   *       0x728A90307FED8931       
   *       0x78404E1A7F790585
   * </pre>
   * 
   * @see IProvider
   */
  class ComponentIdsKernel
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Constants
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  An IVertexFactory object.
     * 
     * This component must be specified for all CLOD meshes.
     */
    static const int64 Req_VertexFactory = (int64) 0x1799E8BAF8703FE5ULL;
    
    /*!
     * @brief  An IVisibilityCriterion object.
     * 
     * This component must be specified for all CLOD meshes.
     */
    static const int64 Req_VisibilityCriterion = (int64) 0x254D8AB4C1607409ULL;
  };
  
} } 

#endif
