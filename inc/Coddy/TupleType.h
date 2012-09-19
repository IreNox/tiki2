////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_VERTEXDATA_TUPLETYPE_H
#define CLODDY_API_VERTEXDATA_TUPLETYPE_H

#include "CodeX/System.h"

// Declare enumeration ::Cloddy::API::VertexData::TupleType.

namespace Cloddy { namespace API { namespace VertexData
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Enumeration of tuple element types.
   */
  enum TupleType
  {
    /*!
     * @brief  A tuple of 8-bit integer values.
     * 
     * An IVertexData instance which IVertexData::GetTupleType is #TupleType_Byte can always be 
     * cast to one of the following classes (depending on the tuple size):
     *   - Byte1
     *   - Byte2
     *   - Byte3
     *   - Byte4
     */
    TupleType_Byte = 0,
    
    /*!
     * @brief  A tuple of 16-bit integer values.
     * 
     * An IVertexData instance which IVertexData::GetTupleType is #TupleType_Short can always be 
     * cast to one of the following classes (depending on the tuple size):
     *   - Short1
     *   - Short2
     *   - Short3
     *   - Short4
     */
    TupleType_Short = 1,
    
    /*!
     * @brief  A tuple of 32-bit integer values.
     * 
     * An IVertexData instance which IVertexData::GetTupleType is #TupleType_Int can always be cast 
     * to one of the following classes (depending on the tuple size):
     *   - Int1
     *   - Int2
     *   - Int3
     *   - Int4
     */
    TupleType_Int = 2,
    
    /*!
     * @brief  A tuple of 64-bit integer values.
     * 
     * An IVertexData instance which IVertexData::GetTupleType is #TupleType_Long can always be 
     * cast to one of the following classes (depending on the tuple size):
     *   - Long1
     *   - Long2
     *   - Long3
     *   - Long4
     */
    TupleType_Long = 3,
    
    /*!
     * @brief  A tuple of 32-bit floating point values.
     * 
     * An IVertexData instance which IVertexData::GetTupleType is #TupleType_Float can always be 
     * cast to one of the following classes (depending on the tuple size):
     *   - Float1
     *   - Float2
     *   - Float3
     *   - Float4
     */
    TupleType_Float = 4,
    
    /*!
     * @brief  A tuple of 64-bit floating point values.
     * 
     * An IVertexData instance which IVertexData::GetTupleType is #TupleType_Double can always be 
     * cast to one of the following classes (depending on the tuple size):
     *   - Double1
     *   - Double2
     *   - Double3
     *   - Double4
     */
    TupleType_Double = 5,
    
    /*!
     * @brief  The tuple type can be any of the other defined types.
     * 
     * The <c>Get*</c> and <c>Set*</c> methods can be used to access the values of an IVertexData 
     * container without downcasting it to a specific type.
     * 
     * When creating a vertex data container for a sematic that has the #TupleType_Any tuple type,
     * the container will have 32-bit or 64-bit floating point precision (
     * see Semantic::GetUseDoubleForAny.
     */
    TupleType_Any = 6
  };
  
} } } 

#endif
