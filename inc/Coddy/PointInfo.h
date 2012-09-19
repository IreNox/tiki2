////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_MESHVISITORS_POINTINFO_H
#define CLODDY_API_MESHVISITORS_POINTINFO_H

#include "CodeX/System.h"

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Brushes { class DisplacementBrush; } } } }

// Declare class ::Cloddy::API::MeshVisitors::PointInfo.

namespace Cloddy { namespace API { namespace MeshVisitors
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced classes.
  
  using Cloddy::API::Heightmaps::Brushes::DisplacementBrush;
  
  /*!
   * @brief  Data container for the result of a picking operation.
   * 
   * The <c>Flag*</c> constants can be used to choose the values which will be computed.
   * 
   * @see Picking
   * @see CollisionDetection
   */
  class PointInfo : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Constants
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  This flag value contains all <c>Flag*</c> constants.
     */
    static const int32 FlagAll = ~0;
    
    /*!
     * @brief  Flag bit that indicates that the cubemap face has been computed.
     * 
     * If this bit is set in #Flags,the following fields are valid:
     *   - #Face
     */
    static const int32 FlagFace = 1;
    
    /*!
     * @brief  Flag bit that indicates that the tangent vector along the cubemap face X-axis has 
     *         been computed.
     * 
     * If this bit is set in #Flags,the following fields are valid:
     *   - #FaceTangentX_X
     *   - #FaceTangentX_Y
     *   - #FaceTangentX_Z
     */
    static const int32 FlagFaceTangentX = 256 + 128 + 64 + 2 + 1;
    
    /*!
     * @brief  Flag bit that indicates that the tangent vector along the cubemap face Y-axis has 
     *         been computed.
     * 
     * If this bit is set in #Flags,the following fields are valid:
     *   - #FaceTangentY_X
     *   - #FaceTangentY_Y
     *   - #FaceTangentY_Z
     */
    static const int32 FlagFaceTangentY = 256 + 128 + 64 + 4 + 2 + 1;
    
    /*!
     * @brief  Flag bit that indicates that the heightmap coordinates have been computed.
     * 
     * If this bit is set in #Flags,the following fields are valid:
     *   - #HeightmapX
     *   - #HeightmapY
     *   - #HeightmapZ
     */
    static const int32 FlagHeightmapCoords = 8;
    
    /*!
     * @brief  Flag bit that indicates that the normal vector has been computed.
     * 
     * If this bit is set in #Flags,the following fields are valid:
     *   - #NormalX
     *   - #NormalY
     *   - #NormalZ
     */
    static const int32 FlagNormal = 16;
    
    /*!
     * @brief  Flag bit that indicates that the point coordinates have been computed.
     * 
     * If this bit is set in #Flags,the following fields are valid:
     *   - #PointX
     *   - #PointY
     *   - #PointZ
     */
    static const int32 FlagPoint = 32;
    
    /*!
     * @brief  Flag bit that indicates that the tangent vector along the heightmap space X-axis has 
     *         been computed.
     * 
     * If this bit is set in #Flags,the following fields are valid:
     *   - #TangentX_X
     *   - #TangentX_Y
     *   - #TangentX_Z
     */
    static const int32 FlagTangentX = 64;
    
    /*!
     * @brief  Flag bit that indicates that the tangent vector along the heightmap space Y-axis has 
     *         been computed.
     * 
     * If this bit is set in #Flags,the following fields are valid:
     *   - #TangentY_X
     *   - #TangentY_Y
     *   - #TangentY_Z
     */
    static const int32 FlagTangentY = 128 + 64;
    
    /*!
     * @brief  Flag bit that indicates that the tangent vector along the heightmap space Z-axis has 
     *         been computed.
     * 
     * If this bit is set in #Flags,the following fields are valid:
     *   - #TangentZ_X
     *   - #TangentZ_Y
     *   - #TangentZ_Z
     */
    static const int32 FlagTangentZ = 256 + 128 + 64;
    
    /*!
     * @brief  Flag bit that indicates that the triangle vertices have been computed.
     * 
     * If this bit is set in #Flags,the following fields are valid:
     *   - #VertexA
     *   - #VertexB
     *   - #VertexC
     */
    static const int32 FlagVertices = 512;
    
    /*!
     * @brief  Flag bit that indicates that the barycentric coordinates of the triangle vertices 
     *         have been computed.
     * 
     * If this bit is set in #Flags,the following fields are valid:
     *   - #Weight1
     *   - #Weight2
     *   - #Weight3
     */
    static const int32 FlagWeights = 1024;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  The cubemap face of the triangle that contains the point.
     */
    int32 Face;
    
    /*!
     * @brief  X-component of the tangent vector on the cubemap face on which the point lies,along 
     *         the cubemap face X-axis.
     * 
     * @see #Face
     */
    float32 FaceTangentX_X;
    
    /*!
     * @brief  Y-component of the tangent vector on the cubemap face on which the point lies,along 
     *         the cubemap face X-axis.
     * 
     * @see #Face
     */
    float32 FaceTangentX_Y;
    
    /*!
     * @brief  Z-component of the tangent vector on the cubemap face on which the point lies,along 
     *         the cubemap face X-axis.
     * 
     * @see #Face
     */
    float32 FaceTangentX_Z;
    
    /*!
     * @brief  X-component of the tangent vector on the cubemap face on which the point lies,along 
     *         the cubemap face Y-axis.
     * 
     * @see #Face
     */
    float32 FaceTangentY_X;
    
    /*!
     * @brief  Y-component of the tangent vector on the cubemap face on which the point lies,along 
     *         the cubemap face Y-axis.
     * 
     * @see #Face
     */
    float32 FaceTangentY_Y;
    
    /*!
     * @brief  Z-component of the tangent vector on the cubemap face on which the point lies,along 
     *         the cubemap face Y-axis.
     * 
     * @see #Face
     */
    float32 FaceTangentY_Z;
    
    /*!
     * @brief  A bitmask that indicates which values have been computed and are thus valid.
     * 
     * See the <c>Flag*</c> constant of this class for details.
     */
    int32 Flags;
    
    /*!
     * @brief  X-component of heightmap coordinates of picked point.
     */
    float64 HeightmapX;
    
    /*!
     * @brief  Y-component of heightmap coordinates of picked point.
     */
    float64 HeightmapY;
    
    /*!
     * @brief  Z-component of heightmap coordinates of picked point.
     */
    float64 HeightmapZ;
    
    /*!
     * @brief  X-component of surface normal at picked point,in terrain-space.
     */
    float32 NormalX;
    
    /*!
     * @brief  Y-component of surface normal at picked point,in terrain-space.
     */
    float32 NormalY;
    
    /*!
     * @brief  Z-component of surface normal at picked point,in terrain-space.
     */
    float32 NormalZ;
    
    /*!
     * @brief  X-coordinate of picked point,in terrain-space.
     */
    float64 PointX;
    
    /*!
     * @brief  Y-coordinate of picked point,in terrain-space.
     */
    float64 PointY;
    
    /*!
     * @brief  Z-coordinate of picked point,in terrain-space.
     */
    float64 PointZ;
    
    /*!
     * @brief  X-component of tangent vector along the heightmap space X-axis.
     */
    float32 TangentX_X;
    
    /*!
     * @brief  Y-component of tangent vector along the heightmap space X-axis.
     */
    float32 TangentX_Y;
    
    /*!
     * @brief  Z-component of tangent vector along the heightmap space X-axis.
     */
    float32 TangentX_Z;
    
    /*!
     * @brief  X-component of tangent vector along the heightmap space Y-axis.
     */
    float32 TangentY_X;
    
    /*!
     * @brief  Y-component of tangent vector along the heightmap space Y-axis.
     */
    float32 TangentY_Y;
    
    /*!
     * @brief  Z-component of tangent vector along the heightmap space Y-axis.
     */
    float32 TangentY_Z;
    
    /*!
     * @brief  X-component of tangent vector along the heightmap space Z-axis.
     */
    float32 TangentZ_X;
    
    /*!
     * @brief  Y-component of tangent vector along the heightmap space Z-axis.
     */
    float32 TangentZ_Y;
    
    /*!
     * @brief  Z-component of tangent vector along the heightmap space Z-axis.
     */
    float32 TangentZ_Z;
    
    /*!
     * @brief  Index of first vertex of picked triangle.
     * 
     * The vertices of the picked triangle are oriented in counter-clockwise direction.
     */
    int32 VertexA;
    
    /*!
     * @brief  Index of second vertex of picked triangle.
     * 
     * The vertices of the picked triangle are oriented in counter-clockwise direction.
     */
    int32 VertexB;
    
    /*!
     * @brief  Index of third vertex of picked triangle.
     * 
     * The vertices of the picked triangle are oriented in counter-clockwise direction.
     */
    int32 VertexC;
    
    /*!
     * @brief  First barycentric coordinate (range <c>[0..1]</c>)of picked point in picked triangle.
     * 
     * The picked point can be expressed using barycentric coordinates as follows:
     * <pre>
     *       p = A * w1 + B * w2 + C * w3
     * </pre>
     * where
     * 
     * p :=the picked point
     * A :=first vertex of picked triangle (#VertexA)
     * B :=second vertex of picked triangle (#VertexB)
     * C :=third vertex of picked triangle (#VertexC)
     * w1 :=first barycentric coordinate of picked point in picked triangle (#Weight1)
     * w2 :=second barycentric coordinate of picked point in picked triangle (#Weight2)
     * w3 :=third barycentric coordinate of picked point in picked triangle (#Weight3)
     * 
     * The sum of the barycentric coordinates is always <c>1.0</c> (ie. <c>w1 +w2 +w3 =1</c>).
     */
    float32 Weight1;
    
    /*!
     * @brief  Second barycentric coordinate (range <c>[0..1]</c>)of picked point in picked 
     *         triangle.
     * 
     * The picked point can be expressed using barycentric coordinates as follows:
     * <pre>
     *       p = A * w1 + B * w2 + C * w3
     * </pre>
     * where
     * 
     * p :=the picked point
     * A :=first vertex of picked triangle (#VertexA)
     * B :=second vertex of picked triangle (#VertexB)
     * C :=third vertex of picked triangle (#VertexC)
     * w1 :=first barycentric coordinate of picked point in picked triangle (#Weight1)
     * w2 :=second barycentric coordinate of picked point in picked triangle (#Weight2)
     * w3 :=third barycentric coordinate of picked point in picked triangle (#Weight3)
     * 
     * The sum of the barycentric coordinates is always <c>1.0</c> (ie. <c>w1 +w2 +w3 =1</c>).
     */
    float32 Weight2;
    
    /*!
     * @brief  Third barycentric coordinate (range <c>[0..1]</c>)of picked point in picked triangle.
     * 
     * The picked point can be expressed using barycentric coordinates as follows:
     * <pre>
     *       p = A * w1 + B * w2 + C * w3
     * </pre>
     * where
     * 
     * p :=the picked point
     * A :=first vertex of picked triangle (#VertexA)
     * B :=second vertex of picked triangle (#VertexB)
     * C :=third vertex of picked triangle (#VertexC)
     * w1 :=first barycentric coordinate of picked point in picked triangle (#Weight1)
     * w2 :=second barycentric coordinate of picked point in picked triangle (#Weight2)
     * w3 :=third barycentric coordinate of picked point in picked triangle (#Weight3)
     * 
     * The sum of the barycentric coordinates is always <c>1.0</c> (ie. <c>w1 +w2 +w3 =1</c>).
     */
    float32 Weight3;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Applies the tangent space of this point info object to given displacement brush.
     * 
     * @param brush <b>[not-null]</b>  The brush.
     */
    void ApplyTangentSpace(DisplacementBrush* brush);
    
    /*!
     * @brief  Clears all flags of this point info object.
     */
    void ClearFlags();
    
    /*!
     * @brief  Sets the #Face field and updates the #Flags field accordingly.
     * 
     * @param face The cubemap face (see Cubemap class).
     */
    void SetFace(int32 face);
    
    /*!
     * @brief  Sets the tangent vector (along the cubemap face X-axis)on the cubemap face on which 
     *         the point lies and updates the #Flags field accordingly.
     * 
     * @param x X-component of tangent vector.
     * @param y Y-component of tangent vector.
     * @param z Z-component of tangent vector.
     */
    void SetFaceTangentX(float32 x, float32 y, float32 z);
    
    /*!
     * @brief  Sets the tangent vector (along the cubemap face Y-axis)on the cubemap face on which 
     *         the point lies and updates the #Flags field accordingly.
     * 
     * @param x X-component of tangent vector.
     * @param y Y-component of tangent vector.
     * @param z Z-component of tangent vector.
     */
    void SetFaceTangentY(float32 x, float32 y, float32 z);
    
    /*!
     * @brief  Sets the heightmap coordinates of the point and updates the #Flags field accordingly.
     * 
     * @param x X-component of heightmap coordinates.
     * @param y Y-component of heightmap coordinates.
     * @param z Z-component of heightmap coordinates.
     */
    void SetHeightmapCoords(float64 x, float64 y, float64 z);
    
    /*!
     * @brief  Sets the normal vector of the point and updates the #Flags field accordingly.
     * 
     * @param x X-component of normal vector.
     * @param y Y-component of normal vector.
     * @param z Z-component of normal vector.
     */
    void SetNormal(float32 x, float32 y, float32 z);
    
    /*!
     * @brief  Sets the coordinates of the point and updates the #Flags field accordingly.
     * 
     * @param x X-coordinate of point.
     * @param y Y-coordinate of point.
     * @param z Z-coordinate of point.
     */
    void SetPoint(float64 x, float64 y, float64 z);
    
    /*!
     * @brief  Sets the tangent vector along the heightmap space X-axis and updates the #Flags 
     *         field accordingly.
     * 
     * @param x X-component of tangent vector.
     * @param y Y-component of tangent vector.
     * @param z Z-component of tangent vector.
     */
    void SetTangentX(float32 x, float32 y, float32 z);
    
    /*!
     * @brief  Sets the tangent vector along the heightmap space Y-axis and updates the #Flags 
     *         field accordingly.
     * 
     * @param x X-component of tangent vector.
     * @param y Y-component of tangent vector.
     * @param z Z-component of tangent vector.
     */
    void SetTangentY(float32 x, float32 y, float32 z);
    
    /*!
     * @brief  Sets the tangent vector along the heightmap space Z-axis and updates the #Flags 
     *         field accordingly.
     * 
     * @param x X-component of tangent vector.
     * @param y Y-component of tangent vector.
     * @param z Z-component of tangent vector.
     */
    void SetTangentZ(float32 x, float32 y, float32 z);
    
    /*!
     * @brief  Sets the vertex indices of the triangle in which the point lies.
     * 
     * @param a Index of first triangle vertex.
     * @param b Index of second triangle vertex.
     * @param c Index of third triangle vertex.
     */
    void SetVertices(int32 a, int32 b, int32 c);
    
    /*!
     * @brief  Sets the barycentric coordinates of the point inside the containing triangle.
     * 
     * @param w1 X-component of barycentric coordinates.
     * @param w2 Y-component of barycentric coordinates.
     * @param w3 Z-component of barycentric coordinates.
     */
    void SetWeights(float32 w1, float32 w2, float32 w3);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    PointInfo();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<PointInfo> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x28623092;
    
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
  
} } } 

#endif
