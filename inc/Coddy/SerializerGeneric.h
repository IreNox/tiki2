////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_IO_SERIALIZATION_SERIALIZERGENERIC_H
#define CLODDY_CORE_IO_SERIALIZATION_SERIALIZERGENERIC_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/ISerializable.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Collections { template<class> class ICollection; } } }
namespace Cloddy { namespace Core { namespace Collections { template<class> class ICollectionConst; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class Serializer; } } } }

// Declare class ::Cloddy::Core::IO::Serialization::SerializerGeneric.

namespace Cloddy { namespace Core { namespace IO { namespace Serialization
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::Collections::ICollection;
  using Cloddy::Core::Collections::ICollectionConst;
  
  template<class T>
  class SerializerGeneric
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Reads an array of objects.
     * 
     * @param serializer <b>[not-null]</b>  The serializer to use.
     * 
     * @return The read array.
     */
    static Array<typename T::Out> ReadArray(Serializer* serializer);
    
    /*!
     * @brief  Reads a collection of objects.
     * 
     * @param serializer <b>[not-null]</b>  The serializer to use.
     * @param collection <b>[not-null]</b>  The output collection.
     */
    static void ReadCollection(Serializer* serializer, ICollection<T>* collection);
    
    /*!
     * @brief  Serializes an array of objects.
     * 
     * @param serializer <b>[not-null]</b>  The serializer to use.
     * @param values The object array or \c null .
     */
    static void WriteArray(Serializer* serializer, Array<typename T::Out> values);
    
    /*!
     * @brief  Writes a collection of objects.
     * 
     * @param serializer <b>[not-null]</b>  The serializer to use.
     * @param values The object collection or \c null .
     */
    static void WriteCollection(Serializer* serializer, ICollectionConst<T>* values);
  };
  
} } } } 

#endif
