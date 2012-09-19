////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_UTIL_SPATIAL_AXISALIGNEDBOXREGION_H
#define CLODDY_API_UTIL_SPATIAL_AXISALIGNEDBOXREGION_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/TerrainSpaceRegion.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Util { namespace Spatial { class ITerrainSpaceRegionVisitor; } } } }

// Declare class ::Cloddy::API::Util::Spatial::AxisAlignedBoxRegion.

namespace Cloddy { namespace API { namespace Util { namespace Spatial
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  A terrain-space region specified by an axis aligned bounding box.
   * 
   * The origin of an AxisAlignedBoxRegion is the center of the bounding box.
   */
  class AxisAlignedBoxRegion : public TerrainSpaceRegion
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Returns the extend of the bounding box along the Z-axis.
     * 
     * @return <b>[>=0]</b>  The box extend.
     */
    float64 GetDepth();
    
    /*!
     * @brief  Returns the extend of the bounding box along the Y-axis.
     * 
     * @return <b>[>=0]</b>  The box extend.
     */
    float64 GetHeight();
    
    /*!
     * @brief  Returns the extend of the bounding box along the X-axis.
     * 
     * @return <b>[>=0]</b>  The box extend.
     */
    float64 GetWidth();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of AxisAlignedBoxRegion.
     * 
     * The origin of the bounding box will be <c>(0,0,0)</c> and the width,height and depth will be 
     * \c 0 .
     */
    AxisAlignedBoxRegion();
    
    /*!
     * @brief  Creates a new instance of AxisAlignedBoxRegion.
     * 
     * The origin of the bounding box will be <c>(0,0,0)</c>.
     * 
     * @param width <b>[>=0]</b>  Extend of the bounding box along the X-axis.
     * @param height <b>[>=0]</b>  Extend of the bounding box along the X-axis.
     * @param depth <b>[>=0]</b>  Extend of the bounding box along the X-axis.
     */
    AxisAlignedBoxRegion(float32 width, float32 height, float32 depth);
    
    /*!
     * @brief  Creates a new instance of AxisAlignedBoxRegion.
     * 
     * @param x1 X-coordinate of first corner of bounding box.
     * @param y1 Y-coordinate of first corner of bounding box.
     * @param z1 Z-coordinate of first corner of bounding box.
     * @param x2 X-coordinate of second corner of bounding box.
     * @param y2 Y-coordinate of second corner of bounding box.
     * @param z2 Z-coordinate of second corner of bounding box.
     */
    AxisAlignedBoxRegion(float32 x1, float32 y1, float32 z1, float32 x2, float32 y2, float32 z2);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void Accept(ITerrainSpaceRegionVisitor* visitor, Object* userData);
    
    virtual bool IntersectsSphere(float64 x, float64 y, float64 z, float64 r);
    
    /*!
     * @brief  Sets the axis aligned bounding box of this region.
     * 
     * @param x1 X-coordinate of first corner of bounding box.
     * @param y1 Y-coordinate of first corner of bounding box.
     * @param z1 Z-coordinate of first corner of bounding box.
     * @param x2 X-coordinate of second corner of bounding box.
     * @param y2 Y-coordinate of second corner of bounding box.
     * @param z2 Z-coordinate of second corner of bounding box.
     */
    void SetBox(float64 x1, float64 y1, float64 z1, float64 x2, float64 y2, float64 z2);
    
    /*!
     * @brief  Sets the size of the bounding box.
     * 
     * @param width <b>[>=0]</b>  Extend of the bounding box along the X-axis.
     * @param height <b>[>=0]</b>  Extend of the bounding box along the Y-axis.
     * @param depth <b>[>=0]</b>  Extend of the bounding box along the Z-axis.
     */
    void SetSize(float64 width, float64 height, float64 depth);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Extend of the bounding box along the Z-axis.
     */
    float64 depth;
    
    /*!
     * @brief  Extend of the bounding box along the Y-axis.
     */
    float64 height;
    
    /*!
     * @brief  Extend of the bounding box along the X-axis.
     */
    float64 width;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<AxisAlignedBoxRegion> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x8732461C;
    
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
      if ((ptr = TerrainSpaceRegion::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } 

#endif
