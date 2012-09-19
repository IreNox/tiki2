////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_MATH_VECTORS_MAT3F_SERIALIZER_H
#define CLODDY_CORE_MATH_VECTORS_MAT3F_SERIALIZER_H

#include "CodeX/System.h"

// Include referenced structures.

#include "Cloddy/Mat3F.h"

// Include referenced interfaces.

#include "Cloddy/IStructSerializer.h"

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class Serializer; } } } }

// Declare class ::Cloddy::Core::Math::Vectors::Mat3F_Serializer.

namespace Cloddy { namespace Core { namespace Math { namespace Vectors
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::IO::Serialization::IStructSerializer;
  
  // Use referenced classes.
  
  using Cloddy::Core::IO::Serialization::Serializer;
  
  class Mat3F_Serializer : public virtual IStructSerializer<Val<Mat3F> >
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual Mat3F Deserialize(Serializer* data);
    
    virtual void Serialize(const Mat3F& value, Serializer* data);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<Mat3F_Serializer> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xA12B441B;
    
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
      if ((ptr = IStructSerializer<Val<Mat3F> >::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } 

#endif
