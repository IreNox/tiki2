////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_BRUSHES_BRUSHMASK_NOISE_H
#define CLODDY_API_HEIGHTMAPS_BRUSHES_BRUSHMASK_NOISE_H

#include "CodeX/System.h"

// Include referenced structures.

#include "Cloddy/Vec3D.h"

// Include referenced classes.

#include "Cloddy/BrushMask.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Brushes { class IBrushMask; } } } }
namespace Cloddy { namespace API { namespace Procedural { class INoiseFunction; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Brushes { class BrushMask; } } } }

// Declare class ::Cloddy::API::Heightmaps::Brushes::BrushMask_Noise.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Brushes
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced structures.
  
  using Cloddy::Core::Math::Vectors::Vec3D;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Procedural::INoiseFunction;
  
  /*!
   * @brief  An implementation of the IBrushMask interface that produces random noise using an 
   *         aggregated INoiseFunction.
   */
  class BrushMask_Noise : public BrushMask
  {
    // Declare friend classes.
    
    friend class BrushMask;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual int32 GetMaskValue(int32 x, int32 y);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
  protected:
    
    virtual Ptr<IBrushMask> DoScale(int32 width, int32 height);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The used noise function.
     */
    Ptr<INoiseFunction> noiseFunction;
    
    /*!
     * @brief  Random origin vector in noise space.
     */
    Vec3D origin;
    
    /*!
     * @brief  Direction vector in noise space for brush mask X-axis.
     */
    Vec3D x;
    
    /*!
     * @brief  Direction vector in noise space for brush mask Y-axis.
     */
    Vec3D y;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    BrushMask_Noise(int32 width, int32 height, INoiseFunction* noiseFunction, const Vec3D& origin, const Vec3D& x, const Vec3D& y);
    
    /*!
     * @brief  Creates a new instance of BrushMask_Noise.
     * 
     * @param width The brush mask width,in samples.
     * @param height The brush mask height,in samples.
     * @param noiseFunction The noise function to use.
     * @param seed Random seed value.
     * @param scale Noise scale factor.
     */
    BrushMask_Noise(int32 width, int32 height, INoiseFunction* noiseFunction, int32 seed, float64 scale);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<BrushMask_Noise> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xC8159105;
    
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
      if ((ptr = BrushMask::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } 

#endif
