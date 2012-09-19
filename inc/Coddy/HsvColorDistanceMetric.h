////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_UTIL_COLORS_HSVCOLORDISTANCEMETRIC_H
#define CLODDY_API_UTIL_COLORS_HSVCOLORDISTANCEMETRIC_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IColorDistanceMetric.h"

// Declare class ::Cloddy::API::Util::Colors::HsvColorDistanceMetric.

namespace Cloddy { namespace API { namespace Util { namespace Colors
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  A color distance metric that compares color values in HSV color space.
   */
  class HsvColorDistanceMetric : public virtual IColorDistanceMetric
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Upper threshold for absolute brightness difference.
     * 
     * An absolute brightness difference of a value greater than or equal to this value will result 
     * in a maximum brightness color error term (ie. <c>1.0</c>).
     * 
     * The default value is \c 255 .
     * 
     * @return <b>[0..255]</b>  The upper threshold for absolute brightness difference.
     */
    int32 GetBrightnessDeltaMax();
    
    /*!
     * @brief  Upper threshold for absolute brightness difference.
     * 
     * An absolute brightness difference of a value greater than or equal to this value will result 
     * in a maximum brightness color error term (ie. <c>1.0</c>).
     * 
     * The default value is \c 255 .
     * 
     * @param value <b>[0..255]</b>  The upper threshold for absolute brightness difference.
     */
    void SetBrightnessDeltaMax(int32 value);
    
    /*!
     * @brief  Lower threshold for absolute brightness difference.
     * 
     * An absolute brightness difference of a value less than or equal to this value will result in 
     * a minimum brightness color error term (ie. <c>0.0</c>).
     * 
     * The default value is \c 0 .
     * 
     * @return <b>[0..255]</b>  The lower threshold for absolute brightness difference.
     */
    int32 GetBrightnessDeltaMin();
    
    /*!
     * @brief  Lower threshold for absolute brightness difference.
     * 
     * An absolute brightness difference of a value less than or equal to this value will result in 
     * a minimum brightness color error term (ie. <c>0.0</c>).
     * 
     * The default value is \c 0 .
     * 
     * @param value <b>[0..255]</b>  The lower threshold for absolute brightness difference.
     */
    void SetBrightnessDeltaMin(int32 value);
    
    /*!
     * @brief  Upper threshold for absolute hue difference.
     * 
     * An absolute hue difference of a value greater than or equal to this value will result in a 
     * maximum hue color error term (ie. <c>1.0</c>).
     * 
     * The default value is \c 256  (ie. 60 degrees).
     * 
     * @return <b>[0..768]</b>  The upper threshold for absolute hue difference (768 :=180 degrees)
     */
    int32 GetHueDeltaMax();
    
    /*!
     * @brief  Upper threshold for absolute hue difference.
     * 
     * An absolute hue difference of a value greater than or equal to this value will result in a 
     * maximum hue color error term (ie. <c>1.0</c>).
     * 
     * The default value is \c 256  (ie. 60 degrees).
     * 
     * @param value <b>[0..768]</b>  The upper threshold for absolute hue difference (768 :=180 
     * degrees)
     */
    void SetHueDeltaMax(int32 value);
    
    /*!
     * @brief  Lower threshold for absolute hue difference.
     * 
     * An absolute hue difference of a value less than or equal to this value will result in a 
     * minimum hue color error term (ie. <c>0.0</c>).
     * 
     * The default value is \c 0 .
     * 
     * @return <b>[0..768]</b>  The lower threshold for absolute hue difference (768 :=180 degrees)
     */
    int32 GetHueDeltaMin();
    
    /*!
     * @brief  Lower threshold for absolute hue difference.
     * 
     * An absolute hue difference of a value less than or equal to this value will result in a 
     * minimum hue color error term (ie. <c>0.0</c>).
     * 
     * The default value is \c 0 .
     * 
     * @param value <b>[0..768]</b>  The lower threshold for absolute hue difference (768 :=180 
     * degrees)
     */
    void SetHueDeltaMin(int32 value);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of HsvColorDistanceMetric.
     */
    HsvColorDistanceMetric();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual float64 ComputeColorDistance(int32 colorA, int32 colorB);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Upper threshold for absolute brightness difference.
     */
    int32 brightnessDeltaMax;
    
    /*!
     * @brief  Lower threshold for absolute brightness difference.
     */
    int32 brightnessDeltaMin;
    
    /*!
     * @brief  Upper threshold for absolute hue difference.
     */
    int32 hueDeltaMax;
    
    /*!
     * @brief  Lower threshold for absolute hue difference.
     */
    int32 hueDeltaMin;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<HsvColorDistanceMetric> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xD8D8CEDB;
    
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
      if ((ptr = IColorDistanceMetric::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } 

#endif
