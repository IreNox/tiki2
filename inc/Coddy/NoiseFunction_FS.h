////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_PROCEDURAL_NOISEFUNCTION_FS_H
#define CLODDY_API_PROCEDURAL_NOISEFUNCTION_FS_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/NoiseFunction_F.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Procedural { class INoiseFunction; } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class ISerializable; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class ISerialTypeInfo; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Procedural { class NoiseFunction_AddS; } } }
namespace Cloddy { namespace API { namespace Procedural { class NoiseFunction_DivInv; } } }
namespace Cloddy { namespace API { namespace Procedural { class NoiseFunction_LogInv; } } }
namespace Cloddy { namespace API { namespace Procedural { class NoiseFunction_LogS; } } }
namespace Cloddy { namespace API { namespace Procedural { class NoiseFunction_MaxS; } } }
namespace Cloddy { namespace API { namespace Procedural { class NoiseFunction_MinS; } } }
namespace Cloddy { namespace API { namespace Procedural { class NoiseFunction_MulS; } } }
namespace Cloddy { namespace API { namespace Procedural { class NoiseFunction_PowInv; } } }
namespace Cloddy { namespace API { namespace Procedural { class NoiseFunction_PowS; } } }
namespace Cloddy { namespace API { namespace Procedural { class NoiseFunction_SubInv; } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class Serializer; } } } }

// Declare class ::Cloddy::API::Procedural::NoiseFunction_FS.

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
   * @brief  Abstract base class for noise functions that used one aggregated inner noise function 
   *         and one scalar parameter.
   */
  class NoiseFunction_FS : public NoiseFunction_F
  {
    // Declare friend classes.
    
    friend class NoiseFunction_AddS;
    friend class NoiseFunction_DivInv;
    friend class NoiseFunction_LogInv;
    friend class NoiseFunction_LogS;
    friend class NoiseFunction_MaxS;
    friend class NoiseFunction_MinS;
    friend class NoiseFunction_MulS;
    friend class NoiseFunction_PowInv;
    friend class NoiseFunction_PowS;
    friend class NoiseFunction_SubInv;
    
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
     * @brief  The scalar parameter.
     */
    float64 value;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Creates a new instance of NoiseFunction_FS.
     * 
     * @param serialType The serial ID.
     */
    NoiseFunction_FS(ISerialTypeInfo* serialType);
    
    /*!
     * @brief  Creates a new instance of NoiseFunction_FS.
     * 
     * @param serialType The serial ID.
     * @param function The inner noise function.
     * @param value The scalar parameter.
     */
    NoiseFunction_FS(ISerialTypeInfo* serialType, INoiseFunction* function, float64 value);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<NoiseFunction_FS> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x16C31837;
    
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
