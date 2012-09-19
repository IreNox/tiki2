////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_DATASETS_BUILDER_DEM_ASTERBLENDIMAGEREADER_H
#define CLODDY_API_DATASETS_BUILDER_DEM_ASTERBLENDIMAGEREADER_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/ImageReaderBase.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Imaging { class IImageReader; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Datasets { namespace Builder { namespace DEM { class AsterBlendImage; } } } } }
namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::API::Datasets::Builder::DEM::AsterBlendImageReader.

namespace Cloddy { namespace API { namespace Datasets { namespace Builder { namespace DEM
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Imaging::IImageReader;
  
  // Use referenced classes.
  
  using Cloddy::API::Imaging::ImageReaderBase;
  using CodeX::System::ByteBuffer;
  
  class AsterBlendImageReader : public ImageReaderBase
  {
    // Declare friend classes.
    
    friend class AsterBlendImage;
    
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
    
    static const Array<int32> BlendCurve;
    
    /*!
     * @brief  Scanline buffer for #num.
     */
    Ptr<ByteBuffer> bufferNum;
    
    /*!
     * @brief  Scanline buffer for #ocean.
     */
    Ptr<ByteBuffer> bufferOcean;
    
    /*!
     * @brief  The ASTER GDEM quality image.
     */
    Ptr<IImageReader> num;
    
    /*!
     * @brief  The ocean mask image.
     */
    Ptr<IImageReader> ocean;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    AsterBlendImageReader(IImageReader* num, IImageReader* ocean);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<AsterBlendImageReader> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x92A65B5A;
    
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
  
} } } } } 

#endif
