////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_BRUSHES_IBRUSH_H
#define CLODDY_API_HEIGHTMAPS_BRUSHES_IBRUSH_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/ITerrainSlopeDependant.h"

// Forward declare referenced structures.

namespace Cloddy { namespace Core { namespace Math { struct Fraction; } } }

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Brushes { class IBrushMask; } } } }
namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleBuffers { class ISampleBuffer; } } } }

// Declare interface ::Cloddy::API::Heightmaps::Brushes::IBrush.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Brushes
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced structures.
  
  using Cloddy::Core::Math::Fraction;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Heightmaps::SampleBuffers::ISampleBuffer;
  
  /*!
   * @brief  Base interface for heightmap brushes.
   * 
   * A heightmap brush is used to modify the samples of a heightmap region.
   */
  class NO_VTABLE IBrush : public virtual ITerrainSlopeDependant
  {
    // ---------------------------------------------------------------------------------------------
    // Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Does this brush modify diffuse colors?
     * 
     * @return \c true  if this brush modifies diffuse color values,\c false  it it does not.
     */
    virtual bool DoesModifyColor() = 0;
    
    /*!
     * @brief  Does this brush modify detail channel values?
     * 
     * @return \c true  if this brush modifies detail channel values,\c false  it it does not.
     */
    virtual bool DoesModifyDetail() = 0;
    
    /*!
     * @brief  Does this brush modify displacement values?
     * 
     * @return \c true  if this brush modifies displacement values,\c false  it it does not.
     */
    virtual bool DoesModifyDisplacement() = 0;
    
    /*!
     * @brief  Does this brush modify elevation values?
     * 
     * @return \c true  if this brush modifies elevation values,\c false  it it does not.
     */
    virtual bool DoesModifyElevation() = 0;
    
    /*!
     * @brief  Height of this brush,in heightmap samples.
     * 
     * @return <b>[>0]</b>  The brush height.
     */
    virtual int32 GetHeight() = 0;
    
    /*!
     * @brief  Sets the strength of this brush.
     * 
     * The brush strength indicates how intense the modifications to the heightmap will be.The 
     * effect of this value is dependant on the actual IBrush implementation.A value of \c 0  means 
     * that the brush will not affect the heightmap at all and a value of \c 1024  means the the 
     * brush will affect the heightmap at maximum strength.
     * 
     * The brush strength is designed as a tool for artists working with tablets and pressure 
     * sensitive pens.
     * 
     * The default value is \c 1024  (ie. maximum strength).
     * 
     * @return The relative strength of this brush.
     */
    virtual int32 GetStrength() = 0;
    
    /*!
     * @brief  Sets the strength of this brush.
     * 
     * The brush strength indicates how intense the modifications to the heightmap will be.The 
     * effect of this value is dependant on the actual IBrush implementation.A value of \c 0  means 
     * that the brush will not affect the heightmap at all and a value of \c 1024  means the the 
     * brush will affect the heightmap at maximum strength.
     * 
     * The brush strength is designed as a tool for artists working with tablets and pressure 
     * sensitive pens.
     * 
     * The default value is \c 1024  (ie. maximum strength).
     * 
     * @param value The relative strength of this brush.
     */
    virtual void SetStrength(int32 value) = 0;
    
    /*!
     * @brief  Width of this brush,in heightmap samples.
     * 
     * @return <b>[>0]</b>  The brush width.
     */
    virtual int32 GetWidth() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Applies this brush to the heightmap samples in the given buffer.
     * 
     * @param sampleBuffer <b>[not-null]</b>  The heightmap sample buffer.
     * @param brushMask Optional brush mask to use.
     */
    virtual void Apply(ISampleBuffer* sampleBuffer, IBrushMask* brushMask) = 0;
    
    /*!
     * @brief  Scales this brush.
     * 
     * @param factor The scale factor.
     * 
     * @return <b>[not-null]</b>  The scaled brush.
     */
    virtual Ptr<IBrush> Scale(const Fraction& factor) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IBrush> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xBBFD1959;
    
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
      if ((ptr = ITerrainSlopeDependant::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
} } } } 

#endif
