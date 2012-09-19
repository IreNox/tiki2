////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_PROCEDURAL_NOISEFUNCTION_FF_H
#define CLODDY_API_PROCEDURAL_NOISEFUNCTION_FF_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/NoiseFunction.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Procedural { class INoiseFunction; } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class ISerializable; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class ISerialTypeInfo; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Procedural { class NoiseFunction_AddF; } } }
namespace Cloddy { namespace API { namespace Procedural { class NoiseFunction_Blend; } } }
namespace Cloddy { namespace API { namespace Procedural { class NoiseFunction_DivF; } } }
namespace Cloddy { namespace API { namespace Procedural { class NoiseFunction_LogF; } } }
namespace Cloddy { namespace API { namespace Procedural { class NoiseFunction_MaxF; } } }
namespace Cloddy { namespace API { namespace Procedural { class NoiseFunction_MinF; } } }
namespace Cloddy { namespace API { namespace Procedural { class NoiseFunction_MulF; } } }
namespace Cloddy { namespace API { namespace Procedural { class NoiseFunction_Perturb; } } }
namespace Cloddy { namespace API { namespace Procedural { class NoiseFunction_PowF; } } }
namespace Cloddy { namespace API { namespace Procedural { class NoiseFunction_SubF; } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class Serializer; } } } }

// Declare class ::Cloddy::API::Procedural::NoiseFunction_FF.

namespace Cloddy { namespace API { namespace Procedural
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::IO::Serialization::ISerializable;
  using Cloddy::Core::IO::Serialization::ISerialTypeInfo;
  
  // Use referenced classes.
  
  using Cloddy::Core::IO::Serialization::Serializer;
  
  /*!
   * @brief  Abstract base class for noise functions that use two aggregated inner noise functions.
   */
  class NoiseFunction_FF : public NoiseFunction
  {
    // Declare friend classes.
    
    friend class NoiseFunction_AddF;
    friend class NoiseFunction_Blend;
    friend class NoiseFunction_DivF;
    friend class NoiseFunction_LogF;
    friend class NoiseFunction_MaxF;
    friend class NoiseFunction_MinF;
    friend class NoiseFunction_MulF;
    friend class NoiseFunction_Perturb;
    friend class NoiseFunction_PowF;
    friend class NoiseFunction_SubF;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual Ptr<ISerializable> Deserialize(int32 serialVersion, Serializer* data);
    
    virtual void Serialize(Serializer* data);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Attributes
    // ---------------------------------------------------------------------------------------------
  protected:
    
    /*!
     * @brief  The first inner noise function.
     */
    Ptr<INoiseFunction> first;
    
    /*!
     * @brief  The second inner noise function.
     */
    Ptr<INoiseFunction> second;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Creates a new instance of NoiseFunction_FF.
     * 
     * @param serialType The serial ID.
     */
    NoiseFunction_FF(ISerialTypeInfo* serialType);
    
    /*!
     * @brief  Creates a new instance of NoiseFunction_FF.
     * 
     * @param serialType The serial ID.
     * @param first The first inner noise function.
     * @param second The second inner noise function.
     */
    NoiseFunction_FF(ISerialTypeInfo* serialType, INoiseFunction* first, INoiseFunction* second);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<NoiseFunction_FF> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xD4422C58;
    
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
      if ((ptr = NoiseFunction::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
