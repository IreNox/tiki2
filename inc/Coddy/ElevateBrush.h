////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_BRUSHES_ELEVATEBRUSH_H
#define CLODDY_API_HEIGHTMAPS_BRUSHES_ELEVATEBRUSH_H

#include "CodeX/System.h"

// Include referenced structures.

#include "Cloddy/Fraction.h"

// Include referenced classes.

#include "Cloddy/BrushBase.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Brushes { class IBrush; } } } }
namespace Cloddy { namespace API { namespace Heightmaps { namespace Brushes { class IBrushMask; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleBuffers { class ElevationBuffer; } } } }

// Declare class ::Cloddy::API::Heightmaps::Brushes::ElevateBrush.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Brushes
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced structures.
  
  using Cloddy::Core::Math::Fraction;
  
  // Use referenced classes.
  
  using Cloddy::API::Heightmaps::SampleBuffers::ElevationBuffer;
  
  /*!
   * @brief  A brush that elevates resp. lowers the terrain.
   * 
   * The ElevateBrush uses the samples in an ElevationBuffer to modify the elevation values of the 
   * heightmap.Usually,the content of the elevation buffer is read from a grayscale image.The brush 
   * factor (see #GetBrushFactor)can be used to control how much the terrain is elevated resp. 
   * lowered.
   */
  class ElevateBrush : public BrushBase
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The elevation values of the brush samples are multiplied with this brush factor 
     *         before they are applied to the target buffer.
     * 
     * The default value is \c 1 .
     * 
     * @return The brush factor value.
     */
    Fraction GetBrushFactor();
    
    /*!
     * @brief  The elevation values of the brush samples are multiplied with this brush factor 
     *         before they are applied to the target buffer.
     * 
     * The default value is \c 1 .
     * 
     * @param value The brush factor value.
     */
    void SetBrushFactor(const Fraction& value);
    
    virtual bool DoesModifyColor();
    
    virtual bool DoesModifyDetail();
    
    virtual bool DoesModifyDisplacement();
    
    virtual bool DoesModifyElevation();
    
    /*!
     * @brief  The elevation value that represents zero.
     * 
     * All brush elevation values below the zero value will lower the terrain and all values above 
     * it will raise the terrain (assuming that the #GetBrushFactor is positive,otherwise the 
     * effect is reversed).
     * 
     * The default value is \c 0  (ie. terrain will always be raised resp. lowered,depending on the 
     * sign of #GetBrushFactor).
     * 
     * @return <b>[0..1073741823]</b>  The zero level elevation value.
     */
    int32 GetZeroLevel();
    
    /*!
     * @brief  The elevation value that represents zero.
     * 
     * All brush elevation values below the zero value will lower the terrain and all values above 
     * it will raise the terrain (assuming that the #GetBrushFactor is positive,otherwise the 
     * effect is reversed).
     * 
     * The default value is \c 0  (ie. terrain will always be raised resp. lowered,depending on the 
     * sign of #GetBrushFactor).
     * 
     * @param value <b>[0..1073741823]</b>  The zero level elevation value.
     */
    void SetZeroLevel(int32 value);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of ElevateBrush.
     * 
     * @param brush <b>[not-null]</b>  The sample buffer that holds the elevation values of this 
     * brush.
     */
    static Ptr<ElevateBrush> From(ElevationBuffer* brush);
    
    /*!
     * @brief  Premultiplies the elevation values of this brush with the given brush mask.
     * 
     * @param mask <b>[not-null]</b>  The brush mask.
     */
    void Premultiply(IBrushMask* mask);
    
    virtual void Visit(ElevationBuffer* buffer);
    
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
     * @brief  The elevation buffer that holds the brush contents.
     */
    Ptr<ElevationBuffer> brush;
    
    /*!
     * @brief  The elevation values of the brush samples are multiplied with this brush factor 
     *         before they are applied to the target buffer.
     */
    Fraction brushFactor;
    
    /*!
     * @brief  The elevation value that represents zero.
     * 
     * All brush elevation values below the zero value will lower the terrain and all values above 
     * it will raise the terrain.
     */
    int32 zeroLevel;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of ElevateBrush.
     * 
     * @param brush The sample buffer that holds the elevation values of this brush.
     */
    ElevateBrush(ElevationBuffer* brush);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<ElevateBrush> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x76517BE;
    
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
