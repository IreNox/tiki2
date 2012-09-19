////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_HEIGHTMAP_H
#define CLODDY_API_HEIGHTMAPS_HEIGHTMAP_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/HeightmapLayer.h"

// Include referenced structures.

#include "Cloddy/SampleBitDepth.h"
#include "Cloddy/Vec3I.h"

// Include referenced interfaces.

#include "Cloddy/IHeightmap.h"

// Include referenced classes.

#include "Cloddy/MapBase.h"

// Forward declare referenced structures.

namespace Cloddy { namespace API { namespace Util { struct Box2I; } } }
namespace Cloddy { namespace Core { namespace Math { namespace Vectors { struct Vec2I; } } } }

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Fractal { class IFractalLayer; } } } }
namespace Cloddy { namespace API { namespace Heightmaps { class IDirtyRegionCallback; } } }
namespace Cloddy { namespace Core { namespace Collections { template<class> class IPredicate; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Heightmaps { class HeightmapRegion; } } }
namespace Cloddy { namespace API { namespace Heightmaps { class HeightmapSample; } } }

// Declare class ::Cloddy::API::Heightmaps::Heightmap.

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
  
  using Cloddy::API::Heightmaps::Fractal::IFractalLayer;
  using Cloddy::Core::Collections::IPredicate;
  
  // Use referenced classes.
  
  using Cloddy::API::Util::MapBase;
  
  /*!
   * @brief  Abstract base class for IHeightmap implementations.
   * 
   * The following interface implementations are provided by this class:
   *   - #GetBaseHeightmap:empty
   *   - #GetBitDepth:empty
   *   - #HasBaseHeightmap:fixed
   *   - #GetUserData:fixed
   *   - #Add:fixed
   *   - #BeginDirty:empty
   *   - #Border:fixed
   *   - #Clip:fixed
   *   - #Get(HeightmapRegion*):default
   *   - #Get(const Vec2I&,HeightmapSample*):fixed
   *   - #Get(const Vec3I&,HeightmapSample*):fixed
   *   - #MarkAsDirty:empty
   *   - #Scale:fixed
   *   - #Set(HeightmapRegion*):default
   *   - #Set(const Vec2I&,HeightmapSample*):fixed
   *   - #Set(const Vec3I&,HeightmapSample*):fixed
   *   - #TransformFromBaseHeightmap:default
   *   - #TransformToBaseHeightmap(const Vec3I&):fixed
   *   - #TransformToBaseHeightmap(int32,int32,int32):default
   */
  class Heightmap : public MapBase, public virtual IHeightmap
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual Ptr<IHeightmap> GetBaseHeightmap();
    
    virtual SampleBitDepth GetBitDepth();
    
    virtual bool HasBaseHeightmap();
    
    virtual bool IsMutable();
    
    virtual HeightmapLayer GetLayerMask() = 0;
    
    virtual void* GetUserData();
    
    virtual void SetUserData(void* value);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Computes the maximum scale for the given heightmaps.
     * 
     * @param first <b>[not-null]</b>  First heightmap.
     * @param second <b>[not-null]</b>  Second heightmap.
     * 
     * @return <b>[pow2+1]</b>  The maximum scale size (see IMap::GetSize).
     */
    static int32 ComputeMaximumScale(IHeightmap* first, IHeightmap* second);
    
    /*!
     * @brief  Creates a cube heightmap that returns constant heightmap sample values.
     * 
     * @param size <b>[pow2+1]</b>  The cubemap size.
     * @param sample <b>[not-null]</b>  The constant heightmap sample values.
     * @param layers The heightmap layers to set.
     * 
     * @return <b>[not-null]</b>  The created heightmap.
     */
    static Ptr<IHeightmap> ConstantCube(int32 size, HeightmapSample* sample, HeightmapLayer layers);
    
    /*!
     * @brief  Creates a rectangular heightmap that returns constant heightmap sample values.
     * 
     * @param width <b>[>0]</b>  The heightmap width.
     * @param height <b>[>0]</b>  The heightmap height.
     * @param sample <b>[not-null]</b>  The constant heightmap sample values.
     * @param layers The heightmap layers to set.
     * 
     * @return <b>[not-null]</b>  The created heightmap.
     */
    static Ptr<IHeightmap> ConstantRect(int32 width, int32 height, HeightmapSample* sample, HeightmapLayer layers);
    
    /*!
     * @brief  Creates a new instance of Heightmap_Fractal.
     * 
     * The fractal heightmap will be a cube,ie. MapType::MapType_Cube.
     * 
     * @param size <b>[pow2+1]</b>  The cubemap size,in samples.
     * @param layer <b>[not-null]</b>  The fractal heightmap layer.
     * @param scale <b>[>0]</b>  The noise space scale factor.
     * 
     * @return <b>[not-null]</b>  The created fractal heightmap.
     */
    static Ptr<IHeightmap> FractalCube(int32 size, IFractalLayer* layer, float64 scale);
    
    /*!
     * @brief  Creates a new instance of Heightmap_Fractal.
     * 
     * The fractal heightmap will be a rectangle,ie. MapType::MapType_Rect.
     * 
     * @param width <b>[>0]</b>  The heightmap width,in samples.
     * @param height <b>[>0]</b>  The heightmap height,in samples.
     * @param layer <b>[not-null]</b>  The fractal heightmap layer.
     * @param scale <b>[>0]</b>  The noise space scale factor.
     * 
     * @return <b>[not-null]</b>  The created fractal heightmap.
     */
    static Ptr<IHeightmap> FractalRect(int32 width, int32 height, IFractalLayer* layer, float64 scale);
    
    virtual Ptr<IHeightmap> Add(IHeightmap* delta);
    
    virtual void Begin();
    
    virtual void BeginDirty(IDirtyRegionCallback* callback);
    
    virtual Ptr<IHeightmap> Border(HeightmapSample* borderSample, int32 borderFalloff);
    
    virtual Ptr<IHeightmap> Clip(int32 blockSize, int32 x, int32 y, int32 width, int32 height, int32 face);
    
    virtual Ptr<IHeightmap> Concat(IHeightmap* second, IPredicate<Ref<HeightmapSample> >* predicate);
    
    virtual Ptr<IHeightmap> Default(HeightmapSample* sample);
    
    virtual void End();
    
    virtual Ptr<IHeightmap> Filter(HeightmapLayer layers);
    
    virtual void Get(HeightmapRegion* region);
    
    virtual void Get(const Vec2I& xy, HeightmapSample* sample);
    
    virtual void Get(int32 x, int32 y, HeightmapSample* sample) = 0;
    
    virtual void Get(const Vec3I& xyz, HeightmapSample* sample);
    
    virtual void Get(int32 x, int32 y, int32 z, HeightmapSample* sample) = 0;
    
    virtual void MarkAsDirty(int32 faceX, int32 faceY, int32 face, int32 width, int32 height);
    
    virtual Ptr<IHeightmap> Scale(int32 newSize);
    
    virtual void Set(HeightmapRegion* region);
    
    virtual void Set(const Vec2I& xy, HeightmapSample* sample);
    
    virtual void Set(int32 x, int32 y, HeightmapSample* sample);
    
    virtual void Set(const Vec3I& xyz, HeightmapSample* sample);
    
    virtual void Set(int32 x, int32 y, int32 z, HeightmapSample* sample);
    
    virtual int32 TransformFromBaseHeightmap(int32 face, Box2I& region);
    
    virtual Vec3I TransformToBaseHeightmap(const Vec3I& point);
    
    virtual Vec3I TransformToBaseHeightmap(int32 x, int32 y, int32 z);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Constructors
    // ---------------------------------------------------------------------------------------------
  protected:
    
    /*!
     * @brief  Creates a new instance of Heightmap.
     */
    Heightmap();
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void DisposeManaged();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The current dirty region callback.
     */
    Ptr<IDirtyRegionCallback> callback;
    
    /*!
     * @brief  The current user data object.
     */
    void* userData;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<Heightmap> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x78D0597F;
    
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
      if ((ptr = MapBase::TryCast(typeId)) != 0) return ptr;
      if ((ptr = IHeightmap::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
