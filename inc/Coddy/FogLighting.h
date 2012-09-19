////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_VISIBILITYCRITERIA_ERRORMETRICS_LIGHTINGS_FOGLIGHTING_H
#define CLODDY_API_VISIBILITYCRITERIA_ERRORMETRICS_LIGHTINGS_FOGLIGHTING_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/Lighting.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace VisibilityCriteria { namespace ErrorMetrics { namespace Lightings { class ILightingVisitor; } } } } }
namespace Cloddy { namespace Kernel { class IProvider; } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Util { class CameraPosition; } } }

// Declare class ::Cloddy::API::VisibilityCriteria::ErrorMetrics::Lightings::FogLighting.

namespace Cloddy { namespace API { namespace VisibilityCriteria { namespace ErrorMetrics { namespace Lightings
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Kernel::IProvider;
  
  // Use referenced classes.
  
  using Cloddy::API::Util::CameraPosition;
  
  /*!
   * @brief  An implementation of the ILighting interface that performs fog computations on the 
   *         input color.
   * 
   * The following fog formulae are supported by the FogLighting class:
   *   - Linear fog:
   *   <c>f :=(end - d)/(end - start)</c>
   *   - Exponential fog:
   *   <c>f :=1 /exp(d *density)</c>
   *   - Squared exponential fog:
   *   <c> f :=1 /exp(sqr(d *density))</c>
   * where \c f  is the fog blend factor (\c 0  results in fog color,\c 1  results in pixel color),
   * \c d  is the distance of the pixel to the scene camera (either range based or z based,
   * see #GetRangeBased),\c end  /\c start  depict the linear fog range and \c density  defines the 
   * exponential fog density.
   * 
   * The final pixel color \c final  is computed from the fog color \c fog  and the plain pixel 
   * color \c pixel  as follows:
   * <pre>
   *       final := fog * (1 - f) + pixel * f
   * </pre>
   */
  class FogLighting : public Lighting
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The fog color.
     * 
     * The default value is \c 0 ,ie. transparent black.
     * 
     * @return The fog color,as a 32-bit ARGB color value.
     */
    int32 GetFogColor();
    
    /*!
     * @brief  The fog color.
     * 
     * The default value is \c 0 ,ie. transparent black.
     * 
     * @param value The fog color,as a 32-bit ARGB color value.
     */
    void SetFogColor(int32 value);
    
    /*!
     * @brief  Use range based fog,ie. euclidean distance to camera,or z based fog (ie. 
     *         Z-coordinate of vertex in camera-space)?
     * 
     * The default value is \c false .
     * 
     * @return \c true  for range based fog,\c false  for z based fog.
     */
    bool GetRangeBased();
    
    /*!
     * @brief  Use range based fog,ie. euclidean distance to camera,or z based fog (ie. 
     *         Z-coordinate of vertex in camera-space)?
     * 
     * The default value is \c false .
     * 
     * @param value \c true  for range based fog,\c false  for z based fog.
     */
    void SetRangeBased(bool value);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void Accept(ILightingVisitor* visitor, Object* userData);
    
    virtual void BeginMeshAction(IProvider* provider);
    
    virtual int32 ComputeLighting(float64 positionX, float64 positionY, float64 positionZ, float32 normalX, float32 normalY, float32 normalZ, int32 diffuse);
    
    virtual void EndMeshAction();
    
    /*!
     * @brief  Uses the exponential resp. squared exponential fog formula.
     * 
     * @param isSquared Use the squared exponential fog formula?
     * @param density <b>[>=0]</b>  The fog density value.
     * 
     * @return <b>[not-null]</b>  this
     */
    Ptr<FogLighting> SetExponential(bool isSquared, float32 density);
    
    /*!
     * @brief  Uses the linear fog formula.
     * 
     * @param start Start distance for fog.
     * @param end End distance for fog.
     * 
     * @return <b>[not-null]</b>  this
     */
    Ptr<FogLighting> SetLinear(float32 start, float32 end);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  First fog coefficient.
     */
    float32 a;
    
    /*!
     * @brief  Second fog coefficient.
     */
    float32 b;
    
    /*!
     * @brief  The current camera position.
     */
    Ptr<CameraPosition> cameraPosition;
    
    /*!
     * @brief  The fog color.
     */
    int32 fogColor;
    
    /*!
     * @brief  Apply linear fog formula (\c true )or exponential fog formula (\c false )?
     */
    bool isLinear;
    
    /*!
     * @brief  Use range based fog,ie. euclidean distance to camera (\c true ),or z based fog (ie. 
     *         Z-coordinate of vertex in camera-space)?
     */
    bool isRangeBased;
    
    /*!
     * @brief  Use squared distance in fog formula?
     */
    bool isSquared;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
  public:
    
    FogLighting();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<FogLighting> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xAFBCACB;
    
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
      if ((ptr = Lighting::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } } 

#endif
