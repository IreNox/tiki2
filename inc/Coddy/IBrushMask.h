////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_BRUSHES_IBRUSHMASK_H
#define CLODDY_API_HEIGHTMAPS_BRUSHES_IBRUSHMASK_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/ITerrainSlopeDependant.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Imaging { class IImageReader; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Heightmaps { class HeightmapRegion; } } }

// Declare interface ::Cloddy::API::Heightmaps::Brushes::IBrushMask.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Brushes
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Imaging::IImageReader;
  
  // Use referenced classes.
  
  using Cloddy::API::Heightmaps::HeightmapRegion;
  
  /*!
   * @brief  Base interface for classes that represent a brush mask.
   * 
   * Brush masks are used to weight the effect of a brush being applied to a heightmap region on a 
   * per sample basis.
   */
  class NO_VTABLE IBrushMask : public virtual ITerrainSlopeDependant
  {
    // ---------------------------------------------------------------------------------------------
    // Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Returns the height of this brush mask.
     * 
     * @return <b>[>0]</b>  The brush mask height,in samples.
     */
    virtual int32 GetHeight() = 0;
    
    /*!
     * @brief  Returns the width of this brush mask.
     * 
     * @return <b>[>0]</b>  The brush mask width,in samples.
     */
    virtual int32 GetWidth() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Returns a brush mask that buffers the mask values of this brush mask in a memory 
     *         buffer.
     * 
     * @return <b>[not-null]</b>  The resulting brush mask.
     */
    virtual Ptr<IBrushMask> Buffer() = 0;
    
    /*!
     * @brief  Returns the brush mask value for the given sample coordinates.
     * 
     * @param x <b>[0..#GetWidth-1]</b>  X-coordinate of brush mask sample to return.
     * @param y <b>[0..#GetHeight-1]</b>  X-coordinate of brush mask sample to return.
     * 
     * @return <b>[0..32768]</b>  The brush mask value (a value of \c 0  means the brush will have 
     * no effect on the heightmap region,a value of \c 32768  means the brush will have its maximum 
     * effect.
     */
    virtual int32 GetMaskValue(int32 x, int32 y) = 0;
    
    /*!
     * @brief  Returns a brush mask that is the inverse of this brush mask.
     * 
     * @return <b>[not-null]</b>  The resulting brush mask.
     */
    virtual Ptr<IBrushMask> Invert() = 0;
    
    /*!
     * @brief  Modulates this brush mask with the given one.
     * 
     * @param mask <b>[not-null]</b>  The brush mask.
     * 
     * @return <b>[not-null]</b>  The resulting brush mask.
     */
    virtual Ptr<IBrushMask> Modulate(IBrushMask* mask) = 0;
    
    /*!
     * @brief  Prepares this brush mask region for the given heightmap region.
     * 
     * The given \e region  must have the same size as this brush mask.
     * 
     * In most cases,a brush mask does not need to be prepared before a brush is applied to a 
     * heightmap region.This only applies to more sophisticated brush mask implementations,eg. a 
     * slope/elevation based filter mask.
     * 
     * @param region <b>[not-null]</b>  The heightmap region for which to prepare this brush mask.
     */
    virtual void Prepare(HeightmapRegion* region) = 0;
    
    /*!
     * @brief  Reads the samples of this brush mask as a 16-bit greyscale image (
     *         see PixelFormat::PixelFormat_Grayscale16).
     * 
     * @return <b>[not-null]</b>  The image reader.
     */
    virtual Ptr<IImageReader> ReadAsImage() = 0;
    
    /*!
     * @brief  Returns a scaled version of this brush mask.
     * 
     * @param width <b>[>0]</b>  The scaled brush mask width,in samples.
     * @param height <b>[>0]</b>  The scaled brush mask height,in samples.
     * 
     * @return <b>[not-null]</b>  The resulting brush mask.
     */
    virtual Ptr<IBrushMask> Scale(int32 width, int32 height) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IBrushMask> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x8C538F59;
    
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
