////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_KERNEL_TRIANGLESTITCHING_H
#define CLODDY_KERNEL_TRIANGLESTITCHING_H

#include "CodeX/System.h"

// Declare enumeration ::Cloddy::Kernel::TriangleStitching.

namespace Cloddy { namespace Kernel
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Enumeration of triangle stitching modes to use for CLOD mesh triangulation.
   * 
   * The following modes are available:
   *   - #TriangleStitching_Chunked:The callback ITriangulationCallback::TriangleStripChunk 
   *   delivers standalone triangle strips;each of them must be rendered with an own render command.
   *   - #TriangleStitching_Concatenate:The callback ITriangulationCallback::TriangleStripChunk 
   *   delivers parts of a single continuous triangle strip which can be rendered using a single 
   *   render command (after the application has concatenated them in an own buffer).
   * 
   * @see CloddyKernel::BeginTriangulation
   * @see Mesh_Terrain::Triangulate
   * @see Traversal_Terrain::Triangulate
   */
  enum TriangleStitching
  {
    /*!
     * @brief  The triangle strips that are generated during CLOD mesh triangulation are stitched 
     *         together to form separate chunks of a given maximum length (
     *         see CloddyKernelOptions::GetTriangleStripChunkSize).
     * 
     * Each chunk that is output via ITriangulationCallback::TriangleStripChunk is a regular 
     * triangle strip primitive which must be rendered by a separate render command..
     */
    TriangleStitching_Chunked = 0,
    
    /*!
     * @brief  The triangle strips that are generated during CLOD mesh triangulation are stitched 
     *         together to form a single continuous triangle strip primitive.
     * 
     * Each chunk that is output via ITriangulationCallback::TriangleStripChunk represents a part 
     * of the continuous triangle strip primitive.The consumer must concatenate all chunks and 
     * issue a single render command.for rendering the whole continuous triangle strip primitive.
     */
    TriangleStitching_Concatenate = 2
  };
  
} } 

#endif
