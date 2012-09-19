////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_VERTEXFACTORIES_VERTEXFORMATS_NORMALCOMPRESSION_H
#define CLODDY_API_VERTEXFACTORIES_VERTEXFORMATS_NORMALCOMPRESSION_H

#include "CodeX/System.h"

// Include referenced structures.

#include "Cloddy/Vec3D.h"

// Declare class ::Cloddy::API::VertexFactories::VertexFormats::NormalCompression.

namespace Cloddy { namespace API { namespace VertexFactories { namespace VertexFormats
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced structures.
  
  using Cloddy::Core::Math::Vectors::Vec3D;
  
  /*!
   * @brief  This class performs lossy compression of normal vectors.
   * 
   * Normal vectors are compressed into an integer value which refers to a sample on a discrete 
   * cubemap.
   * 
   * The following table shows for a given compressed normal vector bit count (\c bits )the mean 
   * error,the standard deviation of the error and the minimum and maximum error between 
   * uncompressed and decompressed normal vectors:
   * <pre>
   *       .   bits |  mean  | stddev |   min  |   max
   *       .   -----+--------+--------+--------+--------
   *       .      8 | 8,470? | 4,408? | 0,061? | 21,204?
   *       .      9 | 5,342? | 2,734? | 0,027? | 13,401?
   *       .     10 | 3,628? | 1,820? | 0,100? |  8,868?
   *       .     11 | 2,591? | 1,285? | 0,050? |  6,238?
   *       .     12 | 1,783? | 0,870? | 0,042? |  4,268?
   *       .     13 | 1,274? | 0,626? | 0,018? |  3,095?
   *       .     14 | 0,872? | 0,431? | 0,002? |  2,091?
   *       .     15 | 0,624? | 0,304? | 0,005? |  1,484?
   *       .     16 | 0,434? | 0,212? | 0,007? |  1,049?
   *       .     17 | 0,310? | 0,152? | 0,001? |  0,726?
   *       .     18 | 0,217? | 0,105? | 0,003? |  0,519?
   *       .     19 | 0,154? | 0,075? | 0,000? |  0,364?
   *       .     20 | 0,109? | 0,053? | 0,001? |  0,256?
   *       .     21 | 0,076? | 0,037? | 0,001? |  0,179?
   *       .     22 | 0,054? | 0,026? | 0,000? |  0,128?
   *       .     23 | 0,038? | 0,019? | 0,000? |  0,090?
   *       .     24 | 0,027? | 0,013? | 0,000? |  0,063?
   *       .     25 | 0,019? | 0,009? | 0,000? |  0,046?
   *       .     26 | 0,013? | 0,006? | 0,000? |  0,032?
   *       .     27 | 0,010? | 0,005? | 0,000? |  0,022?
   *       .     28 | 0,007? | 0,003? | 0,000? |  0,016?
   *       .     29 | 0,005? | 0,002? | 0,000? |  0,011?
   *       .     30 | 0,003? | 0,002? | 0,000? |  0,008?
   * </pre>
   */
  class NormalCompression : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Returns the maximum value for compressed normal vectors.
     * 
     * The maximum value is guaranteed to be less than <c>2^n-1</c>,where \c n  is the bitcount of 
     * compressed normal vector (see NormalCompression).
     * 
     * @return The maximum compressed normal vector value.
     * 
     * @see #CompressNormal(const Vec3D&)
     * @see #CompressNormal(float64,float64,float64)
     */
    int32 GetMaximum();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of NormalCompression.
     * 
     * @param bits <b>[8..30]</b>  The number of bits to use for compressed normal vectors.
     */
    NormalCompression(int32 bits);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Compresses the given normal vector.
     * 
     * @param normal The normal vector.
     * 
     * @return <b>[0..#GetMaximum]</b>  The compressed normal vector.
     * 
     * @see #DecompressNormal
     */
    int32 CompressNormal(const Vec3D& normal);
    
    /*!
     * @brief  Compresses the given normal vector.
     * 
     * @param x X-coordinate of normal vector.
     * @param y Y-coordinate of normal vector.
     * @param z Z-coordinate of normal vector.
     * 
     * @return <b>[0..#GetMaximum]</b>  The compressed normal vector.
     * 
     * @see #DecompressNormal
     */
    int32 CompressNormal(float64 x, float64 y, float64 z);
    
    /*!
     * @brief  Creates a lookup table for decompressing normal vectors.
     * 
     * The returned lookup table can be used as follows:
     * <pre>
     *     table[nc] := n
     * </pre>
     * where \c nc  is the compressed normal vector in the range <c>[0..Maximum]</c> and \c n  is 
     * the decompressed normal vector.
     * 
     * @return <b>[not-null]</b>  The lookup table.
     * 
     * @see #DecompressNormal
     */
    Array<Vec3D> CreateLookupTable();
    
    /*!
     * @brief  Decompressed the given normal vector.
     * 
     * @param compressedNormal <b>[0..#GetMaximum]</b>  The compressed normal vector.
     * 
     * @return The decompressed normal vector.
     * 
     * @see #CompressNormal(const Vec3D&)
     * @see #CompressNormal(float64,float64,float64)
     */
    Vec3D DecompressNormal(int32 compressedNormal);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The cubemap size.
     */
    int32 size;
    
    /*!
     * @brief  Value of #size,divided by two.
     */
    float64 sizeHalf;
    
    /*!
     * @brief  Value of #size,minus one.
     */
    int32 sizeMinusOne;
    
    /*!
     * @brief  The square of #size.
     */
    int32 sizeSqr;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<NormalCompression> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x82526539;
    
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
  
} } } } 

#endif
