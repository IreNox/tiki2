////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_UTIL_MAPFIELD_H
#define CLODDY_API_UTIL_MAPFIELD_H

#include "CodeX/System.h"

// Include referenced structures.

#include "Cloddy/Vec3I.h"

// Declare class ::Cloddy::API::Util::MapField.

namespace Cloddy { namespace API { namespace Util
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced structures.
  
  using Cloddy::Core::Math::Vectors::Vec3I;
  
  /*!
   * @brief  The MapField struct describes a rectangular region of a map.
   * 
   * The top-left corner of a map field is specified in cubemap face coordinates,ie. face X- and 
   * Y-coordinates and cubemap face number (see Cubemap).A map field has a step value which depicts 
   * the distance between adjacent samples.The map field step is always interpreted relative to the 
   * map origin at (0,0).
   * 
   * When a MapField value is created with a field step greater than \c 1 ,the given input map 
   * coordinates are adjusted to match the nearest map samples that match the specified field step (
   * eg. the tighest fitting bounding rectangle is computed).
   * 
   * The following figure illustrates some example map fields for a map of size <c>10 x 5</c>:
   * <pre>
   *       .   '.' := Map sample
   *       .   'o' := Map sample matching field step
   *       .   'x' := Map sample contained in field
   *       .
   *       .   +----------+       +----------+       +----------+
   *       .   |xxxxoooooo|       |o.o.o.o.o.|       |o...x...x.|
   *       .   |xxxxoooooo|       |..........|       |..........|
   *       .   |xxxxoooooo|       |o.x.x.x.o.|       |..........|
   *       .   |oooooooooo|       |..........|       |..........|
   *       .   |oooooooooo|       |o.x.x.x.o.|       |o...o...o.|
   *       .   +----------+       +----------+       +----------+
   *       .   
   *       .   FaceX  := 0        FaceX  := 2        FaceX  := 4
   *       .   FaceY  := 0        FaceY  := 2        FaceY  := 0
   *       .   Width  := 4        Width  := 3        Width  := 2
   *       .   Height := 3        Height := 2        Height := 1
   *       .   Step   := 1        Step   := 2        Step   := 4
   * </pre>
   * //TODO:Validate usages of sparse factory methods!
   */
  struct MapField : StructType
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  An empty map field (ie. containing no map samples).
     */
    static const MapField Empty;
    
    /*!
     * @brief  The cubemap face on which the map field is located.
     * 
     * @see Cubemap
     */
    int32 Face;
    
    /*!
     * @brief  The cubemap face X-coordinate of the top-left corner of the map field.
     */
    int32 FaceX;
    
    /*!
     * @brief  The cubemap face Y-coordinate of the top-left corner of the map field.
     */
    int32 FaceY;
    
    /*!
     * @brief  The height of the map field,in map field sample steps.
     */
    int32 Height;
    
    /*!
     * @brief  Is this map field empty,ie. it contains no samples?
     * 
     * @return \c true  if the map field is empty,\c false  if not.
     */
    bool IsEmpty() const;
    
    /*!
     * @brief  The step distance between adjacent map field samples.
     */
    int32 Step;
    
    /*!
     * @brief  The width of the map field,in map field sample steps.
     */
    int32 Width;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a solid MapField for the given map region.
     * 
     * @param face The cubemap face of the region.
     * @param faceX1 X-coordinate of first corner of map region.
     * @param faceY1 Y-coordinate of first corner of map region.
     * @param faceX2 X-coordinate of second corner of map region.
     * @param faceY2 X-coordinate of second corner of map region.
     * 
     * @return The MapField value.
     */
    static MapField SolidPoints(int32 face, int32 faceX1, int32 faceY1, int32 faceX2, int32 faceY2);
    
    /*!
     * @brief  Creates a solid MapField for the given map region.
     * 
     * @param face <b>[0..5]</b>  The cubemap face of the region.
     * @param faceX X-coordinate of top-left corner of map region.
     * @param faceY Y-coordinate of top-left corner of map region.
     * @param width The map region width,in samples.
     * @param height The map region height,in samples.
     * 
     * @return The MapField value.
     */
    static MapField SolidRect(int32 face, int32 faceX, int32 faceY, int32 width, int32 height);
    
    /*!
     * @brief  Creates a sparse MapField for the given map region.
     * 
     * A sparse map field contains every \c n -th map sample,relative to the top-left map sample at 
     * <c>(0,0)</c>.The value of \c n  must be a power of two.
     * 
     * @param step <b>[>=0]</b>  The field step,in map samples,given as logarithm of base 2 (
     * see Maths::Log2);e.g.\c 0  means a step of \c 1 ,\c 3  means a step of \c 8 .
     * @param face <b>[0..5]</b>  The cubemap face of the region.
     * @param faceX1 X-coordinate of first corner of map region.
     * @param faceY1 Y-coordinate of first corner of map region.
     * @param faceX2 X-coordinate of second corner of map region.
     * @param faceY2 X-coordinate of second corner of map region.
     * 
     * @return The MapField value.
     */
    static MapField SparsePoints(int32 step, int32 face, int32 faceX1, int32 faceY1, int32 faceX2, int32 faceY2);
    
    /*!
     * @brief  Creates a sparse MapField for the given map region.
     * 
     * A sparse map field contains every \c n -th map sample,relative to the top-left map sample at 
     * <c>(0,0)</c>.The value of \c n  must be a power of two.
     * 
     * @param step <b>[>=0]</b>  The field step,in map samples,given as logarithm of base 2 (
     * see Maths::Log2);e.g.\c 0  means a step of \c 1 ,\c 3  means a step of \c 8 .
     * @param face <b>[0..5]</b>  The cubemap face of the region.
     * @param faceX X-coordinate of top-left corner of map region.
     * @param faceY Y-coordinate of top-left corner of map region.
     * @param width Width of map region,in field steps.
     * @param height Height of map region,in field steps.
     * 
     * @return The MapField value.
     */
    static MapField SparseRect(int32 step, int32 face, int32 faceX, int32 faceY, int32 width, int32 height);
    
    /*!
     * @brief  Clips this map field at the given region.
     * 
     * @param x X-coordinate of top-left corner of clip rectangle,in samples.
     * @param y Y-coordinate of top-left corner of clip rectangle,in samples.
     * @param width Width of clip rectangle,in samples.
     * @param height Height of clip rectangle,in samples.
     * 
     * @return The clipped map field.
     */
    MapField Clip(int32 x, int32 y, int32 width, int32 height) const;
    
    /*!
     * @brief  Computes the absolute cubemap coordinates of the given map field sample.
     * 
     * @param x X-coordinate of map field sample.
     * @param y Y-coordinate of map field sample.
     * @param cubemapSizeMinusOne <b>[pow2]</b>  The cubemap size,minus one.
     * 
     * @return The absolute cubemap coordinates.
     */
    Vec3I GetCubeCoords(int32 x, int32 y, int32 cubemapSizeMinusOne) const;
    
    /*!
     * @brief  Computes the absolute cubemap face coordinates of the given map field sample.
     * 
     * @param x X-coordinate of map field sample.
     * @param y Y-coordinate of map field sample.
     * 
     * @return The absolute cubemap face coordinates.
     */
    Vec3I GetFaceCoords(int32 x, int32 y) const;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Creates a new instance of MapField.
     * 
     * @param step The distance between adjacent map field samples.
     * @param face The cubemap face on which the map field is located.
     * @param faceX The cubemap face X-coordinate of the top-left corner of the map field.
     * @param faceY The cubemap face Y-coordinate of the top-left corner of the map field.
     * @param width The width of the map field,in map sample stride steps.
     * @param height The height of the map field,in map sample stride steps.
     */
    MapField(int32 step, int32 face, int32 faceX, int32 faceY, int32 width, int32 height);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
  public:
    
    MapField();
    
    // ---------------------------------------------------------------------------------------------
    //  Copy constructor and copy assignment operator
    // ---------------------------------------------------------------------------------------------
  public:
    
    MapField(const MapField& other);
    
    MapField& operator=(const MapField& other);
  };
  
} } } 

#endif
