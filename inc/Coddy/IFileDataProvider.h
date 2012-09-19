////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_IMAGING_DATAPROVIDERS_IFILEDATAPROVIDER_H
#define CLODDY_API_IMAGING_DATAPROVIDERS_IFILEDATAPROVIDER_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/ISerializable.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace IO { namespace Streams { class IDataStream; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace IO { namespace Files { class Path; } } } }

// Declare interface ::Cloddy::API::Imaging::DataProviders::IFileDataProvider.

namespace Cloddy { namespace API { namespace Imaging { namespace DataProviders
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::IO::Serialization::ISerializable;
  using Cloddy::Core::IO::Streams::IDataStream;
  
  // Use referenced classes.
  
  using Cloddy::Core::IO::Files::Path;
  
  /*!
   * @brief  Base interface for classes that provide data for files (local or logical).
   */
  class NO_VTABLE IFileDataProvider : public virtual ISerializable
  {
    // ---------------------------------------------------------------------------------------------
    // Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Is this file data provider capable of seeking (ie. skipping bytes without overhead)?
     * 
     * @return \c true  if the procider can seek,\c false  if not.
     */
    virtual bool CanSeek() = 0;
    
    /*!
     * @brief  The path of the file which data is provided by this object.
     * 
     * @return <b>[not-null]</b>  Path to the file
     */
    virtual Ptr<Path> GetFilePath() = 0;
    
    /*!
     * @brief  Returns the length of the file data.
     * 
     * @return <b>[>=0]</b>  The file data length,in bytes.
     */
    virtual int64 GetLength() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Opens a data stream that returns the file data.
     * 
     * @return <b>[not-null]</b>  The data stream.
     */
    virtual Ptr<IDataStream> OpenStream() = 0;
    
    /*!
     * @brief  Validates this file data provider.
     * 
     * @return \c null  if all settings of this file data provider are valid.If one or more 
     * settings are invalid,an error message is returned.
     */
    virtual String Validate() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IFileDataProvider> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x4E79E74C;
    
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
      if ((ptr = ISerializable::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
} } } } 

#endif
