////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_BROWSING_IBITMAP_H
#define CLODDY_API_BROWSING_IBITMAP_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/BitmapFormat.h"

// Include referenced interfaces.

#include "CodeX/IDisposable.h"

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Browsing { class BitmapData; } } }

// Declare interface ::Cloddy::API::Browsing::IBitmap.

namespace Cloddy { namespace API { namespace Browsing
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using CodeX::System::IDisposable;
  
  class NO_VTABLE IBitmap : public virtual IDisposable
  {
    // ---------------------------------------------------------------------------------------------
    // Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The storage format of this bitmap.
     * 
     * @return The bitmap pixel format.
     */
    virtual BitmapFormat GetFormat() = 0;
    
    /*!
     * @brief  The bitmap height.
     * 
     * @return <b>[>=0]</b>  The bitmap height,in pixels.
     */
    virtual int32 GetHeight() = 0;
    
    /*!
     * @brief  The bitmap width.
     * 
     * @return <b>[>=0]</b>  The bitmap width,in pixels.
     */
    virtual int32 GetWidth() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Locks a region of this bitmap for reading and/or writing.
     * 
     * @param x <b>[>=0]</b>  X-coordinate of top-left corner of region to lock.
     * @param y <b>[>=0]</b>  Y-coordinate of top-left corner of region to lock.
     * @param width <b>[>0]</b>  Width of region to lock,in pixels.
     * @param height <b>[>0]</b>  Height of region to lock,in pixels.
     * @param format The desired bitmap pixel format.
     * @param read Read from bitmap data.
     * @param write Write to bitmap data.
     * 
     * @return <b>[not-null]</b>  The locked bitmap data.
     */
    virtual Ptr<BitmapData> LockPixels(int32 x, int32 y, int32 width, int32 height, BitmapFormat format, bool read, bool write) = 0;
    
    /*!
     * @brief  Enlarges resp. crops this bitmap by adding resp. removing pad pixels at resp. from 
     *         each bitmap edge.
     * 
     * @param left Number of pixels to add at left bitmap edge.
     * @param right Number of pixels to add at right bitmap edge.
     * @param top Number of pixels to add at top bitmap edge.
     * @param bottom Number of pixels to add at bottom bitmap edge.
     * @param color The 32-bit ARGB color value of the added pixels.
     */
    virtual void Resize(int32 left, int32 right, int32 top, int32 bottom, int32 color) = 0;
    
    /*!
     * @brief  Shifts the pixels of this bitmap.
     * 
     * @param x Shift amount along bitmap X-axis.
     * @param y Shift amount along bitmap Y-axis.
     * @param color The 32-bit ARGB color value of the pixels being shift in.
     */
    virtual void Shift(int32 x, int32 y, int32 color) = 0;
    
    /*!
     * @brief  Unlocks the currently locked bitmap region.
     * 
     * @see #LockPixels
     */
    virtual void UnlockPixels() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IBitmap> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xC7F0404D;
    
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
      if ((ptr = IDisposable::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
} } } 

#endif
