////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_SYSTEM_CHARACTERENCODING_H
#define CLODDY_CORE_SYSTEM_CHARACTERENCODING_H

#include "CodeX/System.h"

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace System { class CharacterEncoding_ASCII; } } }
namespace Cloddy { namespace Core { namespace System { class CharacterEncoding_ISO_8859_1; } } }
namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::Core::System::CharacterEncoding.

namespace Cloddy { namespace Core { namespace System
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced classes.
  
  using CodeX::System::ByteBuffer;
  
  /*!
   * @brief  Single byte character encodings.
   */
  class CharacterEncoding : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Character encoding US-ASCII (7-bit).
     */
    static const StaticPtr<CharacterEncoding> Ascii;
    
    /*!
     * @brief  Character encoding ISO-8859-1.
     */
    static const StaticPtr<CharacterEncoding> Iso88591;
    
    /*!
     * @brief  Returns the name of this character encoding.
     * 
     * @return <b>[not-null]</b>  The encoding name.
     */
    virtual String GetName() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Converts the given unicode string to single-byte encoding.
     * 
     * @param str The unicode string.
     * @param bytes The output buffer (can be \c null ).
     * 
     * @return The resulting buffer or \c null  iff \e str  is \c null .
     */
    virtual Ptr<ByteBuffer> FromUnicode(String str, ByteBuffer* bytes) = 0;
    
    /*!
     * @brief  Converts the given single-byte encoded string to unicode.
     * 
     * @param bytes The single-byte encoded string.
     * 
     * @return The unicode string or \c null  iff \e bytes  is \c null .
     */
    virtual String ToUnicode(ByteBuffer* bytes) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Static Initializer Functions
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief Static initializer function for field Ascii.
     */
    static Object* StaticInitializer_Ascii();
    
    /*!
     * @brief Static initializer function for field Iso88591.
     */
    static Object* StaticInitializer_Iso88591();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<CharacterEncoding> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x39E0CC80;
    
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
  
} } } 

#endif
