////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_UTIL_CUBEMAP_H
#define CLODDY_API_UTIL_CUBEMAP_H

#include "CodeX/System.h"

// Include referenced structures.

#include "Cloddy/Box2I.h"
#include "Cloddy/Box3I.h"
#include "Cloddy/Vec2D.h"
#include "Cloddy/Vec2I.h"
#include "Cloddy/Vec3D.h"
#include "Cloddy/Vec3I.h"

// Declare class ::Cloddy::API::Util::Cubemap.

namespace Cloddy { namespace API { namespace Util
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced structures.
  
  using Cloddy::Core::Math::Vectors::Vec2D;
  using Cloddy::Core::Math::Vectors::Vec2I;
  using Cloddy::Core::Math::Vectors::Vec3D;
  using Cloddy::Core::Math::Vectors::Vec3I;
  
  /*!
   * @brief  The Cubemap class imlements the concept of cubemaps as used by the Cloddy SDK.
   * 
   * The following figure shows the relation between cubemap coordinates and cubemap face 
   * coordinates:
   * <pre>
   *       .        Y-  Z+                                  O--------------O
   *       .         | /                                    |              |
   *       .         |/                                     | ^ fx         |
   *       .    X- --+-- X+                                 | |            |
   *       .        /|                                      | |    Y-      |
   *       .       / |                                      | |         fy |
   *       .     Z-  Y+                                     | o----------> |
   *       .                                                |              |
   *       .   O--------------O--------------O--------------O--------------O
   *       .   |              |              |              |              |
   *       .   | o----------> | o----------> | o----------> | o----------> |
   *       .   | |         fx | |         fx | |         fx | |         fx |
   *       .   | |    Z-      | |    X+      | |    Z+      | |    X-      |
   *       .   | |            | |            | |            | |            |
   *       .   | V fy         | V fy         | V fy         | V fy         |
   *       .   |              |              |              |              |
   *       .   O--------------O--------------O--------------O--------------O
   *       .                                                |              |
   *       .                                                | &lt;----------o |
   *       .                                                | fy         | |
   *       .         +---------------------------+          |      Y+    | |
   *       .         | fx := Cubemap face X-axis |          |            | |
   *       .         | fy := Cubemap face Y-axis |          |         fx V |
   *       .         +---------------------------+          |              |
   *       .                                                O--------------O
   * </pre>
   * 
   * Given a cubemap size of <c>s =2 ^n +1</c>,the total number of samples in the cubemap can be 
   * computed as follows:
   * <pre>
   *       cubemap_samples(s) = s ^ 3 - (s - 2) ^ 3  
   * </pre>
   * For example,the above figures show a cubemap of size \c 5 ,so the total number of samples is 
   * <c>5^3 - 3^3 =98</c>.
   * 
   * The effective cubemap regions can be used to visit each sample in a cubemap using blocks of 
   * size <c>2 ^n</c> (which is handy for some algorithms).The number of samples covered by all 
   * effective cubemap regions is:
   * <pre>
   *       cubemap_effective(s) = (s - 1) ^ 2 * 6
   * </pre>
   * The number of samples covered by effective regions is related to the total number of cubemap 
   * samples:
   * <pre>
   *       cubemap_samples(s) = cubemap_effective(s) + 2
   * </pre>
   * So there will always be two cubemap samples that cannot be reached using effective regions.The 
   * cubemap face partitioning has been designed in a way that the minimum and maximum cubemap 
   * corners (ie. <c>(0,0,0)</c> and <c>(s-1,s-1,s-1)</c>)always represent the unreachable samples;
   * these must be processed separately.
   * 
   * This diagram illustrates the partitioning scheme of the cubemap space into faces and effective 
   * regions:
   * <pre>
   *       .       Y-  Z+                          [n,0,n]                  [n,0,0]
   *       .        | /                                    \\       Y-       /
   *       .        |/                                      O--+--+--+--+--O
   *       .   X- --+-- X+                                  |..|41|42|43|44|
   *       .       /|                                       +--+--+--+--+--+
   *       .      / |                                       |..|31|32|33|34|
   *       .    Z-  Y+                                      +--+--+--+--+--+
   *       .                                                |..|21|22|23|24|
   *       .                                                +--+--+--+--+--+
   *       .                                                |..|11|12|13|14|
   *       .   [0,0,0]     [n,0,0]        [n,0,n]   [0,0,n] +--+--+--+--+--+
   *       .   |      Z-      |      X+      |      Z+     \\|..|..|..|..|##|
   *       .   O--+--+--+--+--O--+--+--+--+--O--+--+--+--+--O--+--+--+--+--O-[0,0,0]
   *       .   |##|..|..|..|..|..|..|..|..|..|00|10|20|30|..|00|10|20|30|##|
   *       .   +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
   *       .   |01|11|21|31|..|01|11|21|31|..|01|11|21|31|..|01|11|21|31|..|
   *       .   +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
   *       .   |02|12|22|32|..|02|12|22|32|..|02|12|22|32|..|02|12|22|32|..| X-
   *       .   +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
   *       .   |03|13|23|33|..|03|13|23|33|..|03|13|23|33|..|03|13|23|33|..|
   *       .   +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
   *       .   |04|14|24|34|..|04|14|24|34|##|##|..|..|..|..|..|..|..|..|..|
   *       .   O--+--+--+--+--O--+--+--+--+--O--+--+--+--+--O--+--+--+--+--O-[0,n,0]
   *       .   |              |              |             /|04|03|02|01|..|
   *       .   [0,n,0]     [n,n,0]        [n,n,n]   [0,n,n] +--+--+--+--+--+
   *       .                                                |14|13|12|11|..|
   *       .   +----------------------------------+         +--+--+--+--+--+
   *       .   | n :=                             |         |24|23|22|21|..|
   *       .   |   Maximum heightmap coordinate   |         +--+--+--+--+--+
   *       .   |                                  |         |34|33|32|31|..|
   *       .   | [0,0,0] .. [n.n.n] :=            |         +--+--+--+--+--+
   *       .   |   Heightmap coordinates (X,Y,Z)  |         |##|..|..|..|..|
   *       .   |                                  |         O--+--+--+--+--O
   *       .   | 00 .. 44 :=                      |         /       Y+       \\
   *       .   |   Cubemap face coordinates (X,Y) |  [n,n,n]                  [n,n,0]
   *       .   |   (effective region)             |
   *       .   |                                  |
   *       .   | ## := Minimum/maximum corner     |
   *       .   |                                  |
   *       .   | .. := Sample covered by          | 
   *       .   |       adjacent region            |
   *       .   +----------------------------------+
   * </pre>
   * 
   * The samples of a cubemap are stored per face,where each face is represented by a grid of 
   * <c>s *s</c> samples,so the total number of samples stored for a cubemap is:
   * <pre>
   *       cubemap_store(s) = s ^ 2 * 6
   * </pre>
   * Since <c>cubemap_store(s)</c> will always be greater than <c>cubemap_samples(s)</c>,some 
   * cubemap face grid cells will not be used.
   * 
   * This figure shows which cubemap face is used to store a certain cubemap sample:
   * <pre>
   *       .       Y-  Z+                          [n,0,n]                  [n,0,0]
   *       .        | /                                    \\       Y-       /
   *       .        |/                                      O--+--+--+--+--O
   *       .   X- --+-- X+                                  |..|..|..|..|..|
   *       .       /|                                       +--+--+--+--+--+
   *       .      / |                                       |##|##|##|##|##|
   *       .    Z-  Y+                                      +--+--+--+--+--+
   *       .                                                |##|##|##|##|##|
   *       .                                                +--+--+--+--+--+
   *       .                                                |##|##|##|##|##|
   *       .   [0,0,0]     [n,0,0]        [n,0,n]   [0,0,n] +--+--+--+--+--+
   *       .   |      Z-      |      X+      |      Z+     \\|..|..|..|..|..|
   *       .   O--+--+--+--+--O--+--+--+--+--O--+--+--+--+--O--+--+--+--+--O-[0,0,0]
   *       .   |..|..|..|..|..|##|##|##|##|##|..|..|..|..|..|##|##|##|##|##|
   *       .   +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
   *       .   |..|##|##|##|..|##|##|##|##|##|..|##|##|##|..|##|##|##|##|##|
   *       .   +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
   *       .   |..|##|##|##|..|##|##|##|##|##|..|##|##|##|..|##|##|##|##|##| X-
   *       .   +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
   *       .   |..|##|##|##|..|##|##|##|##|##|..|##|##|##|..|##|##|##|##|##|
   *       .   +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
   *       .   |..|..|..|..|..|##|##|##|##|##|..|..|..|..|..|##|##|##|##|##|
   *       .   O--+--+--+--+--O--+--+--+--+--O--+--+--+--+--O--+--+--+--+--O-[0,n,0]
   *       .   |              |              |             /|..|..|..|..|..|
   *       .   [0,n,0]     [n,n,0]        [n,n,n]   [0,n,n] +--+--+--+--+--+
   *       .                                                |##|##|##|##|##|
   *       .   +----------------------------------+         +--+--+--+--+--+
   *       .   | ## := Cubemap sample stored in   |         |##|##|##|##|##|
   *       .   |       respective face grid.      |         +--+--+--+--+--+
   *       .   |                                  |         |##|##|##|##|##|
   *       .   | .. := Cubemap sample stored in   |         +--+--+--+--+--+
   *       .   |       adjacent face grid.        |         |..|..|..|..|..|
   *       .   +----------------------------------+         O--+--+--+--+--O
   *       .                                               /       Y+       \\
   *       .                                        [n,n,n]                  [n,n,0]
   * </pre>
   */
  class Cubemap
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Constants
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The X- cubemap face.
     * 
     * <pre>
     *     .      #-------+       Y-  Z+ 
     *     .     ##      /|        | /   
     *     .    # #     / |        |/    
     *     .   #-------+  |   X- --+-- X+   right-handed CS
     *     .   #  #....|  +       /|     
     *     .   # #     | /       / |     
     *     .   ##      |/       Z-  Y+   
     *     .   #-------+
     * </pre>
     */
    static const int32 FaceNegX = 1;
    
    /*!
     * @brief  The Y- cubemap face.
     * 
     * <pre>
     *     .      #########       Y-  Z+ 
     *     .     #       #|        | /   
     *     .    #       # |        |/    
     *     .   #########  |   X- --+-- X+   right-handed CS
     *     .   |  .....|..+       /|     
     *     .   | .     | /       / |     
     *     .   |.      |/       Z-  Y+   
     *     .   +-------+
     * </pre>
     */
    static const int32 FaceNegY = 3;
    
    /*!
     * @brief  The Z- cubemap face.
     * 
     * <pre>
     *     .      +-------+       Y-  Z+ 
     *     .     /.      /|        | /   
     *     .    / .     / |        |/    
     *     .   #########  |   X- --+-- X+   right-handed CS
     *     .   #       #..+       /|     
     *     .   #       # /       / |     
     *     .   #       #/       Z-  Y+   
     *     .   #########
     * </pre>
     */
    static const int32 FaceNegZ = 5;
    
    /*!
     * @brief  The X+cubemap face.
     * 
     * <pre>
     *     .      +-------#       Y-  Z+ 
     *     .     /.      ##        | /   
     *     .    / .     # #        |/    
     *     .   +-------#  #   X- --+-- X+   right-handed CS
     *     .   |  .....#..#       /|     
     *     .   | .     # #       / |     
     *     .   |.      ##       Z-  Y+   
     *     .   +-------#
     * </pre>
     */
    static const int32 FacePosX = 0;
    
    /*!
     * @brief  The Y+cubemap face.
     * 
     * <pre>
     *     .      +-------+       Y-  Z+ 
     *     .     /.      /|        | /   
     *     .    / .     / |        |/    
     *     .   +-------+  |   X- --+-- X+   right-handed CS
     *     .   |  #####|###       /|     
     *     .   | #     | #       / |     
     *     .   |#      |#       Z-  Y+   
     *     .   #########
     * </pre>
     */
    static const int32 FacePosY = 2;
    
    /*!
     * @brief  The Z+cubemap face.
     * 
     * <pre>
     *     .      #########       Y-  Z+ 
     *     .     /#      /#        | /   
     *     .    / #     / #        |/    
     *     .   +-------+  #   X- --+-- X+   right-handed CS
     *     .   |  #####|###       /|     
     *     .   | .     | /       / |     
     *     .   |.      |/       Z-  Y+   
     *     .   +-------+
     * </pre>
     */
    static const int32 FacePosZ = 4;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Computes the bounding box in heightmap coordinates space that contains the given 
     *         region.
     * 
     * @param faceX X-coordinate of top-left corner of region,in cubemap face space.
     * @param faceY Y-coordinate of top-left corner of region,in cubemap face space.
     * @param face The cubemap face.
     * @param width The width of the region.
     * @param height The height of the region.
     * @param n Size of cubemap,minus one.
     * 
     * @return The computed bounding box.
     */
    static Box3I ComputeBoundingBox(int32 faceX, int32 faceY, int32 face, int32 width, int32 height, int32 n);
    
    /*!
     * @brief  Computes the number of samples covered by effective regions (see 
     *         <c>cubemap_effective(s)</c> above).
     * 
     * @param size <b>[pow2+1]</b>  Size of the cubemap.
     * 
     * @return <b>[>0]</b>  The number of samples.
     */
    static int64 ComputeSampleCountEffective(int32 size);
    
    /*!
     * @brief  Computes the number of samples stored for a cubemap (see <c>cubemap_store(s)</c> 
     *         above).
     * 
     * @param size <b>[pow2+1]</b>  Size of the cubemap.
     * 
     * @return <b>[>0]</b>  The number of samples.
     */
    static int64 ComputeSampleCountStore(int32 size);
    
    /*!
     * @brief  Computes the total number of samples in a cubemap (see <c>cubemap_samples(s)</c> 
     *         above).
     * 
     * @param size <b>[pow2+1]</b>  Size of the cubemap.
     * 
     * @return <b>[>0]</b>  The number of samples.
     */
    static int64 ComputeSampleCountTotal(int32 size);
    
    /*!
     * @brief  Computes a set of normalized cubemap coordinates from the given direction vector.
     * 
     * @param v The direction vector.
     * @param n Size of cubemap,minus one.
     * 
     * @return The normalized cubemap coordinates.
     */
    static Vec3D FromVector(const Vec3D& v, int32 n);
    
    /*!
     * @brief  Computes a set of normalized cubemap coordinates from the given direction vector.
     * 
     * @param x X-component of direction vector.
     * @param y Y-component of direction vector.
     * @param z Z-component of direction vector.
     * @param n Size of cubemap,minus one.
     * 
     * @return The normalized cubemap coordinates.
     */
    static Vec3D FromVector(float64 x, float64 y, float64 z, int32 n);
    
    /*!
     * @brief  Returns the bounds of the given cubemap face in cubemap coordinates.
     * 
     * @param face The cubemap face.
     * @param n Size of cubemap,minus one.
     * 
     * @return The face bounds in cubemap coordinates.
     */
    static Box3I GetFaceBounds(int32 face, int32 n);
    
    /*!
     * @brief  Returns the maximum coordinates of the effective region of the given cubemap face.
     * 
     * @param face <b>[0..5]</b>  The cubemap face.
     * @param n Size of cubemap,minus one.
     * 
     * @return Maximum coordinates of effective regions (inclusive).
     */
    static Vec2I GetFaceMax(int32 face, int32 n);
    
    /*!
     * @brief  Returns the minimum coordinates of the effective region of the given cubemap face.
     * 
     * @param face <b>[0..5]</b>  The cubemap face.
     * 
     * @return Minimum coordinates of effective regions (inclusive).
     */
    static Vec2I GetFaceMin(int32 face);
    
    /*!
     * @brief  Returns the tangent space orientation for a given cubemap face.
     * 
     * Given the three heightmap space tangent vectors \c tx ,\c ty  and \c tz ,the cubemap face 
     * tangent vectors \c tix  and \c tiy  for a cubemap face \c f  can be computed as follows:
     * <pre>
     *     tix = tx * GetTangentSpace(f, 0) 
     *     + ty * GetTangentSpace(f, 1) 
     *     + tz * GetTangentSpace(f, 2) 
     *     tiy = tx * GetTangentSpace(f, 3) 
     *     + ty * GetTangentSpace(f, 4) 
     *     + tz * GetTangentSpace(f, 5) 
     * </pre>
     * 
     * @param face <b>[0..5]</b>  The cubemap face (see class constants).
     * @param component <b>[0..5]</b>  The tangent vector component (see remarks).
     */
    static int32 GetTangentSpace(int32 face, int32 component);
    
    static bool IsFace(const Vec3D& coords, int32 face, int32 n);
    
    /*!
     * @brief  Normalizes the given cubemap coordinates.
     * 
     * @param coords The cubemap coordinates.
     * @param n Size of cubemap,minus one.
     */
    static Vec3I Normalize(const Vec3I& coords, int32 n);
    
    /*!
     * @brief  Normalizes the given cubemap coordinates.
     * 
     * @param x X-component of cubemap coordinates.
     * @param y Y-component of cubemap coordinates.
     * @param z Z-component of cubemap coordinates.
     * @param n Size of cubemap,minus one.
     */
    static Vec3I Normalize(int32 x, int32 y, int32 z, int32 n);
    
    /*!
     * @brief  Computes the bounding box in cubemap coordinates for the given bounding box in 
     *         cubemap face coordinates.
     * 
     * @param bounds The bounding box in cubemap face coordinates.
     * @param face The cubemap face.
     * @param n Size of cubemap,minus one.
     * 
     * @return The bounding box in cubemap coordinates.
     */
    static Box3I ToCube(const Box2I& bounds, int32 face, int32 n);
    
    /*!
     * @brief  Converts the given set of unit cubemap face coordinates to unit cubemap coordinates.
     * 
     * The given cubemap face coordinates will be interpreted as follows:
     * <pre>
     *     X := cubemap face X-coordinate.
     *     Y := cubemap face Y-coordinate.
     *     Z := cubemap face index (see Face* constants).
     * </pre>
     * 
     * @param coords The unit cubemap face coordinates.
     * @param n Size of cubemap,minus one.
     * 
     * @return The resulting unit cubemap coordinates.
     */
    static Vec3I ToCube(const Vec3I& coords, int32 n);
    
    /*!
     * @brief  Converts the given set of unit cubemap face coordinates to unit cubemap coordinates.
     * 
     * @param faceX Unit cubemap face X-coordinate.
     * @param faceY Unit cubemap face Y-coordinate.
     * @param face Cubemap face index (see <c>Face*</c> constants).
     * @param n Size of cubemap,minus one.
     * 
     * @return The resulting unit cubemap coordinates.
     */
    static Vec3I ToCube(int32 faceX, int32 faceY, int32 face, int32 n);
    
    static Box2I ToFace(const Box3I& bounds, int32 face, int32 n);
    
    static Vec2D ToFace(const Vec3D& coords, int32 face, int32 n);
    
    /*!
     * @brief  Converts the given set of unit cubemap coordinates to unit cubemap face coordinates.
     * 
     * The returned cubemap face coordinates will be encoded as a Vec3I as follows:
     * <pre>
     *     X := cubemap face X-coordinate.
     *     Y := cubemap face Y-coordinate.
     *     Z := cubemap face index (see Face* constants).
     * </pre>
     * 
     * @param coords The unit cubemap coordinates.
     * @param n Size of cubemap,minus one.
     * 
     * @return The resulting unit cubemap face coordinates.
     */
    static Vec3I ToFace(const Vec3I& coords, int32 n);
    
    /*!
     * @brief  Converts the given set of unit cubemap coordinates to unit cubemap face coordinates.
     * 
     * The returned cubemap face coordinates will be encoded as a Vec3I as follows:
     * <pre>
     *     X := cubemap face X-coordinate.
     *     Y := cubemap face Y-coordinate.
     *     Z := cubemap face index (see Face* constants).
     * </pre>
     * 
     * @param x X-component of unit cubemap coordinates.
     * @param y Y-component of unit cubemap coordinates.
     * @param z Z-component of unit cubemap coordinates.
     * @param n Size of cubemap,minus one.
     * 
     * @return The resulting unit cubemap face coordinates.
     */
    static Vec3I ToFace(int32 x, int32 y, int32 z, int32 n);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  This array defines the tangent space orientation for each cubemap face.
     * 
     * Given the three heightmap space tangent vectors \c tx ,\c ty  and \c tz ,the cubemap face 
     * tangent vectors \c tix  and \c tiy  for a cubemap face \c f  can be computed as follows:
     * <pre>
     *     tix = tx * TangentSpace[f * 6 + 0] 
     *     + ty * TangentSpace[f * 6 + 1] 
     *     + tz * TangentSpace[f * 6 + 2] 
     *     tiy = tx * TangentSpace[f * 6 + 3] 
     *     + ty * TangentSpace[f * 6 + 4] 
     *     + tz * TangentSpace[f * 6 + 5] 
     * </pre>
     */
    static const Array<int32> TangentSpace;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    static Vec2I ToFace(int32 x, int32 y, int32 z, int32 face, int32 n);
  };
  
} } } 

#endif
