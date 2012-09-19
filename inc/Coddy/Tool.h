////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_TOOLS_TOOL_H
#define CLODDY_API_TOOLS_TOOL_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/ITool.h"

// Include referenced classes.

#include "Cloddy/Operation.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Imaging { class IImage; } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class ISerializable; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class ISerialTypeInfo; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Tools { class ToolParameterErrors; } } }
namespace Cloddy { namespace API { namespace Util { namespace Progress { class RunningOperation; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Files { class Path; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class Serializer; } } } }

// Declare class ::Cloddy::API::Tools::Tool.

namespace Cloddy { namespace API { namespace Tools
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Imaging::IImage;
  using Cloddy::Core::IO::Serialization::ISerializable;
  using Cloddy::Core::IO::Serialization::ISerialTypeInfo;
  
  // Use referenced classes.
  
  using Cloddy::API::Util::Progress::Operation;
  using Cloddy::API::Util::Progress::RunningOperation;
  using Cloddy::Core::IO::Files::Path;
  using Cloddy::Core::IO::Serialization::Serializer;
  
  /*!
   * @brief  Abstract base class for ITool implementations.
   */
  class Tool : public Operation, public virtual ITool
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual Ptr<ISerialTypeInfo> GetSerialType() = 0;
    
    virtual int32 GetSerialVersion();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual Ptr<ISerializable> Deserialize(int32 serialVersion, Serializer* data) = 0;
    
    virtual Ptr<RunningOperation> RunAsBackgroundOperation();
    
    virtual void Serialize(Serializer* data) = 0;
    
    virtual Ptr<ToolParameterErrors> Validate();
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
  protected:
    
    /*!
     * @brief  Computes the number of concatenated dataset channels.
     * 
     * @param images The input images.
     * 
     * @return The number of channels.
     */
    static int32 ComputeChannelCount(Array<Ptr<IImage> > images);
    
    /*!
     * @brief  Normalize the given path to a canonical absolute path.
     * 
     * @param path The path to normalize.
     * 
     * @return The normalized path.
     */
    static Ptr<Path> NormalizePath(Path* path);
    
    /*!
     * @brief  Checks if the given file paths point to the same file.
     * 
     * If one of the given file paths is \c null  or empty,the method returns \c false .
     * 
     * @param filePath1 First file path.
     * @param filePath2 Second file path.
     * 
     * @return \c true  if both paths point to the same file,\c false  if not.
     */
    static bool SameFile(Path* filePath1, Path* filePath2);
    
    /*!
     * @brief  Performs the actual validation.
     * 
     * @param errors Error message output.
     */
    virtual void DoValidate(ToolParameterErrors* errors) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<Tool> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xE5779D57;
    
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
      if ((ptr = Operation::TryCast(typeId)) != 0) return ptr;
      if ((ptr = ITool::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
