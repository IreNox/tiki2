////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_PROCEDURAL_NOISEFUNCTION_PERTURB_H
#define CLODDY_API_PROCEDURAL_NOISEFUNCTION_PERTURB_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/NoiseFunction_FF.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Procedural { class INoiseFunction; } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class ISerializable; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class ISerialTypeInfo; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Procedural { class NoiseFunction; } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class Serializer; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { template<class> class SerialTypeInfo; } } } }

// Declare class ::Cloddy::API::Procedural::NoiseFunction_Perturb.

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
  
  /*!
   * @brief  A noise function that distorts the input coordinates before passing them to a source 
   *         noise function.
   */
  class NoiseFunction_Perturb : public NoiseFunction_FF
  {
    // Declare friend classes.
    
    friend class NoiseFunction;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Creates a new instance of NoiseFunction_Perturb.
     */
    NoiseFunction_Perturb();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual float64 Compute(float64 x, float64 y, float64 z);
    
    virtual Ptr<ISerializable> Deserialize(int32 serialVersion, Serializer* data);
    
    virtual void Serialize(Serializer* data);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constants
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The GUID that uniquely identifies this type:{2468A471-A5E0-46EA-B244-64CF3CA99374}
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
     * @brief  The turbulence scale factor.
     */
    float64 scale;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of NoiseFunction_Perturb.
     * 
     * @param source The source noise function.
     * @param turbulence The turbulence noise function.
     * @param scale The turbulence scale factor.
     */
    NoiseFunction_Perturb(INoiseFunction* source, INoiseFunction* turbulence, float64 scale);
    
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
    public: typedef Ptr<NoiseFunction_Perturb> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x641C3D38;
    
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
      if ((ptr = NoiseFunction_FF::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
