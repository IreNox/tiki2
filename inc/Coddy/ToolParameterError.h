////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_TOOLS_TOOLPARAMETERERROR_H
#define CLODDY_API_TOOLS_TOOLPARAMETERERROR_H

#include "CodeX/System.h"

// Declare class ::Cloddy::API::Tools::ToolParameterError.

namespace Cloddy { namespace API { namespace Tools
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Represents a validation failure of the parameters of a ITool.
   */
  class ToolParameterError : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The error message.
     * 
     * @return <b>[not-null]</b>  The error message.
     */
    String GetErrorMessage();
    
    /*!
     * @brief  Name of the invalid tool parameter.
     * 
     * @return <b>[not-null]</b>  The parameter name.
     */
    String GetParameterName();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of ToolParameterError.
     * 
     * @param parameterName <b>[not-null]</b>  Name of the invalid tool parameter.
     * @param errorMessage <b>[not-null]</b>  The error message.
     */
    ToolParameterError(String parameterName, String errorMessage);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The error message.
     */
    String errorMessage;
    
    /*!
     * @brief  Name of the invalid tool parameter.
     */
    String parameterName;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<ToolParameterError> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xF0A668D6;
    
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
      return (void*) 0;
    }
  };
  
} } } 

#endif
