////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_UTIL_CURVES_CATMULLROMCURVE_H
#define CLODDY_API_UTIL_CURVES_CATMULLROMCURVE_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/Continuity.h"

// Include referenced classes.

#include "Cloddy/Curve.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class ISerialTypeInfo; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Util { namespace Curves { class CurveSample; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class Serializer; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { template<class> class SerialTypeInfo; } } } }

// Declare class ::Cloddy::API::Util::Curves::CatmullRomCurve.

namespace Cloddy { namespace API { namespace Util { namespace Curves
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::IO::Serialization::ISerialTypeInfo;
  
  // Use referenced classes.
  
  using Cloddy::Core::IO::Serialization::Serializer;
  using Cloddy::Core::IO::Serialization::SerialTypeInfo;
  
  /*!
   * @brief  An ICurve implementation that performs interpolates between control points with 
   *         Catmull-Rom Splines.
   */
  class CatmullRomCurve : public Curve
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
     * @brief  Creates a new instance of CatmullRomCurve.
     */
    CatmullRomCurve();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void ComputePoint(float64 controlPointIndex, CurveSample* sample);
    
    virtual void Serialize(Serializer* data);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constants
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The GUID that uniquely identifies this type:{2633B7FB-92BB-4FDC-A73C-56682CC6D96C}
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
    public: typedef Ptr<CatmullRomCurve> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x6B661B33;
    
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
