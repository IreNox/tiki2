////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_DATASETS_DATASETBUILDER_H
#define CLODDY_API_DATASETS_DATASETBUILDER_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/Operation.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Datafiles { class IDatafile; } } }
namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleFormats { class ISampleFormat; } } } }
namespace Cloddy { namespace API { namespace Imaging { class IImage; } } }
namespace Cloddy { namespace API { namespace Util { namespace Progress { class IOperation; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Datasets { class DatasetBuilder_1_0_Cube; } } }
namespace Cloddy { namespace API { namespace Datasets { class DatasetBuilder_1_0_Rect; } } }
namespace Cloddy { namespace API { namespace Datasets { class DatasetBuilder_1_1_Rect_Sparse; } } }
namespace Cloddy { namespace API { namespace Imaging { class PatchImage; } } }
namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::API::Datasets::DatasetBuilder.

namespace Cloddy { namespace API { namespace Datasets
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Datafiles::IDatafile;
  using Cloddy::API::Heightmaps::SampleFormats::ISampleFormat;
  using Cloddy::API::Imaging::IImage;
  using Cloddy::API::Util::Progress::IOperation;
  
  // Use referenced classes.
  
  using Cloddy::API::Imaging::PatchImage;
  using Cloddy::API::Util::Progress::Operation;
  using CodeX::System::ByteBuffer;
  
  /*!
   * @brief  The DatasetBuilder class can be used to create rectangular and cubemap datasets.
   */
  class DatasetBuilder : public Operation
  {
    // Declare friend classes.
    
    friend class DatasetBuilder_1_0_Cube;
    friend class DatasetBuilder_1_0_Rect;
    friend class DatasetBuilder_1_1_Rect_Sparse;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual String GetName();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates an uncompressed cubemap dataset file for the CloddySDK using the given input 
     *         data.
     * 
     * A cubemap dataset is used for terrains that use a sphere as base geometry.
     * 
     * The following figure illustrates the orientation of the input image files in respect to 
     * their corresponding cubemap faces:
     * <pre>
     *      .      +-------+    right-handed cs:             O--------------O
     *      .     /.      /|        Y- |  / Z+               |              |
     *      .    / .     / |           | /                   | ^ ix         |
     *      .   +-------+  |           |/                    | |            |
     *      .   |  .....|..+    X- ----O---- X+              | |            |
     *      .   | .     | /           /|                     | |    Y-      |
     *      .   |.      |/           / |                     | |            |
     *      .   +-------+        Z- /  | Y+                  | |         iy |
     *      .                                                | o----------> |
     *      .                                                |              |
     *      .   O--------------O--------------O--------------O--------------O
     *      .   |              |              |              |              |
     *      .   | o----------> | o----------> | o----------> | o----------> |
     *      .   | |         ix | |         ix | |         ix | |         ix |
     *      .   | |            | |            | |            | |            |
     *      .   | |    Z-      | |    X+      | |    Z+      | |    X-      |
     *      .   | |            | |            | |            | |            |
     *      .   | |            | |            | |            | |            |
     *      .   | V iy         | V iy         | V iy         | V iy         |
     *      .   |              |              |              |              |
     *      .   O--------------O--------------O--------------O--------------O
     *      .                                                |              |
     *      .                                                | &lt;----------o |
     *      .                                                | iy         | |
     *      .        +-------------------------------+       |            | |
     *      .        | ix := Image X-coordinate axis |       |      Y+    | |
     *      .        | iy := Image Y-coordinate axis |       |            | |
     *      .        +-------------------------------+       |            | |
     *      .                                                |         ix V |
     *      .                                                |              |
     *      .                                                O--------------O
     * </pre>
     * 
     * The input images provided via the \e images  parameter are used to create the samples of the 
     * cubemap dataset.
     * The input image array is accessed using the following indexing scheme:
     * <pre>
     *      images[face * n]         := 1st input image for cubemap face
     *      images[face * n + 1]     := 2nd input image for cubemap face
     *      images[face * n + 2]     := 3rd input image for cubemap face
     *      images[face * n + n - 1] := last input image for cubemap face
     *      where
     *      face depicts the cubemap face (0 := X+, 1 := X-, 2 := Y+, 
     *      3 := Y-, 4 := Z+, 5 := Z-) and n is the number of input images per face.
     * </pre>
     * 
     * Each input images must be of size <c>2^n+1 x 2^n+1</c> and all input images must have the 
     * same size.The color channels of each input image are concatenated as 8-bit dataset channels 
     * in the dataset file.The input image sets for each cubemap face must have the same total 
     * number of channels.
     * 
     * Color channels are mapped to dataset channels as follows:
     * <pre>
     *      Image format      Color channel            Dataset channel index
     *      -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -
     *      8-bit grayscale:  Bits  7 ..  0         => channel n
     *      16-bit grayscale: Bits 15 ..  8 (high)  => channel n
     *      16-bit grayscale: Bits  7 ..  0 (lo)    => channel n + 1
     *      24-bit truecolor: Bits 23 .. 16 (red)   => channel n
     *      24-bit truecolor: Bits 15 ..  8 (green) => channel n + 1
     *      24-bit truecolor: Bits  7 ..  0 (blue)  => channel n + 2
     *      32-bit truecolor: Bits 23 .. 16 (red)   => channel n
     *      32-bit truecolor: Bits 15 ..  8 (green) => channel n + 1
     *      32-bit truecolor: Bits  7 ..  0 (blue)  => channel n + 2
     *      32-bit truecolor: Bits 31 .. 24 (alpha) => channel n + 3
     * </pre>
     * 
     * @param images <b>[not-empty]</b>  The input images for the dataset (must be of length 
     * <c>6 *n</c>,see remarks).
     * @param format Optional sample format.
     * @param stride <b>[>=1]</b>  Distance between adjacent dataset samples,in image pixels.
     * @param datasetFile <b>[not-null]</b>  The output dataset file.
     * 
     * @return <b>[not-null]</b>  An IOperation that performs the actual work.
     */
    static Ptr<IOperation> BuildCube(Array<Ptr<IImage> > images, ISampleFormat* format, int32 stride, IDatafile* datasetFile);
    
    /*!
     * @brief  Builds a rectangular dataset.
     * 
     * @param images <b>[not-empty]</b>  The input images for the dataset.
     * @param format Optional sample format.
     * @param stride <b>[>=1]</b>  Distance between adjacent dataset samples,in image pixels.
     * @param datasetFile <b>[not-null]</b>  The output dataset file.
     * 
     * @return <b>[not-null]</b>  An IOperation that performs the actual work.
     */
    static Ptr<IOperation> BuildRect(Array<Ptr<IImage> > images, ISampleFormat* format, int32 stride, IDatafile* datasetFile);
    
    /*!
     * @brief  Builds a sparse rectangular dataset.
     * 
     * @param images <b>[not-empty]</b>  The input images for the dataset.
     * @param format Optional sample format.
     * @param voidSample <b>[not-null]</b>  A dataset sample that represents void,ie. no data 
     * exists.
     * @param datasetFile <b>[not-null]</b>  The output dataset file.
     * 
     * @return <b>[not-null]</b>  An IOperation that performs the actual work.
     */
    static Ptr<IOperation> BuildRectSparse(Array<Ptr<PatchImage> > images, ISampleFormat* format, ByteBuffer* voidSample, IDatafile* datasetFile);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Creates a new instance of DatasetBuilder.
     */
    DatasetBuilder();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<DatasetBuilder> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xD726A4EE;
    
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
      if ((ptr = Operation::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
