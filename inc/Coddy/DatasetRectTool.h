////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_TOOLS_DATASETRECTTOOL_H
#define CLODDY_API_TOOLS_DATASETRECTTOOL_H

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
namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::API::Tools::DatasetRectTool.

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
  using CodeX::System::ByteBuffer;
  
  /*!
   * @brief  Creates an uncompressed rectangular dataset file for the CloddySDK using the given 
   *         input data.
   * 
   * A rectangular dataset is used for terrains that use a square as base geometry.
   */
  class DatasetRectTool : public Tool
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
     * @return The ISampleFormat value.
     */
    Ptr<ISampleFormat> GetInputFormat();
    
    /*!
     * @brief  Optional input sample format.
     * 
     * @param value The ISampleFormat value.
     */
    void SetInputFormat(ISampleFormat* value);
    
    /*!
     * @brief  The input map images.
     * 
     * @return Paths to the image files in the filesystem.
     */
    Array<Ptr<IImage> > GetInputMapFiles();
    
    /*!
     * @brief  The input map images.
     * 
     * @param value Paths to the image files in the filesystem.
     */
    void SetInputMapFiles(Array<Ptr<IImage> > value);
    
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
    
    /*!
     * @brief  Optional byte buffer that holds a special dataset sample to use for void areas of a 
     *         sparse dataset.
     * 
     * @return The void sample buffer.
     */
    Ptr<ByteBuffer> GetVoidSample();
    
    /*!
     * @brief  Optional byte buffer that holds a special dataset sample to use for void areas of a 
     *         sparse dataset.
     * 
     * @param value The void sample buffer.
     */
    void SetVoidSample(ByteBuffer* value);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of this class.
     */
    DatasetRectTool();
    
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
     * @brief  The GUID that uniquely identifies this type:{889C750A-9BAE-4BFF-8364-FC25062B2177}
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
     * @brief  The input map images.
     */
    Array<Ptr<IImage> > inputMapFiles;
    
    /*!
     * @brief  The DatasetBuilder background operation.
     */
    Ptr<IOperation> operation;
    
    /*!
     * @brief  Distance between input map samples.Values greater than \c 1  reduce the resolution 
     *         of the output dataset.
     */
    int32 sampleStride;
    
    /*!
     * @brief  Optional byte buffer that holds a special dataset sample to use for void areas of a 
     *         sparse dataset.
     */
    Ptr<ByteBuffer> voidSample;
    
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
    public: typedef Ptr<DatasetRectTool> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x3BB4080D;
    
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
