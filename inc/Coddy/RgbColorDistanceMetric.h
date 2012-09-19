////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_UTIL_COLORS_RGBCOLORDISTANCEMETRIC_H
#define CLODDY_API_UTIL_COLORS_RGBCOLORDISTANCEMETRIC_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IColorDistanceMetric.h"

// Declare class ::Cloddy::API::Util::Colors::RgbColorDistanceMetric.

namespace Cloddy { namespace API { namespace Util { namespace Colors
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  A color distance metric that compares color values in RGB color space.
   */
  class RgbColorDistanceMetric : public virtual IColorDistanceMetric
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Weight of the blue color channel.
     * 
     * The default value is \c 11 .
     * 
     * @return <b>[>0]</b>  The blue color channel weight.
     */
    int32 GetWeightBlue();
    
    /*!
     * @brief  Weight of the blue color channel.
     * 
     * The default value is \c 11 .
     * 
     * @param value <b>[>0]</b>  The blue color channel weight.
     */
    void SetWeightBlue(int32 value);
    
    /*!
     * @brief  Weight of the green color channel.
     * 
     * The default value is \c 59 .
     * 
     * @return <b>[>0]</b>  The green color channel weight.
     */
    int32 GetWeightGreen();
    
    /*!
     * @brief  Weight of the green color channel.
     * 
     * The default value is \c 59 .
     * 
     * @param value <b>[>0]</b>  The green color channel weight.
     */
    void SetWeightGreen(int32 value);
    
    /*!
     * @brief  Weight of the red color channel.
     * 
     * The default value is \c 30 .
     * 
     * @return <b>[>0]</b>  The red color channel weight.
     */
    int32 GetWeightRed();
    
    /*!
     * @brief  Weight of the red color channel.
     * 
     * The default value is \c 30 .
     * 
     * @param value <b>[>0]</b>  The red color channel weight.
     */
    void SetWeightRed(int32 value);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of RgbColorDistanceMetric.
     */
    RgbColorDistanceMetric();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual float64 ComputeColorDistance(int32 colorA, int32 colorB);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Weight of the blue color channel.
     */
    int32 weightBlue;
    
    /*!
     * @brief  Weight of the green color channel.
     */
    int32 weightGreen;
    
    /*!
     * @brief  Weight of the red color channel.
     */
    int32 weightRed;
    
    /*!
     * @brief  The sum of all color channel weights.
     */
    int32 weightSum;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Computes the color channel weight sum.
     */
    void ComputeWeightSum();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<RgbColorDistanceMetric> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xFE2829E9;
    
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
