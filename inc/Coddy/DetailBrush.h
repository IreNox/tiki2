////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_BRUSHES_DETAILBRUSH_H
#define CLODDY_API_HEIGHTMAPS_BRUSHES_DETAILBRUSH_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/DetailOp.h"

// Include referenced classes.

#include "Cloddy/BrushBase.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Brushes { class IBrush; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleBuffers { class DetailBuffer; } } } }

// Declare class ::Cloddy::API::Heightmaps::Brushes::DetailBrush.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Brushes
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced classes.
  
  using Cloddy::API::Heightmaps::SampleBuffers::DetailBuffer;
  
  /*!
   * @brief  This brush combines the detail channel values of a heightmap region with the detail 
   *         channel values of a given sample buffer using a configured channel operation.
   */
  class DetailBrush : public BrushBase
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The channel operation to perform when this brush is applied.
     * 
     * @return The DetailOp to perform.
     */
    DetailOp GetDetailOp();
    
    /*!
     * @brief  The channel operation to perform when this brush is applied.
     * 
     * @param value The DetailOp to perform.
     */
    void SetDetailOp(DetailOp value);
    
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
    static Ptr<DetailBrush> From(DetailBuffer* buffer);
    
    virtual void Visit(DetailBuffer* buffer);
    
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
     * @brief  The sample buffer that holds the brush contents.
     */
    Ptr<DetailBuffer> brush;
    
    /*!
     * @brief  The current channel operation.
     */
    DetailOp detailOp;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of ColorizeBrush.
     * 
     * @param brush The sample buffer that holds the brush contents.
     */
    DetailBrush(DetailBuffer* brush);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<DetailBrush> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x6F0FD935;
    
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
