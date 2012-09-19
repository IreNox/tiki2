////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_VISIBILITYCRITERIA_ERRORMETRICS_COMPONENTS_ERRORTERM_H
#define CLODDY_API_VISIBILITYCRITERIA_ERRORMETRICS_COMPONENTS_ERRORTERM_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IMeshCallback.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace VertexData { class IVertexData; } } }
namespace Cloddy { namespace Kernel { class IProvider; } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Util { class CameraPosition; } } }
namespace Cloddy { namespace API { namespace VertexData { class Float3; } } }
namespace Cloddy { namespace API { namespace VertexData { class Int1; } } }

// Declare class ::Cloddy::API::VisibilityCriteria::ErrorMetrics::Components::ErrorTerm.

namespace Cloddy { namespace API { namespace VisibilityCriteria { namespace ErrorMetrics { namespace Components
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::VertexData::IVertexData;
  using Cloddy::Kernel::IMeshCallback;
  using Cloddy::Kernel::IProvider;
  
  // Use referenced classes.
  
  using Cloddy::API::Util::CameraPosition;
  using Cloddy::API::VertexData::Float3;
  using Cloddy::API::VertexData::Int1;
  
  /*!
   * @brief  This class is a utility class that performs computations that are common to error 
   *         metric components.
   * 
   * The ErrorTerm class holds references to commonly used vertex data containers (ie. for vertex 
   * positions,normal vectors,diffuse colors and bounding sphere radii.
   * 
   * An ErrorTerm object stored the indices of the following indices:
   *   - The vertex #V for which an error term is being computed.
   *   - The grand parent #G of the vertex #V.
   *   - The ancestor #A of the vertex #V.
   * The vertex indices can be used by IErrorMetricComponent instances for computing error terms.
   * 
   * Many error metric components compute similar terms;for example the eye vector or the 
   * interpolated vertex position.In order to avoid duplicated computations,the ErrorTerm provides 
   * means for computing and caching the most commonly used terms:
   *   - The eye vector (ie. a vector pointing from the vertex position to the camera).
   *   - The up vector (ie. a vector pointing from the interpolated vertex position to the actual 
   *   vertex position;note that this vector may actually point downwards in respect to elevation).
   *   - The dot product between the vertex normal vector and the eye vector.
   *   - The interpolated vertex position.
   *   - The interpolated vertex normal vector.
   *   - The interpolated vertex diffuse color.
   * 
   * The following vertex data semantics are used by this class (\e opt  means that the semantic 
   * will be used if present,\e req  means that the semantic must be present):
   *   - \e req  - Semantic::Position
   *   - \e req  - Semantic::Normal
   *   - \e req  - Semantic::Radius
   *   - \e req  - Semantic::DiffuseColor
   */
  class ErrorTerm : public virtual IMeshCallback
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Index of ancestor of #V.
     */
    int32 A;
    
    /*!
     * @brief  Holds the diffuse color for each terrain vertex.
     */
    Ptr<Int1> DiffuseColor;
    
    /*!
     * @brief  The dot product between the unit length eye vector and the vertex normal vector.
     */
    float32 DotEyeNormal;
    
    /*!
     * @brief  X-component of unit length eye vector (pointing from vertex position to camera 
     *         position).
     */
    float64 EyeX;
    
    /*!
     * @brief  Y-component of unit length eye vector (pointing from vertex position to camera 
     *         position).
     */
    float64 EyeY;
    
    /*!
     * @brief  Z-component of unit length eye vector (pointing from vertex position to camera 
     *         position).
     */
    float64 EyeZ;
    
    /*!
     * @brief  Index of grand-parent of #V.
     */
    int32 G;
    
    /*!
     * @brief  The interpolated vertex diffuse color.
     */
    int32 InterpolatedColor;
    
    /*!
     * @brief  X-coordinate of interpolated vertex normal vector.
     */
    float32 InterpolatedNormalX;
    
    /*!
     * @brief  Y-coordinate of interpolated vertex normal vector.
     */
    float32 InterpolatedNormalY;
    
    /*!
     * @brief  Z-coordinate of interpolated vertex normal vector.
     */
    float32 InterpolatedNormalZ;
    
    /*!
     * @brief  X-coordinate of interpolated vertex position.
     */
    float64 InterpolatedPositionX;
    
    /*!
     * @brief  Y-coordinate of interpolated vertex position.
     */
    float64 InterpolatedPositionY;
    
    /*!
     * @brief  Z-coordinate of interpolated vertex position.
     */
    float64 InterpolatedPositionZ;
    
    /*!
     * @brief  Holds the normal vector for each terrain vertex.
     */
    Ptr<Float3> Normal;
    
    /*!
     * @brief  Holds the position for each terrain vertex.
     */
    Ptr<IVertexData> Position;
    
    /*!
     * @brief  Holds the bounding sphere radius for each terrain vertex.
     */
    Ptr<IVertexData> Radius;
    
    /*!
     * @brief  Length of the unnormalized up vector (ie. the euclidean distance between the 
     *         interpolated and actual vertex positions).
     */
    float64 UpLength;
    
    /*!
     * @brief  Reciprocal of #UpLength.
     */
    float64 UpLengthReciprocal;
    
    /*!
     * @brief  Square length of the unnormalized up vector (ie. the euclidean distance between the 
     *         interpolated and actual vertex positions).
     */
    float64 UpLengthSqr;
    
    /*!
     * @brief  X-coordinate of the normalized up vector.
     */
    float32 UpX;
    
    /*!
     * @brief  Y-coordinate of the normalized up vector.
     */
    float32 UpY;
    
    /*!
     * @brief  Z-coordinate of the normalized up vector.
     */
    float32 UpZ;
    
    /*!
     * @brief  Index of vertex for which error metricses are applied.
     */
    int32 V;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of ErrorTerm.
     */
    ErrorTerm();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Resets the error metric kernel for a new vertex.
     * 
     * @param v Index of vertex for which error metricses will be computed.
     * @param g Index of grand parent of \e v .
     * @param a Index of ancestor of \e v .
     */
    void Begin(int32 v, int32 g, int32 a);
    
    virtual void BeginMeshAction(IProvider* provider);
    
    /*!
     * @brief  Computes the dot product between the unit length eye vector and the vertex normal 
     *         vector.
     * 
     * The dot product is stored in the #DotEyeNormal field.
     * 
     * @return The dot product.
     */
    float32 ComputeDotEyeNormal();
    
    /*!
     * @brief  Computes the unit length eye vector (vertex position to camera position).
     * 
     * The unit length eye vector is stored in the #EyeX,#EyeY and #EyeZ fields.
     */
    void ComputeEyeVector();
    
    /*!
     * @brief  Computes the interpolated vertex diffuse color.
     * 
     * The interpolated diffuse color is stored in the #InterpolatedColor field.
     * 
     * @return The interpolated diffuse color.
     */
    int32 ComputeInterpolatedVertexColor();
    
    /*!
     * @brief  Computes the interpolated vertex normal vector.
     * 
     * The interpolated vertex normal vector is stored in 
     * the #InterpolatedNormalX,#InterpolatedNormalY and #InterpolatedNormalZ fields.
     */
    void ComputeInterpolatedVertexNormal();
    
    /*!
     * @brief  Computes the interpolated vertex position.
     * 
     * The interpolated vertex position is stored in 
     * the #InterpolatedPositionX,#InterpolatedPositionY and #InterpolatedPositionZ fields.
     */
    void ComputeInterpolatedVertexPosition();
    
    /*!
     * @brief  Computes the vertex up vector.
     * 
     * The up vector is stored in the #UpX,#UpY and #UpZ fields.The length of the unnormalized up 
     * vector is stored in #UpLengthSqr and #UpLength.The reciprocal of the length is stored 
     * in #UpLengthReciprocal.
     */
    void ComputeUpVector();
    
    virtual void EndMeshAction();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The current camera position,in terrain-space.
     */
    Ptr<CameraPosition> camera;
    
    /*!
     * @brief  Has the interpolated vertex color been computed for the current vertex?
     */
    bool interpolatedVertexColorComputed;
    
    /*!
     * @brief  Has the interpolated vertex position been computed for the current vertex?
     */
    bool interpolatedVertexPositionComputed;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<ErrorTerm> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x20C87842;
    
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
      if ((ptr = IMeshCallback::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } } 

#endif
