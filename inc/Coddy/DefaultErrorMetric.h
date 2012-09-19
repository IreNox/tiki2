////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_VISIBILITYCRITERIA_ERRORMETRICS_DEFAULTERRORMETRIC_H
#define CLODDY_API_VISIBILITYCRITERIA_ERRORMETRICS_DEFAULTERRORMETRIC_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IErrorMetric.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace VertexData { class IVertexData; } } }
namespace Cloddy { namespace API { namespace VisibilityCriteria { namespace ErrorMetrics { namespace Lightings { class ILighting; } } } } }
namespace Cloddy { namespace Kernel { class IProvider; } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Util { class CameraPosition; } } }
namespace Cloddy { namespace API { namespace Util { namespace Colors { class HsvColorDistanceMetric; } } } }
namespace Cloddy { namespace API { namespace VertexData { class Float3; } } }
namespace Cloddy { namespace API { namespace VertexData { class Int1; } } }

// Declare class ::Cloddy::API::VisibilityCriteria::ErrorMetrics::DefaultErrorMetric.

namespace Cloddy { namespace API { namespace VisibilityCriteria { namespace ErrorMetrics
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::VertexData::IVertexData;
  using Cloddy::API::VisibilityCriteria::ErrorMetrics::Lightings::ILighting;
  using Cloddy::Kernel::IProvider;
  
  // Use referenced classes.
  
  using Cloddy::API::Util::CameraPosition;
  using Cloddy::API::Util::Colors::HsvColorDistanceMetric;
  using Cloddy::API::VertexData::Float3;
  using Cloddy::API::VertexData::Int1;
  
  /*!
   * @brief  A default implementation of the IErrorMetric interface.
   * 
   * This error metric has the following features:
   *   - <b>Backface culling</b>
   *   Vertices that lie on triangles that face away from the camera are treated as having a 
   *   terrain-space error of \c 0  (same functionality as BackfaceCullingErrorMetricComponent).
   *   - <b>Lighted color error metric</b>
   *   A lighted color error metric (ie. difference in diffuse color)is applied for each vertex (
   *   same functionality as LightedColorErrorMetricComponent).
   *   - <b>Positional error metric</b>
   *   A positional error metric (ie. difference in elevation)is applied for each vertex (same 
   *   functionality as PositionErrorMetricComponent).
   *   - <b>Anisotropic filtering</b>
   *   The lighted color error metric and positional error metric terms are combined 
   *   anisotropically (same functionality as AnisotropicErrorMetricComponent).
   *   - <b>Maximum triangle area</b>
   *   The maximum area of each mesh triangle can be defined in screen-space.This ensures that the 
   *   mesh has a minimum resolution everywhere (same functionality as RadiusErrorMetricComponent).
   * 
   * The following components of the CloddySDK are used by this class (\e opt  means that the 
   * component will be used if present,\e req  means that the component must be present):
   *   - \e opt  - ComponentIdsApi::Opt_Lighting
   * 
   * The following vertex data semantics are used by this class (\e opt  means that the semantic 
   * will be used if present,\e req  means that the semantic must be present):
   *   - \e req  - Semantic::Position
   *   - \e req  - Semantic::Normal
   *   - \e req  - Semantic::Radius
   *   - \e req  - Semantic::DiffuseColor
   */
  class DefaultErrorMetric : public virtual IErrorMetric
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The backface-culling threshold.
     * 
     * <pre>
     *    a := Angle between eye and normal vector
     *    t := Backface-culling threshold in range [0..1]
     *    Front-facing:
     *    -------------
     *    0   &lt;= a      &lt;  90?
     *    1   >= cos(a) >  -t
     *    Back-facing:
     *    ------------
     *    90? &lt;= a      &lt;= 180?
     *    -t  >= cos(a) >= -1
     * </pre>
     * The default value is <c>0.1</c>.
     * 
     * @return <b>[0..1]</b>  The backface-culling threshold.
     */
    float32 GetBackfaceCullingThreshold();
    
    /*!
     * @brief  The backface-culling threshold.
     * 
     * <pre>
     *    a := Angle between eye and normal vector
     *    t := Backface-culling threshold in range [0..1]
     *    Front-facing:
     *    -------------
     *    0   &lt;= a      &lt;  90?
     *    1   >= cos(a) >  -t
     *    Back-facing:
     *    ------------
     *    90? &lt;= a      &lt;= 180?
     *    -t  >= cos(a) >= -1
     * </pre>
     * The default value is <c>0.1</c>.
     * 
     * @param value <b>[0..1]</b>  The backface-culling threshold.
     */
    void SetBackfaceCullingThreshold(float32 value);
    
    /*!
     * @brief  Returns the used color distance metric.
     * 
     * @return <b>[not-null]</b>  The color distance metric object.
     */
    Ptr<HsvColorDistanceMetric> GetColorDistanceMetric();
    
    /*!
     * @brief  The maximum size of one mesh sector,in pixels.
     * 
     * The default value is \c 64 .
     * 
     * @return <b>[>0]</b>  The maximum sector size,in pixels.
     */
    float32 GetMaxSectorSize();
    
    /*!
     * @brief  The maximum size of one mesh sector,in pixels.
     * 
     * The default value is \c 64 .
     * 
     * @param value <b>[>0]</b>  The maximum sector size,in pixels.
     */
    void SetMaxSectorSize(float32 value);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of DefaultErrorMetric.
     */
    DefaultErrorMetric();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void BeginMeshAction(IProvider* provider);
    
    virtual float64 ComputeVertexError(int32 v, int32 g, int32 a);
    
    virtual void EndMeshAction();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The current backface culling threshold.
     */
    float32 backfaceCullingThreshold;
    
    /*!
     * @brief  The current camera position.
     */
    Ptr<CameraPosition> cameraPosition;
    
    /*!
     * @brief  The used color distance metric.
     */
    Ptr<HsvColorDistanceMetric> colorDistanceMetric;
    
    /*!
     * @brief  The diffuse color data container.
     */
    Ptr<Int1> diffuseColor;
    
    /*!
     * @brief  The current lighting term.
     */
    Ptr<ILighting> lighting;
    
    /*!
     * @brief  The current maximum sector size.
     */
    float32 maxSectorSize;
    
    /*!
     * @brief  The normal vector data container.
     */
    Ptr<Float3> normal;
    
    /*!
     * @brief  The vertex position data container.
     */
    Ptr<IVertexData> position;
    
    /*!
     * @brief  Reciprocal of #maxSectorSize.
     */
    float32 rMaxSectorSize;
    
    /*!
     * @brief  The bounding sphere radius data container.
     */
    Ptr<IVertexData> radius;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<DefaultErrorMetric> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xB46DB5B7;
    
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
      if ((ptr = IErrorMetric::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } 

#endif
