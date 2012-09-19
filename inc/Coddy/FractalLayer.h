////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_FRACTAL_FRACTALLAYER_H
#define CLODDY_API_HEIGHTMAPS_FRACTAL_FRACTALLAYER_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/HeightmapLayer.h"

// Include referenced interfaces.

#include "Cloddy/IFractalLayer.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Fractal { class IFractalDiffuseCombiner; } } } }
namespace Cloddy { namespace API { namespace Procedural { class INoiseFunction; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Heightmaps { class HeightmapSample; } } }

// Declare class ::Cloddy::API::Heightmaps::Fractal::FractalLayer.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Fractal
{
  // Use referenced namespaces.
  
  using namespace Cloddy::API::Heightmaps;
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Procedural::INoiseFunction;
  
  /*!
   * @brief  Abstract base class for IFractalLayer implementations.
   */
  class FractalLayer : public virtual IFractalLayer
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual HeightmapLayer GetLayerMask() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Returns a IFractalLayer object that computes HeightmapSample::Detail0 values using 
     *         the given noise functions and diffuse color combiner.
     * 
     * The value of a diffuse color combiner argument is set to \c 1  if no noise function has been 
     * specified (ie. the parameter was \c null ).
     * 
     * @param a Noise function for 1st diffuse color combiner argument.
     * @param b Noise function for 2nd diffuse color combiner argument.
     * @param c Noise function for 3rd diffuse color combiner argument.
     * @param d Noise function for 4th diffuse color combiner argument.
     * @param combiner <b>[not-null]</b>  The diffuse color combiner.
     * 
     * @return <b>[not-null]</b>  The fractal layer.
     */
    static Ptr<IFractalLayer> Detail0(INoiseFunction* a, INoiseFunction* b, INoiseFunction* c, INoiseFunction* d, IFractalDiffuseCombiner* combiner);
    
    /*!
     * @brief  Returns a IFractalLayer object that computes HeightmapSample::Detail1 values using 
     *         the given noise functions and diffuse color combiner.
     * 
     * The value of a diffuse color combiner argument is set to \c 1  if no noise function has been 
     * specified (ie. the parameter was \c null ).
     * 
     * @param a Noise function for 1st diffuse color combiner argument.
     * @param b Noise function for 2nd diffuse color combiner argument.
     * @param c Noise function for 3rd diffuse color combiner argument.
     * @param d Noise function for 4th diffuse color combiner argument.
     * @param combiner <b>[not-null]</b>  The diffuse color combiner.
     * 
     * @return <b>[not-null]</b>  The fractal layer.
     */
    static Ptr<IFractalLayer> Detail1(INoiseFunction* a, INoiseFunction* b, INoiseFunction* c, INoiseFunction* d, IFractalDiffuseCombiner* combiner);
    
    /*!
     * @brief  Returns a IFractalLayer object that computes HeightmapSample::Detail2 values using 
     *         the given noise functions and diffuse color combiner.
     * 
     * The value of a diffuse color combiner argument is set to \c 1  if no noise function has been 
     * specified (ie. the parameter was \c null ).
     * 
     * @param a Noise function for 1st diffuse color combiner argument.
     * @param b Noise function for 2nd diffuse color combiner argument.
     * @param c Noise function for 3rd diffuse color combiner argument.
     * @param d Noise function for 4th diffuse color combiner argument.
     * @param combiner <b>[not-null]</b>  The diffuse color combiner.
     * 
     * @return <b>[not-null]</b>  The fractal layer.
     */
    static Ptr<IFractalLayer> Detail2(INoiseFunction* a, INoiseFunction* b, INoiseFunction* c, INoiseFunction* d, IFractalDiffuseCombiner* combiner);
    
    /*!
     * @brief  Returns a IFractalLayer object that computes HeightmapSample::Detail3 values using 
     *         the given noise functions and diffuse color combiner.
     * 
     * The value of a diffuse color combiner argument is set to \c 1  if no noise function has been 
     * specified (ie. the parameter was \c null ).
     * 
     * @param a Noise function for 1st diffuse color combiner argument.
     * @param b Noise function for 2nd diffuse color combiner argument.
     * @param c Noise function for 3rd diffuse color combiner argument.
     * @param d Noise function for 4th diffuse color combiner argument.
     * @param combiner <b>[not-null]</b>  The diffuse color combiner.
     * 
     * @return <b>[not-null]</b>  The fractal layer.
     */
    static Ptr<IFractalLayer> Detail3(INoiseFunction* a, INoiseFunction* b, INoiseFunction* c, INoiseFunction* d, IFractalDiffuseCombiner* combiner);
    
    /*!
     * @brief  Returns a IFractalLayer object that computes HeightmapSample::Diffuse values using 
     *         the given noise functions and diffuse color combiner.
     * 
     * The value of a diffuse color combiner argument is set to \c 1  if no noise function has been 
     * specified (ie. the parameter was \c null ).
     * 
     * @param a Noise function for 1st diffuse color combiner argument.
     * @param b Noise function for 2nd diffuse color combiner argument.
     * @param c Noise function for 3rd diffuse color combiner argument.
     * @param d Noise function for 4th diffuse color combiner argument.
     * @param combiner <b>[not-null]</b>  The diffuse color combiner.
     * 
     * @return <b>[not-null]</b>  The fractal layer.
     */
    static Ptr<IFractalLayer> Diffuse(INoiseFunction* a, INoiseFunction* b, INoiseFunction* c, INoiseFunction* d, IFractalDiffuseCombiner* combiner);
    
    /*!
     * @brief  Returns a IFractalLayer object that 
     *         computes HeightmapSample::DisplacementX,HeightmapSample::DisplacementY 
     *         and HeightmapSample::DisplacementZ values using the given noise function.
     * 
     * The noise values returned by the given functions are expected to be within the 
     * range <b>[..1]</b>.They are automatically transformed to valid heightmap sample values (
     * see HeightmapSample::MaxValue).
     * 
     * @param x <b>[not-null]</b>  The noise function for displacement along the terrain space 
     * X-axis.
     * @param y <b>[not-null]</b>  The noise function for displacement along the terrain space 
     * Y-axis.
     * @param z <b>[not-null]</b>  The noise function for displacement along the terrain space 
     * Z-axis.
     * 
     * @return <b>[not-null]</b>  The fractal layer.
     */
    static Ptr<IFractalLayer> Displacement(INoiseFunction* x, INoiseFunction* y, INoiseFunction* z);
    
    /*!
     * @brief  Returns a IFractalLayer object that computes HeightmapSample::Elevation values using 
     *         the given \e function .
     * 
     * The noise values returned by \e function  are expected to be within the range <b>[0..1]</b>.
     * They are automatically scaled to valid heightmap sample values (
     * see HeightmapSample::MaxValue).
     * 
     * @param function <b>[not-null]</b>  The noise function.
     * 
     * @return <b>[not-null]</b>  The fractal layer.
     */
    static Ptr<IFractalLayer> Elevation(INoiseFunction* function);
    
    virtual Ptr<IFractalLayer> Append(IFractalLayer* layer);
    
    virtual void ComputeHeightmapSample(float64 x, float64 y, float64 z, HeightmapSample* sample) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<FractalLayer> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x924FDCD5;
    
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
      if ((ptr = IFractalLayer::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } 

#endif
