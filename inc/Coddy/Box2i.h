////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_UTIL_BOX2I_H
#define CLODDY_API_UTIL_BOX2I_H

#include "CodeX/System.h"

// Include referenced structures.

#include "Cloddy/Vec2I.h"

// Declare class ::Cloddy::API::Util::Box2I.

namespace Cloddy { namespace API { namespace Util
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced structures.
  
  using Cloddy::Core::Math::Vectors::Vec2I;
  
  /*!
   * @brief  A two-dimensional bounding box with integer precision.
   */
  struct Box2I : StructType
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  An empty bounding box.
     */
    static const Box2I Empty;
    
    /*!
     * @brief  Returns the area of this bounding box.
     * 
     * @return The area.
     */
    int32 GetArea() const;
    
    Vec2I GetBottomLeft() const;
    
    Vec2I GetBottomRight() const;
    
    int32 GetHeight() const;
    
    /*!
     * @brief  Is this bounding box empty?
     * 
     * @return \c true  if this bounding box is empty,\c false  if not.
     */
    bool IsEmpty() const;
    
    Vec2I GetTopLeft() const;
    
    Vec2I GetTopRight() const;
    
    int32 GetWidth() const;
    
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
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of Box2I.
     * 
     * @param x1 X-coordinate of minimum corner of bounding box.
     * @param y1 Y-coordinate of minimum corner of bounding box.
     * @param x2 X-coordinate of maximum corner of bounding box.
     * @param y2 Y-coordinate of maximum corner of bounding box.
     */
    Box2I(int32 x1, int32 y1, int32 x2, int32 y2);
    
    Box2I();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of Box2I from the given corner points.
     * 
     * @param x1 X-coordinate of first corner point.
     * @param y1 Y-coordinate of first corner point.
     * @param x2 X-coordinate of second corner point.
     * @param y2 Y-coordinate of second corner point.
     * 
     * @return The bounding box.
     */
    static Box2I FromPoints(int32 x1, int32 y1, int32 x2, int32 y2);
    
    /*!
     * @brief  Creates a new instance of Box2I from the given corner points.
     * 
     * @param a First corner point.
     * @param b Second corner point.
     * 
     * @return The bounding box.
     */
    static Box2I FromPoints(const Vec2I& a, const Vec2I& b);
    
    /*!
     * @brief  Checks the intersection between this bounding box and the given one.
     * 
     * @param box The bounding box.
     * 
     * @return \c -1  if the bounding boxes do not overlap,\c 1  if \e box  fully contains this 
     * bounding box and \c 0  if both bounding boxes overlap without containing each other.
     */
    int32 CheckIntersection(const Box2I& box) const;
    
    /*!
     * @brief  Computes the intersection of the given bounding box and this one.
     * 
     * @param box The bounding box.
     * 
     * @return The resulting bounding box.
     */
    Box2I Intersect(const Box2I& box) const;
    
    /*!
     * @brief  Translates this bounding box.
     * 
     * @param x Translation amount along X-axis.
     * @param y Translation amount along Y-axis.
     * 
     * @return The translated bounding box.
     */
    Box2I Translate(int32 x, int32 y) const;
    
    // ---------------------------------------------------------------------------------------------
    //  Copy constructor and copy assignment operator
    // ---------------------------------------------------------------------------------------------
  public:
    
    Box2I(const Box2I& other);
    
    Box2I& operator=(const Box2I& other);
  };
  
} } } 

#endif
