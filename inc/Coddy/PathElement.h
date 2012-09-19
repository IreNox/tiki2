////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_IO_FILES_PATHELEMENT_H
#define CLODDY_CORE_IO_FILES_PATHELEMENT_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/SerializableBase.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class ISerialTypeInfo; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace IO { namespace Files { class PathElement_Current; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Files { class PathElement_Name; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Files { class PathElement_Parent; } } } }

// Declare class ::Cloddy::Core::IO::Files::PathElement.

namespace Cloddy { namespace Core { namespace IO { namespace Files
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::IO::Serialization::ISerialTypeInfo;
  
  // Use referenced classes.
  
  using Cloddy::Core::IO::Serialization::SerializableBase;
  
  class PathElement : public SerializableBase, public virtual IEquatable<Ref<PathElement> >
  {
    // Declare friend classes.
    
    friend class PathElement_Current;
    friend class PathElement_Name;
    friend class PathElement_Parent;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Returns the path balance of this path element.
     * 
     * A path element can have a balance value of \c -1 ,\c 0  or \c 1 :
     *   - \c -1  :The path element refers to the parent directory.
     *   - \c 0  :The path element refers to the current directory.
     *   - \c 1  :The path element refers to sub file or directory in the current directory.
     * 
     * @return <b>[..1]</b>  The path balance.
     */
    virtual int32 GetBalance() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual bool Equals(PathElement* other) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Creates a new instance of PathElement.
     * 
     * @param serialType The serial type ID.
     */
    PathElement(ISerialTypeInfo* serialType);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<PathElement> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x2784B345;
    
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
  };
  
} } } } 

#endif
