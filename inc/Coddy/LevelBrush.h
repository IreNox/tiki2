////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_BRUSHES_LEVELBRUSH_H
#define CLODDY_API_HEIGHTMAPS_BRUSHES_LEVELBRUSH_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/BrushBase.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Brushes { class IBrush; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleBuffers { class ElevationBuffer; } } } }

// Declare class ::Cloddy::API::Heightmaps::Brushes::LevelBrush.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Brushes
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced classes.
  
  using Cloddy::API::Heightmaps::SampleBuffers::ElevationBuffer;
  
  /*!
   * @brief  A brush that levels the terrain at a given target elevation.
   */
  class LevelBrush : public BrushBase
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual bool DoesModifyColor();
    
    virtual bool DoesModifyDetail();
    
    virtual bool DoesModifyDisplacement();
    
    virtual bool DoesModifyElevation();
    
    /*!
     * @brief  The target elevation.
     * 
     * The default value if HeightmapSample::MidValue.
     * 
     * @return The target elevation value.
     */
    int32 GetElevation();
    
    /*!
     * @brief  The target elevation.
     * 
     * The default value if HeightmapSample::MidValue.
     * 
     * @param value The target elevation value.
     */
    void SetElevation(int32 value);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of LevelBrush.
     * 
     * @param width <b>[>0]</b>  The brush width,in samples.
     * @param height <b>[>0]</b>  The brush height,in samples.
     */
    LevelBrush(int32 width, int32 height);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
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
     * @brief  The target elevation.
     */
    int32 elevation;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<LevelBrush> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x2924CA;
    
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
