////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_IMAGING_FILEIMAGEREADER_TIFF_IFD_H
#define CLODDY_API_IMAGING_FILEIMAGEREADER_TIFF_IFD_H

#include "CodeX/System.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace IO { namespace Streams { class IDataStream; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Imaging { class FileImageReader_Tiff; } } }

// Declare class ::Cloddy::API::Imaging::FileImageReader_Tiff_Ifd.

namespace Cloddy { namespace API { namespace Imaging
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::IO::Streams::IDataStream;
  
  /*!
   * @brief  Represents the Image File Directory (IFD)of a TIFF file.
   */
  class FileImageReader_Tiff_Ifd : public virtual Object
  {
    // Declare friend classes.
    
    friend class FileImageReader_Tiff;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Moves forwards in the IFD until the given field is found.
     * 
     * @param tag Tag of the field to move to.
     * 
     * @return <b>[not-null]</b>  this
     * 
     * @exception CoreException If the field has not been found in the IFD.
     */
    Ptr<FileImageReader_Tiff_Ifd> GetMandatoryField(int32 tag);
    
    /*!
     * @brief  Moves forwards in the IFD until the given field is found.
     * 
     * @param tag Tag of the field to move to.
     * 
     * @return \c true  if the field has been found in the IFD,\c false  if not.
     */
    bool GetOptionalField(int32 tag);
    
    /*!
     * @brief  Reads a number of SHORT or LONG field values.
     * 
     * @return <b>[not-null]</b>  The read values.
     */
    Array<int32> ReadManyShortsOrLongs();
    
    /*!
     * @brief  Reads a single SHORT or LONG field value.
     * 
     * @return The read value.
     */
    int32 ReadSingleShortOrLong();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Number of values of current field.
     */
    int32 count;
    
    /*!
     * @brief  Count per entry.
     */
    Array<int32> counts;
    
    /*!
     * @brief  Stream position to value offset.
     */
    Array<int64> offsets;
    
    /*!
     * @brief  The data stream of the TIFF image file.
     */
    Ptr<IDataStream> stream;
    
    /*!
     * @brief  Tag per entry.
     */
    Array<int32> tags;
    
    /*!
     * @brief  Data type of current field.
     */
    int32 type;
    
    /*!
     * @brief  Type per entry.
     */
    Array<int32> types;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of FileImageReader_Tiff_Ifd.
     * 
     * @param stream The TIFF data stream.The stream must point to the beginning of an IFD.
     */
    FileImageReader_Tiff_Ifd(IDataStream* stream);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<FileImageReader_Tiff_Ifd> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xBC7648CC;
    
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
