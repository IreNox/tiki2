////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_IMAGING_PATCHIMAGEREADER_H
#define CLODDY_API_IMAGING_PATCHIMAGEREADER_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/PixelFormat.h"

// Include referenced classes.

#include "Cloddy/CompositeImageReader.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Imaging { class IImageReader; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Imaging { class Patch; } } }
namespace Cloddy { namespace API { namespace Imaging { class PatchImage; } } }
namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::API::Imaging::PatchImageReader.

namespace Cloddy { namespace API { namespace Imaging
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced classes.
  
  using CodeX::System::ByteBuffer;
  
  /*!
   * @brief  An IImageReader implementation that reads the patches of a PatchImage as a contiguous 
   *         image.
   */
  class PatchImageReader : public CompositeImageReader
  {
    // Declare friend classes.
    
    friend class PatchImage;
    
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
     * @brief  Scanline buffer used for emitting patches that are partially occluded by others.
     */
    Ptr<ByteBuffer> buffer;
    
    /*!
     * @brief  The image readers for each patch.
     */
    Array<Ptr<IImageReader> > imageReaders;
    
    /*!
     * @brief  The patches of the patchwork.
     */
    Array<Ptr<Patch> > patches;
    
    /*!
     * @brief  Holds the patch indices of those patches that intersect the current row of the patch 
     *         image.
     * 
     * The list of patch indices is terminated by the value \c -1 .
     */
    Array<int32> patchesOnRow;
    
    /*!
     * @brief  X-coordinate of top-left corner of bounding rectangle for all patches (inclusive).
     */
    int32 x1;
    
    /*!
     * @brief  Y-coordinate of top-left corner of bounding rectangle for all patches (inclusive).
     */
    int32 y1;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of PatchImageReader.
     * 
     * @param patches The patches.
     * @param pixelFormat The output pixel format.
     * @param x1 Minimum X-coordinate (inclusive).
     * @param y1 Minimum Y-coordinate (inclusive).
     * @param x2 Maximum X-coordinate (exclusive).
     * @param y2 Maximum Y-coordinate (exclusive).
     */
    PatchImageReader(Array<Ptr<Patch> > patches, PixelFormat pixelFormat, int32 x1, int32 y1, int32 x2, int32 y2);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Fins the patches that intersect the given patch image row.
     * 
     * This method initializes the #patchesOnRow array.
     * 
     * @param y Y-coordinate of the patch image row.
     */
    void FindPatchesOnRow(int32 y);
    
    /*!
     * @brief  Returns the IImageReader for the given patch,creating it if necessary.
     * 
     * @param patchIdx The patch index.
     * 
     * @return <b>[not-null]</b>  The IImageReader object.
     */
    Ptr<IImageReader> GetImageReaderForPatch(int32 patchIdx);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<PatchImageReader> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x716BC570;
    
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
      if ((ptr = CompositeImageReader::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
