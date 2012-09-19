////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_VISIBILITYCRITERIA_ERRORMETRICS_LIGHTINGS_COMPOSITELIGHTING_H
#define CLODDY_API_VISIBILITYCRITERIA_ERRORMETRICS_LIGHTINGS_COMPOSITELIGHTING_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/Lighting.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace VisibilityCriteria { namespace ErrorMetrics { namespace Lightings { class ILighting; } } } } }
namespace Cloddy { namespace API { namespace VisibilityCriteria { namespace ErrorMetrics { namespace Lightings { class ILightingVisitor; } } } } }
namespace Cloddy { namespace Kernel { class IProvider; } }

// Declare class ::Cloddy::API::VisibilityCriteria::ErrorMetrics::Lightings::CompositeLighting.

namespace Cloddy { namespace API { namespace VisibilityCriteria { namespace ErrorMetrics { namespace Lightings
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Kernel::IProvider;
  
  /*!
   * @brief  An implementation of the ILighting interface that performs a series of lighting terms (
   *         each represented by an aggregated ILighting object )sequentially to the input color.
   */
  class CompositeLighting : public Lighting
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Returns the number of lighting objects..
     * 
     * @return <b>[>=1]</b>  The number of aggregated lighting object.
     */
    int32 GetCount();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of CompositeLighting.
     * 
     * @param count <b>[>=1]</b>  The number of aggregated lighting objects.
     */
    CompositeLighting(int32 count);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void Accept(ILightingVisitor* visitor, Object* userData);
    
    virtual void BeginMeshAction(IProvider* provider);
    
    virtual Ptr<ILighting> Combine(ILighting* lighting);
    
    virtual int32 ComputeLighting(float64 positionX, float64 positionY, float64 positionZ, float32 normalX, float32 normalY, float32 normalZ, int32 diffuse);
    
    virtual void EndMeshAction();
    
    /*!
     * @brief  Returns the \e index -th lighting object.
     * 
     * @param index <b>[0..#GetCount-1]</b>  Index of the lighting object to get.
     * 
     * @return The ILighting object or \c null .
     */
    Ptr<ILighting> GetLighting(int32 index);
    
    /*!
     * @brief  Sets the \e index -th lighting object.
     * 
     * @param index <b>[0..#GetCount-1]</b>  Index of the lighting object to set.
     * @param lighting The lighting object or \c null .
     * 
     * @return <b>[not-null]</b>  this
     */
    Ptr<CompositeLighting> SetLighting(int32 index, ILighting* lighting);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The aggregated lighting objects.
     */
    Array<Ptr<ILighting> > lightings;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<CompositeLighting> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xAB05DAF8;
    
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
      if ((ptr = Lighting::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } } 

#endif
