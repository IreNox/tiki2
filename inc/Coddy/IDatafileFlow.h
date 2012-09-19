////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_DATAFILES_IDATAFILEFLOW_H
#define CLODDY_API_DATAFILES_IDATAFILEFLOW_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IBeginEnd.h"
#include "CodeX/IDisposable.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Datafiles { class IDatafile; } } }

// Declare interface ::Cloddy::API::Datafiles::IDatafileFlow.

namespace Cloddy { namespace API { namespace Datafiles
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Util::IBeginEnd;
  using CodeX::System::IDisposable;
  
  class NO_VTABLE IDatafileFlow : public virtual IBeginEnd, public virtual IDisposable
  {
    // ---------------------------------------------------------------------------------------------
    // Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Returns the datafile which owns this flow.
     * 
     * @return <b>[not-null]</b>  The owning datafile.
     */
    virtual Ptr<IDatafile> GetDatafile() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Enqueues a read request in the flow.
     * 
     * @param offset <b>[>=0]</b>  File offset to start reading at.
     * @param length <b>[>=0]</b>  Total number of bytes to read.
     */
    virtual void Read(int64 offset, int32 length) = 0;
    
    /*!
     * @brief  Enqueues a write request in the flow.
     * 
     * @param offset <b>[>=0]</b>  File offset to start writing at.
     * @param length <b>[>=0]</b>  Total number of bytes to write.
     */
    virtual void Write(int64 offset, int32 length) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IDatafileFlow> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xFFDEBAF0;
    
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
      if ((ptr = IBeginEnd::TryCast(typeId)) != 0) return ptr;
      if ((ptr = IDisposable::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
} } } 

#endif
