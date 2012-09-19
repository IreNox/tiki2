////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_HEIGHTMAPSAMPLE_H
#define CLODDY_API_HEIGHTMAPS_HEIGHTMAPSAMPLE_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/HeightmapLayer.h"

// Include referenced classes.

#include "Cloddy/Conversions.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Collections { template<class> class IPredicate; } } }

// Declare class ::Cloddy::API::Heightmaps::HeightmapSample.

namespace Cloddy { namespace API { namespace Heightmaps
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::Collections::IPredicate;
  
  // Use referenced classes.
  
  using Cloddy::API::Util::Conversions;
  
  /*!
   * @brief  The HeightmapSample class represents a data container for a single heightmap sample.
   * 
   * @see HeightmapRegion
   */
  class HeightmapSample : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Constants
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Maximum value for normalized elevation and displacement values.
     * 
     * The minimum value is \c 0 .
     */
    static const int32 MaxValue = Conversions::Max30;
    
    /*!
     * @brief  Middle value for normalized elevation and displacement values.
     */
    static const int32 MidValue = 512 * 1024 * 1024;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Values for detail channels 0 to 3.
     * 
     * Each detail channel is an 8-bit value which can freely be used to add detail to the terrain 
     * surface (eg. detail texture weights or detail geometry density).
     */
    int32 Detail0;
    
    /*!
     * @brief  Values for detail channels 4 to 7.
     * 
     * Each detail channel is an 8-bit value which can freely be used to add detail to the terrain 
     * surface (eg. detail texture weights or detail geometry density).
     */
    int32 Detail1;
    
    /*!
     * @brief  Values for detail channels 8 to 11.
     * 
     * Each detail channel is an 8-bit value which can freely be used to add detail to the terrain 
     * surface (eg. detail texture weights or detail geometry density).
     */
    int32 Detail2;
    
    /*!
     * @brief  Values for detail channels 12 to 15.
     * 
     * Each detail channel is an 8-bit value which can freely be used to add detail to the terrain 
     * surface (eg. detail texture weights or detail geometry density).
     */
    int32 Detail3;
    
    /*!
     * @brief  The surface color value.
     * 
     * The color is encoded as a 32-bit ARGB color value.
     */
    int32 Diffuse;
    
    /*!
     * @brief  Normalized displacement along X-axis,in terrain-space.
     * 
     * The range of normalized displacement values is <c>[0..1073741823]</c> (ie. 2^30-1).The 
     * remaining number range of signed integers is reserved for unnormalized displacement values 
     * which can result from interpolation.
     * 
     * A displacement value of #MidValue represents zero displacement.The values \c 0  
     * and #MaxValue represent the maximum displacement along the negative and positive X-axes.
     */
    int32 DisplacementX;
    
    /*!
     * @brief  Normalized displacement along Y-axis,in terrain-space.
     * 
     * The range of normalized displacement values is <c>[0..1073741823]</c> (ie. 2^30-1).The 
     * remaining number range of signed integers is reserved for unnormalized displacement values 
     * which can result from interpolation.
     * 
     * A displacement value of #MidValue represents zero displacement.The values \c 0  
     * and #MaxValue represent the maximum displacement along the negative and positive Y-axes.
     */
    int32 DisplacementY;
    
    /*!
     * @brief  Normalized displacement along Z-axis,in terrain-space.
     * 
     * The range of normalized displacement values is <c>[0..1073741823]</c> (ie. 2^30-1).The 
     * remaining number range of signed integers is reserved for unnormalized displacement values 
     * which can result from interpolation.
     * 
     * A displacement value of #MidValue represents zero displacement.The values \c 0  
     * and #MaxValue represent the maximum displacement along the negative and positive Z-axes.
     */
    int32 DisplacementZ;
    
    /*!
     * @brief  The normalized elevation value.
     * 
     * The range of normalized elevation values is <c>[0..1073741823]</c> (ie. 2^30-1).The 
     * remaining number range of signed integers is reserved for unnormalized elevation values 
     * which can result from interpolation.
     */
    int32 Elevation;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of HeightmapSample.
     */
    HeightmapSample();
    
    /*!
     * @brief  Creates a new instance of HeightmapSample.
     * 
     * @param elevation The elevation value.
     */
    HeightmapSample(int32 elevation);
    
    /*!
     * @brief  Creates a new instance of HeightmapSample.
     * 
     * @param elevation The elevation value.
     * @param diffuse The diffuse color value.
     */
    HeightmapSample(int32 elevation, int32 diffuse);
    
    /*!
     * @brief  Creates a new instance of HeightmapSample.
     * 
     * @param elevation The elevation value.
     * @param diffuse The diffuse color value.
     * @param displacementX The displacement value along the X-axis.
     * @param displacementY The displacement value along the Y-axis.
     * @param displacementZ The displacement value along the Z-axis.
     */
    HeightmapSample(int32 elevation, int32 diffuse, int32 displacementX, int32 displacementY, int32 displacementZ);
    
    /*!
     * @brief  Creates a new instance of HeightmapSample.
     * 
     * @param elevation The elevation value.
     * @param diffuse The diffuse color value.
     * @param displacementX The displacement value along the X-axis.
     * @param displacementY The displacement value along the Y-axis.
     * @param displacementZ The displacement value along the Z-axis.
     * @param detail0 Values for detail channels 0 to 3.
     * @param detail1 Values for detail channels 4 to 7.
     * @param detail2 Values for detail channels 8 to 11.
     * @param detail3 Values for detail channels 12 to 15.
     */
    HeightmapSample(int32 elevation, int32 diffuse, int32 displacementX, int32 displacementY, int32 displacementZ, int32 detail0, int32 detail1, int32 detail2, int32 detail3);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Clamps the given heightmap sample value.
     * 
     * @param value The input value.
     * 
     * @return <b>[0..#MaxValue]</b>  The output value.
     */
    static int32 Clamp(int64 value);
    
    /*!
     * @brief  Returns a heightmap sample predicate when the diffuse color (see HeightmapSample)is 
     *         not equal to the given color key.
     * 
     * @param colorKey The color key.
     * 
     * @return <b>[not-null]</b>  The heightmap sample predicate.
     * 
     * @see IHeightmap::Concat
     */
    static Ptr<IPredicate<Ref<HeightmapSample> > > DiffuseNotEqual(int32 colorKey);
    
    /*!
     * @brief  Creates a new instance of HeightmapSample.
     * 
     * @return <b>[not-null]</b>  The created heightmap sample.
     */
    static Ptr<HeightmapSample> New();
    
    /*!
     * @brief  Adds the given heightmap sample to this one and stores the result back into 
     *         this HeightmapSample object.
     * 
     * The #Add and #Sub method use modulo integer arithmetics and thus perform no value clamping.
     * This allows to compute delta values between heightmap samples,which is useful for creating 
     * composite heightmaps (ie. a immutable base heightmap and a mutable delta heightmap).
     * 
     * @param sample <b>[not-null]</b>  The heightmap sample.
     * 
     * @see #Sub
     */
    void Add(HeightmapSample* sample);
    
    /*!
     * @brief  Clears all heightmap sample values (ie. zero elevation,transparent black diffuse 
     *         color and no displacement).
     */
    void Clear();
    
    /*!
     * @brief  Copies sample data from the given heightmap sample to this one.
     * 
     * @param other <b>[not-null]</b>  The other heightmap sample.
     * @param layers The heightmap layer mask.
     */
    void Copy(HeightmapSample* other, HeightmapLayer layers);
    
    /*!
     * @brief  Compares this heightmap sample and the given one for equality.
     * 
     * @param sample <b>[not-null]</b>  The heightmap sample.
     * 
     * @return \c true  if both heightmap samples are equal,\c false  if not.
     */
    bool Equals(HeightmapSample* sample);
    
    /*!
     * @brief  Mixes the given heightmap samples and writes the mixed heightmap sample back to this 
     *         heightmap sample.
     * 
     * This method uses discrete linear interpolation.
     * 
     * @param a First heightmap sample.
     * @param b Second heightmap sample.
     * @param f Mix factor in the range <c>[0..65536]</c>.
     */
    void Mix(HeightmapSample* a, HeightmapSample* b, int32 f);
    
    /*!
     * @brief  Mixes the given heightmap samples and writes the mixed heightmap sample back to this 
     *         heightmap sample.
     * 
     * This method uses a discrete Catmull-Rom spline for interpolation.
     * 
     * @param a First heightmap sample.
     * @param b Second heightmap sample.
     * @param c Third heightmap sample.
     * @param d Fourth heightmap sample.
     * @param f Mix factor in the range <c>[0..65536]</c>.
     */
    void Mix(HeightmapSample* a, HeightmapSample* b, HeightmapSample* c, HeightmapSample* d, int32 f);
    
    /*!
     * @brief  Sets this heightmap sample to the given one.
     * 
     * @param sample The heightmap sample.
     */
    void Set(HeightmapSample* sample);
    
    Ptr<HeightmapSample> SetDetail0(int32 detail0);
    
    Ptr<HeightmapSample> SetDetail1(int32 detail1);
    
    Ptr<HeightmapSample> SetDetail2(int32 detail2);
    
    Ptr<HeightmapSample> SetDetail3(int32 detail3);
    
    Ptr<HeightmapSample> SetDiffuse(int32 diffuse);
    
    Ptr<HeightmapSample> SetDisplacement(int32 x, int32 y, int32 z);
    
    Ptr<HeightmapSample> SetElevation(int32 elevation);
    
    /*!
     * @brief  Subtracts the given heightmap sample from this one and stores the result back into 
     *         this HeightmapSample object:
     *         <pre>
     *             this := this - sample
     *         </pre>
     * 
     * The #Add and #Sub method use modulo integer arithmetics and thus perform no value clamping.
     * This allows to compute delta values between heightmap samples,which is useful for creating 
     * composite heightmaps (ie. a immutable base heightmap and a mutable delta heightmap).
     * 
     * @param sample <b>[not-null]</b>  The heightmap sample.
     * 
     * @see #Add
     */
    void Sub(HeightmapSample* sample);
    
    /*!
     * @brief  Subtracts this heightmap sample from the given one,rounds the difference value in 
     *         order to avoid precision errors and stores the result back into this HeightmapSample 
     *         object:
     *         <pre>
     *             this = round(sample - this)
     *         </pre>
     * 
     * The #Add and #Sub method use modulo integer arithmetics and thus perform no value clamping.
     * This allows to compute delta values between heightmap samples,which is useful for creating 
     * composite heightmaps (ie. a immutable base heightmap and a mutable delta heightmap).
     * 
     * @param sample <b>[not-null]</b>  The heightmap sample.
     * @param elevationBits <b>[0..30]</b>  The number of significant elevation bits.
     * @param displacementBits <b>[0..30]</b>  The number of significant displacement bits.
     * 
     * @see #Add
     */
    void SubInvRound(HeightmapSample* sample, int32 elevationBits, int32 displacementBits);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Adds the given color values.
     * 
     * @param a First color value.
     * @param b Second color value.
     * 
     * @return The resulting color value.
     */
    static int32 AddColor(int32 a, int32 b);
    
    /*!
     * @brief  Subtracts the second color value from the first one.
     * 
     * @param a First color value.
     * @param b Second color value.
     * 
     * @return The resulting color value.
     */
    static int32 SubtractColor(int32 a, int32 b);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<HeightmapSample> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x74DD125;
    
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
      return (void*) 0;
    }
  };
  
} } } 

#endif
