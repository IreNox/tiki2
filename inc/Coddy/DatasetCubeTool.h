////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_TOOLS_DATASETCUBETOOL_H
#define CLODDY_API_TOOLS_DATASETCUBETOOL_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/Tool.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleFormats { class ISampleFormat; } } } }
namespace Cloddy { namespace API { namespace Imaging { class IImage; } } }
namespace Cloddy { namespace API { namespace Util { namespace Progress { class IOperation; } } } }
namespace Cloddy { namespace API { namespace Util { namespace Progress { class IProgressMonitor; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class ISerializable; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class ISerialTypeInfo; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Tools { class ToolParameterErrors; } } }
namespace Cloddy { namespace Core { namespace IO { namespace Files { class Path; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class Serializer; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { template<class> class SerialTypeInfo; } } } }

// Declare class ::Cloddy::API::Tools::DatasetCubeTool.

namespace Cloddy { namespace API { namespace Tools
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Heightmaps::SampleFormats::ISampleFormat;
  using Cloddy::API::Imaging::IImage;
  using Cloddy::API::Util::Progress::IOperation;
  using Cloddy::API::Util::Progress::IProgressMonitor;
  using Cloddy::Core::IO::Serialization::ISerializable;
  using Cloddy::Core::IO::Serialization::ISerialTypeInfo;
  
  // Use referenced classes.
  
  using Cloddy::Core::IO::Files::Path;
  using Cloddy::Core::IO::Serialization::Serializer;
  using Cloddy::Core::IO::Serialization::SerialTypeInfo;
  
  /*!
   * @brief  Creates an uncompressed cube dataset file for the CloddySDK using the given input data.
   * 
   * A cube dataset is used for terrains that use a sphere as base geometry.
   */
  class DatasetCubeTool : public Tool
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Path to output dataset file.
     * 
     * @return Path to the dataset file in the filesystem.
     */
    Ptr<Path> GetDatasetFile();
    
    /*!
     * @brief  Path to output dataset file.
     * 
     * @param value Path to the dataset file in the filesystem.
     */
    void SetDatasetFile(Path* value);
    
    /*!
     * @brief  Optional input sample format.
     * 
     * @return The sample format.
     */
    Ptr<ISampleFormat> GetInputFormat();
    
    /*!
     * @brief  Optional input sample format.
     * 
     * @param value The sample format.
     */
    void SetInputFormat(ISampleFormat* value);
    
    /*!
     * @brief  The input map images for the X- cubemap face.
     * 
     * @return Paths to the image files in the filesystem.
     */
    Array<Ptr<IImage> > GetInputMapFilesNegX();
    
    /*!
     * @brief  The input map images for the X- cubemap face.
     * 
     * @param value Paths to the image files in the filesystem.
     */
    void SetInputMapFilesNegX(Array<Ptr<IImage> > value);
    
    /*!
     * @brief  The input map images for the Y- cubemap face.
     * 
     * @return Paths to the image files in the filesystem.
     */
    Array<Ptr<IImage> > GetInputMapFilesNegY();
    
    /*!
     * @brief  The input map images for the Y- cubemap face.
     * 
     * @param value Paths to the image files in the filesystem.
     */
    void SetInputMapFilesNegY(Array<Ptr<IImage> > value);
    
    /*!
     * @brief  The input map images for the Z- cubemap face.
     * 
     * @return Paths to the image files in the filesystem.
     */
    Array<Ptr<IImage> > GetInputMapFilesNegZ();
    
    /*!
     * @brief  The input map images for the Z- cubemap face.
     * 
     * @param value Paths to the image files in the filesystem.
     */
    void SetInputMapFilesNegZ(Array<Ptr<IImage> > value);
    
    /*!
     * @brief  The input map images for the X+cubemap face.
     * 
     * @return Paths to the image files in the filesystem.
     */
    Array<Ptr<IImage> > GetInputMapFilesPosX();
    
    /*!
     * @brief  The input map images for the X+cubemap face.
     * 
     * @param value Paths to the image files in the filesystem.
     */
    void SetInputMapFilesPosX(Array<Ptr<IImage> > value);
    
    /*!
     * @brief  The input map images for the Y+cubemap face.
     * 
     * @return Paths to the image files in the filesystem.
     */
    Array<Ptr<IImage> > GetInputMapFilesPosY();
    
    /*!
     * @brief  The input map images for the Y+cubemap face.
     * 
     * @param value Paths to the image files in the filesystem.
     */
    void SetInputMapFilesPosY(Array<Ptr<IImage> > value);
    
    /*!
     * @brief  The input map images for the Z+cubemap face.
     * 
     * @return Paths to the image files in the filesystem.
     */
    Array<Ptr<IImage> > GetInputMapFilesPosZ();
    
    /*!
     * @brief  The input map images for the Z+cubemap face.
     * 
     * @param value Paths to the image files in the filesystem.
     */
    void SetInputMapFilesPosZ(Array<Ptr<IImage> > value);
    
    virtual String GetName();
    
    /*!
     * @brief  Distance between input map samples.Values greater than \c 1  reduce the resolution 
     *         of the output dataset.
     * 
     * This value defaults to \c 1 .
     * 
     * @return Stride between input map samples.
     */
    int32 GetSampleStride();
    
    /*!
     * @brief  Distance between input map samples.Values greater than \c 1  reduce the resolution 
     *         of the output dataset.
     * 
     * This value defaults to \c 1 .
     * 
     * @param value Stride between input map samples.
     */
    void SetSampleStride(int32 value);
    
    virtual Ptr<ISerialTypeInfo> GetSerialType();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of DatasetCubeTool.
     */
    DatasetCubeTool();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual Ptr<ISerializable> Deserialize(int32 serialVersion, Serializer* data);
    
    virtual void Prepare(IProgressMonitor* progressMonitor);
    
    virtual void Run(IProgressMonitor* argument);
    
    virtual void Serialize(Serializer* data);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
  protected:
    
    virtual void DisposeManaged();
    
    virtual void DoValidate(ToolParameterErrors* errors);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constants
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The GUID that uniquely identifies this type:{8A692F0A-FF8B-424C-AF36-0699C326838D}
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
     * @brief  Path to output dataset file.
     */
    Ptr<Path> datasetFile;
    
    /*!
     * @brief  Optional input sample format.
     */
    Ptr<ISampleFormat> inputFormat;
    
    /*!
     * @brief  The input map images for the X- cubemap face.
     */
    Array<Ptr<IImage> > inputMapFilesNegX;
    
    /*!
     * @brief  The input map images for the Y- cubemap face.
     */
    Array<Ptr<IImage> > inputMapFilesNegY;
    
    /*!
     * @brief  The input map images for the Z- cubemap face.
     */
    Array<Ptr<IImage> > inputMapFilesNegZ;
    
    /*!
     * @brief  The input map images for the X+cubemap face.
     */
    Array<Ptr<IImage> > inputMapFilesPosX;
    
    /*!
     * @brief  The input map images for the Y+cubemap face.
     */
    Array<Ptr<IImage> > inputMapFilesPosY;
    
    /*!
     * @brief  The input map images for the Z+cubemap face.
     */
    Array<Ptr<IImage> > inputMapFilesPosZ;
    
    /*!
     * @brief  The DatasetBuilder background operation.
     */
    Ptr<IOperation> operation;
    
    /*!
     * @brief  Distance between input map samples.Values greater than \c 1  reduce the resolution 
     *         of the output dataset.
     */
    int32 sampleStride;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Checks if the size of the given image is equal to the given expected size.
     * 
     * @param expectedWidth The expected image width.
     * @param expectedHeight The expected image height.
     * @param image The image descriptor.
     * 
     * @return \c true  if the image size matches the expected size,\c false  if not.
     */
    static bool CheckImageSize(int32 expectedWidth, int32 expectedHeight, IImage* image);
    
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
    public: typedef Ptr<DatasetCubeTool> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x531DDBA2;
    
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
      if ((ptr = Tool::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
