////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_IO_SERIALIZATION_SERIALIZERGENERIC_HPP
#define CLODDY_CORE_IO_SERIALIZATION_SERIALIZERGENERIC_HPP

#include "Cloddy/SerializerGeneric.h"

// Include referenced interfaces.

#include "Cloddy/ICollection.h"
#include "Cloddy/ICollectionConst.h"
#include "Cloddy/IEnumerator.h"
#include "Cloddy/ISerializable.h"

// Include referenced classes.

#include "CodeX/ErrorInfo.h"
#include "CodeX/InvalidArgumentException.h"
#include "Cloddy/Serializer.h"

namespace Cloddy { namespace Core { namespace IO { namespace Serialization {

// Use referenced namespaces.

using namespace CodeX;

// Use referenced interfaces.

using Cloddy::Core::Collections::ICollection;
using Cloddy::Core::Collections::ICollectionConst;
using Cloddy::Core::Collections::IEnumerator;

// Use referenced classes.

using CodeX::System::ErrorInfo;
using CodeX::System::InvalidArgumentException;

// -------------------------------------------------------------------------------------------------
// Public / Methods
// -------------------------------------------------------------------------------------------------

/*!
 * @brief  Reads an array of objects.
 * 
 * @param serializer <b>[not-null]</b>  The serializer to use.
 * 
 * @return The read array.
 */
template<class T>
Array<typename T::Out> SerializerGeneric<T>::ReadArray(Serializer* serializer)
{
#ifdef _DEBUG
  if (serializer == null) throw InvalidArgumentException::NotNull(ZSTRING("SerializerGeneric.ReadArray"), ZSTRING("serializer"));
#endif
  
  int32 length;
  Array<typename T::Out> result;
  
  // Read array length.
  
  length = serializer->ReadInt32();
  
  if (length == -1) return null;
  
  // Read array element type.
  
  result = Array<typename T::Out>(length);
  
  // Read array elements.
  
  for (int32 i = 0; i < result.Length(); i++)
    result[i] = cast<typename T::Self>(serializer->ReadObject());
  
  return result;
}

/*!
 * @brief  Reads a collection of objects.
 * 
 * @param serializer <b>[not-null]</b>  The serializer to use.
 * @param collection <b>[not-null]</b>  The output collection.
 */
template<class T>
void SerializerGeneric<T>::ReadCollection(Serializer* serializer, ICollection<T>* collection)
{
#ifdef _DEBUG
  if (serializer == null) throw InvalidArgumentException::NotNull(ZSTRING("SerializerGeneric.ReadCollection"), ZSTRING("serializer"));
  if (collection == null) throw InvalidArgumentException::NotNull(ZSTRING("SerializerGeneric.ReadCollection"), ZSTRING("collection"));
#endif
  
  int32 length;
  
  // Read array length.
  
  length = serializer->ReadInt32();
  
  if (length == -1) return;
  
  // Read array elements.
  
  for (int32 i = 0; i < length; i++)
    collection->Add(cast<typename T::Self>(serializer->ReadObject()));
}

/*!
 * @brief  Serializes an array of objects.
 * 
 * @param serializer <b>[not-null]</b>  The serializer to use.
 * @param values The object array or \c null .
 */
template<class T>
void SerializerGeneric<T>::WriteArray(Serializer* serializer, Array<typename T::Out> values)
{
#ifdef _DEBUG
  if (serializer == null) throw InvalidArgumentException::NotNull(ZSTRING("SerializerGeneric.WriteArray"), ZSTRING("serializer"));
#endif
  
  // Write array length.
  
  if (values == null) 
  {
    serializer->WriteInt32(-1);
    
    return;
  }
  
  serializer->WriteInt32(values.Length());
  
  // Write array elements.
  
  for (int32 i = 0; i < values.Length(); i++)
    serializer->WriteObject(values[i]);
}

/*!
 * @brief  Writes a collection of objects.
 * 
 * @param serializer <b>[not-null]</b>  The serializer to use.
 * @param values The object collection or \c null .
 */
template<class T>
void SerializerGeneric<T>::WriteCollection(Serializer* serializer, ICollectionConst<T>* values)
{
#ifdef _DEBUG
  if (serializer == null) throw InvalidArgumentException::NotNull(ZSTRING("SerializerGeneric.WriteCollection"), ZSTRING("serializer"));
#endif
  
  // Write array length.
  
  if (values == null) 
  {
    serializer->WriteInt32(-1);
    
    return;
  }
  
  serializer->WriteInt32(values->GetCount());
  
  // Write array elements.
  
  for (Ptr<IEnumerator<T> > it = values->GetEnumerator(); it->Next(); )
    serializer->WriteObject(it->GetCurrent());
}

} } } } 

#endif
