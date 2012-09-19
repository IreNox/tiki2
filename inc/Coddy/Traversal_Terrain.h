////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_KERNEL_TRAVERSAL_TERRAIN_H
#define CLODDY_KERNEL_TRAVERSAL_TERRAIN_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/Traversal.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Kernel { class IMeshVisitor; } }

// Forward declare referenced classes.

namespace Cloddy { namespace Kernel { class Mesh_Terrain; } }

// Declare class ::Cloddy::Kernel::Traversal_Terrain.

namespace Cloddy { namespace Kernel
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  This class implements the traversal algorithm for traversing a CLOD mesh in a quadtree 
   *         like fashion.
   * 
   * In respect to heightmap coordinate space,CLOD mesh sectors are twisted.The following figure 
   * illustrate the different twist flavours.There are four distinct twists,each representing a 
   * rotation in counter-clockwise direction about 0,90,180 or 270 degrees.CLOD mesh sector twists 
   * are usually relevant when computing vertex tangent vectors.
   * <pre>
   *    Fig. 1a: Untwisted sector                            Fig. 1b: Untwisted sector
   *    +-------------------------------------------------+  +----------------------------------+
   *    |                                                 |  | A               R                |
   *    |          A            V  := Center vertex       |  |  o------+------o                 |
   *    |          O            L  := Left parent vertex  |  |  |      |      |         Y-      |
   *    |         / \\  S1       R  := Right parent vertex |  |  |  S1  |  S2  |         |       |
   *    |        /   \\/         G  := Grand parent vertex |  |  |      |      |         |       |
   *    |   S0  /  .  \\         A  := Ancestor vertex     |  |  +------+------+   X- ---O--- X+ |
   *    |     \\/\\     /\\        S0 := First subsector     |  |  |      |      |         |       |
   *    |     /  \\ V /  \\       S1 := Second subsector    |  |  |  S0  |  S3  |         |       |
   *    |    /    \\ /    \\      S2 := Third subsector     |  |  |      |      |         Y+      |
   *    | L O  .   O   .  O R   S3 := Fourth subsector    |  |  o------+------o                 |
   *    |    \\    / \\    /                                |  | L               G                |
   *    |     \\  /   \\  /              X-    Y-           |  |                                  |
   *    |      \\/  .  \\/\\               \\   /             |  | A := (0,0)                       |
   *    |       \\     /  S2              \\ /              |  | R := (n,0)                       |
   *    |       /\\   /                    O               |  | L := (0,n)                       |
   *    |     S3  \\ /                    / \\              |  | G := (n,n)                       |
   *    |          O                    /   \\             |  |                                  |
   *    |          G                   Y+    X+           |  | n := Maximum heightmap           |
   *    |                                                 |  |      coordinate                  |
   *    +-------------------------------------------------+  +----------------------------------+
   *    Fig. 2: Sector twists
   *    +---------------------+---------------------+---------------------+---------------------+
   *    |    Twist == 0       |    Twist == 1       |    Twist == 2       |    Twist == 3       |
   *    |                     |                     |                     |                     |
   *    |          A          |          R          |          G          |          L          |
   *    |          O          |          O          |          O          |          O          |
   *    |         / \\  S1     |         / \\  S2     |         / \\  S3     |         / \\  S0     |
   *    |        /   \\/       |        /   \\/       |        /   \\/       |        /   \\/       |
   *    |   S0  /  .  \\       |   S1  /  .  \\       |   S2  /  .  \\       |   S1  /  .  \\       |
   *    |     \\/\\     /\\      |     \\/\\     /\\      |     \\/\\     /\\      |     \\/\\     /\\      |
   *    |     /  \\ V /  \\     |     /  \\ V /  \\     |     /  \\ V /  \\     |     /  \\ V /  \\     |
   *    |    /    \\ /    \\    |    /    \\ /    \\    |    /    \\ /    \\    |    /    \\ /    \\    |
   *    | L O  .   O   .  O R | A O  .   O   .  O G | R O  .   O   .  O L | G O  .   O   .  O A |
   *    |    \\    / \\    /    |    \\    / \\    /    |    \\    / \\    /    |    \\    / \\    /    |
   *    |     \\  /   \\  /     |     \\  /   \\  /     |     \\  /   \\  /     |     \\  /   \\  /     |
   *    |      \\/  .  \\/\\     |      \\/  .  \\/\\     |      \\/  .  \\/\\     |      \\/  .  \\/\\     |
   *    |       \\     /  S2   |       \\     /  S3   |       \\     /  S0   |       \\     /  S3   |
   *    |       /\\   /        |       /\\   /        |       /\\   /        |       /\\   /        |
   *    |     S3  \\ /         |     S0  \\ /         |     S1  \\ /         |     S2  \\ /         |
   *    |          O          |          O          |          O          |          O          |
   *    |          G          |          L          |          A          |          R          |
   *    +---------------------+---------------------+---------------------+---------------------+
   * </pre>
   */
  class Traversal_Terrain : public Traversal
  {
    // Declare friend classes.
    
    friend class Mesh_Terrain;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual int32 GetVertices(Array<int32> vertices);
    
    virtual void Triangulate();
    
    virtual void VisitSubsectors(IMeshVisitor* meshVisitor, int32 userData);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Ancestor of Traversal::Vertex.
     */
    int32 a;
    
    /*!
     * @brief  The vertex child references.
     * 
     * @see CloddyKernel::linkChild0123
     */
    Array<int32> c;
    
    /*!
     * @brief  Left parent of Traversal::Vertex.
     */
    int32 l;
    
    /*!
     * @brief  The CLOD mesh this traversal object belongs to.
     */
    Ptr<Mesh_Terrain> mesh;
    
    /*!
     * @brief  Right parent of Traversal::Vertex.
     */
    int32 r;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of Traversal_Terrain.
     * 
     * @param mesh The CLOD mesh the traversal object belongs to.
     */
    Traversal_Terrain(Mesh_Terrain* mesh);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Visits a mesh sector.
     * 
     * @param meshVisitor The IMeshVisitor to use.
     * @param v Index of center vertex of sector to visit.
     * @param l Index of left parent of \e v .
     * @param r Index of right parent of \e v .
     * @param g Index of grand parent of \e v .
     * @param a Index of ancestor of \e v .
     * @param userData Optional user data to pass down during traversal.
     */
    void VisitSector(IMeshVisitor* meshVisitor, int32 v, int32 l, int32 r, int32 g, int32 a, int32 userData);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<Traversal_Terrain> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x433156A5;
    
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
      if ((ptr = Traversal::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } 

#endif
