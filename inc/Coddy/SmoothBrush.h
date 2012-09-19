////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_BRUSHES_SMOOTHBRUSH_H
#define CLODDY_API_HEIGHTMAPS_BRUSHES_SMOOTHBRUSH_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/BrushBase.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Brushes { class IBrush; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleBuffers { class ColorBuffer; } } } }
namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleBuffers { class DisplacementBuffer; } } } }
namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleBuffers { class ElevationBuffer; } } } }

// Declare class ::Cloddy::API::Heightmaps::Brushes::SmoothBrush.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Brushes
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced classes.
  
  using Cloddy::API::Heightmaps::SampleBuffers::ColorBuffer;
  using Cloddy::API::Heightmaps::SampleBuffers::DisplacementBuffer;
  using Cloddy::API::Heightmaps::SampleBuffers::ElevationBuffer;
  
  /*!
   * @brief  This brush applies a smoothing filter to the samples in the given heightmap region.
   */
  class SmoothBrush : public BrushBase
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual bool DoesModifyColor();
    
    virtual bool DoesModifyDetail();
    
    virtual bool DoesModifyDisplacement();
    
    virtual bool DoesModifyElevation();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of SmoothBrush.
     * 
     * The brush will modify elevation,diffuse color and displacement values.
     * 
     * @param size <b>[>0]</b>  The size of this brush (both width and height).
     */
    SmoothBrush(int32 size);
    
    /*!
     * @brief  Creates a new instance of SmoothBrush.
     * 
     * @param size <b>[>0]</b>  The size of this brush (both width and height).
     * @param doesModifyElevation Shall the brush modify elevation values?
     * @param doesModifyColor Shall the brush modify diffuse color values?
     * @param doesModifyDisplacement Shall the brush modify displacement values?
     */
    SmoothBrush(int32 size, bool doesModifyElevation, bool doesModifyColor, bool doesModifyDisplacement);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void Visit(ElevationBuffer* buffer);
    
    virtual void Visit(DisplacementBuffer* buffer);
    
    virtual void Visit(ColorBuffer* buffer);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
  protected:
    
    virtual Ptr<IBrush> DoScale(int32 numerator, int32 denominator);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Does this brush modify diffuse color values?
     */
    bool doesModifyColor;
    
    /*!
     * @brief  Does this brush modify displacement values?
     */
    bool doesModifyDisplacement;
    
    /*!
     * @brief  Does this brush modify elevation values?
     */
    bool doesModifyElevation;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Mixes the given color values.
     * 
     * @param center The center color value.
     * @param left The left color value.
     * @param right The right color value.
     * @param above The above color value.
     * @param down The down color value.
     * @param factor The scale factor in the range <c>[0..65536]</c>.
     * 
     * @return The resulting color value.
     */
    static int32 MixColor(int32 center, int32 left, int32 right, int32 above, int32 down, int32 factor);
    
    /*!
     * @brief  Mixes the given values.
     * 
     * @param center The center value.
     * @param left The left value.
     * @param right The right value.
     * @param above The above value.
     * @param down The down value.
     * @param factor The scale factor in the range <c>[0..65536]</c>.
     * 
     * @return The resulting value.
     */
    static int32 MixScalar(int32 center, int32 left, int32 right, int32 above, int32 down, int32 factor);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<SmoothBrush> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x506B444E;
    
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
      if ((ptr = BrushBase::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } 

#endif
