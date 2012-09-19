////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_UTIL_WORLDTRANSFORM_H
#define CLODDY_API_UTIL_WORLDTRANSFORM_H

#include "CodeX/System.h"

// Include referenced structures.

#include "Cloddy/Mat4D.h"
#include "Cloddy/Vec3D.h"

// Include referenced classes.

#include "Cloddy/SerializableBase.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class ISerializable; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class ISerialTypeInfo; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class Serializer; } } } }

// Declare class ::Cloddy::API::Util::WorldTransform.

namespace Cloddy { namespace API { namespace Util
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced structures.
  
  using Cloddy::Core::Math::Vectors::Mat4D;
  using Cloddy::Core::Math::Vectors::Vec3D;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::IO::Serialization::ISerializable;
  using Cloddy::Core::IO::Serialization::ISerialTypeInfo;
  
  // Use referenced classes.
  
  using Cloddy::Core::IO::Serialization::SerializableBase;
  using Cloddy::Core::IO::Serialization::Serializer;
  
  /*!
   * @brief  The WorldTransform represents an affine transformation from terrain-space to 
   *         world-space.
   */
  class WorldTransform : public SerializableBase
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The transformation matrix from terrain-space to world-space.
     * 
     * @return The matrix.
     */
    Mat4D GetMatrix();
    
    /*!
     * @brief  The inverse of #GetMatrix.
     * 
     * @return The matrix.
     */
    Mat4D GetMatrixInverse();
    
    /*!
     * @brief  The inverse transpose of #GetMatrix.
     * 
     * @return The matrix.
     */
    Mat4D GetMatrixInverseTranspose();
    
    /*!
     * @brief  The transpose of #GetMatrix.
     * 
     * @return The matrix.
     */
    Mat4D GetMatrixTranspose();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual Ptr<ISerializable> Deserialize(int32 serialVersion, Serializer* data);
    
    virtual void Serialize(Serializer* data);
    
    /*!
     * @brief  Transforms the given position vector from terrain-space to world-space.
     * 
     * @param v The position vector,in terrain-space.
     * 
     * @return The position vector,in world-space.
     */
    Vec3D TerrainToWorldCoords(const Vec3D& v);
    
    /*!
     * @brief  Transforms the given position vector from terrain-space to world-space.
     * 
     * @param x X-coordinate of position vector,in terrain-space.
     * @param y Y-coordinate of position vector,in terrain-space.
     * @param z Z-coordinate of position vector,in terrain-space.
     * 
     * @return The position vector,in world-space.
     */
    Vec3D TerrainToWorldCoords(float64 x, float64 y, float64 z);
    
    /*!
     * @brief  Transforms the given direction vector from terrain-space to world-space.
     * 
     * @param v The direction vector,in terrain-space.
     * 
     * @return The direction vector,in world-space.
     */
    Vec3D TerrainToWorldVector(const Vec3D& v);
    
    /*!
     * @brief  Transforms the given direction vector from terrain-space to world-space.
     * 
     * @param x X-component of direction vector,in terrain-space.
     * @param y Y-component of direction vector,in terrain-space.
     * @param z Z-component of direction vector,in terrain-space.
     * 
     * @return The direction vector,in world-space.
     */
    Vec3D TerrainToWorldVector(float64 x, float64 y, float64 z);
    
    /*!
     * @brief  Transforms the given position vector from world-space to terrain-space.
     * 
     * @param v The position vector,in world-space.
     * 
     * @return The position vector,in terrain-space.
     */
    Vec3D WorldToTerrainCoords(const Vec3D& v);
    
    /*!
     * @brief  Transforms the given position vector from world-space to terrain-space.
     * 
     * @param x X-coordinate of position vector,in world-space.
     * @param y Y-coordinate of position vector,in world-space.
     * @param z Z-coordinate of position vector,in world-space.
     * 
     * @return The position vector,in terrain-space.
     */
    Vec3D WorldToTerrainCoords(float64 x, float64 y, float64 z);
    
    /*!
     * @brief  Transforms the given direction vector from world-space to terrain-space.
     * 
     * @param v The direction vector,in world-space.
     * 
     * @return The direction vector,in terrain-space.
     */
    Vec3D WorldToTerrainVector(const Vec3D& v);
    
    /*!
     * @brief  Transforms the given direction vector from world-space to terrain-space.
     * 
     * @param x X-component of direction vector,in world-space.
     * @param y Y-component of direction vector,in world-space.
     * @param z Z-component of direction vector,in world-space.
     * 
     * @return The direction vector,in terrain-space.
     */
    Vec3D WorldToTerrainVector(float64 x, float64 y, float64 z);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Constructors
    // ---------------------------------------------------------------------------------------------
  protected:
    
    /*!
     * @brief  Creates a new instance of WorldTransform.
     * 
     * @param serialId The serial type ID.
     */
    WorldTransform(ISerialTypeInfo* serialId);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Computes the transformation matrices.
     * 
     * @param matrix The transformation matrix from terrain-space to world-space.
     */
    void ComputeMatrices(const Mat4D& matrix);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The transformation matrix from terrain-space to world-space.
     */
    Mat4D matrix;
    
    /*!
     * @brief  Inverse of #matrix.
     */
    Mat4D matrixInverse;
    
    /*!
     * @brief  Inverse transpose of #matrix.
     */
    Mat4D matrixInverseTranspose;
    
    /*!
     * @brief  Transpose of #matrix.
     */
    Mat4D matrixTranspose;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<WorldTransform> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xECA039C6;
    
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
      return (void*) 0;
    }
  };
  
} } } 

#endif
