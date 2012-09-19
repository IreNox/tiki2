////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_IMAGING_SCALEIMAGEREADER_H
#define CLODDY_API_IMAGING_SCALEIMAGEREADER_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/ImageReaderBase.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Imaging { class IImageReader; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Imaging { class ScaleImageReader_XMag; } } }
namespace Cloddy { namespace API { namespace Imaging { class ScaleImageReader_XMin; } } }
namespace Cloddy { namespace API { namespace Imaging { class ScaleImageReader_YMag; } } }
namespace Cloddy { namespace API { namespace Imaging { class ScaleImageReader_YMin; } } }

// Declare class ::Cloddy::API::Imaging::ScaleImageReader.

namespace Cloddy { namespace API { namespace Imaging
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Base class for IImageReader implementations that perform image scaling.
   */
  class ScaleImageReader : public ImageReaderBase
  {
    // Declare friend classes.
    
    friend class ScaleImageReader_XMag;
    friend class ScaleImageReader_XMin;
    friend class ScaleImageReader_YMag;
    friend class ScaleImageReader_YMin;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual Ptr<IImageReader> Normalize(float32 min, float32 max, float32 noData);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Attributes
    // ---------------------------------------------------------------------------------------------
  protected:
    
    /*!
     * @brief  The source image reader.
     */
    Ptr<IImageReader> sourceImageReader;
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Mixes the first and second value.
     * 
     * @param a Zeroth value.
     * @param b First value.
     * @param c Second value.
     * @param d Third value.
     * @param f Mix factor in the range <c>[0..65536]</c>.
     * 
     * @return <b>[0..65535]</b>  The mixed value.
     */
    static int32 Mix16(int32 a, int32 b, int32 c, int32 d, int32 f);
    
    /*!
     * @brief  Mixes the first and second value.
     * 
     * @param a Zeroth value.
     * @param b First value.
     * @param c Second value.
     * @param d Third value.
     * @param f Mix factor in the range <c>[0..65536]</c>.
     * 
     * @return <b>[0..255]</b>  The mixed value.
     */
    static int32 Mix8(int32 a, int32 b, int32 c, int32 d, int32 f);
    
    virtual void DisposeManaged();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Creates a new instance of ScaleImageReader.
     * 
     * @param sourceImageReader The source image reader.
     */
    ScaleImageReader(IImageReader* sourceImageReader);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<ScaleImageReader> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x84A06C24;
    
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
      if ((ptr = ImageReaderBase::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
