////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_IMAGING_BLENDIMAGEREADER_H
#define CLODDY_API_IMAGING_BLENDIMAGEREADER_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/ImageReaderBase.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Imaging { class IImageReader; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Imaging { class ImageReaderBase; } } }
namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::API::Imaging::BlendImageReader.

namespace Cloddy { namespace API { namespace Imaging
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced classes.
  
  using CodeX::System::ByteBuffer;
  
  /*!
   * @brief  An IImageReader implementation that reads a BlendImage.
   */
  class BlendImageReader : public ImageReaderBase
  {
    // Declare friend classes.
    
    friend class ImageReaderBase;
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
  protected:
    
    virtual void DisposeManaged();
    
    virtual void DoReadScanline(int32 scanlineY, ByteBuffer* scanline);
    
    virtual void DoSkipScanlines(int32 count);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The input image that contains the per pixel blend factors.
     */
    Ptr<IImageReader> blend;
    
    /*!
     * @brief  Scanline buffer for #blend.
     */
    Ptr<ByteBuffer> blendScanline;
    
    /*!
     * @brief  The first input image.
     */
    Ptr<IImageReader> first;
    
    /*!
     * @brief  Scanline buffer for #first.
     */
    Ptr<ByteBuffer> firstScanline;
    
    /*!
     * @brief  The second input image.
     */
    Ptr<IImageReader> second;
    
    /*!
     * @brief  Scanline buffer for #second.
     */
    Ptr<ByteBuffer> secondScanline;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of BlendImageReader.
     * 
     * @param first The first input image.
     * @param second The second input image.
     * @param blend The input image that contains the per pixel blend factors.
     */
    BlendImageReader(IImageReader* first, IImageReader* second, IImageReader* blend);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Blends the given 8-bit values,interpreting them as unsigned values.
     * 
     * @param first First input value.
     * @param second Second input value.
     * @param factor The blend factor in the range <c>[0..255]</c>.
     * 
     * @return The resulting value.
     */
    static int8 Blend(int8 first, int8 second, int8 factor);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<BlendImageReader> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xA87E0DD;
    
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
