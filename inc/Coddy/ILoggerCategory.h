////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_LOGGING_ILOGGERCATEGORY_H
#define CLODDY_CORE_LOGGING_ILOGGERCATEGORY_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/ILogMessageSource.h"

// Declare interface ::Cloddy::Core::Logging::ILoggerCategory.

namespace Cloddy { namespace Core { namespace Logging
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Base interface for classes that represent categories for ILogger objects.
   */
  class NO_VTABLE ILoggerCategory : public virtual ILogMessageSource
  {
    // ---------------------------------------------------------------------------------------------
    // Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Returns the full name of this category.
     * 
     * @return <b>[not-null]</b>  The full name.
     */
    virtual String GetFullName() = 0;
    
    /*!
     * @brief  Returns the name of this category.
     * 
     * @return <b>[not-null]</b>  The name.
     */
    virtual String GetName() = 0;
    
    /*!
     * @brief  Returns the parent category of this category.
     * 
     * @return The parent category or \c null  if this category is the root.
     */
    virtual Ptr<ILoggerCategory> GetParent() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<ILoggerCategory> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x7CC8265;
    
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
      if ((ptr = ILogMessageSource::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
} } } 

#endif
