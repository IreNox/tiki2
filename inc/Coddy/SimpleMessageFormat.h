////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_LOGGING_FORMATS_SIMPLEMESSAGEFORMAT_H
#define CLODDY_CORE_LOGGING_FORMATS_SIMPLEMESSAGEFORMAT_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/LogSeverity.h"

// Include referenced interfaces.

#include "Cloddy/ILogMessageFormat.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Logging { class ILogger; } } }

// Declare class ::Cloddy::Core::Logging::Formats::SimpleMessageFormat.

namespace Cloddy { namespace Core { namespace Logging { namespace Formats
{
  // Use referenced namespaces.
  
  using namespace Cloddy::Core::Logging;
  using namespace CodeX;
  
  /*!
   * @brief  A simple log message format.
   */
  class SimpleMessageFormat : public virtual ILogMessageFormat
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Singleton instance of this class (full name of category is output).
     */
    static const StaticPtr<ILogMessageFormat> WithCategory;
    
    /*!
     * @brief  Singleton instance of this class (full name of category is not output).
     */
    static const StaticPtr<ILogMessageFormat> WithoutCategory;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual String FormatLogMessage(ILogger* source, LogSeverity logSeverity, String logMessage);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Include the full name of the log message source category?
     */
    bool includeCategoryName;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of SimpleMessageFormat.
     * 
     * @param includeCategoryName Include the full name of the log message source category?
     */
    SimpleMessageFormat(bool includeCategoryName);
    
    // ---------------------------------------------------------------------------------------------
    // Static Initializer Functions
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Static initializer function for field WithCategory.
     */
    static Object* StaticInitializer_WithCategory();
    
    /*!
     * @brief Static initializer function for field WithoutCategory.
     */
    static Object* StaticInitializer_WithoutCategory();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<SimpleMessageFormat> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x6093E830;
    
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
      if ((ptr = ILogMessageFormat::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } 

#endif
