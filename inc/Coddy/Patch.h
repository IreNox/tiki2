////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_IMAGING_PATCH_H
#define CLODDY_API_IMAGING_PATCH_H

#include "CodeX/System.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Imaging { class IImage; } } }

// Declare class ::Cloddy::API::Imaging::Patch.

namespace Cloddy { namespace API { namespace Imaging
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Represents a patch of image data in a PatchImage.
   */
  class Patch : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Height of this patch in the patchwork.
     * 
     * @return <b>[>0]</b>  Height of the patch,in pixels.
     */
    int32 GetHeight();
    
    /*!
     * @brief  The image for this patch.
     * 
     * @return <b>[not-null]</b>  The image descriptor of the source image.
     */
    Ptr<IImage> GetSourceImage();
    
    /*!
     * @brief  Width of this patch in the patchwork.
     * 
     * @return <b>[>0]</b>  Width of the patch,in pixels.
     */
    int32 GetWidth();
    
    /*!
     * @brief  X-coordinate of top-left corner of this patch in the patchwork.
     * 
     * @return X-coordinate of patch.
     */
    int32 GetX();
    
    /*!
     * @brief  Y-coordinate of top-left corner of this patch in the patchwork.
     * 
     * @return Y-coordinate of patch.
     */
    int32 GetY();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of Patch.
     * 
     * @param image <b>[not-null]</b>  The image for this patch.
     * @param x X-coordinate of top-left corner of this patch in the patchwork.
     * @param y Y-coordinate of top-left corner of this patch in the patchwork.
     */
    Patch(IImage* image, int32 x, int32 y);
    
    /*!
     * @brief  Creates a new instance of Patch.
     * 
     * @param image <b>[not-null]</b>  The image for this patch.
     * @param x X-coordinate of top-left corner of this patch in the patchwork.
     * @param y Y-coordinate of top-left corner of this patch in the patchwork.
     * @param width <b>[>0]</b>  Width of the patch in the patchwork.
     * @param height <b>[>0]</b>  Height of the patch in the patchwork.
     */
    Patch(IImage* image, int32 x, int32 y, int32 width, int32 height);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Checks if this patch intersects with the given row.
     * 
     * @param y Y-coordinate of row.
     * 
     * @return \c true  if this patch intersects with the row,\c false  if not.
     */
    bool IntersectY(int32 y);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Height of this patch in the patchwork.
     */
    int32 height;
    
    /*!
     * @brief  The image for this patch.
     */
    Ptr<IImage> sourceImage;
    
    /*!
     * @brief  Width of this patch in the patchwork.
     */
    int32 width;
    
    /*!
     * @brief  X-coordinate of top-left corner of this patch in the patchwork.
     */
    int32 x;
    
    /*!
     * @brief  Y-coordinate of top-left corner of this patch in the patchwork.
     */
    int32 y;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Computes the width and height of this patch.
     */
    void ComputeWidthAndHeight();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<Patch> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x14DDB9A;
    
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
