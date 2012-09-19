////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_PROJECTION_LATLON_SERIALIZER_H
#define CLODDY_API_HEIGHTMAPS_PROJECTION_LATLON_SERIALIZER_H

#include "CodeX/System.h"

// Include referenced structures.

#include "Cloddy/LatLon.h"

// Include referenced interfaces.

#include "Cloddy/IStructSerializer.h"

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class Serializer; } } } }

// Declare class ::Cloddy::API::Heightmaps::Projection::LatLon_Serializer.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Projection
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::IO::Serialization::IStructSerializer;
  
  // Use referenced classes.
  
  using Cloddy::Core::IO::Serialization::Serializer;
  
  class LatLon_Serializer : public virtual IStructSerializer<Val<LatLon> >
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual LatLon Deserialize(Serializer* data);
    
    virtual void Serialize(const LatLon& value, Serializer* data);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<LatLon_Serializer> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x4B18D532;
    
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
      if ((ptr = IStructSerializer<Val<LatLon> >::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } 

#endif
