////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_VISIBILITYCRITERIA_ERRORMETRICS_LIGHTINGS_LAMBERTIANLIGHTING_H
#define CLODDY_API_VISIBILITYCRITERIA_ERRORMETRICS_LIGHTINGS_LAMBERTIANLIGHTING_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/Lighting.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace VisibilityCriteria { namespace ErrorMetrics { namespace Lightings { class ILightingVisitor; } } } } }

// Declare class ::Cloddy::API::VisibilityCriteria::ErrorMetrics::Lightings::LambertianLighting.

namespace Cloddy { namespace API { namespace VisibilityCriteria { namespace ErrorMetrics { namespace Lightings
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  An ILighting implementation that applies lambertian lighting to vertex colors (
   *         directional lights and ambient).
   */
  class LambertianLighting : public Lighting
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The ambient color.
     * 
     * @return The ambient color,as an 32-bit ARGB color value.
     */
    int32 GetAmbient();
    
    /*!
     * @brief  The ambient color.
     * 
     * @param value The ambient color,as an 32-bit ARGB color value.
     */
    void SetAmbient(int32 value);
    
    /*!
     * @brief  Number of directional lights.
     * 
     * @return <b>[>=0]</b>  The number of directional lights.
     */
    int32 GetLightCount();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of this class.
     * 
     * @param lightCount <b>[>=0]</b>  Number of directional lights.
     */
    LambertianLighting(int32 lightCount);
    
    /*!
     * @brief  Creates a new instance of this class.
     * 
     * @param lightCount <b>[>=0]</b>  Number of directional lights.
     * @param ambient The ambient light color.
     */
    LambertianLighting(int32 lightCount, int32 ambient);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void Accept(ILightingVisitor* visitor, Object* userData);
    
    virtual int32 ComputeLighting(float64 positionX, float64 positionY, float64 positionZ, float32 normalX, float32 normalY, float32 normalZ, int32 diffuse);
    
    /*!
     * @brief  Returns wether the given directional light is enabled or disabled.
     * 
     * @param index <b>[0..#GetLightCount-1]</b>  Index of directional light.
     * 
     * @return \c true  if the light is enabled,\c false  if it is disabled.
     */
    bool IsLightEnabled(int32 index);
    
    /*!
     * @brief  Sets the \e index -th directional light.
     * 
     * @param index <b>[0..#GetLightCount-1]</b>  Index of directional light.
     * @param directionX X-component of direction vector in terrain-space (will be normalized if 
     * necessary).
     * @param directionY Y-component of direction vector in terrain-space (will be normalized if 
     * necessary).
     * @param directionZ Z-component of direction vector in terrain-space (will be normalized if 
     * necessary).
     * @param color The light color.
     * 
     * @return <b>[not-null]</b>  this
     */
    Ptr<LambertianLighting> SetLight(int32 index, float32 directionX, float32 directionY, float32 directionZ, int32 color);
    
    /*!
     * @brief  Enables or disabled the given directional light.
     * 
     * @param index <b>[0..#GetLightCount-1]</b>  Index of the directional light to enable/disable.
     * @param enabled \c true  to enable the light,\c false  to disable it.
     * 
     * @return <b>[not-null]</b>  this
     */
    Ptr<LambertianLighting> SetLightEnabled(int32 index, bool enabled);
    
    /*!
     * @brief  Enables or disables all directional lights.
     * 
     * @param enabled \c true  to enable all lights,\c false  to disable them.
     * 
     * @return <b>[not-null]</b>  this
     */
    Ptr<LambertianLighting> SetLightEnabledAll(bool enabled);
    
    /*!
     * @brief  Sets the enabled state of all directional lights (up to a #GetLightCount of 64).
     * 
     * If the LambertianLighting object has more than 64 directional lights,only the enabled states 
     * of the first 64 will be updated.
     * 
     * @param enabledMask The bitmask that holds the enabled state for each directional light.The 
     * least significant bit represents the zeroth directional light.
     * 
     * @return <b>[not-null]</b>  this
     */
    Ptr<LambertianLighting> SetLightsEnabled(int64 enabledMask);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The ambient color.
     */
    int32 ambient;
    
    /*!
     * @brief  Holds the enabled flags per light.
     */
    Array<bool> enabled;
    
    /*!
     * @brief  Color of directional light.
     */
    Array<int32> lightColor;
    
    /*!
     * @brief  The number of directional lights.
     */
    int32 lightCount;
    
    /*!
     * @brief  X-component of direction vector of directional light.
     */
    Array<float32> lightDirectionX;
    
    /*!
     * @brief  Y-component of direction vector of directional light.
     */
    Array<float32> lightDirectionY;
    
    /*!
     * @brief  Z-component of direction vector of directional light.
     */
    Array<float32> lightDirectionZ;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<LambertianLighting> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x82763C32;
    
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
