////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_PROCEDURAL_CELLULARNOISEGENERATOR_H
#define CLODDY_API_PROCEDURAL_CELLULARNOISEGENERATOR_H

#include "CodeX/System.h"

// Declare class ::Cloddy::API::Procedural::CellularNoiseGenerator.

namespace Cloddy { namespace API { namespace Procedural
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  This class is a generator for cellular noise.
   */
  class CellularNoiseGenerator : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Distance to the nearest feature point.
     */
    float64 F1;
    
    /*!
     * @brief  Distance to the second nearest feature point.
     */
    float64 F2;
    
    /*!
     * @brief  Distance to the third nearest feature point.
     */
    float64 F3;
    
    /*!
     * @brief  Distance to the fourth nearest feature point.
     */
    float64 F4;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Computes a cellular noise sample.
     * 
     * @param x Input X-coordinate.
     * @param y Input Y-coordinate.
     * @param z Input Z-coordinate.
     * 
     * @return <b>[>=0]</b>  The noise value.
     */
    float64 Compute1(float64 x, float64 y, float64 z);
    
    /*!
     * @brief  Computes a cellular noise sample.
     * 
     * @param x Input X-coordinate.
     * @param y Input Y-coordinate.
     * @param z Input Z-coordinate.
     * 
     * @return <b>[>=0]</b>  The noise value.
     */
    float64 Compute2(float64 x, float64 y, float64 z);
    
    /*!
     * @brief  Computes a cellular noise sample.
     * 
     * @param x Input X-coordinate.
     * @param y Input Y-coordinate.
     * @param z Input Z-coordinate.
     * 
     * @return <b>[>=0]</b>  The noise value.
     */
    float64 Compute3(float64 x, float64 y, float64 z);
    
    /*!
     * @brief  Computes a cellular noise sample.
     * 
     * @param x Input X-coordinate.
     * @param y Input Y-coordinate.
     * @param z Input Z-coordinate.
     * 
     * @return <b>[>=0]</b>  The noise value.
     */
    float64 Compute4(float64 x, float64 y, float64 z);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Distribution table of feature points in space.
     */
    static const Array<int32> PoissonCount;
    
    /*!
     * @brief  Precomputed value that is used during computation.
     */
    float64 dx;
    
    /*!
     * @brief  Precomputed value that is used during computation.
     */
    float64 dy;
    
    /*!
     * @brief  Precomputed value that is used during computation.
     */
    float64 dz;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Processes the features points in the given feature space cube and updates the 
     *         distance #F1 accordingly.
     * 
     * @param xi X-coordinate of feature space cube.
     * @param yi Y-coordinate of feature space cube.
     * @param zi Z-coordinate of feature space cube.
     */
    void AddSamples1(int64 xi, int64 yi, int64 zi);
    
    /*!
     * @brief  Processes the features points in the given feature space cube and updates the 
     *         distances #F1 and #F2 accordingly.
     * 
     * @param xi X-coordinate of feature space cube.
     * @param yi Y-coordinate of feature space cube.
     * @param zi Z-coordinate of feature space cube.
     */
    void AddSamples2(int64 xi, int64 yi, int64 zi);
    
    /*!
     * @brief  Processes the features points in the given feature space cube and updates the 
     *         distances #F1,#F2 and #F3 accordingly.
     * 
     * @param xi X-coordinate of feature space cube.
     * @param yi Y-coordinate of feature space cube.
     * @param zi Z-coordinate of feature space cube.
     */
    void AddSamples3(int64 xi, int64 yi, int64 zi);
    
    /*!
     * @brief  Processes the features points in the given feature space cube and updates the 
     *         distances #F1,#F2,#F3 and #F4 accordingly.
     * 
     * @param xi X-coordinate of feature space cube.
     * @param yi Y-coordinate of feature space cube.
     * @param zi Z-coordinate of feature space cube.
     */
    void AddSamples4(int64 xi, int64 yi, int64 zi);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
  public:
    
    CellularNoiseGenerator();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<CellularNoiseGenerator> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x58306EDA;
    
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
