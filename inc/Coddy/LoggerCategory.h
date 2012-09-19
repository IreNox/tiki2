////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_LOGGING_LOGGERCATEGORY_H
#define CLODDY_CORE_LOGGING_LOGGERCATEGORY_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/LogSeverity.h"

// Include referenced interfaces.

#include "Cloddy/ILoggerCategory.h"

// Include referenced classes.

#include "Cloddy/LogMessageSource.h"

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace Logging { class Logger; } } }
namespace Cloddy { namespace Core { namespace Logging { class LoggingHelper; } } }

// Declare class ::Cloddy::Core::Logging::LoggerCategory.

namespace Cloddy { namespace Core { namespace Logging
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Default implementation of the ILoggerCategory interface.
   */
  class LoggerCategory : public LogMessageSource, public virtual ILoggerCategory
  {
    // Declare friend classes.
    
    friend class Logger;
    friend class LoggingHelper;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual String GetFullName();
    
    virtual String GetName();
    
    virtual Ptr<ILoggerCategory> GetParent();
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
  protected:
    
    virtual void OnSeverityChanged(bool updateDescendants, bool updateAncestors);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Points to the first child.
     */
    Ptr<LoggerCategory> firstChild;
    
    /*!
     * @brief  The first logger in the linked list of loggers that are associated with this 
     *         category.
     */
    Ptr<Logger> firstLogger;
    
    /*!
     * @brief  The cached full name of this logger category.
     */
    String fullName;
    
    /*!
     * @brief  The name of this logger category.
     */
    String name;
    
    /*!
     * @brief  Points to the next sibling.
     */
    Ptr<LoggerCategory> nextSibling;
    
    /*!
     * @brief  The parent category.
     */
    Ptr<LoggerCategory> parent;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of LoggerCategory.
     */
    LoggerCategory();
    
    /*!
     * @brief  Creates a new instance of LoggerCategory.
     * 
     * @param name The name of this logger category.
     * @param parent The parent category.
     * @param nextSibling Points to the next sibling.
     */
    LoggerCategory(String name, LoggerCategory* parent, LoggerCategory* nextSibling);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Clears this logger category.
     */
    void ClearOnShutdown();
    
    /*!
     * @brief  Returns a child category of this category.
     * 
     * @param childName Name of the child category.
     * 
     * @return The child category.
     */
    Ptr<LoggerCategory> GetChild(String childName);
    
    /*!
     * @brief  Returns a logger of this category.
     * 
     * @param name Name of the logger.
     * 
     * @return The logger.
     */
    Ptr<Logger> GetLogger(String name);
    
    /*!
     * @brief  Updates the severity of this category if the given severity levels is greater (ie. 
     *         more detailed).
     * 
     * @param severity The log severity level.
     */
    void UpdateSeverityIfGreater(LogSeverity severity);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<LoggerCategory> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xB6BD0EB4;
    
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
      if ((ptr = LogMessageSource::TryCast(typeId)) != 0) return ptr;
      if ((ptr = ILoggerCategory::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
