////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_TOOLS_SPHERICALTOOL_H
#define CLODDY_API_TOOLS_SPHERICALTOOL_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IMapRegionCallback.h"

// Include referenced classes.

#include "Cloddy/Tool.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Projection { class IMapProjection; } } } }
namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleFormats { class ISampleFormat; } } } }
namespace Cloddy { namespace API { namespace Util { class IMapRegion; } } }
namespace Cloddy { namespace API { namespace Util { namespace Progress { class IProgressMonitor; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class ISerializable; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class ISerialTypeInfo; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Projection { class HeightmapProjector; } } } }
namespace Cloddy { namespace API { namespace Tools { class ToolParameterErrors; } } }
namespace Cloddy { namespace Core { namespace IO { namespace Files { class Path; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class Serializer; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { template<class> class SerialTypeInfo; } } } }

// Declare class ::Cloddy::API::Tools::SphericalTool.

namespace Cloddy { namespace API { namespace Tools
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Heightmaps::Projection::IMapProjection;
  using Cloddy::API::Heightmaps::SampleFormats::ISampleFormat;
  using Cloddy::API::Util::IMapRegion;
  using Cloddy::API::Util::IMapRegionCallback;
  using Cloddy::API::Util::Progress::IProgressMonitor;
  using Cloddy::Core::IO::Serialization::ISerializable;
  using Cloddy::Core::IO::Serialization::ISerialTypeInfo;
  
  // Use referenced classes.
  
  using Cloddy::API::Heightmaps::Projection::HeightmapProjector;
  using Cloddy::Core::IO::Files::Path;
  using Cloddy::Core::IO::Serialization::Serializer;
  using Cloddy::Core::IO::Serialization::SerialTypeInfo;
  
  /*!
   * @brief  Creates an uncompressed cubemap dataset file for the CloddySDK using the given input 
   *         data.
   * 
   * A cubemap dataset is used for terrains that use a sphere as base geometry.
   * 
   * The following figure illustrates the mapping from dataset coordinates to spherical 
   * coordinates (ie. longitude and latitude):
   * <pre>
   *      .   90?00'00""N                                 90?00'00""N
   *      .   180?00'00""E                                180?00'00""W
   *      .   
   *      .   #------------------------------------------#
   *      .   |                                          |
   *      .   | (0,0)                              (w,0) |
   *      .   |                                          |
   *      .   |               input dataset              |
   *      .   |                                          |
   *      .   |            w := dataset width            |
   *      .   |            h := dataset height           |
   *      .   |                                          |
   *      .   | (0,h)                              (w,h) |
   *      .   |                                          |
   *      .   #------------------------------------------#
   *      .   
   *      .   90?00'00""S                                 90?00'00""S
   *      .   180?00'00""E                                180?00'00""W
   *      .   
   *      .      +-------+
   *      .     /.      /|        Y- |  / Z+
   *      .    / .     / |           | /
   *      .   +-------+  |           |/          The center of the input dataset
   *      .   |  .....|..+    X- ----O---- X+    corresponds to the center of the
   *      .   | .     | /           /|           cubemap face Z-.
   *      .   |.      |/           / |
   *      .   +-------+        Z- /  | Y+
   * </pre>
   * 
   * The following table shows the dataset channel layout for each sample format:
   * <pre>
   *      Sample Format  Channels  Layout (starting at channel #0)
   *      ----------------------------------------------------------------------------
   *      E8             1         elevation
   *      E8C24          4         elevation, red, green, blue
   *      E8C32          5         elevation, alpha, red, green, blue
   *      E16            2         elevation hi, elevation lo
   *      E16C24         5         elevation hi, elevation lo, red, green, blue
   *      E16C32         6         elevation hi, elevation lo, alpha, red, green, blue
   * </pre>
   */
  class SphericalTool : public Tool, public virtual IMapRegionCallback
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The input dataset file.
     * 
     * @return Path to the dataset file in the filesystem.
     */
    Ptr<Path> GetInputDataset();
    
    /*!
     * @brief  The input dataset file.
     * 
     * @param value Path to the dataset file in the filesystem.
     */
    void SetInputDataset(Path* value);
    
    /*!
     * @brief  Sample format of the input dataset.
     * 
     * @return The ISampleFormat object.
     */
    Ptr<ISampleFormat> GetInputSampleFormat();
    
    /*!
     * @brief  Sample format of the input dataset.
     * 
     * @param value The ISampleFormat object.
     */
    void SetInputSampleFormat(ISampleFormat* value);
    
    /*!
     * @brief  The map projection descriptions string.
     * 
     * If no map projection is given,a simple plate carree projection is used.
     * 
     * @return The map projection description or \c null .
     */
    String GetMapProjectionDescription();
    
    /*!
     * @brief  The map projection descriptions string.
     * 
     * If no map projection is given,a simple plate carree projection is used.
     * 
     * @param value The map projection description or \c null .
     */
    void SetMapProjectionDescription(String value);
    
    virtual String GetName();
    
    /*!
     * @brief  The output dataset file.
     * 
     * @return Path to the dataset file in the filesystem.
     */
    Ptr<Path> GetOutputDataset();
    
    /*!
     * @brief  The output dataset file.
     * 
     * @param value Path to the dataset file in the filesystem.
     */
    void SetOutputDataset(Path* value);
    
    /*!
     * @brief  Sample format of the output dataset.
     * 
     * @return The ISampleFormat object.
     */
    Ptr<ISampleFormat> GetOutputSampleFormat();
    
    /*!
     * @brief  Sample format of the output dataset.
     * 
     * @param value The ISampleFormat object.
     */
    void SetOutputSampleFormat(ISampleFormat* value);
    
    /*!
     * @brief  Optional cubemap region for selective projection.
     * 
     * @return The map region object.
     */
    Ptr<IMapRegion> GetRegion();
    
    /*!
     * @brief  Optional cubemap region for selective projection.
     * 
     * @param value The map region object.
     */
    void SetRegion(IMapRegion* value);
    
    virtual Ptr<ISerialTypeInfo> GetSerialType();
    
    /*!
     * @brief  Size of the output dataset.When set to \c 0 ,the output dataset size will be 
     *         determined from the size of the input dataset.Must be a power of two plus one 
     *         otherwise.
     * 
     * @return Size of the output dataset.
     */
    int32 GetSize();
    
    /*!
     * @brief  Size of the output dataset.When set to \c 0 ,the output dataset size will be 
     *         determined from the size of the input dataset.Must be a power of two plus one 
     *         otherwise.
     * 
     * @param value Size of the output dataset.
     */
    void SetSize(int32 value);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void ConsumeMapRegion(int32 face, int32 faceX, int32 faceY, int32 width, int32 height);
    
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
     * @brief  The GUID that uniquely identifies this type:{2640AD17-5D7A-4F6E-9B81-B484CAD8B836}
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
     * @brief  The input dataset.
     */
    Ptr<Path> inputDataset;
    
    /*!
     * @brief  Sample format of the input dataset.
     */
    Ptr<ISampleFormat> inputSampleFormat;
    
    /*!
     * @brief  The map projection descriptions string.
     */
    String mapProjectionDescription;
    
    /*!
     * @brief  The output cubemap dataset.
     */
    Ptr<Path> outputDataset;
    
    /*!
     * @brief  Sample format of the output dataset.
     */
    Ptr<ISampleFormat> outputSampleFormat;
    
    Ptr<HeightmapProjector> projector;
    
    /*!
     * @brief  Optional cubemap region for selective projection.
     */
    Ptr<IMapRegion> region;
    
    /*!
     * @brief  Size of the output dataset.When set to \c 0 ,the output dataset size will be 
     *         determined from the size of the input dataset.
     */
    int32 size;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates an IMapProjection instance for the given map projection description string.
     * 
     * @param width The map width.
     * @param height The map height.
     * @param cubeSize The cubemap size.
     * @param description The map projection description string.
     * 
     * @return The created IMapProjection object or \c null  if \e description  is invalid.
     */
    static Ptr<IMapProjection> CreateMapProjection(int32 width, int32 height, int32 cubeSize, String description);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
  public:
    
    SphericalTool();
    
    // ---------------------------------------------------------------------------------------------
    // Static Initializer Functions
    // ---------------------------------------------------------------------------------------------
  private:
    
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
    public: typedef Ptr<SphericalTool> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x4B3D9D34;
    
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
      if ((ptr = IMapRegionCallback::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
