////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_MATH_VECTORS_QUAT4D_H
#define CLODDY_CORE_MATH_VECTORS_QUAT4D_H

#include "CodeX/System.h"

// Forward declare referenced structures.

namespace Cloddy { namespace Core { namespace Math { namespace Vectors { struct Mat4D; } } } }
namespace Cloddy { namespace Core { namespace Math { namespace Vectors { struct Vec3D; } } } }

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace IO { namespace Serialization { template<class> class IStructSerializer; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace Math { namespace Vectors { class Quat4D_Serializer; } } } }

// Declare class ::Cloddy::Core::Math::Vectors::Quat4D.

namespace Cloddy { namespace Core { namespace Math { namespace Vectors
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::IO::Serialization::IStructSerializer;
  
  struct Quat4D : StructType
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
    
    static const Quat4D Identity;
    
    /*!
     * @brief  The serialization helper object for values of Quat4D.
     */
    static const StaticPtr<IStructSerializer<Val<Quat4D> > > Serializer;
    
    float64 GetLength() const;
    
    float64 GetLengthSqr() const;
    
    /*!
     * @brief  W-component of the quaternion.
     */
    float64 W;
    
    /*!
     * @brief  X-component of the quaternion.
     */
    float64 X;
    
    /*!
     * @brief  Y-component of the quaternion.
     */
    float64 Y;
    
    /*!
     * @brief  Z-component of the quaternion.
     */
    float64 Z;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    Quat4D(float64 x, float64 y, float64 z, float64 w);
    
    Quat4D(const Vec3D& v, float64 s);
    
    Quat4D();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    static Quat4D RotateAxis(const Vec3D& axis, float64 angle);
    
    static Quat4D RotateAxis(float64 axisX, float64 axisY, float64 axisZ, float64 angle);
    
    static Quat4D RotateMatrix(const Mat4D& m);
    
    static Quat4D RotateYawPitchRoll(float64 yaw, float64 pitch, float64 roll);
    
    Quat4D Add(const Quat4D& q) const;
    
    Quat4D Add(float64 x, float64 y, float64 z, float64 w) const;
    
    Quat4D Concat(const Quat4D& q) const;
    
    Quat4D Concat(float64 x, float64 y, float64 z, float64 w) const;
    
    Quat4D Conjugate() const;
    
    Quat4D Div(const Quat4D& q) const;
    
    Quat4D Div(float64 x, float64 y, float64 z, float64 w) const;
    
    float64 Dot(const Quat4D& q) const;
    
    float64 Dot(float64 x, float64 y, float64 z, float64 w) const;
    
    bool Equals(const Quat4D& q) const;
    
    bool Equals(float64 x, float64 y, float64 z, float64 w) const;
    
    Quat4D Inverse() const;
    
    Quat4D Lerp(const Quat4D& q, float64 amount) const;
    
    Quat4D Mul(float64 s) const;
    
    Quat4D Mul(const Quat4D& q) const;
    
    Quat4D Mul(float64 x, float64 y, float64 z, float64 w) const;
    
    Quat4D Neg() const;
    
    Quat4D Norm() const;
    
    Quat4D Slerp(const Quat4D& q, float64 amount) const;
    
    Quat4D Sub(const Quat4D& q) const;
    
    Quat4D Sub(float64 x, float64 y, float64 z, float64 w) const;
    
    // ---------------------------------------------------------------------------------------------
    //  Copy constructor and copy assignment operator
    // ---------------------------------------------------------------------------------------------
  public:
    
    Quat4D(const Quat4D& other);
    
    Quat4D& operator=(const Quat4D& other);
    
    // ---------------------------------------------------------------------------------------------
    // Static Initializer Functions
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief Static initializer function for field Serializer.
     */
    static Object* StaticInitializer_Serializer();
  };
  
} } } } 

#endif
