////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_UTIL_BOX3I_H
#define CLODDY_API_UTIL_BOX3I_H

#include "CodeX/System.h"

// Forward declare referenced structures.

namespace Cloddy { namespace Core { namespace Math { namespace Vectors { struct Vec3I; } } } }

// Declare class ::Cloddy::API::Util::Box3I.

namespace Cloddy { namespace API { namespace Util
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced structures.
  
  using Cloddy::Core::Math::Vectors::Vec3I;
  
  /*!
   * @brief  A three-dimensional bounding box with integer precision.
   */
  struct Box3I : StructType
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  An empty bounding box.
     */
    static const Box3I Empty;
    
    /*!
     * @brief  Is this bounding box empty?
     * 
     * @return \c true  if this bounding box is empty,\c false  if not.
     */
    bool IsEmpty() const;
    
    /*!
     * @brief  Returns the volume of this bounding box.
     * 
     * @return The bounding box volume.
     */
    int32 GetVolume() const;
    
    /*!
     * @brief  X-coordinate of minimum corner of bounding box.
     */
    int32 X1;
    
    /*!
     * @brief  X-coordinate of maximum corner of bounding box.
     */
    int32 X2;
    
    /*!
     * @brief  Y-coordinate of minimum corner of bounding box.
     */
    int32 Y1;
    
    /*!
     * @brief  Y-coordinate of maximum corner of bounding box.
     */
    int32 Y2;
    
    /*!
     * @brief  Z-coordinate of minimum corner of bounding box.
     */
    int32 Z1;
    
    /*!
     * @brief  Z-coordinate of maximum corner of bounding box.
     */
    int32 Z2;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of Box3I.
     * 
     * @param x1 X-coordinate of minimum corner of bounding box.
     * @param y1 Y-coordinate of minimum corner of bounding box.
     * @param z1 Z-coordinate of minimum corner of bounding box.
     * @param x2 X-coordinate of maximum corner of bounding box.
     * @param y2 Y-coordinate of maximum corner of bounding box.
     * @param z2 Z-coordinate of maximum corner of bounding box.
     */
    Box3I(int32 x1, int32 y1, int32 z1, int32 x2, int32 y2, int32 z2);
    
    Box3I();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of Box3I from the given corner points.
     * 
     * @param x1 X-coordinate of first corner point.
     * @param y1 Y-coordinate of first corner point.
     * @param z1 Z-coordinate of first corner point.
     * @param x2 X-coordinate of second corner point.
     * @param y2 Y-coordinate of second corner point.
     * @param z2 Z-coordinate of second corner point.
     * 
     * @return The bounding box.
     */
    static Box3I FromPoints(int32 x1, int32 y1, int32 z1, int32 x2, int32 y2, int32 z2);
    
    /*!
     * @brief  Creates a new instance of Box3I from the given corner points.
     * 
     * @param a First corner point.
     * @param b Second corner point.
     * 
     * @return The bounding box.
     */
    static Box3I FromPoints(const Vec3I& a, const Vec3I& b);
    
    /*!
     * @brief  Checks the intersection between this bounding box and the given one.
     * 
     * @param box The other bounding box.
     * 
     * @return \c -1  if the bounding boxes do not overlap,\c 1  if \e box  fully contains this 
     * bounding box and \c 0  if both bounding boxes overlap without containing each other.
     */
    int32 CheckIntersection(const Box3I& box) const;
    
    /*!
     * @brief  Computes the overlap of this bounding box and the given one.
     * 
     * @param box Second bounding box.
     * 
     * @return <b>[>=0]</b>  The amount of overlap (ie. the volume of the intersection).
     */
    int32 ComputeOverlap(const Box3I& box) const;
    
    Box3I Intersect(const Box3I& box) const;
    
    /*!
     * @brief  Translates this bounding box.
     * 
     * @param x Translation amount along X-axis.
     * @param y Translation amount along Y-axis.
     * @param z Translation amount along Z-axis.
     * 
     * @return The resulting bounding box.
     */
    Box3I Translate(int32 x, int32 y, int32 z) const;
    
    // ---------------------------------------------------------------------------------------------
    //  Copy constructor and copy assignment operator
    // ---------------------------------------------------------------------------------------------
  public:
    
    Box3I(const Box3I& other);
    
    Box3I& operator=(const Box3I& other);
  };
  
} } } 

#endif
