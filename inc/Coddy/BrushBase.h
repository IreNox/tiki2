////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_BRUSHES_BRUSHBASE_H
#define CLODDY_API_HEIGHTMAPS_BRUSHES_BRUSHBASE_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IBrush.h"
#include "Cloddy/ISampleBufferVisitor.h"

// Forward declare referenced structures.

namespace Cloddy { namespace Core { namespace Math { struct Fraction; } } }

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Brushes { class IBrushMask; } } } }
namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleBuffers { class ISampleBuffer; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleBuffers { class ColorBuffer; } } } }
namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleBuffers { class DetailBuffer; } } } }
namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleBuffers { class DisplacementBuffer; } } } }
namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleBuffers { class ElevationBuffer; } } } }
namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleBuffers { class SlopeBuffer; } } } }

// Declare class ::Cloddy::API::Heightmaps::Brushes::BrushBase.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Brushes
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced structures.
  
  using Cloddy::Core::Math::Fraction;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Heightmaps::SampleBuffers::ISampleBuffer;
  using Cloddy::API::Heightmaps::SampleBuffers::ISampleBufferVisitor;
  
  // Use referenced classes.
  
  using Cloddy::API::Heightmaps::SampleBuffers::ColorBuffer;
  using Cloddy::API::Heightmaps::SampleBuffers::DetailBuffer;
  using Cloddy::API::Heightmaps::SampleBuffers::DisplacementBuffer;
  using Cloddy::API::Heightmaps::SampleBuffers::ElevationBuffer;
  using Cloddy::API::Heightmaps::SampleBuffers::SlopeBuffer;
  
  /*!
   * @brief  Abstract base class for IBrush implementations.
   */
  class BrushBase : public virtual IBrush, public virtual ISampleBufferVisitor
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual bool DoesModifyColor() = 0;
    
    virtual bool DoesModifyDetail() = 0;
    
    virtual bool DoesModifyDisplacement() = 0;
    
    virtual bool DoesModifyElevation() = 0;
    
    virtual bool DoesUseSlope();
    
    virtual int32 GetHeight();
    
    virtual int32 GetStrength();
    
    virtual void SetStrength(int32 value);
    
    virtual int32 GetWidth();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void Apply(ISampleBuffer* sampleBuffer, IBrushMask* brushMask);
    
    virtual Ptr<IBrush> Scale(const Fraction& factor);
    
    virtual void Visit(ColorBuffer* buffer);
    
    virtual void Visit(DetailBuffer* buffer);
    
    virtual void Visit(DisplacementBuffer* buffer);
    
    virtual void Visit(ElevationBuffer* buffer);
    
    virtual void Visit(SlopeBuffer* buffer);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Attributes
    // ---------------------------------------------------------------------------------------------
  protected:
    
    /*!
     * @brief  The brush height,in samples.
     */
    int32 height;
    
    /*!
     * @brief  The brush width,in samples.
     */
    int32 width;
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of BrushBase.
     * 
     * @param width <b>[>0]</b>  The brush width,in samples.
     * @param height <b>[>0]</b>  The brush height,in samples.
     */
    BrushBase(int32 width, int32 height);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Returns a scaled version of this brush.
     * 
     * The given scale factor (see \e numerator  and \e denominator )is guaranteed to be greater 
     * than zero and different from \c 1 .
     * 
     * @param numerator The numerator of the scale factor.
     * @param denominator The denominator of the scale factor.
     * 
     * @return <b>[not-null]</b>  The scales brush.
     */
    virtual Ptr<IBrush> DoScale(int32 numerator, int32 denominator) = 0;
    
    /*!
     * @brief  Returns the brush mask value for the given brush sample.
     * 
     * @param x X-coordinate of brush sample.
     * @param y Y-coordinate of brush sample.
     * 
     * @return <b>[0..32768]</b>  The brush mask value.Will be \c 32768  if no brush mask is used.
     */
    int32 GetMaskValue(int32 x, int32 y);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The current brush mask.
     */
    Ptr<IBrushMask> mask;
    
    /*!
     * @brief  The relative strength of this brush.
     */
    int32 strength;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<BrushBase> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x33026E8D;
    
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
      if ((ptr = IBrush::TryCast(typeId)) != 0) return ptr;
      if ((ptr = ISampleBufferVisitor::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } 

#endif
