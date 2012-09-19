////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_IO_STREAMS_IDATASTREAMFACTORY_H
#define CLODDY_CORE_IO_STREAMS_IDATASTREAMFACTORY_H

#include "CodeX/System.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace IO { namespace Streams { class IDataStream; } } } }

// Declare interface ::Cloddy::Core::IO::Streams::IDataStreamFactory.

namespace Cloddy { namespace Core { namespace IO { namespace Streams
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Base interface for classes that can produce IDataStream objects.
   */
  class NO_VTABLE IDataStreamFactory : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Creates an IDataStream object for accessing the data of this object.
     * 
     * The returned stream will use a default buffer size of \c 65536  bytes.
     * 
     * @return <b>[not-null]</b>  The data stream.
     */
    virtual Ptr<IDataStream> ToStream() = 0;
    
    /*!
     * @brief  Creates an IDataStream object for accessing the data of this object.
     * 
     * @param bufferSize <b>[>0]</b>  The buffer size to use.
     * 
     * @return <b>[not-null]</b>  The data stream.
     */
    virtual Ptr<IDataStream> ToStream(int32 bufferSize) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IDataStreamFactory> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xDD298011;
    
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
} } } } 

#endif
