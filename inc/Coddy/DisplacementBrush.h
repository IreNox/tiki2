////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_BRUSHES_DISPLACEMENTBRUSH_H
#define CLODDY_API_HEIGHTMAPS_BRUSHES_DISPLACEMENTBRUSH_H

#include "CodeX/System.h"

// Include referenced structures.

#include "Cloddy/Vec3I.h"

// Include referenced classes.

#include "Cloddy/BrushBase.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Brushes { class IBrush; } } } }
namespace Cloddy { namespace API { namespace Heightmaps { namespace Brushes { class IBrushMask; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleBuffers { class DisplacementBuffer; } } } }

// Declare class ::Cloddy::API::Heightmaps::Brushes::DisplacementBrush.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Brushes
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced structures.
  
  using Cloddy::Core::Math::Vectors::Vec3I;
  
  // Use referenced classes.
  
  using Cloddy::API::Heightmaps::SampleBuffers::DisplacementBuffer;
  
  /*!
   * @brief  The DisplacementBrush class modifies the XYZ displacement values of a heightmap.
   */
  class DisplacementBrush : public BrushBase
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  This vector represents the direction in terrain-space into which the displacement 
     *         along the X-axis is applied (see HeightmapSample::DisplacementX.
     * 
     * The components of the vector are stored in <c>22.10</c> fixed-point precision,i.e.a value of 
     * \c 1024  corresponds to the floating-point value <c>1.0</c>.
     * 
     * The default value is (1024,0,0).
     * 
     * @return The displacement vector along the X-axis.
     */
    Vec3I GetDisplacementX();
    
    /*!
     * @brief  This vector represents the direction in terrain-space into which the displacement 
     *         along the X-axis is applied (see HeightmapSample::DisplacementX.
     * 
     * The components of the vector are stored in <c>22.10</c> fixed-point precision,i.e.a value of 
     * \c 1024  corresponds to the floating-point value <c>1.0</c>.
     * 
     * The default value is (1024,0,0).
     * 
     * @param value The displacement vector along the X-axis.
     */
    void SetDisplacementX(const Vec3I& value);
    
    /*!
     * @brief  This vector represents the direction in terrain-space into which the displacement 
     *         along the X-axis is applied (see HeightmapSample::DisplacementX.
     * 
     * The components of the vector are stored in <c>22.10</c> fixed-point precision,i.e.a value of 
     * \c 1024  corresponds to the floating-point value <c>1.0</c>.
     * 
     * The default value is (0,1024,0).
     * 
     * @return The displacement vector along the Y-axis.
     */
    Vec3I GetDisplacementY();
    
    /*!
     * @brief  This vector represents the direction in terrain-space into which the displacement 
     *         along the X-axis is applied (see HeightmapSample::DisplacementX.
     * 
     * The components of the vector are stored in <c>22.10</c> fixed-point precision,i.e.a value of 
     * \c 1024  corresponds to the floating-point value <c>1.0</c>.
     * 
     * The default value is (0,1024,0).
     * 
     * @param value The displacement vector along the Y-axis.
     */
    void SetDisplacementY(const Vec3I& value);
    
    /*!
     * @brief  This vector represents the direction in terrain-space into which the displacement 
     *         along the X-axis is applied (see HeightmapSample::DisplacementX.
     * 
     * The components of the vector are stored in <c>22.10</c> fixed-point precision,i.e.a value of 
     * \c 1024  corresponds to the floating-point value <c>1.0</c>.
     * 
     * The default value is (0,0,1024).
     * 
     * @return The displacement vector along the Z-axis.
     */
    Vec3I GetDisplacementZ();
    
    /*!
     * @brief  This vector represents the direction in terrain-space into which the displacement 
     *         along the X-axis is applied (see HeightmapSample::DisplacementX.
     * 
     * The components of the vector are stored in <c>22.10</c> fixed-point precision,i.e.a value of 
     * \c 1024  corresponds to the floating-point value <c>1.0</c>.
     * 
     * The default value is (0,0,1024).
     * 
     * @param value The displacement vector along the Z-axis.
     */
    void SetDisplacementZ(const Vec3I& value);
    
    virtual bool DoesModifyColor();
    
    virtual bool DoesModifyDetail();
    
    virtual bool DoesModifyDisplacement();
    
    virtual bool DoesModifyElevation();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of DisplacementBrush.
     * 
     * @param buffer <b>[not-null]</b>  The displacement buffer that holds the brush values.
     */
    static Ptr<DisplacementBrush> From(DisplacementBuffer* buffer);
    
    /*!
     * @brief  Premultiplies the displacement values of this brush with the given brush mask.
     * 
     * @param mask <b>[not-null]</b>  The brush mask.
     */
    void Premultiply(IBrushMask* mask);
    
    /*!
     * @brief  Resets the displacement vectors #GetDisplacementX,#GetDisplacementY 
     *         and #GetDisplacementZ to their default values.
     */
    void ResetDisplacementVectors();
    
    virtual void Visit(DisplacementBuffer* buffer);
    
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
     * @brief  The brush displacement values.
     */
    Ptr<DisplacementBuffer> brush;
    
    /*!
     * @brief  This vector represents the direction in terrain-space into which the displacement 
     *         along the X-axis is applied (see HeightmapSample::DisplacementX.
     * 
     * The components of the vector are stored in <c>22.10</c> fixed-point precision,i.e.a value of 
     * \c 1024  corresponds to the floating-point value <c>1.0</c>.
     * 
     * The default value is (1024,0,0).
     */
    Vec3I displacementX;
    
    /*!
     * @brief  This vector represents the direction in terrain-space into which the displacement 
     *         along the X-axis is applied (see HeightmapSample::DisplacementX.
     * 
     * The components of the vector are stored in <c>22.10</c> fixed-point precision,i.e.a value of 
     * \c 1024  corresponds to the floating-point value <c>1.0</c>.
     * 
     * The default value is (0,1024,0).
     */
    Vec3I displacementY;
    
    /*!
     * @brief  This vector represents the direction in terrain-space into which the displacement 
     *         along the X-axis is applied (see HeightmapSample::DisplacementX.
     * 
     * The components of the vector are stored in <c>22.10</c> fixed-point precision,i.e.a value of 
     * \c 1024  corresponds to the floating-point value <c>1.0</c>.
     * 
     * The default value is (0,0,1024).
     */
    Vec3I displacementZ;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of DisplacementBrush.
     * 
     * @param brush The displacement buffer that holds the brush values.
     */
    DisplacementBrush(DisplacementBuffer* brush);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<DisplacementBrush> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xFF305F83;
    
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
