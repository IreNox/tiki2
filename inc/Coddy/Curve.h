////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_UTIL_CURVES_CURVE_H
#define CLODDY_API_UTIL_CURVES_CURVE_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/Continuity.h"

// Include referenced interfaces.

#include "Cloddy/ICurve.h"

// Include referenced classes.

#include "Cloddy/SerializableBase.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class ISerializable; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class ISerialTypeInfo; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Util { namespace Curves { class CurveSample; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class Serializer; } } } }

// Declare class ::Cloddy::API::Util::Curves::Curve.

namespace Cloddy { namespace API { namespace Util { namespace Curves
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::IO::Serialization::ISerializable;
  using Cloddy::Core::IO::Serialization::ISerialTypeInfo;
  
  // Use referenced classes.
  
  using Cloddy::Core::IO::Serialization::SerializableBase;
  using Cloddy::Core::IO::Serialization::Serializer;
  
  /*!
   * @brief  Abstract base class for ICurve implementations.
   */
  class Curve : public SerializableBase, public virtual ICurve
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual Continuity GetContinuity() = 0;
    
    virtual int32 GetControlPointCount();
    
    virtual int32 GetMaxControlPointIndex() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates an ICurve instance that provides the given continuity.
     * 
     * @param continuity The requested continuity.
     * 
     * @return <b>[not-null]</b>  The ICurve instance.
     */
    static Ptr<ICurve> ForContinuity(Continuity continuity);
    
    virtual Ptr<ICurve> AddControlPoint(float64 x);
    
    virtual Ptr<ICurve> AddControlPoint(float64 x, float64 y);
    
    virtual Ptr<ICurve> AddControlPoint(float64 x, float64 y, float64 z);
    
    virtual Ptr<ICurve> AddControlPoint(float64 x, float64 y, float64 z, float64 w);
    
    virtual Ptr<ICurve> ClearControlPoints();
    
    virtual void ComputePoint(float64 controlPointIndex, CurveSample* sample) = 0;
    
    virtual Ptr<ISerializable> Deserialize(int32 serialVersion, Serializer* data);
    
    virtual void Serialize(Serializer* data);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Attributes
    // ---------------------------------------------------------------------------------------------
  protected:
    
    /*!
     * @brief  The current number of control points.
     */
    int32 controlPointCount;
    
    /*!
     * @brief  W-coordinates of control points.
     */
    Array<float64> w;
    
    /*!
     * @brief  X-coordinates of control points.
     */
    Array<float64> x;
    
    /*!
     * @brief  Y-coordinates of control points.
     */
    Array<float64> y;
    
    /*!
     * @brief  Z-coordinates of control points.
     */
    Array<float64> z;
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of Curve.
     * 
     * @param serialType The serial ID.
     */
    Curve(ISerialTypeInfo* serialType);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<Curve> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xC3791745;
    
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
      if ((ptr = SerializableBase::TryCast(typeId)) != 0) return ptr;
      if ((ptr = ICurve::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } 

#endif
