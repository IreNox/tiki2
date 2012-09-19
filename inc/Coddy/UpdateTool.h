////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_TOOLS_UPDATETOOL_H
#define CLODDY_API_TOOLS_UPDATETOOL_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/Tool.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Datasets { class IDataset; } } }
namespace Cloddy { namespace API { namespace Imaging { class IImage; } } }
namespace Cloddy { namespace API { namespace Imaging { class IImageReader; } } }
namespace Cloddy { namespace API { namespace Util { namespace Progress { class IProgressMonitor; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class ISerializable; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class ISerialTypeInfo; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Tools { class ToolParameterErrors; } } }
namespace Cloddy { namespace Core { namespace IO { namespace Files { class Path; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class Serializer; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { template<class> class SerialTypeInfo; } } } }
namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::API::Tools::UpdateTool.

namespace Cloddy { namespace API { namespace Tools
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Datasets::IDataset;
  using Cloddy::API::Imaging::IImage;
  using Cloddy::API::Imaging::IImageReader;
  using Cloddy::API::Util::Progress::IProgressMonitor;
  using Cloddy::Core::IO::Serialization::ISerializable;
  using Cloddy::Core::IO::Serialization::ISerialTypeInfo;
  
  // Use referenced classes.
  
  using Cloddy::Core::IO::Files::Path;
  using Cloddy::Core::IO::Serialization::Serializer;
  using Cloddy::Core::IO::Serialization::SerialTypeInfo;
  using CodeX::System::ByteBuffer;
  
  /*!
   * @brief  Updates a mutable (see IMap::IsMutable)rectangular or cube dataset using the given 
   *         image data.
   */
  class UpdateTool : public Tool
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Index of the first dataset channel to update.
     * 
     * @return <b>[>=0]</b>  Dataset channel index.
     */
    int32 GetChannel();
    
    /*!
     * @brief  Index of the first dataset channel to update.
     * 
     * @param value <b>[>=0]</b>  Dataset channel index.
     */
    void SetChannel(int32 value);
    
    /*!
     * @brief  The dataset to update.
     * 
     * @return Path to the dataset file.
     */
    Ptr<Path> GetDatasetFile();
    
    /*!
     * @brief  The dataset to update.
     * 
     * @param value Path to the dataset file.
     */
    void SetDatasetFile(Path* value);
    
    /*!
     * @brief  Dataset face to update.
     * 
     * Defaults to Cubemap::FaceNegZ.
     * 
     * @return The dataset face,constants of Cubemap.
     */
    int32 GetFace();
    
    /*!
     * @brief  Dataset face to update.
     * 
     * Defaults to Cubemap::FaceNegZ.
     * 
     * @param value The dataset face,constants of Cubemap.
     */
    void SetFace(int32 value);
    
    /*!
     * @brief  The input map image files that hold the update data.
     * 
     * @return The input map image descriptors.
     */
    Array<Ptr<IImage> > GetInputMapFiles();
    
    /*!
     * @brief  The input map image files that hold the update data.
     * 
     * @param value The input map image descriptors.
     */
    void SetInputMapFiles(Array<Ptr<IImage> > value);
    
    virtual String GetName();
    
    virtual Ptr<ISerialTypeInfo> GetSerialType();
    
    /*!
     * @brief  Dataset face X-coordinate of top-left corner of update image data.
     * 
     * @return The X-coordinate.
     */
    int32 GetX();
    
    /*!
     * @brief  Dataset face X-coordinate of top-left corner of update image data.
     * 
     * @param value The X-coordinate.
     */
    void SetX(int32 value);
    
    /*!
     * @brief  Dataset face Y-coordinate of top-left corner of update image data.
     * 
     * @return The Y-coordinate.
     */
    int32 GetY();
    
    /*!
     * @brief  Dataset face Y-coordinate of top-left corner of update image data.
     * 
     * @param value The Y-coordinate.
     */
    void SetY(int32 value);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of UpdateTool.
     */
    UpdateTool();
    
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
     * @brief  The GUID that uniquely identifies this type:{49E074F2-EA84-49CE-B9D0-CD9706D5860D}
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
     * @brief  Index of the first dataset channel to update.
     */
    int32 channel;
    
    /*!
     * @brief  The dataset to update.
     */
    Ptr<Path> datasetFile;
    
    /*!
     * @brief  Dataset face to update.
     */
    int32 face;
    
    /*!
     * @brief  The input map image files that hold the update data.
     */
    Array<Ptr<IImage> > inputMapFiles;
    
    /*!
     * @brief  Dataset X-coordinate of top-left corner of update image data.
     */
    int32 x;
    
    /*!
     * @brief  Dataset Y-coordinate of top-left corner of update image data.
     */
    int32 y;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Updates a cube dataset.
     * 
     * @param dataset The dataset.
     * @param readers The image readers.
     * @param scanlines The scanline buffers.
     * @param progressMonitor The progress monitor.
     */
    void UpdateCube(IDataset* dataset, Array<Ptr<IImageReader> > readers, Array<Ptr<ByteBuffer> > scanlines, IProgressMonitor* progressMonitor);
    
    /*!
     * @brief  Updates a rectangular dataset.
     * 
     * @param dataset The dataset.
     * @param readers The image readers.
     * @param scanlines The scanline buffers.
     * @param progressMonitor The progress monitor.
     */
    void UpdateRect(IDataset* dataset, Array<Ptr<IImageReader> > readers, Array<Ptr<ByteBuffer> > scanlines, IProgressMonitor* progressMonitor);
    
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
    public: typedef Ptr<UpdateTool> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x766E731C;
    
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
