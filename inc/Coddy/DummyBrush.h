////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_BRUSHES_DUMMYBRUSH_H
#define CLODDY_API_HEIGHTMAPS_BRUSHES_DUMMYBRUSH_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/BrushBase.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Brushes { class IBrush; } } } }

// Declare class ::Cloddy::API::Heightmaps::Brushes::DummyBrush.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Brushes
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  The DummyBrush is a mock implementation of the IBrush interface and does not modify 
   *         any heightmap samples.
   */
  class DummyBrush : public BrushBase
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
     * @brief  Creates a new instance of DummyBrush.
     * 
     * @param width <b>[>0]</b>  The brush width,in samples.
     * @param height <b>[>0]</b>  The brush height,in samples.
     */
    DummyBrush(int32 width, int32 height);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
  protected:
    
    virtual Ptr<IBrush> DoScale(int32 numerator, int32 denominator);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<DummyBrush> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x52080458;
    
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
