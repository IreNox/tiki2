////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_UTIL_CURVES_UNIFORMBCURVE_H
#define CLODDY_API_UTIL_CURVES_UNIFORMBCURVE_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/Continuity.h"

// Include referenced classes.

#include "Cloddy/Curve.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class ISerialTypeInfo; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Util { namespace Curves { class CurveSample; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { template<class> class SerialTypeInfo; } } } }

// Declare class ::Cloddy::API::Util::Curves::UniformBCurve.

namespace Cloddy { namespace API { namespace Util { namespace Curves
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::IO::Serialization::ISerialTypeInfo;
  
  // Use referenced classes.
  
  using Cloddy::Core::IO::Serialization::SerialTypeInfo;
  
  /*!
   * @brief  An ICurve implementation that performs interpolates between control points using an 
   *         Uniform-B spline.
   */
  class UniformBCurve : public Curve
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual Continuity GetContinuity();
    
    virtual int32 GetMaxControlPointIndex();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of UniformBCurve.
     */
    UniformBCurve();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void ComputePoint(float64 controlPointIndex, CurveSample* sample);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constants
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The GUID that uniquely identifies this type:{951CFAE0-CE0A-4A83-8E7C-8B6002A120AA}
     */
    static const String SerialGuid;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Serialization information about this type.
     */
    static const StaticPtr<ISerialTypeInfo> SerialId;
    
    // ---------------------------------------------------------------------------------------------
    // Static Initializer Functions
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Static initializer function for field SerialId.
     */
    static Object* StaticInitializer_SerialId();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<UniformBCurve> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x33D3443F;
    
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
      if ((ptr = Curve::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } 

#endif
