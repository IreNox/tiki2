////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_HEIGHTMAP_INTERPOLATE_H
#define CLODDY_API_HEIGHTMAPS_HEIGHTMAP_INTERPOLATE_H

#include "CodeX/System.h"

// Include referenced structures.

#include "Cloddy/Vec3I.h"

// Include referenced classes.

#include "Cloddy/CompositeHeightmapOne.h"

// Forward declare referenced structures.

namespace Cloddy { namespace API { namespace Util { struct Box2I; } } }

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Heightmaps { class IHeightmap; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Heightmaps { class Heightmap; } } }
namespace Cloddy { namespace API { namespace Heightmaps { class HeightmapSample; } } }

// Declare class ::Cloddy::API::Heightmaps::Heightmap_Interpolate.

namespace Cloddy { namespace API { namespace Heightmaps
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced structures.
  
  using Cloddy::API::Util::Box2I;
  using Cloddy::Core::Math::Vectors::Vec3I;
  
  /*!
   * @brief  A heightmap that increases the resolution of another heightmap by interpolation.
   */
  class Heightmap_Interpolate : public CompositeHeightmapOne
  {
    // Declare friend classes.
    
    friend class Heightmap;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual void Get(int32 x, int32 y, HeightmapSample* sample);
    
    virtual void Get(int32 x, int32 y, int32 z, HeightmapSample* sample);
    
    virtual int32 TransformFromBaseHeightmap(int32 face, Box2I& region);
    
    virtual Vec3I TransformToBaseHeightmap(int32 x, int32 y, int32 z);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
  protected:
    
    virtual void DisposeManaged();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Factor by which this heightmap is bigger than the heightmap that gets interpolated.
     */
    int32 factor;
    
    /*!
     * @brief  Shift value used for computing proper interpolation factors.
     */
    int32 factorShift;
    
    /*!
     * @brief  Maximum coordinate of CompositeHeightmapOne::heightmap.
     */
    int32 m;
    
    /*!
     * @brief  Bitmask used to filter bits that refer to heightmap samples that need to be 
     *         interpolated.
     */
    int32 mask;
    
    /*!
     * @brief  Maximum X-coordinate of CompositeHeightmapOne::heightmap.
     */
    int32 mx;
    
    /*!
     * @brief  Maximum Y-coordinate of CompositeHeightmapOne::heightmap.
     */
    int32 my;
    
    /*!
     * @brief  Maximum coordinate of this heightmap.
     */
    int32 n;
    
    /*!
     * @brief  Maximum Y-coordinate of this heightmap.
     */
    int32 ny;
    
    /*!
     * @brief  A heightmap sample used for interpolation.
     */
    Ptr<HeightmapSample> s1;
    
    /*!
     * @brief  A heightmap sample used for interpolation.
     */
    Ptr<HeightmapSample> s2;
    
    /*!
     * @brief  A heightmap sample used for interpolation.
     */
    Ptr<HeightmapSample> s3;
    
    /*!
     * @brief  A heightmap sample used for interpolation.
     */
    Ptr<HeightmapSample> s4;
    
    /*!
     * @brief  A heightmap sample used for interpolation.
     */
    Ptr<HeightmapSample> s5;
    
    /*!
     * @brief  A heightmap sample used for interpolation.
     */
    Ptr<HeightmapSample> s6;
    
    /*!
     * @brief  Shift amount used to compute heightmap sample coordinates to feed 
     *         into CompositeHeightmapOne::heightmap.
     */
    int32 shift;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of this class.
     * 
     * @param size Size of the interpolated heightmap.
     * @param heightmap The heightmap to interpolate.
     */
    Heightmap_Interpolate(int32 size, IHeightmap* heightmap);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Asserts that the given upscale shift value is valid.
     * 
     * @param shift The upscale shift value.
     */
    static void AssertValidShift(int32 shift);
    
    /*!
     * @brief  Interpolates a sample along the X-axis.
     * 
     * @param x X-coordinate of sample.
     * @param y Y-coordinate of sample.
     * @param sample The output heightmap sample.
     */
    void Interpolate_X(int32 x, int32 y, HeightmapSample* sample);
    
    /*!
     * @brief  Interpolates a sample.
     * 
     * @param x X-coordinate of sample.
     * @param y Y-coordinate of sample.
     * @param sample The output heightmap sample.
     */
    void Interpolate_XY(int32 x, int32 y, HeightmapSample* sample);
    
    /*!
     * @brief  Interpolates a sample on the Z- face.
     * 
     * @param x X-coordinate of sample.
     * @param y Y-coordinate of sample.
     * @param sample The output heightmap sample.
     */
    void Interpolate_XY_NegZ(int32 x, int32 y, HeightmapSample* sample);
    
    /*!
     * @brief  Interpolates a sample on the Z+face.
     * 
     * @param x X-coordinate of sample.
     * @param y Y-coordinate of sample.
     * @param sample The output heightmap sample.
     */
    void Interpolate_XY_PosZ(int32 x, int32 y, HeightmapSample* sample);
    
    /*!
     * @brief  Interpolates a sample on the Y- face.
     * 
     * @param x X-coordinate of sample.
     * @param z Z-coordinate of sample.
     * @param sample The output heightmap sample.
     */
    void Interpolate_XZ_NegY(int32 x, int32 z, HeightmapSample* sample);
    
    /*!
     * @brief  Interpolates a sample on the Y+face.
     * 
     * @param x X-coordinate of sample.
     * @param z Z-coordinate of sample.
     * @param sample The output heightmap sample.
     */
    void Interpolate_XZ_PosY(int32 x, int32 z, HeightmapSample* sample);
    
    /*!
     * @brief  Interpolates a sample along the X-axis on the Y- face.
     * 
     * @param x X-coordinate of sample.
     * @param z Z-coordinate of sample.
     * @param sample The output heightmap sample.
     */
    void Interpolate_X_NegY(int32 x, int32 z, HeightmapSample* sample);
    
    /*!
     * @brief  Interpolates a sample along the X-axis on the Z- face.
     * 
     * @param x X-coordinate of sample.
     * @param y Y-coordinate of sample.
     * @param sample The output heightmap sample.
     */
    void Interpolate_X_NegZ(int32 x, int32 y, HeightmapSample* sample);
    
    /*!
     * @brief  Interpolates a sample along the X-axis on the Y+face.
     * 
     * @param x X-coordinate of sample.
     * @param z Z-coordinate of sample.
     * @param sample The output heightmap sample.
     */
    void Interpolate_X_PosY(int32 x, int32 z, HeightmapSample* sample);
    
    /*!
     * @brief  Interpolates a sample along the X-axis on the Z+face.
     * 
     * @param x X-coordinate of sample.
     * @param y Y-coordinate of sample.
     * @param sample The output heightmap sample.
     */
    void Interpolate_X_PosZ(int32 x, int32 y, HeightmapSample* sample);
    
    /*!
     * @brief  Interpolates a sample along the Y-axis.
     * 
     * @param x X-coordinate of sample.
     * @param y Y-coordinate of sample.
     * @param sample The output heightmap sample.
     */
    void Interpolate_Y(int32 x, int32 y, HeightmapSample* sample);
    
    /*!
     * @brief  Interpolates a sample on the X- face.
     * 
     * @param y Y-coordinate of sample.
     * @param z Z-coordinate of sample.
     * @param sample The output heightmap sample.
     */
    void Interpolate_YZ_NegX(int32 y, int32 z, HeightmapSample* sample);
    
    /*!
     * @brief  Interpolates a sample on the X+face.
     * 
     * @param y Y-coordinate of sample.
     * @param z Z-coordinate of sample.
     * @param sample The output heightmap sample.
     */
    void Interpolate_YZ_PosX(int32 y, int32 z, HeightmapSample* sample);
    
    /*!
     * @brief  Interpolates a sample along the Y-axis on the X- face.
     * 
     * @param y Y-coordinate of sample.
     * @param z Z-coordinate of sample.
     * @param sample The output heightmap sample.
     */
    void Interpolate_Y_NegX(int32 y, int32 z, HeightmapSample* sample);
    
    /*!
     * @brief  Interpolates a sample along the Y-axis on the Z- face.
     * 
     * @param x X-coordinate of sample.
     * @param y Y-coordinate of sample.
     * @param sample The output heightmap sample.
     */
    void Interpolate_Y_NegZ(int32 x, int32 y, HeightmapSample* sample);
    
    /*!
     * @brief  Interpolates a sample along the Y-axis on the X+face.
     * 
     * @param y Y-coordinate of sample.
     * @param z Z-coordinate of sample.
     * @param sample The output heightmap sample.
     */
    void Interpolate_Y_PosX(int32 y, int32 z, HeightmapSample* sample);
    
    /*!
     * @brief  Interpolates a sample along the Y-axis on the Z+face.
     * 
     * @param x X-coordinate of sample.
     * @param y Y-coordinate of sample.
     * @param sample The output heightmap sample.
     */
    void Interpolate_Y_PosZ(int32 x, int32 y, HeightmapSample* sample);
    
    /*!
     * @brief  Interpolates a sample along the Z-axis on the X- face.
     * 
     * @param y Y-coordinate of sample.
     * @param z Z-coordinate of sample.
     * @param sample The output heightmap sample.
     */
    void Interpolate_Z_NegX(int32 y, int32 z, HeightmapSample* sample);
    
    /*!
     * @brief  Interpolates a sample along the Z-axis on the Y- face.
     * 
     * @param x X-coordinate of sample.
     * @param z Z-coordinate of sample.
     * @param sample The output heightmap sample.
     */
    void Interpolate_Z_NegY(int32 x, int32 z, HeightmapSample* sample);
    
    /*!
     * @brief  Interpolates a sample along the Z-axis on the X+face.
     * 
     * @param y Y-coordinate of sample.
     * @param z Z-coordinate of sample.
     * @param s The output heightmap sample.
     */
    void Interpolate_Z_PosX(int32 y, int32 z, HeightmapSample* s);
    
    /*!
     * @brief  Interpolates a sample along the Z-axis on the Y+face.
     * 
     * @param x X-coordinate of sample.
     * @param z Z-coordinate of sample.
     * @param sample The output heightmap sample.
     */
    void Interpolate_Z_PosY(int32 x, int32 z, HeightmapSample* sample);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<Heightmap_Interpolate> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x1F52DE77;
    
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
      if ((ptr = CompositeHeightmapOne::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
