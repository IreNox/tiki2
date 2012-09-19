////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_BRUSHES_COLORIZEBRUSH_H
#define CLODDY_API_HEIGHTMAPS_BRUSHES_COLORIZEBRUSH_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/ColorOp.h"

// Include referenced classes.

#include "Cloddy/BrushBase.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Brushes { class IBrush; } } } }
namespace Cloddy { namespace API { namespace Heightmaps { namespace Brushes { class IBrushMask; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleBuffers { class ColorBuffer; } } } }

// Declare class ::Cloddy::API::Heightmaps::Brushes::ColorizeBrush.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Brushes
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced classes.
  
  using Cloddy::API::Heightmaps::SampleBuffers::ColorBuffer;
  
  /*!
   * @brief  This brush combines the diffuse color values of a heightmap region with the color 
   *         values of a given sample buffer using a configured color operation.
   */
  class ColorizeBrush : public BrushBase
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The base color.
     * 
     * The color values read from the color buffer are modulated with the base color before being 
     * applied to the heightmap region.
     * 
     * The default value is Color::White.
     * 
     * @return The base color value.
     */
    int32 GetBaseColor();
    
    /*!
     * @brief  The base color.
     * 
     * The color values read from the color buffer are modulated with the base color before being 
     * applied to the heightmap region.
     * 
     * The default value is Color::White.
     * 
     * @param value The base color value.
     */
    void SetBaseColor(int32 value);
    
    /*!
     * @brief  The color operation to perform when this brush is applied.
     * 
     * @return The ColorOp to perform.
     */
    ColorOp GetColorOp();
    
    /*!
     * @brief  The color operation to perform when this brush is applied.
     * 
     * @param value The ColorOp to perform.
     */
    void SetColorOp(ColorOp value);
    
    virtual bool DoesModifyColor();
    
    virtual bool DoesModifyDetail();
    
    virtual bool DoesModifyDisplacement();
    
    virtual bool DoesModifyElevation();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of ColorizeBrush.
     * 
     * @param buffer <b>[not-null]</b>  The sample buffer that holds the brush contents.
     */
    static Ptr<ColorizeBrush> From(ColorBuffer* buffer);
    
    /*!
     * @brief  Premultiplies the alpha values of this brush with the given brush mask.
     * 
     * @param mask <b>[not-null]</b>  The brush mask.
     */
    void Premultiply(IBrushMask* mask);
    
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
     * @brief  The base color.
     */
    int32 baseColor;
    
    /*!
     * @brief  The sample buffer that holds the brush contents.
     */
    Ptr<ColorBuffer> brush;
    
    /*!
     * @brief  The current color operation.
     */
    ColorOp colorOp;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of ColorizeBrush.
     * 
     * @param brush The sample buffer that holds the brush contents.
     */
    ColorizeBrush(ColorBuffer* brush);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<ColorizeBrush> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x2ECE842F;
    
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
