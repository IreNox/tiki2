////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_TOOLS_SWAPBLOCKTOOL_H
#define CLODDY_API_TOOLS_SWAPBLOCKTOOL_H

#include "CodeX/System.h"

// Include referenced structures.

#include "Cloddy/SwapBlock.h"

// Include referenced classes.

#include "Cloddy/Tool.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Datasets { class IDataset; } } }
namespace Cloddy { namespace API { namespace Util { namespace Progress { class IProgressMonitor; } } } }
namespace Cloddy { namespace Core { namespace Collections { template<class> class IList; } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class ISerializable; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class ISerialTypeInfo; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Tools { class ToolParameterErrors; } } }
namespace Cloddy { namespace Core { namespace IO { namespace Files { class Path; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class Serializer; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { template<class> class SerialTypeInfo; } } } }

// Declare class ::Cloddy::API::Tools::SwapBlockTool.

namespace Cloddy { namespace API { namespace Tools
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Datasets::IDataset;
  using Cloddy::API::Util::Progress::IProgressMonitor;
  using Cloddy::Core::Collections::IList;
  using Cloddy::Core::IO::Serialization::ISerializable;
  using Cloddy::Core::IO::Serialization::ISerialTypeInfo;
  
  // Use referenced classes.
  
  using Cloddy::Core::IO::Files::Path;
  using Cloddy::Core::IO::Serialization::Serializer;
  using Cloddy::Core::IO::Serialization::SerialTypeInfo;
  
  /*!
   * @brief  Swaps blocks of data in the given input dataset.
   */
  class SwapBlockTool : public Tool
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The dataset to use.
     * 
     * @return The input dataset.
     */
    Ptr<IDataset> GetInputDataset();
    
    /*!
     * @brief  The dataset to use.
     * 
     * @param value The input dataset.
     */
    void SetInputDataset(IDataset* value);
    
    /*!
     * @brief  Path to the dataset file.
     * 
     * @return The dataset file path.
     */
    Ptr<Path> GetInputDatasetFile();
    
    /*!
     * @brief  Path to the dataset file.
     * 
     * @param value The dataset file path.
     */
    void SetInputDatasetFile(Path* value);
    
    virtual String GetName();
    
    virtual Ptr<ISerialTypeInfo> GetSerialType();
    
    /*!
     * @brief  Returns the block swaps.
     * 
     * @return <b>[not-null]</b>  The array of block swaps.
     */
    Array<SwapBlock> GetSwaps();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of SwapBlockTool.
     */
    SwapBlockTool();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Adds a block swap.
     * 
     * @param swap The block swap.
     * 
     * @return <b>[not-null]</b>  this
     */
    Ptr<SwapBlockTool> AddSwap(const SwapBlock& swap);
    
    virtual Ptr<ISerializable> Deserialize(int32 serialVersion, Serializer* data);
    
    virtual void Prepare(IProgressMonitor* progressMonitor);
    
    virtual void Run(IProgressMonitor* argument);
    
    virtual void Serialize(Serializer* data);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
  protected:
    
    virtual void DisposeManaged();
    
    virtual void DisposeManagedChildren();
    
    virtual void DoValidate(ToolParameterErrors* errors);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constants
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The GUID that uniquely identifies this type:{D435C54E-2273-402D-8D63-5943D77527AA}
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
     * @brief  The dataset to use.
     */
    Ptr<IDataset> inputDataset;
    
    /*!
     * @brief  Path to the dataset file.
     */
    Ptr<Path> inputDatasetFile;
    
    /*!
     * @brief  The block swaps.
     */
    Ptr<IList<Val<SwapBlock> > > swaps;
    
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
    public: typedef Ptr<SwapBlockTool> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x75C5EC1B;
    
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
      if ((ptr = Tool::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
