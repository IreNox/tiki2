////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_TOOLS_TOOLPARAMETERERRORS_H
#define CLODDY_API_TOOLS_TOOLPARAMETERERRORS_H

#include "CodeX/System.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Collections { template<class> class IList; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Tools { class ToolParameterError; } } }

// Declare class ::Cloddy::API::Tools::ToolParameterErrors.

namespace Cloddy { namespace API { namespace Tools
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::Collections::IList;
  
  /*!
   * @brief  Represents a set of tool parameter errors that have been found during validation of 
   *         an ITool object.
   */
  class ToolParameterErrors : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Returns the number of tool parameter errors.
     * 
     * @return <b>[>=0]</b>  The number of tool parameter errors.
     */
    int32 GetCount();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of ToolParameterErrors.
     */
    ToolParameterErrors();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Adds a tool parameter error.
     * 
     * @param parameterName <b>[not-null]</b>  Name of the tool parameter.
     * @param errorMessage <b>[not-null]</b>  The error description.
     */
    void Add(String parameterName, String errorMessage);
    
    /*!
     * @brief  Returns the \e index -th tool parameter error.
     * 
     * @param index <b>[0..#GetCount-1]</b>  Index of the tool parameter error to return.
     * 
     * @return <b>[not-null]</b>  The ToolParameterError object.
     */
    Ptr<ToolParameterError> Get(int32 index);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The tool parameter errors.
     */
    Ptr<IList<Ref<ToolParameterError> > > errors;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<ToolParameterErrors> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x4E01AAE1;
    
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
