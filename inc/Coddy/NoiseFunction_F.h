////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_PROCEDURAL_NOISEFUNCTION_F_H
#define CLODDY_API_PROCEDURAL_NOISEFUNCTION_F_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/NoiseFunction.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Procedural { class INoiseFunction; } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class ISerializable; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class ISerialTypeInfo; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Procedural { class NoiseFunction_Abs; } } }
namespace Cloddy { namespace API { namespace Procedural { class NoiseFunction_Atan; } } }
namespace Cloddy { namespace API { namespace Procedural { class NoiseFunction_Clamp; } } }
namespace Cloddy { namespace API { namespace Procedural { class NoiseFunction_Cos; } } }
namespace Cloddy { namespace API { namespace Procedural { class NoiseFunction_Curve; } } }
namespace Cloddy { namespace API { namespace Procedural { class NoiseFunction_FS; } } }
namespace Cloddy { namespace API { namespace Procedural { class NoiseFunction_Multi; } } }
namespace Cloddy { namespace API { namespace Procedural { class NoiseFunction_Nan; } } }
namespace Cloddy { namespace API { namespace Procedural { class NoiseFunction_Neg; } } }
namespace Cloddy { namespace API { namespace Procedural { class NoiseFunction_Shift; } } }
namespace Cloddy { namespace API { namespace Procedural { class NoiseFunction_Sin; } } }
namespace Cloddy { namespace API { namespace Procedural { class NoiseFunction_Sqr; } } }
namespace Cloddy { namespace API { namespace Procedural { class NoiseFunction_Sqrt; } } }
namespace Cloddy { namespace API { namespace Procedural { class NoiseFunction_Tan; } } }
namespace Cloddy { namespace API { namespace Procedural { class NoiseFunction_Transform3; } } }
namespace Cloddy { namespace API { namespace Procedural { class NoiseFunction_Transform4; } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class Serializer; } } } }

// Declare class ::Cloddy::API::Procedural::NoiseFunction_F.

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
   * @brief  Abstract base class for noise functions that used one aggregated inner noise function.
   */
  class NoiseFunction_F : public NoiseFunction
  {
    // Declare friend classes.
    
    friend class NoiseFunction_Abs;
    friend class NoiseFunction_Atan;
    friend class NoiseFunction_Clamp;
    friend class NoiseFunction_Cos;
    friend class NoiseFunction_Curve;
    friend class NoiseFunction_FS;
    friend class NoiseFunction_Multi;
    friend class NoiseFunction_Nan;
    friend class NoiseFunction_Neg;
    friend class NoiseFunction_Shift;
    friend class NoiseFunction_Sin;
    friend class NoiseFunction_Sqr;
    friend class NoiseFunction_Sqrt;
    friend class NoiseFunction_Tan;
    friend class NoiseFunction_Transform3;
    friend class NoiseFunction_Transform4;
    
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
     * @brief  The aggregated noise function.
     */
    Ptr<INoiseFunction> function;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Creates a new instance of NoiseFunction_F.
     * 
     * @param serialType Serial type info.
     */
    NoiseFunction_F(ISerialTypeInfo* serialType);
    
    /*!
     * @brief  Creates a new instance of NoiseFunction_F.
     * 
     * @param serialType Serial type info.
     * @param function The aggregated noise function.
     */
    NoiseFunction_F(ISerialTypeInfo* serialType, INoiseFunction* function);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<NoiseFunction_F> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xF950BB42;
    
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
