////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_IHEIGHTMAP_H
#define CLODDY_API_HEIGHTMAPS_IHEIGHTMAP_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/HeightmapLayer.h"

// Include referenced structures.

#include "Cloddy/SampleBitDepth.h"
#include "Cloddy/Vec3I.h"

// Include referenced interfaces.

#include "Cloddy/IMap.h"
#include "Cloddy/IUserData.h"

// Forward declare referenced structures.

namespace Cloddy { namespace API { namespace Util { struct Box2I; } } }
namespace Cloddy { namespace Core { namespace Math { namespace Vectors { struct Vec2I; } } } }

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Heightmaps { class IDirtyRegionCallback; } } }
namespace Cloddy { namespace Core { namespace Collections { template<class> class IPredicate; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Heightmaps { class HeightmapRegion; } } }
namespace Cloddy { namespace API { namespace Heightmaps { class HeightmapSample; } } }

// Declare interface ::Cloddy::API::Heightmaps::IHeightmap.

namespace Cloddy { namespace API { namespace Heightmaps
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced structures.
  
  using Cloddy::API::Heightmaps::SampleFormats::SampleBitDepth;
  using Cloddy::API::Util::Box2I;
  using Cloddy::Core::Math::Vectors::Vec2I;
  using Cloddy::Core::Math::Vectors::Vec3I;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Util::IMap;
  using Cloddy::Core::Collections::IPredicate;
  using Cloddy::Kernel::IUserData;
  
  /*!
   * @brief  A heightmap provides elevation and surface color data for a terrain.
   * 
   * The application must provide an IHeightmap object for each CLOD mesh by adding 
   * a ComponentIdsApi::Req_Heightmap component to the meshes IProvider object.
   * 
   * Heightmap data is returned using HeightmapSample objects for individual heightmaps samples 
   * and HeightmapRegion objects for heightmap sample blocks.
   * 
   * All read and write accesses (includes IFlushable::Flush)to an IHeightmap object must be 
   * wrapped in IBeginEnd::Begin /#BeginDirty /IBeginEnd::End calls.
   */
  class NO_VTABLE IHeightmap : public virtual IMap, public virtual IUserData
  {
    // ---------------------------------------------------------------------------------------------
    // Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Returns the mutable base heightmap of this heightmap.
     * 
     * The mutable base heightmap of a heightmap is defined as follows:
     *   - The heightmap itself,iff IMap::IsMutable returns \c true .
     *   - The mutable base heightmap of an aggregated heightmap.
     *   - \c null  if the heightmap is not mutable (ie. IMap::IsMutable return \c false )and no 
     *   aggregated heightmap provides a mutable base heightmap.
     * 
     * Even if an IHeightmap object itself is immutable (see IMap::IsMutable),one of the heightmaps 
     * it aggregates (if it is a composite heightmap)may be mutable.In this case,deformation can be 
     * performed on that mutable base heightmap,which will affect the samples of this heightmap (
     * for example through interpolation).
     * 
     * @return The base heightmap object;can be \c null ,\c this  or any aggregated heightmap 
     * object.
     * 
     * @see #TransformFromBaseHeightmap
     * @see #TransformToBaseHeightmap(const Vec3I&)
     * @see #TransformToBaseHeightmap(int32,int32,int32)
     */
    virtual Ptr<IHeightmap> GetBaseHeightmap() = 0;
    
    /*!
     * @brief  Returns the bit depth this heightmap uses to encode heightmap samples.
     * 
     * @return The sample bit depth.
     */
    virtual SampleBitDepth GetBitDepth() = 0;
    
    /*!
     * @brief  Does this heightmap have a mutable base heightmap?
     * 
     * The mutable base heightmap of a heightmap is defined as follows:
     *   - The heightmap itself,iff IMap::IsMutable returns \c true .
     *   - The mutable base heightmap of an aggregated heightmap.
     *   - \c null  if the heightmap is not mutable (ie. IMap::IsMutable return \c false )and no 
     *   aggregated heightmap provides a mutable base heightmap.
     * 
     * @return \c true  if this heightmap does provide a mutable base heightmap,\c false  if not.
     */
    virtual bool HasBaseHeightmap() = 0;
    
    /*!
     * @brief  The layers of this heightmap.
     * 
     * @return Bitwise combination of HeightmapLayer values.
     */
    virtual HeightmapLayer GetLayerMask() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a combined heightmap that adds the heightmap samples of the given difference 
     *         heightmap to the samples of this heightmap.
     * 
     * The returned heightmap will be mutable iff this the given delta heightmap is mutable.With 
     * this method,an immutable heightmap can be made mutable;the difference between the combined 
     * heightmap and the original heightmap is then stored in \e delta .
     * 
     * @param delta <b>[not-null]</b>  The difference heightmap.
     * 
     * @return <b>[not-null]</b>  The combined heightmap.
     */
    virtual Ptr<IHeightmap> Add(IHeightmap* delta) = 0;
    
    /*!
     * @brief  Begins an access to the samples of this heightmap.
     * 
     * This method serves the same purpose as IBeginEnd::Begin.
     * 
     * The application receives a notification method call for each heightmap update (
     * see #MarkAsDirty).
     * 
     * This method can be called on immutable (see IMap::IsMutable)heightmaps.However,the given 
     * callback will never be invoked in this case.
     * 
     * @param callback The callback object that receives notifications for each updated heightmap 
     * region.
     * 
     * @see #MarkAsDirty
     */
    virtual void BeginDirty(IDirtyRegionCallback* callback) = 0;
    
    /*!
     * @brief  Pads this heightmap to the smallest fitting size of <c>2^n+1</c>.
     * 
     * This method will add a border region at the right and bottom edges of a rectangular 
     * heightmap (see MapType::MapType_Rect).A smooth falloff is computed at the heightmap edges in 
     * order to avoid unnecessary triangles being created by CLOD mesh refinement for overly sharp 
     * corners.
     * 
     * @param borderSample Optional border heightmap sample.If \c null ,an all zero heightmap 
     * sample will be used (see HeightmapSample::Clear).
     * @param borderFalloff <b>[>0]</b>  Width of the border falloff region,in heightmap samples.
     * 
     * @return <b>[not-null]</b>  The padded heightmap.
     */
    virtual Ptr<IHeightmap> Border(HeightmapSample* borderSample, int32 borderFalloff) = 0;
    
    /*!
     * @brief  Returns a clipped version of this heightmap.
     * 
     * Choosing the subregion for a clipped heightmap is performed as follows:
     *   -# A block size is chosen (must be a power of two plus one),see \e blockSize .
     *   -# The heightmap is divided into blocks according to the chosen block size (adjacent 
     *   blocks overlap by one heightmap sample row resp. column).
     *   -# A grid of adjacent blocks is selected as the subregion for the clipped heightmap.
     * Small block sizes will reduce performance when accessing heightmap samples that are stored 
     * in a LOD friendly manner (eg. when using a dataset heightmap via IDataset::CreateHeightmap().
     * Thus,the block size should be as big as possible.
     * 
     * The user data object set for this IHeightmap object (see IUserData::GetUserData)will be set 
     * for the returned IHeightmap object as well.
     * 
     * @param blockSize <b>[pow2+1]</b>  The block size.
     * @param x <b>[>=0]</b>  X-coordinate of top-left block of subregion.
     * @param y <b>[>=0]</b>  Y-coordinate of top-left block of subregion.
     * @param width <b>[>0]</b>  Width of subregion,in blocks.
     * @param height <b>[>0]</b>  Height of subregion,in blocks.
     * @param face The cubemap face of the subregion (see constants in Cubemap class for possible 
     * values).For rectangular heightmaps,use Cubemap::FaceNegZ.
     * 
     * @return <b>[not-null]</b>  The clipped heightmap.
     */
    virtual Ptr<IHeightmap> Clip(int32 blockSize, int32 x, int32 y, int32 width, int32 height, int32 face) = 0;
    
    /*!
     * @brief  Concatenates the given heightmap to this one.
     * 
     * Concatenated heightmap fill data into a HeightmapSample object in order,with heightmaps at a 
     * later stage overwriting sample data written by heightmaps of an earlier stage.
     * 
     * Both heightmaps (this one and \e second )will be scaled to the maximum possible size (
     * see Heightmap::ComputeMaximumScale).
     * 
     * @param second <b>[not-null]</b>  The second heightmap.
     * @param predicate Optional predicate;when specified,the second heightmap sample will only be 
     * applied if the predicate evaluates to \c true .
     * 
     * @return <b>[not-null]</b>  The resulting heightmap.
     * 
     * @see HeightmapSample::DiffuseNotEqual
     */
    virtual Ptr<IHeightmap> Concat(IHeightmap* second, IPredicate<Ref<HeightmapSample> >* predicate) = 0;
    
    /*!
     * @brief  Returns an IHeightmap object that initializes thosw heightmap layers that are not 
     *         set by this heightmap to the given default values.
     * 
     * @param sample <b>[not-null]</b>  The heightmap layer default values.
     * 
     * @return <b>[not-null]</b>  The resulting heightmap.
     */
    virtual Ptr<IHeightmap> Default(HeightmapSample* sample) = 0;
    
    /*!
     * @brief  Filters the heightmap layer that are output to HeightmapSample objects.
     * 
     * @param layers The output heightmap layer mask.
     * 
     * @return <b>[not-null]</b>  The resulting heightmap.
     */
    virtual Ptr<IHeightmap> Filter(HeightmapLayer layers) = 0;
    
    /*!
     * @brief  Returns a region of this heightmap in a single bulk operation.
     * 
     * All calls to this method must be wrapped in IBeginEnd::Begin /#BeginDirty /IBeginEnd::End 
     * 
     * The heightmap coordinates are read from the HeightmapRegion::FaceX,HeightmapRegion::FaceY 
     * and HeightmapRegion::Face of \e region .
     * 
     * @param region <b>[not-null]</b>  The output heightmap region.
     */
    virtual void Get(HeightmapRegion* region) = 0;
    
    /*!
     * @brief  Returns a single heightmap sample.
     * 
     * All calls to this method must be wrapped in IBeginEnd::Begin /#BeginDirty /IBeginEnd::End 
     * 
     * @param xy Coordinates of heightmap sample.
     * @param sample <b>[not-null]</b>  The output heightmap sample.
     */
    virtual void Get(const Vec2I& xy, HeightmapSample* sample) = 0;
    
    /*!
     * @brief  Returns a single heightmap sample.
     * 
     * All calls to this method must be wrapped in IBeginEnd::Begin /#BeginDirty /IBeginEnd::End 
     * 
     * @param x X-coordinate of heightmap sample.
     * @param y Y-coordinate of heightmap sample.
     * @param sample <b>[not-null]</b>  The output heightmap sample.
     */
    virtual void Get(int32 x, int32 y, HeightmapSample* sample) = 0;
    
    /*!
     * @brief  Returns a single heightmap sample.
     * 
     * All calls to this method must be wrapped in IBeginEnd::Begin /#BeginDirty /IBeginEnd::End 
     * 
     * @param xyz Coordinates of heightmap sample.
     * @param sample <b>[not-null]</b>  The output heightmap sample.
     */
    virtual void Get(const Vec3I& xyz, HeightmapSample* sample) = 0;
    
    /*!
     * @brief  Returns a single heightmap sample.
     * 
     * All calls to this method must be wrapped in IBeginEnd::Begin /#BeginDirty /IBeginEnd::End 
     * 
     * @param x X-coordinate of heightmap sample.
     * @param y Y-coordinate of heightmap sample.
     * @param z Z-coordinate of heightmap sample.
     * @param sample <b>[not-null]</b>  The output heightmap sample.
     */
    virtual void Get(int32 x, int32 y, int32 z, HeightmapSample* sample) = 0;
    
    /*!
     * @brief  Marks the given region of this heightmap as dirty.
     * 
     * Dirty regions can only be tracked when the #BeginDirty method has been called to initiate 
     * the heightmap access.
     * 
     * @param faceX X-component of cubemap face coordinates of top-left corner of dirty region.
     * @param faceY Y-component of cubemap face coordinates of top-left corner of dirty region.
     * @param face The cubemap face (see constants in Cubemap).
     * @param width <b>[>=0]</b>  Width of the dirty region.
     * @param height <b>[>=0]</b>  Height of the dirty region.
     * 
     * @see #BeginDirty
     */
    virtual void MarkAsDirty(int32 faceX, int32 faceY, int32 face, int32 width, int32 height) = 0;
    
    /*!
     * @brief  Returns a scaled version of this heightmap.
     * 
     * The user data object set for this IHeightmap object (see IUserData::GetUserData)will be set 
     * for the returned IHeightmap object as well.
     * 
     * The maximum upscaling factor for heightmaps is \c 65536 ,so the given condition must be met 
     * when upscaling a heightmap:
     * <pre>
     * (newSize - 1) / (Size - 1) &lt;= 65536
     * </pre>
     * where \e newSize  is the new heightmap size and IMap::GetSize is the current size of this 
     * heightmap.
     * A workaround for this limitation is to perform multiple scale operations one after another.
     * 
     * @param newSize <b>[pow2+1]</b>  The scaled internal size (see IMap::GetSize).
     * 
     * @return <b>[not-null]</b>  The scaled heightmap.
     */
    virtual Ptr<IHeightmap> Scale(int32 newSize) = 0;
    
    /*!
     * @brief  Updates a region of this heightmap in a single bulk operation.
     * 
     * All calls to this method must be wrapped in IBeginEnd::Begin /#BeginDirty /IBeginEnd::End 
     * 
     * Use the #MarkAsDirty method for tracking dirty regions in the heightmap.
     * 
     * The heightmap coordinates are read from the HeightmapRegion::FaceX,HeightmapRegion::FaceY 
     * and HeightmapRegion::Face of \e region .
     * 
     * If this heightmap is immutable (see IMap::IsMutable),the method does nothing and returns 
     * silently.
     * 
     * @param region <b>[not-null]</b>  The heightmap region.
     */
    virtual void Set(HeightmapRegion* region) = 0;
    
    /*!
     * @brief  Updates a single heightmap sample.
     * 
     * All calls to this method must be wrapped in IBeginEnd::Begin /#BeginDirty /IBeginEnd::End 
     * calls.
     * 
     * Use the #MarkAsDirty method for tracking dirty regions in the heightmap.
     * 
     * If this heightmap is immutable (see IMap::IsMutable),the method does nothing and returns 
     * silently.
     * 
     * @param xy Coordinates of heightmap sample.
     * @param sample <b>[not-null]</b>  The input heightmap sample.
     */
    virtual void Set(const Vec2I& xy, HeightmapSample* sample) = 0;
    
    /*!
     * @brief  Updates a single heightmap sample.
     * 
     * All calls to this method must be wrapped in IBeginEnd::Begin /#BeginDirty /IBeginEnd::End 
     * calls.
     * 
     * Use the #MarkAsDirty method for tracking dirty regions in the heightmap.
     * 
     * If this heightmap is immutable (see IMap::IsMutable),the method does nothing and returns 
     * silently.
     * 
     * @param x X-coordinate of heightmap sample.
     * @param y Y-coordinate of heightmap sample.
     * @param sample <b>[not-null]</b>  The input heightmap sample.
     */
    virtual void Set(int32 x, int32 y, HeightmapSample* sample) = 0;
    
    /*!
     * @brief  Updates a single heightmap sample.
     * 
     * All calls to this method must be wrapped in IBeginEnd::Begin /#BeginDirty /IBeginEnd::End 
     * calls.
     * 
     * Use the #MarkAsDirty method for tracking dirty regions in the heightmap.
     * 
     * If this heightmap is immutable (see IMap::IsMutable),the method does nothing and returns 
     * silently.
     * 
     * @param xyz Coordinates of heightmap sample.
     * @param sample <b>[not-null]</b>  The input heightmap sample.
     */
    virtual void Set(const Vec3I& xyz, HeightmapSample* sample) = 0;
    
    /*!
     * @brief  Updates a single heightmap sample.
     * 
     * All calls to this method must be wrapped in IBeginEnd::Begin /#BeginDirty /IBeginEnd::End 
     * calls.
     * 
     * Use the #MarkAsDirty method for tracking dirty regions in the heightmap.
     * 
     * If this heightmap is immutable (see IMap::IsMutable),the method does nothing and returns 
     * silently.
     * 
     * @param x X-coordinate of heightmap sample.
     * @param y Y-coordinate of heightmap sample.
     * @param z Z-coordinate of heightmap sample.
     * @param sample <b>[not-null]</b>  The input heightmap sample.
     */
    virtual void Set(int32 x, int32 y, int32 z, HeightmapSample* sample) = 0;
    
    /*!
     * @brief  Transform the given region from the base heightmap coordinate space to that of this 
     *         heightmap.
     * 
     * If #GetBaseHeightmap returns \c null ,this method performs no action and returns silently.
     * 
     * @param face The cubemap face of the give region (see the constants in the Cubemap class for 
     * possible values).For rectangular heightmaps,use Cubemap::FaceNegZ.
     * @param region The region,in base heightmap cubemap face coordinates.
     * 
     * @return The cubemap face of the transformed region.
     * 
     * @see #GetBaseHeightmap
     */
    virtual int32 TransformFromBaseHeightmap(int32 face, Box2I& region) = 0;
    
    /*!
     * @brief  Transforms the given point from the coordinate space of this heightmap to that of 
     *         the base heightmap 
     * 
     * If #GetBaseHeightmap returns \c null ,this method performs no action and returns \e point .
     * 
     * @param point The point,in cubemap face coordinates of this heightmap.
     * 
     * @return The resulting point.
     * 
     * @see #GetBaseHeightmap
     */
    virtual Vec3I TransformToBaseHeightmap(const Vec3I& point) = 0;
    
    /*!
     * @brief  Transforms the given point from the coordinate space of this heightmap to that of 
     *         the base heightmap 
     * 
     * If #GetBaseHeightmap returns \c null ,this method performs no action and returns the given 
     * point.
     * 
     * @param x X-coordinate of point,in cubemap face coordinates of this heightmap.
     * @param y Y-coordinate of point,in cubemap face coordinates of this heightmap.
     * @param z Z-coordinate of point,in cubemap face coordinates of this heightmap.
     * 
     * @return The resulting point.
     * 
     * @see #GetBaseHeightmap
     */
    virtual Vec3I TransformToBaseHeightmap(int32 x, int32 y, int32 z) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IHeightmap> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x76736194;
    
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
      if ((ptr = IMap::TryCast(typeId)) != 0) return ptr;
      if ((ptr = IUserData::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
} } } 

#endif
