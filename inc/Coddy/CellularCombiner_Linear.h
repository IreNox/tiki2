////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_PROCEDURAL_CELLULARCOMBINER_LINEAR_H
#define CLODDY_API_PROCEDURAL_CELLULARCOMBINER_LINEAR_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/CellularCombiner.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class ISerializable; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class ISerialTypeInfo; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Procedural { class CellularCombiner; } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class Serializer; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { template<class> class SerialTypeInfo; } } } }

// Declare class ::Cloddy::API::Procedural::CellularCombiner_Linear.

namespace Cloddy { namespace API { namespace Procedural
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::IO::Serialization::ISerializable;
  using Cloddy::Core::IO::Serialization::ISerialTypeInfo;
  
  // Use referenced classes.
  
  using Cloddy::Core::IO::Serialization::Serializer;
  using Cloddy::Core::IO::Serialization::SerialTypeInfo;
  
  class CellularCombiner_Linear : public CellularCombiner
  {
    // Declare friend classes.
    
    friend class CellularCombiner;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Creates a new instance of CellularCombiner_Linear.
     */
    CellularCombiner_Linear();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual float64 Combine(float64 f1, float64 f2);
    
    virtual float64 Combine(float64 f1, float64 f2, float64 f3);
    
    virtual float64 Combine(float64 f1, float64 f2, float64 f3, float64 f4);
    
    virtual Ptr<ISerializable> Deserialize(int32 serialVersion, Serializer* data);
    
    virtual void Serialize(Serializer* data);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constants
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The GUID that uniquely identifies this type:{5E5A080C-42E0-44F3-AF69-5EDE1DC4441C}
     */
    static const String SerialGuid;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Serialization information about this type.
     */
    static const StaticPtr<ISerialTypeInfo> SerialId;
    
    /*!
     * @brief  Linear coefficient for F1.
     */
    float64 a;
    
    /*!
     * @brief  Linear coefficient for F2.
     */
    float64 b;
    
    /*!
     * @brief  Linear coefficient for F3.
     */
    float64 c;
    
    /*!
     * @brief  Linear coefficient for F4.
     */
    float64 d;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of CellularCombiner_Linear.
     * 
     * @param a Coefficient for F1.
     * @param b Coefficient for F2.
     * @param c Coefficient for F3.
     * @param d Coefficient for F4.
     */
    CellularCombiner_Linear(float64 a, float64 b, float64 c, float64 d);
    
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
    public: typedef Ptr<CellularCombiner_Linear> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xDEB38E34;
    
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
      if ((ptr = CellularCombiner::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
