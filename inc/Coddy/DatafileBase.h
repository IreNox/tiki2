////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_DATAFILES_DATAFILEBASE_H
#define CLODDY_API_DATAFILES_DATAFILEBASE_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IDatafile.h"

// Include referenced classes.

#include "CodeX/Disposable.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Collections { template<class> class ISetConst; } } }
namespace Cloddy { namespace Core { namespace IO { namespace Streams { class IDataStream; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Datafiles { class IoStats; } } }
namespace Cloddy { namespace Core { namespace IO { namespace Files { class Path; } } } }
namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::API::Datafiles::DatafileBase.

namespace Cloddy { namespace API { namespace Datafiles
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::Collections::ISetConst;
  using Cloddy::Core::IO::Streams::IDataStream;
  
  // Use referenced classes.
  
  using Cloddy::Core::IO::Files::Path;
  using CodeX::System::ByteBuffer;
  using CodeX::System::Disposable;
  
  /*!
   * @brief  Abstract base class for IDatafile implementations.
   * 
   * The following interface implementations are provided by this class:
   *   - #Begin:empty
   *   - #End:empty
   *   - #Flush:empty
   *   - #ToStream():fixed
   *   - #ToStream(int32):fixed
   * TODO:Add PreLoad(...)to list when name resolver is fixed!
   */
  class DatafileBase : public Disposable, public virtual IDatafile
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual Ptr<Path> GetFilePath() = 0;
    
    virtual bool IsReadOnly() = 0;
    
    virtual int64 GetLength() = 0;
    
    virtual void SetLength(int64 value) = 0;
    
    virtual Ptr<IoStats> GetStats();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void Begin();
    
    virtual void End();
    
    virtual void Flush();
    
    virtual void PreLoad(int64 offset, int32 count);
    
    virtual void PreLoad(ISetConst<Prm<int64> >* offsets, int32 count);
    
    virtual Ptr<ByteBuffer> Read(int64 offset, int32 bytes) = 0;
    
    virtual Ptr<IDataStream> ToStream();
    
    virtual Ptr<IDataStream> ToStream(int32 bufferSize);
    
    virtual Ptr<ByteBuffer> Write(int64 offset, int32 bytes) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Attributes
    // ---------------------------------------------------------------------------------------------
  protected:
    
    /*!
     * @brief  The I/O information object.
     */
    Ptr<IoStats> stats;
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of DatafileBase.
     */
    DatafileBase();
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Asserts that this datafile is writeable.
     */
    void AssertWriteable();
    
    virtual void DisposeManaged();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<DatafileBase> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x9BECA170;
    
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
      if ((ptr = Disposable::TryCast(typeId)) != 0) return ptr;
      if ((ptr = IDatafile::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
