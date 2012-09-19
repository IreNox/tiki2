////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_DATAFILES_IDATAFILEFACTORY_H
#define CLODDY_API_DATAFILES_IDATAFILEFACTORY_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/ISerializable.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Datafiles { class IDatafile; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace IO { namespace Files { class Path; } } } }

// Declare interface ::Cloddy::API::Datafiles::IDatafileFactory.

namespace Cloddy { namespace API { namespace Datafiles
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::IO::Serialization::ISerializable;
  
  // Use referenced classes.
  
  using Cloddy::Core::IO::Files::Path;
  
  class NO_VTABLE IDatafileFactory : public virtual ISerializable
  {
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Returns an IDatafileFactory instance which produces chunked datafiles.
     * 
     * A chunked datafile is split into chunks of a given size.Each chunk is accessed as an 
     * aggregated datafile which is opened resp. created using this IDatafileFactory.
     * 
     * The following naming convention is used for the individual chunks of a datafile:
     * <pre>
     *       Chunk #0 : SomeDatafileName.dat
     *       Chunk #1 : SomeDatafileName.0001.dat
     *       Chunk #2 : SomeDatafileName.0002.dat
     *       Chunk #3 : SomeDatafileName.0003.dat
     *       ...
     *       Chunk #n : SomeDatafileName.nnnn.dat
     *       ...
     *       Chunk #10000 : SomeDatafileName.10000.dat
     * </pre>
     * where <c>SomeDatafileName.dat</c> is the file name that has been specified when calling the 
     * TODO:Two Create Methods.Please consider in documentation!!!#Create(Path*) resp. #Open 
     * methods on the returned IDatafileFactory instance.
     * 
     * @param chunkSize <b>[pow2]</b>  The chunk size,in bytes.
     * 
     * @return <b>[not-null]</b>  The resulting IDatafileFactory
     */
    virtual Ptr<IDatafileFactory> Chunked(int64 chunkSize) = 0;
    
    /*!
     * @brief  Creates a new datafile.
     * 
     * The created datafile will have an initial length of \c 0  bytes.
     * 
     * @param filePath <b>[not-null]</b>  The file path.
     * 
     * @return <b>[not-null]</b>  The created datafile.
     */
    virtual Ptr<IDatafile> Create(Path* filePath) = 0;
    
    /*!
     * @brief  Creates a new datafile.
     * 
     * @param filePath <b>[not-null]</b>  The file path.
     * @param initialLength <b>[>=0]</b>  The initial file length,in bytes.
     * 
     * @return <b>[not-null]</b>  The created datafile.
     */
    virtual Ptr<IDatafile> Create(Path* filePath, int64 initialLength) = 0;
    
    /*!
     * @brief  Opens an existing datafile.
     * 
     * @param filePath <b>[not-null]</b>  The file path.
     * @param readOnly Open the file in read-only mode?
     * 
     * @return <b>[not-null]</b>  The openend datafile.
     */
    virtual Ptr<IDatafile> Open(Path* filePath, bool readOnly) = 0;
    
    /*!
     * @brief  Opens an existing datafile.
     * 
     * @param fileName The file path.
     * @param host Streaming host or ip
     * @param port Streaming port
     * 
     * @return <b>[not-null]</b>  The openend datafile.
     */
    virtual Ptr<IDatafile> Open(String fileName, String host, int port) {return 0;}
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IDatafileFactory> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x3502EDB2;
    
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
} } } 

#endif
