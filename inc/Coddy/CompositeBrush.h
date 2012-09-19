////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_BRUSHES_COMPOSITEBRUSH_H
#define CLODDY_API_HEIGHTMAPS_BRUSHES_COMPOSITEBRUSH_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IBrush.h"

// Forward declare referenced structures.

namespace Cloddy { namespace Core { namespace Math { struct Fraction; } } }

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Brushes { class IBrushMask; } } } }
namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleBuffers { class ISampleBuffer; } } } }

// Declare class ::Cloddy::API::Heightmaps::Brushes::CompositeBrush.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Brushes
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced structures.
  
  using Cloddy::Core::Math::Fraction;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Heightmaps::SampleBuffers::ISampleBuffer;
  
  /*!
   * @brief  This brush is a composite that applies a sequence of aggregated brushes.
   */
  class CompositeBrush : public virtual IBrush
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual bool DoesModifyColor();
    
    virtual bool DoesModifyDetail();
    
    virtual bool DoesModifyDisplacement();
    
    virtual bool DoesModifyElevation();
    
    virtual bool DoesUseSlope();
    
    virtual int32 GetHeight();
    
    virtual int32 GetStrength();
    
    virtual void SetStrength(int32 value);
    
    virtual int32 GetWidth();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of CompositeBrush.
     * 
     * @param brushes <b>[not-empty]</b>  The brushes to combine.
     */
    CompositeBrush(Array<Ptr<IBrush> > brushes);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void Apply(ISampleBuffer* sampleBuffer, IBrushMask* brushMask);
    
    virtual Ptr<IBrush> Scale(const Fraction& factor);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The aggregated brushes.
     */
    Array<Ptr<IBrush> > brushes;
    
    /*!
     * @brief  Does this brush modify diffuse color values?
     */
    bool doesModifyColor;
    
    /*!
     * @brief  Does this brush modify detail channel values?
     */
    bool doesModifyDetail;
    
    /*!
     * @brief  Does this brush modify displacement values?
     */
    bool doesModifyDisplacement;
    
    /*!
     * @brief  Does this brush modify elevation values?
     */
    bool doesModifyElevation;
    
    /*!
     * @brief  Height of this brush.
     */
    int32 height;
    
    /*!
     * @brief  Width of this brush.
     */
    int32 width;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<CompositeBrush> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xEBEEF93D;
    
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
      return (void*) 0;
    }
  };
  
} } } } 

#endif
