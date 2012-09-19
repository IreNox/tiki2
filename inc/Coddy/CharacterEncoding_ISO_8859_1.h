////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_SYSTEM_CHARACTERENCODING_ISO_8859_1_H
#define CLODDY_CORE_SYSTEM_CHARACTERENCODING_ISO_8859_1_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/CharacterEncoding.h"

// Forward declare referenced classes.

namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::Core::System::CharacterEncoding_ISO_8859_1.

namespace Cloddy { namespace Core { namespace System
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced classes.
  
  using CodeX::System::ByteBuffer;
  
  class CharacterEncoding_ISO_8859_1 : public CharacterEncoding
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual String GetName();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual Ptr<ByteBuffer> FromUnicode(String str, ByteBuffer* bytes);
    
    virtual String ToUnicode(ByteBuffer* bytes);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
  private:
    
    static int8 ConvertChar(wchar_t c);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<CharacterEncoding_ISO_8859_1> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x737C41C7;
    
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
      if ((ptr = CharacterEncoding::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
