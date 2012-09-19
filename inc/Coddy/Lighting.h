////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_VISIBILITYCRITERIA_ERRORMETRICS_LIGHTINGS_LIGHTING_H
#define CLODDY_API_VISIBILITYCRITERIA_ERRORMETRICS_LIGHTINGS_LIGHTING_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/ILighting.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace VisibilityCriteria { namespace ErrorMetrics { namespace Lightings { class ILightingVisitor; } } } } }
namespace Cloddy { namespace Kernel { class IProvider; } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace VisibilityCriteria { namespace ErrorMetrics { namespace Lightings { class FogLighting; } } } } }
namespace Cloddy { namespace API { namespace VisibilityCriteria { namespace ErrorMetrics { namespace Lightings { class LambertianLighting; } } } } }

// Declare class ::Cloddy::API::VisibilityCriteria::ErrorMetrics::Lightings::Lighting.

namespace Cloddy { namespace API { namespace VisibilityCriteria { namespace ErrorMetrics { namespace Lightings
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Kernel::IProvider;
  
  /*!
   * @brief  Abstract base class for ILighting implementations.
   */
  class Lighting : public virtual ILighting
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    static Ptr<FogLighting> Fog();
    
    /*!
     * @brief  Creates a new instance of FogLighting that uses an exponential fog term.
     * 
     * @param fogColor The fog color.
     * @param isRangeBased Apply range based fog (\c true )or non range based fog (\c false ).
     * @param isSquared Use the squared version of the exponential fog term?
     * @param density The fog density coefficient.
     * 
     * @return <b>[not-null]</b>  The created FogLighting object.
     */
    static Ptr<FogLighting> FogExponential(int32 fogColor, bool isRangeBased, bool isSquared, float32 density);
    
    /*!
     * @brief  Creates a new instance of FogLighting that uses a linear fog term.
     * 
     * @param fogColor The fog color.
     * @param isRangeBased Apply range based fog (\c true )or non range based fog (\c false ).
     * @param start Start distance of fog (ie. zero density).
     * @param end End distance of fog (ie. maximum density).
     * 
     * @return <b>[not-null]</b>  The created FogLighting object.
     */
    static Ptr<FogLighting> FogLinear(int32 fogColor, bool isRangeBased, float32 start, float32 end);
    
    /*!
     * @brief  Creates a new instance of LambertianLighting.
     * 
     * @param lightCount <b>[>=0]</b>  The number of directional lights.
     * 
     * @return <b>[not-null]</b>  The created LambertianLighting object.
     */
    static Ptr<LambertianLighting> Lambertian(int32 lightCount);
    
    /*!
     * @brief  Creates a new instance of LambertianLighting.
     * 
     * @param lightCount <b>[>=0]</b>  The number of directional lights.
     * @param ambient The ambient light color.
     * 
     * @return <b>[not-null]</b>  The created LambertianLighting object.
     */
    static Ptr<LambertianLighting> Lambertian(int32 lightCount, int32 ambient);
    
    virtual void Accept(ILightingVisitor* visitor, Object* userData) = 0;
    
    virtual void BeginMeshAction(IProvider* provider);
    
    virtual Ptr<ILighting> Combine(ILighting* lighting);
    
    virtual int32 ComputeLighting(float64 positionX, float64 positionY, float64 positionZ, float32 normalX, float32 normalY, float32 normalZ, int32 diffuse) = 0;
    
    virtual void EndMeshAction();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<Lighting> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x64EA1F5;
    
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
      if ((ptr = ILighting::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } } 

#endif
