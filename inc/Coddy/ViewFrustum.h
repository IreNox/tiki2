////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_MESHVISITORS_VIEWFRUSTUM_H
#define CLODDY_API_MESHVISITORS_VIEWFRUSTUM_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/ViewFrustumPlane.h"

// Include referenced structures.

#include "Cloddy/Plane.h"

// Include referenced classes.

#include "Cloddy/Frustum.h"

// Forward declare referenced structures.

namespace Cloddy { namespace Core { namespace Math { namespace Vectors { struct Mat4D; } } } }

// Declare class ::Cloddy::API::MeshVisitors::ViewFrustum.

namespace Cloddy { namespace API { namespace MeshVisitors
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced structures.
  
  using Cloddy::Core::Math::Geom::Plane;
  using Cloddy::Core::Math::Vectors::Mat4D;
  
  /*!
   * @brief  A typcial view frustum with left,right,top,bottom,near and far planes.
   */
  class ViewFrustum : public Frustum
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Creates a new instance of ViewFrustum.
     */
    ViewFrustum();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Computes an inside mask (see FrustumCulling::GetInsideMask)for the given set of view 
     *         frustum planes.
     * 
     * @param planeMask The view frustum plane mask.
     * 
     * @return The inside mask value.
     */
    static int32 ComputeInsideMask(ViewFrustumPlane planeMask);
    
    /*!
     * @brief  Extracts the view frustum planes from the unit cube in homogeneous clip space that 
     *         is defined by the given matrix.
     * 
     * The following inequalities are used to extract the view frustum planes from the given matrix:
     * <pre>
     *       -w &lt; x &lt; w
     *       -w &lt; y &lt; w
     *       C &lt; z &lt; w
     * </pre>
     * where \c x ,\c y ,\c z  and \c w  are the coordinates of a transformed vertex in homogeneous 
     * clip space (as produced by the given matrix).The value \c C  affets the near clipping plane.
     * Its value depends on the used graphics API and can be \c 0  (e.g.Direct3D)or \c -w  (e.g.
     * OpenGL).
     * 
     * Calling this method will update all planes of this frustum.
     * 
     * @param matrix The input matrix.
     * @param nearAtZero Is the near clipping plane at <c>C =0</c> (e.g.Direct3D),or is it at 
     * <c>C =-w</c> (e.g.OpenGL)?
     */
    void ExtractFromMatrix(const Mat4D& matrix, bool nearAtZero);
    
    /*!
     * @brief  Returns a view frustum plane.
     * 
     * @param frustumPlane The view frustum plane.
     * 
     * @return The plane.
     */
    Plane GetViewFrustumPlane(ViewFrustumPlane frustumPlane);
    
    /*!
     * @brief  Sets a view frustum plane.
     * 
     * @param frustumPlane The view frustum plane.
     * @param plane The frustum plane.
     */
    void SetViewFrustumPlane(ViewFrustumPlane frustumPlane, const Plane& plane);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Returns the index of the given view frustum plane.
     * 
     * @param frustumPlane The view frustum plane.
     * 
     * @return The plane index.
     */
    static int32 GetPlaneIdx(ViewFrustumPlane frustumPlane);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<ViewFrustum> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x32F75CFB;
    
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
      if ((ptr = Frustum::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
