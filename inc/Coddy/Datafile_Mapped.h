////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_DATAFILES_DATAFILE_MAPPED_H
#define CLODDY_API_DATAFILES_DATAFILE_MAPPED_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/DatafileBase.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace IO { namespace Files { class IFile; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Datafiles { class DatafileFactory_Mapped; } } }
namespace Cloddy { namespace Core { namespace IO { namespace Files { class Path; } } } }
namespace CodeX { namespace System { class ByteBuffer; } }
namespace CodeX { namespace System { class Monitor; } }

// Declare class ::Cloddy::API::Datafiles::Datafile_Mapped.

namespace Cloddy { namespace API { namespace Datafiles
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::IO::Files::IFile;
  
  // Use referenced classes.
  
  using Cloddy::Core::IO::Files::Path;
  using CodeX::System::ByteBuffer;
  using CodeX::System::Monitor;
  
  /*!
   * @brief  An implementation of the IDatafile interface that uses memory mapping to access the 
   *         contents of a file in the local filesystem.
   */
  class Datafile_Mapped : public DatafileBase
  {
    // Declare friend classes.
    
    friend class DatafileFactory_Mapped;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual Ptr<Path> GetFilePath();
    
    virtual bool IsReadOnly();
    
    virtual int64 GetLength();
    
    virtual void SetLength(int64 value);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void Begin();
    
    virtual void End();
    
    virtual void Flush();
    
    virtual Ptr<ByteBuffer> Read(int64 offset, int32 bytes);
    
    virtual Ptr<ByteBuffer> Write(int64 offset, int32 bytes);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
  protected:
    
    virtual void DisposeManaged();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The memory mapped file.
     */
    Ptr<ByteBuffer> mapped;
    
    /*!
     * @brief  Monitor object used to synchronize access to this datafile.
     */
    Ptr<Monitor> monitor;
    
    /*!
     * @brief  The source file.
     */
    Ptr<IFile> sourceFile;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of Datafile_Mapped.
     * 
     * @param sourceFile The source file.
     */
    Datafile_Mapped(IFile* sourceFile);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<Datafile_Mapped> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xBDEC0A5D;
    
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
      if ((ptr = DatafileBase::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
