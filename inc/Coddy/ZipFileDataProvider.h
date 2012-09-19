////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_IMAGING_DATAPROVIDERS_ZIPFILEDATAPROVIDER_H
#define CLODDY_API_IMAGING_DATAPROVIDERS_ZIPFILEDATAPROVIDER_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IFileDataProvider.h"

// Include referenced classes.

#include "Cloddy/SerializableBase.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class ISerializable; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class ISerialTypeInfo; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Streams { class IDataStream; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace IO { namespace Files { class Path; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class Serializer; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { template<class> class SerialTypeInfo; } } } }

// Declare class ::Cloddy::API::Imaging::DataProviders::ZipFileDataProvider.

namespace Cloddy { namespace API { namespace Imaging { namespace DataProviders
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::IO::Serialization::ISerializable;
  using Cloddy::Core::IO::Serialization::ISerialTypeInfo;
  using Cloddy::Core::IO::Streams::IDataStream;
  
  // Use referenced classes.
  
  using Cloddy::Core::IO::Files::Path;
  using Cloddy::Core::IO::Serialization::SerializableBase;
  using Cloddy::Core::IO::Serialization::Serializer;
  using Cloddy::Core::IO::Serialization::SerialTypeInfo;
  
  /*!
   * @brief  An implementation of the IFileDataProvider that for a file entry in a ZIP file.
   */
  class ZipFileDataProvider : public SerializableBase, public virtual IFileDataProvider
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual bool CanSeek();
    
    virtual Ptr<Path> GetFilePath();
    
    virtual int64 GetLength();
    
    /*!
     * @brief  Name of the ZIP entry.
     * 
     * @return <b>[not-null]</b>  The entry name.
     */
    String GetZipEntryName();
    
    /*!
     * @brief  Name of the ZIP entry.
     * 
     * @param value <b>[not-null]</b>  The entry name.
     */
    void SetZipEntryName(String value);
    
    /*!
     * @brief  The ZIP file data.
     * 
     * @return <b>[not-null]</b>  The file data provider for the ZIP file.
     */
    Ptr<IFileDataProvider> GetZipFileData();
    
    /*!
     * @brief  The ZIP file data.
     * 
     * @param value <b>[not-null]</b>  The file data provider for the ZIP file.
     */
    void SetZipFileData(IFileDataProvider* value);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of ZipFileDataProvider.
     */
    ZipFileDataProvider();
    
    /*!
     * @brief  Creates a new instance of ZipFileDataProvider.
     * 
     * @param zipEntryName <b>[not-null]</b>  Name of the ZIP entry.
     * @param zipFileData <b>[not-null]</b>  The ZIP file data.
     */
    ZipFileDataProvider(String zipEntryName, IFileDataProvider* zipFileData);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual Ptr<ISerializable> Deserialize(int32 serialVersion, Serializer* data);
    
    virtual Ptr<IDataStream> OpenStream();
    
    virtual void Serialize(Serializer* data);
    
    virtual String Validate();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constants
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The GUID that uniquely identifies this type:{C11AE0F0-4CD0-4498-AF60-FC0F74D3412D}
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
     * @brief  Name of the ZIP entry.
     */
    String zipEntryName;
    
    /*!
     * @brief  The ZIP file data.
     */
    Ptr<IFileDataProvider> zipFileData;
    
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
    public: typedef Ptr<ZipFileDataProvider> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xDD90E134;
    
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
      if ((ptr = SerializableBase::TryCast(typeId)) != 0) return ptr;
      if ((ptr = IFileDataProvider::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } 

#endif
