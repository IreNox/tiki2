////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_MESHVISITORS_POINTINFOHELPER_H
#define CLODDY_API_MESHVISITORS_POINTINFOHELPER_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IMeshCallback.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace VertexData { class IVertexData; } } }
namespace Cloddy { namespace Kernel { class IProvider; } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace MeshVisitors { class PointInfo; } } }
namespace Cloddy { namespace API { namespace VertexData { class Float3; } } }
namespace Cloddy { namespace API { namespace VertexData { class Int2; } } }

// Declare class ::Cloddy::API::MeshVisitors::PointInfoHelper.

namespace Cloddy { namespace API { namespace MeshVisitors
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::VertexData::IVertexData;
  using Cloddy::Kernel::IMeshCallback;
  using Cloddy::Kernel::IProvider;
  
  // Use referenced classes.
  
  using Cloddy::API::VertexData::Float3;
  using Cloddy::API::VertexData::Int2;
  
  /*!
   * @brief  The PointInfoHelper class is a helper for computing missing values in a PointInfo 
   *         object.
   * 
   * Given a PointInfo object and its current set of PointInfo::Flags,the PointInfoHelper class 
   * computes all required values that have not yet been computed (the set of required values can 
   * be specified via the #GetFlags property).
   * 
   * The following vertex data semantics are used by this class (\e opt  means that the semantic 
   * will be used if present,\e req  means that the semantic must be present):
   *   - \e opt  - Semantic::HeightmapCoords
   *   - \e opt  - Semantic::Position
   *   - \e opt  - Semantic::Normal
   *   - \e opt  - Semantic::TangentX
   *   - \e opt  - Semantic::TangentY
   *   - \e opt  - Semantic::TangentZ
   * 
   * @see CollisionDetection
   * @see Picking
   */
  class PointInfoHelper : public virtual IMeshCallback
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The set of required PointInfo values.
     * 
     * @return Bitwise combination of the <c>Flag*</c> constants of the PointInfo class.
     */
    int32 GetFlags();
    
    /*!
     * @brief  The set of required PointInfo values.
     * 
     * @param value Bitwise combination of the <c>Flag*</c> constants of the PointInfo class.
     */
    void SetFlags(int32 value);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void BeginMeshAction(IProvider* provider);
    
    /*!
     * @brief  Computes all required PointInfo values (see #GetFlags).
     * 
     * @param info <b>[not-null]</b>  The PointInfo object.
     */
    void Compute(PointInfo* info);
    
    virtual void EndMeshAction();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    int32 cubemapSizeMinusOne;
    
    /*!
     * @brief  The set of required PointInfo flags.
     */
    int32 flags;
    
    /*!
     * @brief  Vertex data container for heightmap coordinates.
     */
    Ptr<Int2> heightmapCoords;
    
    /*!
     * @brief  Vertex data container for normal vectors.
     */
    Ptr<Float3> normal;
    
    /*!
     * @brief  Vertex data container for vertex positions.
     */
    Ptr<IVertexData> position;
    
    /*!
     * @brief  Vertex data container for tangent vectors along the heightmap space X-axis.
     */
    Ptr<Float3> tangentX;
    
    /*!
     * @brief  Vertex data container for tangent vectors along the heightmap space Y-axis.
     */
    Ptr<Float3> tangentY;
    
    /*!
     * @brief  Vertex data container for tangent vectors along the heightmap space Z-axis.
     */
    Ptr<Float3> tangentZ;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
  public:
    
    PointInfoHelper();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<PointInfoHelper> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x5BB6B2DA;
    
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
      if ((ptr = IMeshCallback::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
