////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_IO_FILES_PATH_H
#define CLODDY_CORE_IO_FILES_PATH_H

#include "CodeX/System_Native.h"

// Include referenced classes.

#include "Cloddy/SerializableBase.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace IO { namespace Files { class IFileSystem; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class ISerializable; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class ISerialTypeInfo; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace IO { namespace Files { class PathElement; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Files { class PathFormat; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class Serializer; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { template<class> class SerialTypeInfo; } } } }

// Declare class ::Cloddy::Core::IO::Files::Path.

namespace Cloddy { namespace Core { namespace IO { namespace Files
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::IO::Serialization::ISerializable;
  using Cloddy::Core::IO::Serialization::ISerialTypeInfo;
  
  // Use referenced classes.
  
  using Cloddy::Core::IO::Serialization::SerializableBase;
  using Cloddy::Core::IO::Serialization::Serializer;
  using Cloddy::Core::IO::Serialization::SerialTypeInfo;
  
  /*!
   * @brief  Represents a path into a IFileSystem.
   */
  class Path : public SerializableBase, public virtual IEquatable<Ref<Path> >
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Returns the number of path elements in this path.
     * 
     * @return <b>[>=0]</b>  The number of path elements.
     */
    int32 GetCount();
    
    /*!
     * @brief  Returns the file extension of this path.
     * 
     * @return The file extension (excluding the '.'character);will be an empty string if this path 
     * does not include a file extension.
     */
    String GetFileExtension();
    
    /*!
     * @brief  Is this path absolute?
     * 
     * An absolute path points to a file or directory independently of the current directory of the 
     * process.
     * 
     * @return \c true  if this path is absolute,\c false  if it is relative.
     */
    bool IsAbsolute();
    
    /*!
     * @brief  Is this path relative?
     * 
     * The file or directory a relative path points to is dependent on the current directory of the 
     * process.
     * 
     * @return \c true  if this path is relative,\c false  if it is absolute.
     */
    bool IsRelative();
    
    /*!
     * @brief  Is this path rooted?
     * 
     * On some platforms,a path may contain a root selector (eg. <c>C:</c> on windows platforms).
     * 
     * @return \c true  if this path has a root selector,\c false  if it does not.
     */
    bool IsRooted();
    
    /*!
     * @brief  Returns the last part of this path.
     * 
     * Example:
     * <pre>
     *     c:\\some\\directory\\structure\\myfile.txt
     *     Last => "myfile.txt"
     *     c:\\
     *     Last => ""
     * </pre>
     * 
     * @return The last path part.
     */
    String GetLast();
    
    /*!
     * @brief  Returns a Path that represents the parent directory of this path.
     * 
     * Example:
     * <pre>
     *     c:\\some\\directory\\structure\\myfile.txt
     *     Parent => c:\\some\\directory\\structure
     *     c:\\some
     *     Parent => c:\\
     *     c:\\
     *     Parent => null
     * </pre>
     * 
     * @return The parent directory path or \c null  if this path has no parent directory.
     */
    Ptr<Path> GetParent();
    
    /*!
     * @brief  Returns the root selector of this path.
     * 
     * On some platforms,a path may contain a root selector (eg. <c>C:</c> on windows platforms):
     * <pre>
     *     c:\\somefile.txt
     *     Root => "c"
     *     /usr/tmp
     *     Root => null
     * </pre>
     * 
     * @return The root selector or \c null  if this path does not have one.
     */
    String GetRoot();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of Path.
     */
    Path();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Parses the given path string and returns the resulting Path object.
     * 
     * @param path <b>[not-empty]</b>  The path string.
     * 
     * @return <b>[not-null]</b>  The Path object.
     * 
     * @exception IOException If the given path string is 
     * invalid (IOException::GetError ==IOError::IOError_BadPath).
     */
    static Ptr<Path> From(String path);
    
    /*!
     * @brief  Parses the given path string and returns the resulting Path object.
     * 
     * @param path The path string.
     * 
     * @return The Path object or \c null  if the given path string is invalid.
     */
    static Ptr<Path> FromNull(String path);
    
    /*!
     * @brief  Returns the \e index -th path element.
     * 
     * Example:
     * <pre>
     *     c:\\some\\directory\\..\\structure\\.\\myfile.txt
     *     At(0) => "some"
     *     At(1) => "directory"
     *     At(2) => ".."
     *     At(3) => "structure"
     *     At(4) => "."
     *     At(5) => "myfile.txt"
     * </pre>
     * 
     * @param index <b>[0..#GetCount-1]</b>  The path element index.
     * 
     * @return <b>[not-null]</b>  The path element value.
     */
    String At(int32 index);
    
    /*!
     * @brief  Appends the given path element to this path.
     * 
     * Example:
     * <pre>
     *     c:\\some\\directory\\structure
     *     Child("myfile.txt") => c:\\some\\directory\\structure\\myfile.txt
     * </pre>
     * 
     * @param name <b>[not-empty]</b>  The path element to add.
     * 
     * @return <b>[not-null]</b>  The resulting path.
     */
    Ptr<Path> Child(String name);
    
    /*!
     * @brief  Concatenates this path and the given one.
     * 
     * @param other <b>[not-null]</b>  The other path.
     * 
     * @return <b>[not-null]</b>  The resulting path.
     */
    Ptr<Path> Concat(Path* other);
    
    /*!
     * @brief  Cuts the file extension from this file path.
     * 
     * @return <b>[not-null]</b>  The resulting path.
     */
    Ptr<Path> CutFileExtension();
    
    virtual Ptr<ISerializable> Deserialize(int32 serialVersion, Serializer* data);
    
    bool Equals(Path* other);
    
    /*!
     * @brief  Tries to find the given directory in the local filesystem (see LocalFileSystem).
     * 
     * Beginning at the directory pointed to by this Path object,this method probes each parent 
     * directory in order to find a subdirectory named \e directory .
     * 
     * @param directory <b>[not-empty]</b>  Name of the directory to find.
     * 
     * @return The full path to the found directory or \c null  if no directory has been found.
     */
    Ptr<Path> FindDirectory(String directory);
    
    /*!
     * @brief  Tries to find the given directory.
     * 
     * Beginning at the directory pointed to by this Path object,this method probes each parent 
     * directory in order to find a subdirectory named \e directory .
     * 
     * @param fileSystem <b>[not-null]</b>  The file system to use.
     * @param directory <b>[not-empty]</b>  Name of the directory to find.
     * 
     * @return The full path to the found directory or \c null  if no directory has been found.
     */
    Ptr<Path> FindDirectory(IFileSystem* fileSystem, String directory);
    
    /*!
     * @brief  Normalizes this path.
     * 
     * Normalization involves the following actions:
     *   - All path elements that refer to the current directory are removed (ie. '\.').
     *   - All path elements that refer to the parent directory consume the preceeding path element.
     * 
     * @return <b>[not-null]</b>  The normalized path.
     */
    Ptr<Path> Normalize();
    
    /*!
     * @brief  Extracts a part of this path.
     * 
     * Extracting a part from a path will preseve its root but may turn an absolute path into a 
     * relative one:
     * <pre>
     *     c:\\some\\directory\\structure\\myfile.txt
     *     Part(0, 1) => c:\\some                 (rooted, absolute)
     *     Part(1, 2) => c:directory             (rooted, relative)
     *     Part(2, 4) => c:structure\\myfile.txt  (rooted, relative)
     *     /some/directory/structure/myfile.txt
     *     Part(0, 1) => /some                   (not rooted, absolute)
     *     Part(1, 2) => directory               (not rooted, relative)
     *     Part(2, 4) => structure/myfile.txt    (not rooted, relative)
     * </pre>
     * 
     * @param from <b>[0..#GetCount-1]</b>  Index of first path element to extract (inclusive).
     * @param to <b>[from..#GetCount]</b>  Index of last path element to extract (exclusive).
     * 
     * @return <b>[not-null]</b>  The extracted path.
     */
    Ptr<Path> Part(int32 from, int32 to);
    
    virtual void Serialize(Serializer* data);
    
    /*!
     * @brief  Returns the path to a sibling file or directory contained in this paths parent.
     * 
     * @param name <b>[not-empty]</b>  Name of sibling file or directory.
     * 
     * @return <b>[not-null]</b>  The resulting path.
     */
    Ptr<Path> Sibling(String name);
    
    /*!
     * @brief  Appends the given suffix to the last path element of this path.
     * 
     * The last path element must refer to a sub file or directory:
     * <pre>
     *    c:\\some\\directory\\structure
     *    Suffix(".test") => c:\\some\\directory\\structure.test
     *    c:\\some\\directory\\structure\\myfile.txt
     *    Suffix(".bak") => c:\\some\\directory\\structure\\myfile.txt.bak
     *    c:\\
     *    Suffix(".test") => c:\\.test
     * </pre>
     * 
     * @param name <b>[not-empty]</b>  The suffix to append.
     * 
     * @return <b>[not-null]</b>  The resulting path.
     */
    Ptr<Path> Suffix(String name);
    
    /*!
     * @brief  Makes this path absolute.
     * 
     * @return <b>[not-null]</b>  The resulting path.
     */
    Ptr<Path> ToAbsolute();
    
    /*!
     * @brief  Makes this path relative.
     * 
     * @return <b>[not-null]</b>  The resulting path.
     */
    Ptr<Path> ToRelative();
    
    /*!
     * @brief  Changes the root selector of this path.
     * 
     * @param root The new root selector or \c null .
     * 
     * @return <b>[not-null]</b>  The resulting path.
     */
    Ptr<Path> ToRoot(String root);
    
    /*!
     * @brief  Returns the string representation of this path.
     * 
     * @param format <b>[not-null]</b>  The path format to use.
     * 
     * @return <b>[not-null]</b>  The string representation.
     */
    String ToString(PathFormat* format);
    
    virtual String ToString();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constants
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The GUID that uniquely identifies this type:{917D8722-BC9A-4A72-B469-C715EF4D2B25}
     */
    static const String SerialGuid;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Serialization information about this type.
     */
    static const StaticPtr<ISerialTypeInfo> SerialId;
    
    bool absolute;
    
    int32 count;
    
    int32 offset;
    
    Array<Ptr<PathElement> > pathElements;
    
    String root;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    Path(String root, bool absolute, Array<Ptr<PathElement> > pathElements, int32 offset, int32 count);
    
    // ---------------------------------------------------------------------------------------------
    // Static Initializer Functions
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Static initializer function for field SerialId.
     */
    static Object* StaticInitializer_SerialId();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<Path> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xE8050B1F;
    
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
      if ((ptr = SerializableBase::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
    
    // ---------------------------------------------------------------------------------------------
    // Native code
    // ---------------------------------------------------------------------------------------------
    
    NATIVE_BLOCK_BEGIN ("443513EC-2520-4211-A93B-635245998681")
    
    // Nothing to do here.
    
    NATIVE_BLOCK_END   ("443513EC-2520-4211-A93B-635245998681")
  };
  
} } } } 

#endif
