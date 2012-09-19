////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_PROCEDURAL_NOISEFUNCTION_MULTI_H
#define CLODDY_API_PROCEDURAL_NOISEFUNCTION_MULTI_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/NoiseFunction_F.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Procedural { class INoiseFunction; } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class ISerializable; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class ISerialTypeInfo; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Procedural { class NoiseFunction_MultiAbs; } } }
namespace Cloddy { namespace API { namespace Procedural { class NoiseFunction_MultiMul; } } }
namespace Cloddy { namespace API { namespace Procedural { class NoiseFunction_MultiRidged; } } }
namespace Cloddy { namespace API { namespace Procedural { class NoiseFunction_MultiSum; } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class Serializer; } } } }

// Declare class ::Cloddy::API::Procedural::NoiseFunction_Multi.

namespace Cloddy { namespace API { namespace Procedural
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::IO::Serialization::ISerializable;
  using Cloddy::Core::IO::Serialization::ISerialTypeInfo;
  
  // Use referenced classes.
  
  using Cloddy::Core::IO::Serialization::Serializer;
  
  class NoiseFunction_Multi : public NoiseFunction_F
  {
    // Declare friend classes.
    
    friend class NoiseFunction_MultiAbs;
    friend class NoiseFunction_MultiMul;
    friend class NoiseFunction_MultiRidged;
    friend class NoiseFunction_MultiSum;
    
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
     * @brief  The amplitude of this noise function.
     */
    float64 amplitude;
    
    /*!
     * @brief  The frequency of this noise function.
     */
    float64 frequency;
    
    /*!
     * @brief  The number of octaves to compute.
     */
    int32 octaves;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Creates a new instance of NoiseFunction_Multi.
     * 
     * @param serialType The serial type ID.
     */
    NoiseFunction_Multi(ISerialTypeInfo* serialType);
    
    /*!
     * @brief  Creates a new instance of NoiseFunction_Multi.
     * 
     * @param serialType The serial type ID.
     * @param octaves The number of octaves to compute.
     * @param amplitude The amplitude is the factor by which the noise value resulting from 
     * consecutive evaluations of the inner noise function is scaled.
     * @param frequency The frequency is the factor by which the input coordinates are scaled 
     * between consecutive evaluations of the inner noise function.
     * @param function The inner noise function.
     */
    NoiseFunction_Multi(ISerialTypeInfo* serialType, int32 octaves, float64 amplitude, float64 frequency, INoiseFunction* function);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<NoiseFunction_Multi> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x41D3A7B;
    
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
      if ((ptr = NoiseFunction_F::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
