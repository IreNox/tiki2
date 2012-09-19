////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_VERTEXFACTORIES_VERTEXFORMATS_FIXEDRANGE_H
#define CLODDY_API_VERTEXFACTORIES_VERTEXFORMATS_FIXEDRANGE_H

#include "CodeX/System.h"

// Include referenced structures.

#include "Cloddy/Vec3D.h"
#include "Cloddy/Vec3I.h"

// Include referenced classes.

#include "Cloddy/SerializableBase.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class ISerializable; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class ISerialTypeInfo; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class Serializer; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { template<class> class SerialTypeInfo; } } } }

// Declare class ::Cloddy::API::VertexFactories::VertexFormats::FixedRange.

namespace Cloddy { namespace API { namespace VertexFactories { namespace VertexFormats
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced structures.
  
  using Cloddy::Core::Math::Vectors::Vec3D;
  using Cloddy::Core::Math::Vectors::Vec3I;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::IO::Serialization::ISerializable;
  using Cloddy::Core::IO::Serialization::ISerialTypeInfo;
  
  // Use referenced classes.
  
  using Cloddy::Core::IO::Serialization::SerializableBase;
  using Cloddy::Core::IO::Serialization::Serializer;
  using Cloddy::Core::IO::Serialization::SerialTypeInfo;
  
  /*!
   * @brief  Helper class for converting floating-point coordinates into a fixed range for 
   *         improving precision on systems that allow only 32-bit floating-point values to be 
   *         used (ie. shaders).
   * 
   * Applications that require high precision arithmetics will typically work with 64-bit 
   * floating-point numbers.At some point these values need to be transferred to a secondary 
   * system (eg. to a GPU shader)which can only consume 32-bit values (floating-point numbers resp. 
   * integers).Casting 64-bit floating-point numbers to 32-bit will dramatically reduce accuracy:
   * For example,32-bit floating-point values are not sufficient to represent the vertices of a 
   * triangle mesh built from a heightmap of size <c>2^24+1 =16777217</c> (in the context of Cloddy,
   * this is a small heightmap).Assuming that the secondary system can consume 32-bit integer 
   * values,the following range transformation can be applied to all high precision floating-point 
   * input numbers in order to produce integer values that represent a fixed number range:
   * <pre>
   *     .   min   := Minimum bound of fixed number range.
   *     .   max   := Maximum bound of fixed number range.
   *     .   V     := High precision floating-point number (64 bits or more).
   *     .   Vi    := 32-bit integer in the range [-2147483647 .. 2147483647], 
   *     .            representing the high precision number range [min .. max]. 
   *     .   
   *     .   Fi(v) := (int)(2147483647 * (2 * v + max - min) / (max - min) + 0.5)
   *     .   
   *     .   F(vi) := 0.5 * ((max - min) * vi / 2147483647 + (max + min));
   * </pre>
   * The functions <c>Fi(v)</c> and <c>F(vi)</c> convert between high-precision numbers and 
   * fixed-range numbers (see #ToFixedRange and #FromFixedRange).
   * The fixed-range numbers will have 32-bits of precision,whereas 32-bit floating-point numbers 
   * have much less precision bits (usually 23).By transferring fixed-range numbers to the 
   * secondary system instead a floating-point values,the precision can be increased significantly.
   * Once a 32-bit fixed-range number has been received by the secondary systems,two situations are 
   * possible:
   *   - The secondary system internally uses high-precision floating-point arithmetics.In this 
   *   case,the function <c>F(vi)</c> can be implemented as is.
   *   - The secondary system is limited to 32-bit floating-point arithmetics.In that case,
   *   additional effort is necessary in order to achieve an increase in presicion (see below for 
   *   details).
   * Floating-point precision can be increased by splitting a number \c V  into a sum:
   * <pre>
   *     V = Vhi + Vlo
   * </pre>
   * where the exponents of \c Vhi  and \c Vlo  greatly differ.Evaluating the sum would lead to 
   * loss in precision.Instead,all computations are performed separately on the terms of the sum 
   * \c Vhi  and \c Vlo ,and the combination is made at the latest possible moment,for example:
   * <pre>
   *     Vws := A vertex in world-space.
   *     C   := The camera position, inworld-space.
   *     (Vws - C) => (Vws_hi + Vws_lo) - (Chi + Clo)
   *     = (Vws_hi - Chi) + (Vws_lo - Clo)
   * </pre>
   * Regrouping the terms by exponents of similar order will increase floating-point precision 
   * dramatically.
   */
  class FixedRange : public SerializableBase
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Maximum coordinates of fixed range.
     * 
     * @return The coordinates.
     */
    Vec3D GetMaximum();
    
    /*!
     * @brief  Minimum coordinates of fixed range.
     * 
     * @return The coordinates.
     */
    Vec3D GetMinimum();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of FixedRange.
     */
    FixedRange();
    
    /*!
     * @brief  Creates a new instance of FixedRange.
     * 
     * @param minimum Minimum coordinates of fixed range.
     * @param maximum Maximum coordinates of fixed range.
     */
    FixedRange(const Vec3D& minimum, const Vec3D& maximum);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual Ptr<ISerializable> Deserialize(int32 serialVersion, Serializer* data);
    
    /*!
     * @brief  Converts the given fixed-range coordinates to floating-point coordinates.
     * 
     * @param v The fixed-range coordinates.
     * 
     * @return The floating-point coordinates.
     */
    Vec3D FromFixedRange(const Vec3I& v);
    
    virtual void Serialize(Serializer* data);
    
    /*!
     * @brief  Converts the given floating-point coordiantes to fixed-range coordinates.
     * 
     * @param v The floating-point coordinates.
     * 
     * @return The fixed-range coordinates.
     */
    Vec3I ToFixedRange(const Vec3D& v);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constants
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The GUID that uniquely identifies this type:{BB7FD42F-F10C-47AC-8072-0F07C38A7FA5}
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
     * @brief  Center coordinates of fixed range.
     */
    Vec3D center;
    
    /*!
     * @brief  Maximum coordinates of fixed range.
     */
    Vec3D maximum;
    
    /*!
     * @brief  Minimum coordinates of fixed range.
     */
    Vec3D minimum;
    
    /*!
     * @brief  Scale factor for #FromFixedRange 
     */
    Vec3D rScale;
    
    /*!
     * @brief  Scale factor for #ToFixedRange.
     */
    Vec3D scale;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Computes #center,#scale and #rScale.
     */
    void ComputeValues();
    
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
    public: typedef Ptr<FixedRange> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x3012BA71;
    
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
  
} } } } 

#endif
