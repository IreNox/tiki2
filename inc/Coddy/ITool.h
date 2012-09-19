////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_TOOLS_ITOOL_H
#define CLODDY_API_TOOLS_ITOOL_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "CodeX/IDisposable.h"
#include "Cloddy/ISerializable.h"

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Tools { class ToolParameterErrors; } } }
namespace Cloddy { namespace API { namespace Util { namespace Progress { class RunningOperation; } } } }

// Declare interface ::Cloddy::API::Tools::ITool.

namespace Cloddy { namespace API { namespace Tools
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::IO::Serialization::ISerializable;
  using CodeX::System::IDisposable;
  
  // Use referenced classes.
  
  using Cloddy::API::Util::Progress::RunningOperation;
  
  /*!
   * @brief  Base interface for preprocessor tools.
   */
  class NO_VTABLE ITool : public virtual IDisposable, public virtual ISerializable
  {
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Runs the tool.
     * 
     * The #Validate method must be called before the #RunAsBackgroundOperation method is invoked.A 
     * tool may be run iff parameter validation has reported no errors.
     * 
     * @return The RunningOperation object that represents the running tool background operation.
     */
    virtual Ptr<RunningOperation> RunAsBackgroundOperation() = 0;
    
    /*!
     * @brief  Validates the parameters for this tool.
     * 
     * @return <b>[not-null]</b>  The found tool parameter errors.
     */
    virtual Ptr<ToolParameterErrors> Validate() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<ITool> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xDC1BD4;
    
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
      if ((ptr = IDisposable::TryCast(typeId)) != 0) return ptr;
      if ((ptr = ISerializable::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
} } } 

#endif
