////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_BROWSING_BITMAPDATA_H
#define CLODDY_API_BROWSING_BITMAPDATA_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/BitmapFormat.h"

// Forward declare referenced classes.

namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::API::Browsing::BitmapData.

namespace Cloddy { namespace API { namespace Browsing
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced classes.
  
  using CodeX::System::ByteBuffer;
  
  class BitmapData : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The bitmap data pixel storage format.
     */
    BitmapFormat Format;
    
    /*!
     * @brief  The bitmap data height,in pixels.
     */
    int32 Height;
    
    /*!
     * @brief  The buffer that holds the bitmap data pixels.
     * 
     * @return <b>[not-null]</b>  The bitmap pixel buffer.
     */
    Ptr<ByteBuffer> GetPixels();
    
    /*!
     * @brief  Distance between neighbouring pixels,in bytes.
     */
    int32 StrideX;
    
    /*!
     * @brief  Distance between consecutive scanlines,in bytes.
     */
    int32 StrideY;
    
    /*!
     * @brief  The bitmap data width,in pixels.
     */
    int32 Width;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Returns BitmapData object that represents a shared view onto a subrectangle of 
     *         this BitmapData object.
     * 
     * @param x <b>[>=0]</b>  X-coordinate of top-left corner of subrectangle.
     * @param y <b>[>=0]</b>  Y-coordinate of top-left corner of subrectangle.
     * @param width <b>[>=0]</b>  Width of subrectangle,in pixels.
     * @param height <b>[>=0]</b>  Height of subrectangle,in pixels.
     * 
     * @return <b>[not-null]</b>  The resulting BitmapData object.
     */
    Ptr<BitmapData> Clip(int32 x, int32 y, int32 width, int32 height);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The buffer that holds the bitmap data pixels.
     */
    Ptr<ByteBuffer> pixels;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of BitmapData.
     * 
     * @param width The bitmap data width,in pixels.
     * @param height The bitmap data height,in pixels.
     * @param strideY Distance between consecutive scanlines,in bytes.
     * @param strideX Distance between neighbouring pixels,in bytes.
     * @param pixels The buffer that holds the bitmap data pixels.
     * @param format The bitmap data pixel storage format.
     */
    BitmapData(int32 width, int32 height, int32 strideY, int32 strideX, ByteBuffer* pixels, BitmapFormat format);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<BitmapData> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x534EAAD6;
    
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
