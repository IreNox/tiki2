////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_IMAGING_PATCHIMAGE_H
#define CLODDY_API_IMAGING_PATCHIMAGE_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/PixelFormat.h"

// Include referenced interfaces.

#include "Cloddy/IMapRegion.h"

// Include referenced classes.

#include "Cloddy/CompositeImage.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Imaging { class IImage; } } }
namespace Cloddy { namespace API { namespace Imaging { class IImageReader; } } }
namespace Cloddy { namespace API { namespace Imaging { class IImageVisitor; } } }
namespace Cloddy { namespace API { namespace Util { class IMapRegionCallback; } } }
namespace Cloddy { namespace Core { namespace Collections { template<class> class IList; } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class ISerialTypeInfo; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Imaging { class ImageInfo; } } }
namespace Cloddy { namespace API { namespace Imaging { class Patch; } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { template<class> class SerialTypeInfo; } } } }

// Declare class ::Cloddy::API::Imaging::PatchImage.

namespace Cloddy { namespace API { namespace Imaging
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Util::IMapRegion;
  using Cloddy::API::Util::IMapRegionCallback;
  using Cloddy::Core::Collections::IList;
  using Cloddy::Core::IO::Serialization::ISerialTypeInfo;
  
  // Use referenced classes.
  
  using Cloddy::Core::IO::Serialization::SerialTypeInfo;
  
  /*!
   * @brief  An Imaging Object Model node that can be used to combine multiple images into one big 
   *         image.
   * 
   * Multiple Patch objects are placed on a virtual canvas.Each patch refers to an image.The 
   * position and size of each patch can be set freely,the referred imaged files will be rescaled 
   * as necessary.
   * <pre>
   *     +----------+-----------------------+------------+
   *     |..........|.......................|............|
   *     |..........|.......Patch #2........|............|
   *     |.Patch #1.|.......................|............|
   *     |..........+-----------------------+............| 
   *     |..........|                       |............|
   *     |..........|  +------------+       |..Patch #3..|
   *     +----------++ |............|       |............|
   *     |...........| |..Patch #4..|       |............|
   *     |...........| |............|       |............|
   *     |...........| |....+-------+--+    |............|
   *     |.Patch #6..| |....|.......|..|    |............|
   *     |...........| +----+-------+..|    +------------+
   *     |...........|      |.Patch #5.|    |............|
   *     |...........|      +----------+    |..Patch #7..|
   *     |...........|                      |............|
   *     +-----------+----------------------+------------+
   * </pre>
   * Pixels in the patchwork that are not covered by any patch are set to \c 0 .Pixels that are 
   * covered by more than one patch are combined:the maximum sample value per channel is used for 
   * the final pixel.
   * 
   * @see Patch
   */
  class PatchImage : public CompositeImage, public virtual IMapRegion
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Forced maximum X-coordinate of whole patch image (exclusive).
     * 
     * The default value is Maths::MinInt 
     * 
     * @return The maximum X-coordinate.
     */
    int32 GetForceMaxX();
    
    /*!
     * @brief  Forced maximum X-coordinate of whole patch image (exclusive).
     * 
     * The default value is Maths::MinInt 
     * 
     * @param value The maximum X-coordinate.
     */
    void SetForceMaxX(int32 value);
    
    /*!
     * @brief  Forced maximum Y-coordinate of whole patch image (exclusive).
     * 
     * The default value is Maths::MinInt 
     * 
     * @return The maximum Y-coordinate.
     */
    int32 GetForceMaxY();
    
    /*!
     * @brief  Forced maximum Y-coordinate of whole patch image (exclusive).
     * 
     * The default value is Maths::MinInt 
     * 
     * @param value The maximum Y-coordinate.
     */
    void SetForceMaxY(int32 value);
    
    /*!
     * @brief  Forced minimum X-coordinate of whole patch image (inclusive).
     * 
     * The default value is Maths::MaxInt 
     * 
     * @return The minimum X-coordinate.
     */
    int32 GetForceMinX();
    
    /*!
     * @brief  Forced minimum X-coordinate of whole patch image (inclusive).
     * 
     * The default value is Maths::MaxInt 
     * 
     * @param value The minimum X-coordinate.
     */
    void SetForceMinX(int32 value);
    
    /*!
     * @brief  Forced minimum Y-coordinate of whole patch image (inclusive).
     * 
     * The default value is Maths::MaxInt 
     * 
     * @return The minimum Y-coordinate.
     */
    int32 GetForceMinY();
    
    /*!
     * @brief  Forced minimum Y-coordinate of whole patch image (inclusive).
     * 
     * The default value is Maths::MaxInt 
     * 
     * @param value The minimum Y-coordinate.
     */
    void SetForceMinY(int32 value);
    
    /*!
     * @brief  The total height of this patchwork.
     * 
     * @return <b>[>=0]</b>  Height of the patchwork,in pixels.
     */
    int32 GetHeight();
    
    /*!
     * @brief  Maximum X-coordinate of all patches (exclusive).
     * 
     * @return The maximum X-coordinate.
     */
    int32 GetMaxX();
    
    /*!
     * @brief  Maximum Y-coordinate of all patches (exclusive).
     * 
     * @return The maximum Y-coordinate.
     */
    int32 GetMaxY();
    
    /*!
     * @brief  Minimum X-coordinate of all patches (inclusive).
     * 
     * @return The minimum X-coordinate.
     */
    int32 GetMinX();
    
    /*!
     * @brief  Minimum Y-coordinate of all patches (inclusive).
     * 
     * @return The minimum Y-coordinate.
     */
    int32 GetMinY();
    
    /*!
     * @brief  Returns the number of patches in this patchwork.
     * 
     * @return <b>[>=0]</b>  The number of patches.
     */
    int32 GetPatchCount();
    
    /*!
     * @brief  The pixel format of the patchwork.
     * 
     * If set to PixelFormat::PixelFormat_UnknownPixelFormat,the pixel format of the returned image 
     * will be determined from the pixel formats of the patch images (
     * see ImageUtil::GetCombinedPixelFormat).
     * 
     * @return The pixel format of the patchwork.
     */
    PixelFormat GetPixelFormat();
    
    /*!
     * @brief  The pixel format of the patchwork.
     * 
     * If set to PixelFormat::PixelFormat_UnknownPixelFormat,the pixel format of the returned image 
     * will be determined from the pixel formats of the patch images (
     * see ImageUtil::GetCombinedPixelFormat).
     * 
     * @param value The pixel format of the patchwork.
     */
    void SetPixelFormat(PixelFormat value);
    
    virtual Ptr<ISerialTypeInfo> GetSerialType();
    
    /*!
     * @brief  The total width of this patchwork.
     * 
     * @return <b>[>=0]</b>  Width of the patchwork,in pixels.
     */
    int32 GetWidth();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of PatchImage.
     */
    PatchImage();
    
    /*!
     * @brief  Creates a new instance of PatchImage.
     * 
     * @param pixelFormat The pixel format of the patchwork.
     */
    PatchImage(PixelFormat pixelFormat);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void Accept(IImageVisitor* visitor, Object* userData);
    
    /*!
     * @brief  Adds a Patch to this PatchImage.
     * 
     * Each patch must refer to a separate image file.If two or more patches refer to the same file,
     * an I/O error will occur!
     * 
     * @param patch <b>[not-null]</b>  The Patch to add.
     * 
     * @return <b>[not-null]</b>  this
     */
    Ptr<PatchImage> AddPatch(Patch* patch);
    
    /*!
     * @brief  Returns the \e index -th patch.
     * 
     * @param index <b>[0..#GetPatchCount-1]</b>  Index of patch to return.
     * 
     * @return <b>[not-null]</b>  The Patch object.
     */
    Ptr<Patch> GetPatch(int32 index);
    
    virtual Ptr<IMapRegion> MapRegionCompile();
    
    virtual void MapRegionEnumerate(IMapRegionCallback* callback);
    
    virtual int32 MapRegionIntersectsWith(int32 minX, int32 minY, int32 minZ, int32 maxX, int32 maxY, int32 maxZ);
    
    virtual Ptr<IMapRegion> MapRegionUnion(IMapRegion* region);
    
    /*!
     * @brief  Removes the given Patch from this PatchImage.
     * 
     * @param patch <b>[not-null]</b>  The Patch to remove.
     * 
     * @return <b>[not-null]</b>  this
     */
    Ptr<PatchImage> RemovePatch(Patch* patch);
    
    virtual void Validate();
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Attributes
    // ---------------------------------------------------------------------------------------------
  protected:
    
    virtual int32 GetSourceImageCount();
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual Ptr<IImageReader> DoReadImage();
    
    virtual Ptr<ImageInfo> DoReadImageInfo();
    
    virtual Ptr<IImage> GetSourceImageAt(int32 index);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constants
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The GUID that uniquely identifies this type:{1E918889-F914-4B6B-9701-A987A79E9C96}
     */
    static const String SerialGuid;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Serialization information about this type.
     */
    static const StaticPtr<ISerialTypeInfo> SerialId;
    
    /*!
     * @brief  Forced maximum X-coordinate of whole patch image (exclusive).
     */
    int32 forceMaxX;
    
    /*!
     * @brief  Forced maximum Y-coordinate of whole patch image (exclusive).
     */
    int32 forceMaxY;
    
    /*!
     * @brief  Forced minimum X-coordinate of whole patch image (inclusive).
     */
    int32 forceMinX;
    
    /*!
     * @brief  Forced minimum Y-coordinate of whole patch image (inclusive).
     */
    int32 forceMinY;
    
    /*!
     * @brief  Total height of this patchwork.
     */
    int32 height;
    
    /*!
     * @brief  Maximum X-coordinate of all patches (exclusive).
     */
    int32 maxX;
    
    /*!
     * @brief  Maximum Y-coordinate of all patches (exclusive).
     */
    int32 maxY;
    
    /*!
     * @brief  Minimum X-coordinate of all patches (inclusive).
     */
    int32 minX;
    
    /*!
     * @brief  Minimum Y-coordinate of all patches (inclusive).
     */
    int32 minY;
    
    /*!
     * @brief  The list of Patch objects.
     */
    Ptr<IList<Ref<Patch> > > patches;
    
    /*!
     * @brief  The pixel format of the resulting image.
     */
    PixelFormat pixelFormat;
    
    /*!
     * @brief  Total width of this patchwork.
     */
    int32 width;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Computes the extends of the patchwork.
     */
    void ComputeExtends();
    
    /*!
     * @brief  Returns the pixel format to use for this patchwork.
     * 
     * @return The PixelFormat.
     */
    PixelFormat ComputePixelFormat();
    
    // ---------------------------------------------------------------------------------------------
    // Static Initializer Functions
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Static initializer function for field SerialId.
     */
    static Object* StaticInitializer_SerialId();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<PatchImage> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xF5F5EDBB;
    
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
      if ((ptr = CompositeImage::TryCast(typeId)) != 0) return ptr;
      if ((ptr = IMapRegion::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
