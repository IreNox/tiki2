////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_PROJECTION_HEIGHTMAPPROJECTOR_H
#define CLODDY_API_HEIGHTMAPS_PROJECTION_HEIGHTMAPPROJECTOR_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IBeginEnd.h"

// Include referenced classes.

#include "CodeX/Disposable.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Heightmaps { class IHeightmap; } } }
namespace Cloddy { namespace API { namespace Heightmaps { namespace Projection { class IMapProjection; } } } }
namespace Cloddy { namespace API { namespace Util { namespace Progress { class IProgressMonitor; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Heightmaps { class HeightmapSample; } } }

// Declare class ::Cloddy::API::Heightmaps::Projection::HeightmapProjector.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Projection
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Heightmaps::IHeightmap;
  using Cloddy::API::Util::IBeginEnd;
  using Cloddy::API::Util::Progress::IProgressMonitor;
  
  // Use referenced classes.
  
  using Cloddy::API::Heightmaps::HeightmapSample;
  using CodeX::System::Disposable;
  
  /*!
   * @brief  The HeightmapProjector class can be used to perform map projections between heightmaps.
   */
  class HeightmapProjector : public Disposable, public virtual IBeginEnd
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Optional IProgressMonitor object to use when projecting heightmap samples.
     * 
     * For each projected cubemap sample,the progress will be incremented by one tick.
     * 
     * @return The progress monitor object.
     */
    Ptr<IProgressMonitor> GetProgressMonitor();
    
    /*!
     * @brief  Optional IProgressMonitor object to use when projecting heightmap samples.
     * 
     * For each projected cubemap sample,the progress will be incremented by one tick.
     * 
     * @param value The progress monitor object.
     */
    void SetProgressMonitor(IProgressMonitor* value);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of HeightmapProjector.
     * 
     * @param input <b>[not-null]</b>  The input heightmap.
     * @param projection <b>[not-null]</b>  The projection to use.
     * @param output <b>[not-null]</b>  The output heightmap.
     */
    HeightmapProjector(IHeightmap* input, IMapProjection* projection, IHeightmap* output);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void Begin();
    
    virtual void End();
    
    /*!
     * @brief  Computes and sets the given cube heightmap sample by projecting it onto the input 
     *         rectangular heightmap.
     * 
     * @param x X-coordinate of cube heightmap sample.
     * @param y Y-coordinate of cube heightmap sample.
     * @param z Z-coordinate of cube heightmap sample.
     */
    void Project(int32 x, int32 y, int32 z);
    
    /*!
     * @brief  Computes and sets the given cube heightmap sample range by projecting it onto the 
     *         input rectangular heightmap.
     * 
     * @param faceX X-coordinate of top-left sample of heightmap range,in cubemap face coordinates.
     * @param faceY Y-coordinate of top-left sample of heightmap range,in cubemap face coordinates.
     * @param face <b>[0..5]</b>  The cubemap face (see Cubemap class).
     * @param size <b>[pow2]</b>  Size of the heightmap range (both width and height).
     */
    void Project(int32 faceX, int32 faceY, int32 face, int32 size);
    
    /*!
     * @brief  Computes and sets the given cube heightmap sample range by projecting it onto the 
     *         input rectangular heightmap.
     * 
     * @param faceX X-coordinate of top-left sample of heightmap range,in cubemap face coordinates.
     * @param faceY Y-coordinate of top-left sample of heightmap range,in cubemap face coordinates.
     * @param face <b>[0..5]</b>  The cubemap face (see Cubemap class).
     * @param width <b>[>0]</b>  Width of heightmap range.
     * @param height <b>[>0]</b>  Height of heightmap range.
     */
    void Project(int32 faceX, int32 faceY, int32 face, int32 width, int32 height);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
  protected:
    
    virtual void DisposeManaged();
    
    virtual void DisposeManagedChildren();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Size of the cube heightmap,minus one.
     */
    int32 cubemapSizeMinusOne;
    
    /*!
     * @brief  Cubemap face of the current heightmap range.
     */
    int32 face;
    
    /*!
     * @brief  Height of current heightmap range.
     */
    int32 faceHeight;
    
    /*!
     * @brief  Width of current heightmap range.
     */
    int32 faceWidth;
    
    /*!
     * @brief  X-coordinate of top-left sampe of current heightmap range.
     */
    int32 faceX;
    
    /*!
     * @brief  X-coordinate of top-left sampe of current heightmap range.
     */
    int32 faceY;
    
    /*!
     * @brief  The input heightmap.
     */
    Ptr<IHeightmap> input;
    
    /*!
     * @brief  Heightmap X-coordinate of current sample window.
     */
    int32 ix;
    
    /*!
     * @brief  Heightmap Y-coordinate of current sample window.
     */
    int32 iy;
    
    /*!
     * @brief  The output heightmap.
     */
    Ptr<IHeightmap> output;
    
    /*!
     * @brief  Optional IProgressMonitor object to use when projecting heightmap samples.
     * 
     * For each projected cubemap sample,the progress will be incremented by one tick.
     */
    Ptr<IProgressMonitor> progressMonitor;
    
    /*!
     * @brief  Number of projected cubemap samples.
     */
    int64 projectedCount;
    
    /*!
     * @brief  The used map projection.
     */
    Ptr<IMapProjection> projection;
    
    /*!
     * @brief  Top-left sample of heightmap window.
     * 
     * <pre>
     *     +----+----+
     *     |*s0*| s1 |
     *     +----+----+
     *     | s2 | s3 |
     *     +----+----+
     * </pre>
     */
    Ptr<HeightmapSample> s0;
    
    /*!
     * @brief  Top-right sample of heightmap window.
     * 
     * <pre>
     *     +----+----+
     *     | s0 |*s1*|
     *     +----+----+
     *     | s2 | s3 |
     *     +----+----+
     * </pre>
     */
    Ptr<HeightmapSample> s1;
    
    /*!
     * @brief  Bottom-left sample of heightmap window.
     * 
     * <pre>
     *     +----+----+
     *     | s0 | s1 |
     *     +----+----+
     *     |*s2*| s3 |
     *     +----+----+
     * </pre>
     */
    Ptr<HeightmapSample> s2;
    
    /*!
     * @brief  Bottom-right sample of heightmap window.
     * 
     * <pre>
     *     +----+----+
     *     | s0 | s1 |
     *     +----+----+
     *     | s2 |*s3*|
     *     +----+----+
     * </pre>
     */
    Ptr<HeightmapSample> s3;
    
    /*!
     * @brief  Helper sample for mixing the heightmap window.
     */
    Ptr<HeightmapSample> s4;
    
    /*!
     * @brief  Helper sample for mixing the heightmap window.
     */
    Ptr<HeightmapSample> s5;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    void Project(int32 x, int32 y);
    
    void Project0(int32 x, int32 y, int32 size);
    
    void Project1(int32 x, int32 y, int32 size);
    
    void Project2(int32 x, int32 y, int32 size);
    
    void Project3(int32 x, int32 y, int32 size);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<HeightmapProjector> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x630E8DD6;
    
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
      if ((ptr = Disposable::TryCast(typeId)) != 0) return ptr;
      if ((ptr = IBeginEnd::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } 

#endif
