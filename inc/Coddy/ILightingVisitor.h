////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_VISIBILITYCRITERIA_ERRORMETRICS_LIGHTINGS_ILIGHTINGVISITOR_H
#define CLODDY_API_VISIBILITYCRITERIA_ERRORMETRICS_LIGHTINGS_ILIGHTINGVISITOR_H

#include "CodeX/System.h"

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace VisibilityCriteria { namespace ErrorMetrics { namespace Lightings { class CompositeLighting; } } } } }
namespace Cloddy { namespace API { namespace VisibilityCriteria { namespace ErrorMetrics { namespace Lightings { class FogLighting; } } } } }
namespace Cloddy { namespace API { namespace VisibilityCriteria { namespace ErrorMetrics { namespace Lightings { class IdentityLighting; } } } } }
namespace Cloddy { namespace API { namespace VisibilityCriteria { namespace ErrorMetrics { namespace Lightings { class LambertianLighting; } } } } }

// Declare interface ::Cloddy::API::VisibilityCriteria::ErrorMetrics::Lightings::ILightingVisitor.

namespace Cloddy { namespace API { namespace VisibilityCriteria { namespace ErrorMetrics { namespace Lightings
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Visitor interface for ILighting implementations.
   */
  class NO_VTABLE ILightingVisitor : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Visits the given ILighting object.
     * 
     * @param lighting <b>[not-null]</b>  The object.
     * @param userData Optional user data to pass.
     */
    virtual void Visit(CompositeLighting* lighting, Object* userData) = 0;
    
    /*!
     * @brief  Visits the given ILighting object.
     * 
     * @param lighting <b>[not-null]</b>  The object.
     * @param userData Optional user data to pass.
     */
    virtual void Visit(FogLighting* lighting, Object* userData) = 0;
    
    /*!
     * @brief  Visits the given ILighting object.
     * 
     * @param lighting <b>[not-null]</b>  The object.
     * @param userData Optional user data to pass.
     */
    virtual void Visit(IdentityLighting* lighting, Object* userData) = 0;
    
    /*!
     * @brief  Visits the given ILighting object.
     * 
     * @param lighting <b>[not-null]</b>  The object.
     * @param userData Optional user data to pass.
     */
    virtual void Visit(LambertianLighting* lighting, Object* userData) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<ILightingVisitor> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x610ABDCA;
    
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
      return (void*) 0;
    }
  };
} } } } } 

#endif
