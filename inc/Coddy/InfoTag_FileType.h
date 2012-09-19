////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_TOOLS_INFOTAG_FILETYPE_H
#define CLODDY_API_TOOLS_INFOTAG_FILETYPE_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/InfoTag.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Tools { class IInfoTagVisitor; } } }

// Declare class ::Cloddy::API::Tools::InfoTag_FileType.

namespace Cloddy { namespace API { namespace Tools
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  class InfoTag_FileType : public InfoTag
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Constants
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The file is a dataset file.
     */
    static const int32 Dataset = 1;
    
    /*!
     * @brief  The file is an image that can be read using the Imaging API.
     */
    static const int32 Image = 0;
    
    /*!
     * @brief  The file has an unknown type.
     */
    static const int32 Unknown = -1;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  The file type (one of the constants declared in this class).
     * 
     * @return The file type.
     */
    int32 GetType();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of InfoTag_FileType.
     * 
     * @param type The file type (one of the constants declared in this class).
     */
    InfoTag_FileType(int32 type);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void Accept(IInfoTagVisitor* visitor);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The file type (one of the constants declared in this class).
     */
    int32 type;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<InfoTag_FileType> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x37D69C00;
    
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
      if ((ptr = InfoTag::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
