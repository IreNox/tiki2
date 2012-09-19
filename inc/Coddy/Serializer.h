////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_IO_SERIALIZATION_SERIALIZER_H
#define CLODDY_CORE_IO_SERIALIZATION_SERIALIZER_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IFlushable.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class ISerializable; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Streams { class IDataStream; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace IO { namespace Files { class Path; } } } }
namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::Core::IO::Serialization::Serializer.

namespace Cloddy { namespace Core { namespace IO { namespace Serialization
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::IO::IFlushable;
  using Cloddy::Core::IO::Streams::IDataStream;
  
  // Use referenced classes.
  
  using Cloddy::Core::IO::Files::Path;
  using CodeX::System::ByteBuffer;
  
  /*!
   * @brief  Helper class for serialization /deserialization of objects that implement 
   *         the ISerializable interface.
   */
  class Serializer : public virtual IFlushable
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Clones the given serializable object.
     * 
     * The clone is created by first serializing the given object and then deserializing the clone 
     * from the binary data stream.
     * 
     * @param obj The object to clone.
     * 
     * @return The cloned object.
     */
    static Ptr<ISerializable> Clone(ISerializable* obj);
    
    /*!
     * @brief  Deserializes an object from the given data stream.
     * 
     * @param stream <b>[not-null]</b>  The data stream.
     * 
     * @return The deserialized object or \c null .
     */
    static Ptr<ISerializable> Deserialize(IDataStream* stream);
    
    /*!
     * @brief  Deserializes an object from the given byte buffer.
     * 
     * @param buffer <b>[not-null]</b>  The byte buffer.
     * 
     * @return The deserialized object or \c null .
     */
    static Ptr<ISerializable> Deserialize(ByteBuffer* buffer);
    
    /*!
     * @brief  Deserializes an object from the given file.
     * 
     * @param file <b>[not-null]</b>  The file path.
     * 
     * @return The deserialized object or \c null .
     */
    static Ptr<ISerializable> Deserialize(Path* file);
    
    /*!
     * @brief  Serializes the given object to the given file.
     * 
     * @param obj The object to serialize or \c null .
     * @param file <b>[not-null]</b>  The file path.
     */
    static void Serialize(ISerializable* obj, Path* file);
    
    /*!
     * @brief  Serializes the given object to the provided data stream.
     * 
     * @param obj The object to serialize or \c null .
     * @param stream <b>[not-null]</b>  The data stream.
     */
    static void Serialize(ISerializable* obj, IDataStream* stream);
    
    /*!
     * @brief  Serializes the given object.
     * 
     * @param obj The object to serialize or \c null .
     * 
     * @return <b>[not-null]</b>  The byte buffer that holds the serialized object data.
     */
    static Ptr<ByteBuffer> Serialize(ISerializable* obj);
    
    virtual void Flush();
    
    /*!
     * @brief  Returns a data token of the object being deserialized.
     * 
     * @return The data token value.
     */
    bool ReadBool();
    
    /*!
     * @brief  Returns a data token of the object being deserialized.
     * 
     * @return The data token value.
     */
    Array<bool> ReadBoolArray();
    
    /*!
     * @brief  Returns a data token of the object being deserialized.
     * 
     * @return The data token value.
     */
    float32 ReadFloat32();
    
    /*!
     * @brief  Returns a data token of the object being deserialized.
     * 
     * @return The data token value.
     */
    Array<float32> ReadFloat32Array();
    
    /*!
     * @brief  Returns a data token of the object being deserialized.
     * 
     * @return The data token value.
     */
    float64 ReadFloat64();
    
    /*!
     * @brief  Returns a data token of the object being deserialized.
     * 
     * @return The data token value.
     */
    Array<float64> ReadFloat64Array();
    
    /*!
     * @brief  Returns a data token of the object being deserialized.
     * 
     * @return The data token value.
     */
    int16 ReadInt16();
    
    /*!
     * @brief  Returns a data token of the object being deserialized.
     * 
     * @return The data token value.
     */
    Array<int16> ReadInt16Array();
    
    /*!
     * @brief  Returns a data token of the object being deserialized.
     * 
     * @return The data token value.
     */
    int32 ReadInt32();
    
    /*!
     * @brief  Returns a data token of the object being deserialized.
     * 
     * @return The data token value.
     */
    Array<int32> ReadInt32Array();
    
    /*!
     * @brief  Returns a data token of the object being deserialized.
     * 
     * @return The data token value.
     */
    int64 ReadInt64();
    
    /*!
     * @brief  Returns a data token of the object being deserialized.
     * 
     * @return The data token value.
     */
    Array<int64> ReadInt64Array();
    
    /*!
     * @brief  Returns a data token of the object being deserialized.
     * 
     * @return The data token value.
     */
    int8 ReadInt8();
    
    /*!
     * @brief  Returns a data token of the object being deserialized.
     * 
     * @return The data token value.
     */
    Array<int8> ReadInt8Array();
    
    /*!
     * @brief  Returns a data token of the object being deserialized.
     * 
     * @return The data token value.
     */
    Ptr<ISerializable> ReadObject();
    
    /*!
     * @brief  Returns a data token of the object being deserialized.
     * 
     * @return The data token value.
     */
    String ReadString();
    
    /*!
     * @brief  Writes the value of a data token of the object being serialized.
     * 
     * @param value The data token value.
     */
    void WriteBool(bool value);
    
    /*!
     * @brief  Writes the value of a data token of the object being serialized.
     * 
     * @param value The data token value.
     */
    void WriteBoolArray(Array<bool> value);
    
    /*!
     * @brief  Writes the value of a data token of the object being serialized.
     * 
     * @param value The data token value.
     * @param first <b>[>=0]</b>  Index of first array element to write.
     * @param count <b>[>=0]</b>  Number array elements to write.
     */
    void WriteBoolArray(Array<bool> value, int32 first, int32 count);
    
    /*!
     * @brief  Writes the value of a data token of the object being serialized.
     * 
     * @param value The data token value.
     */
    void WriteFloat32(float32 value);
    
    /*!
     * @brief  Writes the value of a data token of the object being serialized.
     * 
     * @param value The data token value.
     */
    void WriteFloat32Array(Array<float32> value);
    
    /*!
     * @brief  Writes the value of a data token of the object being serialized.
     * 
     * @param value The data token value.
     * @param first <b>[>=0]</b>  Index of first array element to write.
     * @param count <b>[>=0]</b>  Number array elements to write.
     */
    void WriteFloat32Array(Array<float32> value, int32 first, int32 count);
    
    /*!
     * @brief  Writes the value of a data token of the object being serialized.
     * 
     * @param value The data token value.
     */
    void WriteFloat64(float64 value);
    
    /*!
     * @brief  Writes the value of a data token of the object being serialized.
     * 
     * @param value The data token value.
     */
    void WriteFloat64Array(Array<float64> value);
    
    /*!
     * @brief  Writes the value of a data token of the object being serialized.
     * 
     * @param value The data token value.
     * @param first <b>[>=0]</b>  Index of first array element to write.
     * @param count <b>[>=0]</b>  Number array elements to write.
     */
    void WriteFloat64Array(Array<float64> value, int32 first, int32 count);
    
    /*!
     * @brief  Writes the value of a data token of the object being serialized.
     * 
     * @param value The data token value.
     */
    void WriteInt16(int16 value);
    
    /*!
     * @brief  Writes the value of a data token of the object being serialized.
     * 
     * @param value The data token value.
     */
    void WriteInt16Array(Array<int16> value);
    
    /*!
     * @brief  Writes the value of a data token of the object being serialized.
     * 
     * @param value The data token value.
     * @param first <b>[>=0]</b>  Index of first array element to write.
     * @param count <b>[>=0]</b>  Number array elements to write.
     */
    void WriteInt16Array(Array<int16> value, int32 first, int32 count);
    
    /*!
     * @brief  Writes the value of a data token of the object being serialized.
     * 
     * @param value The data token value.
     */
    void WriteInt32(int32 value);
    
    /*!
     * @brief  Writes the value of a data token of the object being serialized.
     * 
     * @param value The data token value.
     */
    void WriteInt32Array(Array<int32> value);
    
    /*!
     * @brief  Writes the value of a data token of the object being serialized.
     * 
     * @param value The data token value.
     * @param first <b>[>=0]</b>  Index of first array element to write.
     * @param count <b>[>=0]</b>  Number array elements to write.
     */
    void WriteInt32Array(Array<int32> value, int32 first, int32 count);
    
    /*!
     * @brief  Writes the value of a data token of the object being serialized.
     * 
     * @param value The data token value.
     */
    void WriteInt64(int64 value);
    
    /*!
     * @brief  Writes the value of a data token of the object being serialized.
     * 
     * @param value The data token value.
     */
    void WriteInt64Array(Array<int64> value);
    
    /*!
     * @brief  Writes the value of a data token of the object being serialized.
     * 
     * @param value The data token value.
     * @param first <b>[>=0]</b>  Index of first array element to write.
     * @param count <b>[>=0]</b>  Number array elements to write.
     */
    void WriteInt64Array(Array<int64> value, int32 first, int32 count);
    
    /*!
     * @brief  Writes the value of a data token of the object being serialized.
     * 
     * @param value The data token value.
     */
    void WriteInt8(int8 value);
    
    /*!
     * @brief  Writes the value of a data token of the object being serialized.
     * 
     * @param value The data token value.
     */
    void WriteInt8Array(Array<int8> value);
    
    /*!
     * @brief  Writes the value of a data token of the object being serialized.
     * 
     * @param value The data token value.
     * @param first <b>[>=0]</b>  Index of first array element to write.
     * @param count <b>[>=0]</b>  Number array elements to write.
     */
    void WriteInt8Array(Array<int8> value, int32 first, int32 count);
    
    /*!
     * @brief  Writes the value of a data token of the object being serialized.
     * 
     * @param value The data token value.
     */
    void WriteObject(ISerializable* value);
    
    /*!
     * @brief  Writes the value of a data token of the object being serialized.
     * 
     * @param value The data token value.
     */
    void WriteString(String value);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    Ptr<IDataStream> dataStream;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    Serializer(IDataStream* dataStream);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<Serializer> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x6C6EE549;
    
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
      if ((ptr = IFlushable::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } 

#endif
