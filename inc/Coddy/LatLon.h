////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_PROJECTION_LATLON_H
#define CLODDY_API_HEIGHTMAPS_PROJECTION_LATLON_H

#include "CodeX/System.h"

// Include referenced structures.

#include "Cloddy/Vec2D.h"
#include "Cloddy/Vec3D.h"
#include "Cloddy/Vec3I.h"

// Forward declare referenced structures.

namespace Cloddy { namespace Core { namespace Math { namespace Vectors { struct Vec2I; } } } }

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Geometries { class IGeometry; } } }
namespace Cloddy { namespace API { namespace Heightmaps { namespace Projection { class IMapProjection; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { template<class> class IStructSerializer; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Projection { class LatLon_Serializer; } } } }

// Declare class ::Cloddy::API::Heightmaps::Projection::LatLon.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Projection
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced structures.
  
  using Cloddy::Core::Math::Vectors::Vec2D;
  using Cloddy::Core::Math::Vectors::Vec2I;
  using Cloddy::Core::Math::Vectors::Vec3D;
  using Cloddy::Core::Math::Vectors::Vec3I;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Geometries::IGeometry;
  using Cloddy::Core::IO::Serialization::IStructSerializer;
  
  /*!
   * @brief  A set of longitude/latitude coordinates,measured in degress,with 64-bit floating-point 
   *         precision.
   * 
   * A set of longitude/latitude values represent a location on a planetary body,for example on 
   * earth:
   * <pre>
   *     +---------------------------------------------------------------------------------+  90?N
   *     |                     @@@@ @@@@@@@@@@@@@@@@     @@@@@@           @@                             | +90?  
   *     |             @@           @@@@@@@@@@@@              @@     @@@@@@@@                          |   
   *     |    @@@@@@@@  @@  @@@@@@ @@   @@    @@@@@@@@@@        @@      @@ @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  @@             |   
   *     |  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@   @@@@@@  @@@@           @@ @@@@ @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@         |   
   *     | @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@   @@     @@          @@  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  @@@@          |   
   *     |      @@@@@@@@@@@@@@@@@@   @@@@@@                @@  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                |   
   *     |      @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@             @@  @@@@ @@@@@@@@@@@@@@@@@@@@@@ @@@@@@@@@@@@@@@@@@@@@@@@@@    @@           |   
   *     |      @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@              @@@@@@ @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@              |   
   *     |      @@@@@@@@@@@@@@  @@@@@@@@@@              @@@@@@ @@@@@@@@@@ @@@@ @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ @@@@@@@@              |   
   *     |     @@@@@@@@@@@@@@@@@@@@@@@@@@              @@@@   @@  @@   @@@@ @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  @@            |   
   *     |     @@@@@@@@@@@@@@@@@@@@@@                @@@@    @@@@ @@@@@@@@@@  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                  |   
   *     |     @@@@@@@@@@@@@@@@@@@@@@                  @@@@@@      @@@@@@@@@@@@@@@@@@@@ @@@@@@@@@@@@@@@@@@@@  @@ @@            |   
   *     |     @@@@@@@@@@@@@@@@@@                  @@@@@@@@@@@@     @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                |   
   *     |      @@@@@@@@                      @@@@@@@@@@@@@@@@@@@@@@@@@@@@ @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                |   
   *     |       @@@@@@                     @@@@@@@@@@@@@@@@@@@@@@@@ @@@@@@@@   @@@@@@@@@@@@ @@ @@@@@@@@@@                |    L
   *     |       @@@@     @@               @@@@@@@@@@@@@@@@@@ @@@@@@@@ @@@@@@@@@@  @@@@@@@@@@ @@@@@@@@@@                  |    a
   *     |        @@@@@@@@  @@               @@@@@@@@@@@@@@@@ @@@@@@@@@@ @@@@@@@@    @@@@@@   @@ @@                   |    t
   *     |          @@@@@@                 @@@@@@@@@@@@@@@@@@@@@@@@@@@@  @@       @@     @@ @@                  |    i
   *     |               @@@@              @@@@@@@@@@@@@@@@@@@@@@@@@@@@  @@      @@      @@@@                  + 0? t  
   *     |              @@@@@@@@@@            @@@@  @@@@ @@@@@@@@@@@@@@@@@@        @@    @@      @@ @@         @@ |    u
   *     |              @@@@@@@@@@@@@@                @@@@@@@@@@@@@@@@@@@@                 @@                |    d 
   *     |             @@@@@@@@@@@@@@@@                @@@@@@@@@@@@@@@@@@              @@  @@@@                |    e
   *     |             @@@@@@@@@@@@@@@@@@@@@@             @@@@@@@@@@@@@@@@                @@  @@   @@@@@@@@         |   
   *     |             @@@@@@@@@@@@@@@@@@@@@@@@             @@@@@@@@@@@@@@                 @@        @@@@        |   
   *     |              @@@@@@@@@@@@@@@@@@@@@@             @@@@@@@@@@@@@@                            @@       |   
   *     |               @@@@@@@@@@@@@@@@@@              @@@@@@@@@@@@@@                       @@@@ @@         |   
   *     |                @@@@@@@@@@@@@@@@               @@  @@@@  @@                   @@@@@@@@@@@@         |   
   *     |                @@@@@@ @@@@@@@@              @@@@@@@@@@   @@                  @@@@@@@@@@@@@@@@        |   
   *     |                @@@@@@ @@@@                @@ @@@@@@                     @@@@@@@@@@@@@@@@@@        |   
   *     |                @@@@@@@@@@@@                  @@@@@@                    @@@@@@@@@@@@@@@@@@@@        |   
   *     |                 @@@@@@@@                  @@@@@@                      @@@@@@ @@@@@@@@@@        |   
   *     |                 @@@@@@                                                 @@@@@@     @@   |   
   *     |                 @@@@                                                          @@   |   
   *     |                 @@@@                                                  @@           |   
   *     |                 @@@@                                                       @@      |   
   *     |                  @@                                                              |   
   *     |                   @@                                                             |  90?S    
   *     +-----------------------------------------+---------------------------------------+ -90?
   *     180?W                                    0?                                  180?E
   *     -180?                                 Longitude                              +180?
   * </pre>
   * The mapping from longitude/latitude coordinates to cubemap coordinates (see Cubemap class)is 
   * defined as follows:
   * <pre>
   *     .   Cubemap | Face center lies at:
   *     .    face   | Longitude | Latitude
   *     .   --------+-----------+---------
   *     .      X-   |     90?W  |   0?N  
   *     .           |    -90?   |   0?    
   *     .   --------+-----------+---------
   *     .      X+   |     90?E  |   0?N  
   *     .           |    +90?   |   0?    
   *     .   --------+-----------+---------
   *     .      Y-   |      0?E  |  90?N  
   *     .           |      0?   | +90?    
   *     .   --------+-----------+---------
   *     .      Y+   |      0?E  |  90?S  
   *     .           |      0?   | -90?    
   *     .   --------+-----------+---------
   *     .      Z-   |      0?E  |   0?N  
   *     .           |      0?   |   0?    
   *     .   --------+-----------+---------
   *     .      Z+   |    180?W  |   0?N  
   *     .           |   -180?   |   0?    
   * </pre>
   */
  struct LatLon : StructType
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Constants
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  One degree longitude/latitude.
     */
    static const float64 OneDegree;
    
    /*!
     * @brief  One thousandth of a second longitude/latitude.
     */
    static const float64 OneMillisecond;
    
    /*!
     * @brief  One minute longitude/latitude.
     */
    static const float64 OneMinue;
    
    /*!
     * @brief  One second longitude/latitude.
     */
    static const float64 OneSecond;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  180?E 0?N 
     */
    static const LatLon East;
    
    /*!
     * @brief  0?E 90?N 
     */
    static const LatLon North;
    
    /*!
     * @brief  180?E 90?N 
     */
    static const LatLon NorthEast;
    
    /*!
     * @brief  180?W 90?N 
     */
    static const LatLon NorthWest;
    
    /*!
     * @brief  The serialization helper object for values of LatLon.
     */
    static const StaticPtr<IStructSerializer<Val<LatLon> > > Serializer;
    
    /*!
     * @brief  0?E 90?S 
     */
    static const LatLon South;
    
    /*!
     * @brief  180?E 90?S 
     */
    static const LatLon SouthEast;
    
    /*!
     * @brief  180?W 90?S 
     */
    static const LatLon SouthWest;
    
    /*!
     * @brief  180?W 0?N 
     */
    static const LatLon West;
    
    /*!
     * @brief  0?E 0?N 
     */
    static const LatLon Zero;
    
    /*!
     * @brief  The latitude in the range <c>[-90..90]</c>.
     */
    float64 Latitude;
    
    /*!
     * @brief  The longitude in the range <c>[-180..180]</c>.
     */
    float64 Longitude;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of LatLon.
     * 
     * @param latitude The latitude in the range <c>[-90..90]</c>.
     * @param longitude The longitude in the range <c>[-180..180]</c>.s
     */
    LatLon(float64 latitude, float64 longitude);
    
    /*!
     * @brief  Creates a new instance of LatLon.
     * 
     * @param latDeg The latitude degrees.
     * @param latMin The latitude minutes.
     * @param latSec The latitude seconds.
     * @param lonDeg The longitude degrees.
     * @param lonMin The longitude minutes.
     * @param lonSec The longitude seconds.
     */
    LatLon(float64 latDeg, float64 latMin, float64 latSec, float64 lonDeg, float64 lonMin, float64 lonSec);
    
    LatLon();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Translates the given geocentric coordinates to longitude/latitude coordinates.
     * 
     * @param coords The geocentric coordinates.
     * @param geometry <b>[not-null]</b>  The geometry object.
     * 
     * @return The longitude/latitude coordinates.
     */
    static LatLon FromCoords(const Vec3D& coords, IGeometry* geometry);
    
    /*!
     * @brief  Translates the given geocentric coordinates to longitude/latitude coordinates.
     * 
     * @param x The geocentric X-coordinate.
     * @param y The geocentric Y-coordinate.
     * @param z The geocentric Z-coordinate.
     * @param geometry <b>[not-null]</b>  The geometry object.
     * 
     * @return The longitude/latitude coordinates.
     */
    static LatLon FromCoords(float64 x, float64 y, float64 z, IGeometry* geometry);
    
    /*!
     * @brief  Converts the given cubemap coordinates to longitude/latitude coordinates.
     * 
     * @param cube The cubemap coordinates.
     * @param n Size of cubemap,minus one.
     * 
     * @return The longitude/latitude coordinates.
     */
    static LatLon FromCube(const Vec3I& cube, int32 n);
    
    /*!
     * @brief  Converts the given cubemap coordinates to longitude/latitude coordinates.
     * 
     * @param x The cubemap X-coordinate.
     * @param y The cubemap X-coordinate.
     * @param z The cubemap X-coordinate.
     * @param n Size of cubemap,minus one.
     * 
     * @return The longitude/latitude coordinates.
     */
    static LatLon FromCube(int32 x, int32 y, int32 z, int32 n);
    
    /*!
     * @brief  Converts the given cubemap coordinates to longitude/latitude coordinates.
     * 
     * @param cube The cubemap coordinates.
     * @param n Size of cubemap,minus one.
     * 
     * @return The longitude/latitude coordinates.
     */
    static LatLon FromCube(const Vec3D& cube, int32 n);
    
    /*!
     * @brief  Converts the given cubemap coordinates to longitude/latitude coordinates.
     * 
     * @param x The cubemap X-coordinate.
     * @param y The cubemap X-coordinate.
     * @param z The cubemap X-coordinate.
     * @param n Size of cubemap,minus one.
     * 
     * @return The longitude/latitude coordinates.
     */
    static LatLon FromCube(float64 x, float64 y, float64 z, int32 n);
    
    /*!
     * @brief  Translates the given local map coordinates to longitude/latitude coordinates using 
     *         the specified map projection.
     * 
     * @param xy The local map coordinates.
     * @param projection <b>[not-null]</b>  The map projection.
     * 
     * @return The longitude/latitude coordinates.
     */
    static LatLon FromMap(const Vec2I& xy, IMapProjection* projection);
    
    /*!
     * @brief  Translates the given local map coordinates to longitude/latitude coordinates using 
     *         the specified map projection.
     * 
     * @param xy The local map coordinates.
     * @param projection <b>[not-null]</b>  The map projection.
     * 
     * @return The longitude/latitude coordinates.
     */
    static LatLon FromMap(const Vec2D& xy, IMapProjection* projection);
    
    /*!
     * @brief  Translates the given local map coordinates to longitude/latitude coordinates using 
     *         the specified map projection.
     * 
     * @param x The local map X-coordinate.
     * @param y The local map Y-coordinate.
     * @param projection <b>[not-null]</b>  The map projection.
     * 
     * @return The longitude/latitude coordinates.
     */
    static LatLon FromMap(float64 x, float64 y, IMapProjection* projection);
    
    /*!
     * @brief  Creates a LatLon value from the given string representation.
     * 
     * @param str <b>[not-null]</b>  The string representation.
     * 
     * @return The LatLon value.
     * 
     * @see #ToString
     */
    static LatLon FromString(String str);
    
    /*!
     * @brief  Creates a LatLon value from the given string representation.
     * 
     * @param str <b>[not-null]</b>  The string representation.
     * @param latLon The output LatLon value.
     * 
     * @return The LatLon value.
     * 
     * @see #ToString
     */
    static bool FromString(String str, LatLon& latLon);
    
    /*!
     * @brief  Adds the given longitude/latitude values to this LatLon value.
     * 
     * @param longitude The value to add to the longitude of this value.
     * @param latitude The value to add to the latitude of this value.
     * 
     * @return The resulting LatLon value (#Normalize)should be called on the returned value in 
     * order to avoid range overflows).
     */
    LatLon Add(float64 longitude, float64 latitude) const;
    
    /*!
     * @brief  Adds the given longitude/latitude values to this LatLon value.
     * 
     * @param value The longitude/latitude values to add to this value.
     * 
     * @return The resulting LatLon value (#Normalize)should be called on the returned value in 
     * order to avoid range overflows).
     */
    LatLon Add(const LatLon& value) const;
    
    /*!
     * @brief  Divides the longitude and latitude values of this LatLon value by the given scalar.
     * 
     * @param value The scalar value to divide by.
     * 
     * @return The resulting LatLon value (#Normalize)should be called on the returned value in 
     * order to avoid range overflows).
     */
    LatLon Div(float64 value) const;
    
    /*!
     * @brief  Compares this LatLon value with the given one.
     * 
     * @param other The other LatLon value.
     * 
     * @return \c true  if both values are equal,\c false  if they are not.
     */
    bool Equals(const LatLon& other) const;
    
    /*!
     * @brief  Multiplies the longitude/latitude values of this LatLon value by the given scalar 
     *         factor.
     * 
     * @param value The scalar multiplication factor.
     * 
     * @return The resulting LatLon value (#Normalize)should be called on the returned value in 
     * order to avoid range overflows).
     */
    LatLon Mul(float64 value) const;
    
    /*!
     * @brief  Negates the longitude and latitude values of this LatLon value.
     * 
     * @return The resulting LatLon value.
     */
    LatLon Neg() const;
    
    /*!
     * @brief  Normalizes this pair of latitude/longitude values so that the longitude value lies 
     *         in the range <c>[-180..180]</c> and the latitude lies within <c>[-90..90]</c>.
     * 
     * Longitude values are wrapped at the normalization range boundaries;latitude values are 
     * clamped to the range boundaries.
     * 
     * @return The normalized value pair.
     */
    LatLon Normalize() const;
    
    /*!
     * @brief  Subtracts the given longitude/latitude values from this LatLon value.
     * 
     * @param longitude The value to subtract from the longitude of this value.
     * @param latitude The value to subtract from the latitude of this value.
     * 
     * @return The resulting LatLon value (#Normalize)should be called on the returned value in 
     * order to avoid range overflows).
     */
    LatLon Sub(float64 longitude, float64 latitude) const;
    
    /*!
     * @brief  Subtracts the given longitude/latitude values from this LatLon value.
     * 
     * @param value The longitude/latitude values to subtract from this value.
     * 
     * @return The resulting LatLon value (#Normalize)should be called on the returned value in 
     * order to avoid range overflows).
     */
    LatLon Sub(const LatLon& value) const;
    
    /*!
     * @brief  Translates these longitude/latitude coordinates into geocentric coordinates.
     * 
     * @param elevation <b>[>=0]</b>  The elevation value (see HeightmapSample::MaxValue).
     * @param geometry <b>[not-null]</b>  The geometry object.
     * 
     * @return The geocentric coordinates.
     */
    Vec3D ToCoords(int32 elevation, IGeometry* geometry) const;
    
    /*!
     * @brief  Converts this set of longitude/latitude coordinates to cubemap coordinates.
     * 
     * @param n Size of cubemap,minus one.
     * 
     * @return The cubemap coordinates.
     */
    Vec3D ToCubeD(int32 n) const;
    
    /*!
     * @brief  Converts this set of longitude/latitude coordinates to cubemap coordinates.
     * 
     * @param n Size of cubemap,minus one.
     * 
     * @return The cubemap coordinates.
     */
    Vec3I ToCubeI(int32 n) const;
    
    /*!
     * @brief  Translates these latitude/longitude coordinates to local map coordinates using the 
     *         given map projection.
     * 
     * @param projection <b>[not-null]</b>  The map projection.
     * 
     * @return The local map coordinates.
     */
    Vec2D ToMap(IMapProjection* projection) const;
    
    /*!
     * @brief  Returns the string representation of this set of longitude/latitude coordinates.
     * 
     * @return <b>[not-null]</b>  The string representation.
     * 
     * @see #FromString(String)
     */
    String ToString() const;
    
    // ---------------------------------------------------------------------------------------------
    //  Copy constructor and copy assignment operator
    // ---------------------------------------------------------------------------------------------
  public:
    
    LatLon(const LatLon& other);
    
    LatLon& operator=(const LatLon& other);
    
    // ---------------------------------------------------------------------------------------------
    // Static Initializer Functions
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief Static initializer function for field Serializer.
     */
    static Object* StaticInitializer_Serializer();
  };
  
} } } } 

#endif
