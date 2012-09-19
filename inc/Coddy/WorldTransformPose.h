////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_UTIL_WORLDTRANSFORMPOSE_H
#define CLODDY_API_UTIL_WORLDTRANSFORMPOSE_H

#include "CodeX/System.h"

// Include referenced structures.

#include "Cloddy/Vec3D.h"
#include "Cloddy/Vec4D.h"

// Include referenced classes.

#include "Cloddy/WorldTransform.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class ISerialTypeInfo; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace IO { namespace Serialization { template<class> class SerialTypeInfo; } } } }

// Declare class ::Cloddy::API::Util::WorldTransformPose.

namespace Cloddy { namespace API { namespace Util
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced structures.
  
  using Cloddy::Core::Math::Vectors::Vec3D;
  using Cloddy::Core::Math::Vectors::Vec4D;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::IO::Serialization::ISerialTypeInfo;
  
  // Use referenced classes.
  
  using Cloddy::Core::IO::Serialization::SerialTypeInfo;
  
  /*!
   * @brief  Represents the global pose of an entity in terrain-space.
   * 
   * The global pose can be expressed as a transformation of the following form:
   * <pre>
   *     GP := S * R * T
   * </pre>
   * where \c S  is a scaling transformation,\c R  is a rotation and \c T  is a translation.
   */
  class WorldTransformPose : public WorldTransform
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The rotation quaternion,in terrain-space.
     * 
     * @return The rotation quaternion.
     */
    Vec4D GetRotation();
    
    /*!
     * @brief  The rotation quaternion,in terrain-space.
     * 
     * @param value The rotation quaternion.
     */
    void SetRotation(const Vec4D& value);
    
    /*!
     * @brief  The scale factors per axis,in terrain-space.
     * 
     * @return The scale factors.
     */
    Vec3D GetScaling();
    
    /*!
     * @brief  The scale factors per axis,in terrain-space.
     * 
     * @param value The scale factors.
     */
    void SetScaling(const Vec3D& value);
    
    /*!
     * @brief  The translation vector,in world-space.
     * 
     * @return The translation value.
     */
    Vec3D GetTranslation();
    
    /*!
     * @brief  The translation vector,in world-space.
     * 
     * @param value The translation value.
     */
    void SetTranslation(const Vec3D& value);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of WorldTransformPose.
     */
    WorldTransformPose();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Sets this global pose to identity.
     */
    void Identity();
    
    /*!
     * @brief  Sets the rotation part of this affine transformation.
     * 
     * @param x X-coordinate of rotation axis.
     * @param y Y-coordinate of rotation axis.
     * @param z Z-coordinate of rotation axis.
     * @param angle The rotation angle,in radians.
     */
    void RotateAxis(float64 x, float64 y, float64 z, float64 angle);
    
    /*!
     * @brief  Sets the rotation part of this global pose.
     * 
     * @param x X-component of rotation quaternion,in object-space.
     * @param y Y-component of rotation quaternion,in object-space.
     * @param z Z-component of rotation quaternion,in object-space.
     * @param w W-component of rotation quaternion,in object-space.
     */
    void RotateQuaternion(float64 x, float64 y, float64 z, float64 w);
    
    /*!
     * @brief  Sets the scaling part of this global pose.
     * 
     * @param x Scale factor along X-axis,in object-space.
     * @param y Scale factor along Y-axis,in object-space.
     * @param z Scale factor along Z-axis,in object-space.
     */
    void Scale(float64 x, float64 y, float64 z);
    
    /*!
     * @brief  Sets the scaling part of this global pose.
     * 
     * @param f Uniform scale factor,in object-space.
     */
    void Scale(float64 f);
    
    /*!
     * @brief  Sets this global pose to the given value.
     * 
     * @param pose <b>[not-null]</b>  The global pose value to set.
     */
    void Set(WorldTransformPose* pose);
    
    /*!
     * @brief  Sets the translation part of this global pose.
     * 
     * @param x X-component of translation vector,in terrain-space.
     * @param y Y-component of translation vector,in terrain-space.
     * @param z Z-component of translation vector,in terrain-space.
     */
    void Translate(float64 x, float64 y, float64 z);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constants
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The GUID that uniquely identifies this type:{A4FD82BE-3882-4207-B883-9B3B93B5A12E}
     */
    static const String SerialGuid;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Serialization information about this type.
     */
    static const StaticPtr<ISerialTypeInfo> SerialId;
    
    /*!
     * @brief  The rotation quaternion,in terrain-space.
     */
    Vec4D rotation;
    
    /*!
     * @brief  The scale factors per axis,in terrain-space.
     */
    Vec3D scaling;
    
    /*!
     * @brief  The translation vector,in world-space.
     */
    Vec3D translation;
    
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
    public: typedef Ptr<WorldTransformPose> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xBDBC2E37;
    
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
      if ((ptr = WorldTransform::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
