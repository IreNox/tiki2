////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_IO_SERIALIZATION_SERIALTYPEINFO_HPP
#define CLODDY_CORE_IO_SERIALIZATION_SERIALTYPEINFO_HPP

#include "Cloddy/SerialTypeInfo.h"

// Include referenced interfaces.

#include "Cloddy/ISerialTypeInfo.h"

// Include referenced classes.

#include "CodeX/ErrorInfo.h"
#include "CodeX/InvalidArgumentException.h"
#include "Cloddy/SerialTypeInfos.h"

namespace Cloddy { namespace Core { namespace IO { namespace Serialization {

// Use referenced namespaces.

using namespace CodeX;

// Use referenced classes.

using CodeX::System::ErrorInfo;
using CodeX::System::InvalidArgumentException;

// -------------------------------------------------------------------------------------------------
// Public / Attributes
// -------------------------------------------------------------------------------------------------

template<class T>
String SerialTypeInfo<T>::GetName()
{
  return name;
}

template<class T>
String SerialTypeInfo<T>::GetGuid()
{
  return guid;
}

// -------------------------------------------------------------------------------------------------
// Public / Constructors
// -------------------------------------------------------------------------------------------------

/*!
 * @brief  Creates a new instance of SerialTypeInfo.
 * 
 * @param name <b>[not-empty]</b>  Name of the type.
 */
template<class T>
SerialTypeInfo<T>::SerialTypeInfo(String name)
{
#ifdef _DEBUG
  if (name == null || name.Length() == 0) throw InvalidArgumentException::NotEmpty(ZSTRING("SerialTypeInfo.SerialTypeInfo"), ZSTRING("name"));
#endif
  
  this->name = name;
  guid = null;
  
  SerialTypeInfos::AddSerialTypeInfo(name, null, this);
}

/*!
 * @brief  Creates a new instance of SerialTypeInfo.
 * 
 * @param name <b>[not-empty]</b>  Name of the type.
 * @param guid <b>[not-empty]</b>  The type GUID.
 */
template<class T>
SerialTypeInfo<T>::SerialTypeInfo(String name, String guid)
{
#ifdef _DEBUG
  if (name == null || name.Length() == 0) throw InvalidArgumentException::NotEmpty(ZSTRING("SerialTypeInfo.SerialTypeInfo"), ZSTRING("name"));
  if (guid == null || guid.Length() == 0) throw InvalidArgumentException::NotEmpty(ZSTRING("SerialTypeInfo.SerialTypeInfo"), ZSTRING("guid"));
#endif
  
  this->name = name;
  this->guid = guid;
  
  SerialTypeInfos::AddSerialTypeInfo(name, guid, this);
}

// -------------------------------------------------------------------------------------------------
// Public / Methods
// -------------------------------------------------------------------------------------------------

template<class T>
Ptr<ISerializable> SerialTypeInfo<T>::CreateInstance()
{
  // Create new object instance.
  
  NATIVE_REGION_BEGIN ("90D50DE1-79FF-4DF1-804A-7DB0A723F629")
  
  return (new typename T::Self())->Cast<ISerializable>();
  
  NATIVE_REGION_END   ("90D50DE1-79FF-4DF1-804A-7DB0A723F629")
}

} } } } 

#endif
