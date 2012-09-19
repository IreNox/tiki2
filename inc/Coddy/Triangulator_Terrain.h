////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_KERNEL_TRIANGULATOR_TERRAIN_H
#define CLODDY_KERNEL_TRIANGULATOR_TERRAIN_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/Orientation.h"
#include "Cloddy/TriangleStitching.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Kernel { class ITriangulationCallback; } }

// Forward declare referenced classes.

namespace Cloddy { namespace Kernel { class CloddyKernel; } }
namespace Cloddy { namespace Kernel { class Mesh_Terrain; } }
namespace Cloddy { namespace Kernel { class Traversal_Terrain; } }

// Declare class ::Cloddy::Kernel::Triangulator_Terrain.

namespace Cloddy { namespace Kernel
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Helper class for performing CLOD mesh triangulation.
   */
  class Triangulator_Terrain : public virtual Object
  {
    // Declare friend classes.
    
    friend class CloddyKernel;
    friend class Mesh_Terrain;
    friend class Traversal_Terrain;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Holds all four child vertex indices per vertex.
     */
    Array<int32> c;
    
    /*!
     * @brief  The currently locked region of the current indexBuffer is mapped to this array.
     */
    Array<int32> indexBuffer;
    
    /*!
     * @brief  Fill the last chunk of a triangulation with the most recent vertex?
     */
    bool indexBufferFill;
    
    /*!
     * @brief  Current write index into #indexBuffer.
     */
    int32 indexBufferIdx;
    
    /*!
     * @brief  Index of the last vertex of the most recently generated triangle strip.
     * 
     * @see #Leaf
     * @see #Sector
     */
    int32 indexBufferLast;
    
    /*!
     * @brief  Parity of the last triangle of the most recently generated triangle strip.
     */
    bool indexBufferLastParity;
    
    /*!
     * @brief  The maximum vertex index value in the current triangle strip chunk.
     */
    int32 indexBufferMax;
    
    /*!
     * @brief  The minimum vertex index value in the current triangle strip chunk.
     */
    int32 indexBufferMin;
    
    /*!
     * @brief  Maximum size of generated triangle strip chunks.
     */
    int32 indexBufferSize;
    
    /*!
     * @brief  Triangle orientation of current triangulation process.
     */
    Orientation orientation;
    
    /*!
     * @brief  The triangle stitching method of the current triangulation process.
     */
    TriangleStitching triangleStitching;
    
    /*!
     * @brief  The callback method used to emit the triangle strip.
     */
    Ptr<ITriangulationCallback> triangulationCallback;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of Triangulator_Terrain.
     * 
     * @param capacity Capacity of the kernel,in vertices.
     * @param triStripChunkSize Maximum size of a triangle strip chunk,in indices.
     * @param c The vertex child indices (see CloddyKernel::linkChild0123).
     */
    Triangulator_Terrain(int32 capacity, int32 triStripChunkSize, Array<int32> c);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Appends the given vertex to the current triangle strip chunk buffer.
     * 
     * @param v The vertex index to push.
     */
    void Append(int32 v);
    
    /*!
     * @brief  Appends the given vertices to the current triangle strip chunk buffer.
     * 
     * @param a First vertex index to push.
     * @param b Second vertex index to push.
     */
    void Append_ab(int32 a, int32 b);
    
    /*!
     * @brief  Appends the given vertices to the current triangle strip chunk buffer.
     * 
     * @param a First vertex index to push.
     * @param b Second vertex index to push.
     */
    void Append_aba(int32 a, int32 b);
    
    /*!
     * @brief  Appends the given vertices to the current triangle strip chunk buffer.
     * 
     * @param a First vertex index to push.
     * @param b Second vertex index to push.
     * @param c Third vertex index to push.
     */
    void Append_abac(int32 a, int32 b, int32 c);
    
    /*!
     * @brief  Appends the given vertices to the current triangle strip chunk buffer.
     * 
     * @param a First vertex index to push.
     * @param b Second vertex index to push.
     * @param c Third vertex index to push.
     */
    void Append_abc(int32 a, int32 b, int32 c);
    
    /*!
     * @brief  Traverses the left-anchor triangle of the given vertex diamond from left to right,
     *         entering at the left base edge and leaving at the right side edge.
     * 
     * @param v Index of the vertex to traverse.
     * @param r Right parent of \e v .
     * @param a Ancestor of \e v .
     */
    void BS_LL(int32 v, int32 r, int32 a);
    
    /*!
     * @brief  Traverses the left-anchor triangle of the given vertex diamond from right to left,
     *         entering at the left base edge and leaving at the right side edge.
     * 
     * @param v Index of the vertex to traverse.
     * @param l Left parent of \e v .
     * @param g Grand parent of \e v .
     */
    void BS_LR(int32 v, int32 l, int32 g);
    
    /*!
     * @brief  Traverses the right-anchor triangle of the given vertex diamond from left to right,
     *         entering at the left base edge and leaving at the right side edge.
     * 
     * @param v Index of the vertex to traverse.
     * @param r Right parent of \e v .
     * @param g Grand parent of \e v .
     */
    void BS_RL(int32 v, int32 r, int32 g);
    
    /*!
     * @brief  Traverses the right-anchor triangle of the given vertex diamond from right to left,
     *         entering at the left base edge and leaving at the right side edge.
     * 
     * @param v Index of the vertex to traverse.
     * @param r Right parent of \e v .
     * @param a Ancestor of \e v .
     */
    void BS_RR(int32 v, int32 r, int32 a);
    
    /*!
     * @brief  Begins a triangulation process.
     * 
     * @param callback The triangulation callback object.
     * @param orientation The triangle orientation.
     * @param stitching The triangle strip stitching mode.
     * @param fill Fill the last triangle strip chunk?
     * @param userData Optional user data to pass to callback.
     */
    void Begin(ITriangulationCallback* callback, Orientation orientation, TriangleStitching stitching, bool fill, void* userData);
    
    /*!
     * @brief  Starts a new triangle strip.
     * 
     * The new triangle strip is stitched together with the last one (if there is one).
     * 
     * @param v Index of the first vertex of the new triangle strip (will be emitted).
     */
    void BeginStrip(int32 v);
    
    /*!
     * @brief  Iterates over the vertices of the first half of the left-anchor non-terminal 
     *         triangle of the given vertex diamond,heading towards the edge opposite to the 
     *         incoming edge.
     * 
     * @param v Index of the vertex.
     */
    void C0_LR(int32 v);
    
    /*!
     * @brief  Iterates over the vertices of the first half of the left-anchor non-terminal 
     *         triangle of the given vertex diamond,heading towards the incoming edge.
     * 
     * @param v Index of the vertex.
     * @param l Left parent of \e v .
     */
    void C0_LR_INV(int32 v, int32 l);
    
    /*!
     * @brief  Iterates over the vertices of the first half of the right-anchor non-terminal 
     *         triangle of the given vertex diamond,heading towards the edge opposite to the 
     *         incoming edge.
     * 
     * @param v Index of the vertex.
     */
    void C0_RL(int32 v);
    
    /*!
     * @brief  Iterates over the vertices of the first half of the right-anchor non-terminal 
     *         triangle of the given vertex diamond,heading towards the incoming edge.
     * 
     * @param v Index of the vertex.
     * @param r Right parent of \e v .
     */
    void C0_RL_INV(int32 v, int32 r);
    
    /*!
     * @brief  Iterates over the vertices of the second half of the left-anchor non-terminal 
     *         triangle of the given vertex diamond,heading towards the edge opposite to the 
     *         outgoing edge.
     * 
     * @param v Index of the vertex.
     */
    void C1_LR(int32 v);
    
    /*!
     * @brief  Iterates over the vertices of the second half of the left-anchor non-terminal 
     *         triangle of the given vertex diamond,heading towards the outgoing edge.
     * 
     * @param v Index of the vertex.
     * @param l Left parent of \e v .
     */
    void C1_LR_INV(int32 v, int32 l);
    
    /*!
     * @brief  Iterates over the vertices of the second half of the right-anchor non-terminal 
     *         triangle of the given vertex diamond,heading towards the edge opposite to the 
     *         outgoing edge.
     * 
     * @param v Index of the vertex.
     */
    void C1_RL(int32 v);
    
    /*!
     * @brief  Iterates over the vertices of the second half of the right-anchor non-terminal 
     *         triangle of the given vertex diamond,heading towards the outgoing edge.
     * 
     * @param v Index of the vertex.
     * @param r Right parent of \e v .
     */
    void C1_RL_INV(int32 v, int32 r);
    
    /*!
     * @brief  Ends the current triangulation process.
     */
    void End();
    
    /*!
     * @brief  Ends the current triangle strip.
     */
    void EndStrip();
    
    /*!
     * @brief  This method flushes the triangle strip chunk buffer.
     */
    void Flush();
    
    /*!
     * @brief  Triangulates the given leaf sector.
     * 
     * @param l Left parent vertex of leaf sector,premultiplied by 4.
     * @param r Right parent vertex of leaf sector,premultiplied by 4.
     * @param g Grand parent vertex of leaf sector,premultiplied by 4.
     * @param a Ancestor vertex of leaf sector,premultiplied by 4.
     */
    void Leaf(int32 l, int32 r, int32 g, int32 a);
    
    /*!
     * @brief  Traverses the left-anchor triangle of the given vertex diamond from left to right,
     *         entering at the left side edge and leaving at the right base edge.
     * 
     * @param v Index of the vertex to traverse.
     * @param l Left parent of \e v .
     * @param a Ancestor of \e v .
     */
    void SB_LL(int32 v, int32 l, int32 a);
    
    /*!
     * @brief  Traverses the left-anchor triangle of the given vertex diamond from right to left,
     *         entering at the left side edge and leaving at the right base edge.
     * 
     * @param v Index of the vertex to traverse.
     * @param l Left parent of \e v .
     * @param g Grand parent of \e v .
     */
    void SB_LR(int32 v, int32 l, int32 g);
    
    /*!
     * @brief  Traverses the right-anchor triangle of the given vertex diamond from left to right,
     *         entering at the left side edge and leaving at the right base edge.
     * 
     * @param v Index of the vertex to traverse.
     * @param r Right parent of \e v .
     * @param g Grand parent of \e v .
     */
    void SB_RL(int32 v, int32 r, int32 g);
    
    /*!
     * @brief  Traverses the right-anchor triangle of the given vertex diamond from right to left,
     *         entering at the left side edge and leaving at the right base edge.
     * 
     * @param v Index of the vertex to traverse.
     * @param r Right parent of \e v .
     * @param a Ancestor of \e v .
     */
    void SB_RR(int32 v, int32 r, int32 a);
    
    /*!
     * @brief  Traverses the left-anchor triangle of the given vertex diamond from left to right,
     *         entering at the left side edge and leaving at the right side edge.
     * 
     * @param v Index of the vertex to traverse.
     * @param l Left parent of \e v .
     * @param a Ancestor of \e v .
     */
    void SS_LL(int32 v, int32 l, int32 a);
    
    /*!
     * @brief  Traverses the left-anchor triangle of the given vertex diamond from right to left,
     *         entering at the left side edge and leaving at the right side edge.
     * 
     * @param v Index of the vertex to traverse.
     * @param l Left parent of \e v .
     * @param g Grand parent of \e v .
     */
    void SS_LR(int32 v, int32 l, int32 g);
    
    /*!
     * @brief  Traverses the right-anchor triangle of the given vertex diamond from left to right,
     *         entering at the left side edge and leaving at the right side edge.
     * 
     * @param v Index of the vertex to traverse.
     * @param r Right parent of \e v .
     * @param g Grand parent of \e v .
     */
    void SS_RL(int32 v, int32 r, int32 g);
    
    /*!
     * @brief  Traverses the right-anchor triangle of the given vertex diamond from right to left,
     *         entering at the left side edge and leaving at the right side edge.
     * 
     * @param v Index of the vertex to traverse.
     * @param r Right parent of \e v .
     * @param a Ancestor of \e v .
     */
    void SS_RR(int32 v, int32 r, int32 a);
    
    /*!
     * @brief  Generates a triangle strip that covers the given mesh sector.The triangles of the 
     *         generated strip are oriented in counter-clockwise direction.
     * 
     * @param vm Center vertex.
     * @param lm Left parent of \e vm .
     * @param rm Right parent of \e vm .
     * @param gm Grand parent of \e vm .
     * @param am Ancestor of \e vm .
     */
    void Sector(int32 vm, int32 lm, int32 rm, int32 gm, int32 am);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<Triangulator_Terrain> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xCF8A46DF;
    
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
  
} } 

#endif
