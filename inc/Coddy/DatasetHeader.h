////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_DATASETS_DATASETHEADER_H
#define CLODDY_API_DATASETS_DATASETHEADER_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/MapType.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Datafiles { class IDatafile; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace IO { namespace Files { class Path; } } } }

// Declare class ::Cloddy::API::Datasets::DatasetHeader.

namespace Cloddy { namespace API { namespace Datasets
{
  // Use referenced namespaces.
  
  using namespace Cloddy::API::Util;
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Datafiles::IDatafile;
  
  // Use referenced classes.
  
  using Cloddy::Core::IO::Files::Path;
  
  /*!
   * @brief  Represents the information stored in a dataset file header.
   */
  class DatasetHeader : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Constants
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Size of dataset file header,in bytes.
     */
    static const int32 HeaderSize = 32;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Number of channels.
     * 
     * @return The number of dataset channels.
     */
    int32 GetChannels();
    
    /*!
     * @brief  Number of channels.
     * 
     * @param value The number of dataset channels.
     */
    void SetChannels(int32 value);
    
    /*!
     * @brief  Is the dataset compressed?
     * 
     * @return \c true  if the dataset is compressed,\c false  if it is uncompressed.
     */
    bool GetCompressed();
    
    /*!
     * @brief  Is the dataset compressed?
     * 
     * @param value \c true  if the dataset is compressed,\c false  if it is uncompressed.
     */
    void SetCompressed(bool value);
    
    /*!
     * @brief  Height of the dataset.
     * 
     * @return Height of the dataset,in samples.
     */
    int32 GetHeight();
    
    /*!
     * @brief  Height of the dataset.
     * 
     * @param value Height of the dataset,in samples.
     */
    void SetHeight(int32 value);
    
    /*!
     * @brief  Is this dataset mutable,ie. can the application modify its samples?
     * 
     * @return \c true  if the map is mutable,\c false  if not.
     */
    bool IsMutable();
    
    /*!
     * @brief  The type of this dataset (rectangular or cubemap).
     * 
     * @return The MapType of the dataset.
     */
    MapType GetMapType();
    
    /*!
     * @brief  The type of this dataset (rectangular or cubemap).
     * 
     * @param value The MapType of the dataset.
     */
    void SetMapType(MapType value);
    
    /*!
     * @brief  Is this a sparse dataset?
     * 
     * @return \c true  if the dataset is sparse,\c false  if it is not.
     */
    bool GetSparse();
    
    /*!
     * @brief  Is this a sparse dataset?
     * 
     * @param value \c true  if the dataset is sparse,\c false  if it is not.
     */
    void SetSparse(bool value);
    
    /*!
     * @brief  Major part of file format version.
     * 
     * @return The major version number.
     */
    int32 GetVersionMajor();
    
    /*!
     * @brief  Major part of file format version.
     * 
     * @param value The major version number.
     */
    void SetVersionMajor(int32 value);
    
    /*!
     * @brief  Minor part of file format version.
     * 
     * @return The minor version number.
     */
    int32 GetVersionMinor();
    
    /*!
     * @brief  Minor part of file format version.
     * 
     * @param value The minor version number.
     */
    void SetVersionMinor(int32 value);
    
    /*!
     * @brief  Width of the dataset.
     * 
     * @return Width of the dataset,in samples.
     */
    int32 GetWidth();
    
    /*!
     * @brief  Width of the dataset.
     * 
     * @param value Width of the dataset,in samples.
     */
    void SetWidth(int32 value);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Reads the header from the given dataset file.
     * 
     * @param filePath <b>[not-null]</b>  Path to the dataset file.
     * 
     * @return <b>[not-null]</b>  The dataset header.
     */
    static Ptr<DatasetHeader> Read(Path* filePath);
    
    /*!
     * @brief  Asserts that this dataset header refers to a rectangular dataset.
     */
    void AssertIsCube();
    
    /*!
     * @brief  Asserts that this dataset header refers to a rectangular dataset.
     */
    void AssertIsRect();
    
    /*!
     * @brief  Reads the header values from the given dataset file.
     * 
     * @param datafile <b>[not-null]</b>  The IDatafile that represents the dataset file.
     */
    void Read(IDatafile* datafile);
    
    /*!
     * @brief  Writes the header values to the given dataset file.
     * 
     * @param datafile <b>[not-null]</b>  The IDatafile that represents the dataset file.
     */
    void Write(IDatafile* datafile);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constants
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Magic value.
     */
    static const int64 Magic = (int64) 0xA1A0A54534489ULL;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Number of channels.
     */
    int32 channels;
    
    /*!
     * @brief  Is the dataset compressed?
     */
    bool compressed;
    
    /*!
     * @brief  Height of the dataset.
     */
    int32 height;
    
    /*!
     * @brief  The type of this dataset (rectangular or cubemap).
     */
    MapType mapType;
    
    /*!
     * @brief  Is this a sparse dataset?
     */
    bool sparse;
    
    /*!
     * @brief  Major part of file format version.
     */
    int32 versionMajor;
    
    /*!
     * @brief  Minor part of file format version.
     */
    int32 versionMinor;
    
    /*!
     * @brief  Width of the dataset.
     */
    int32 width;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
  public:
    
    DatasetHeader();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<DatasetHeader> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xAA3DDB7E;
    
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
