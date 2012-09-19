////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_TOOLS_IINFOTAGVISITOR_H
#define CLODDY_API_TOOLS_IINFOTAGVISITOR_H

#include "CodeX/System.h"

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Tools { class InfoTag_Dataset; } } }
namespace Cloddy { namespace API { namespace Tools { class InfoTag_FileType; } } }
namespace Cloddy { namespace API { namespace Tools { class InfoTag_Image; } } }

// Declare interface ::Cloddy::API::Tools::IInfoTagVisitor.

namespace Cloddy { namespace API { namespace Tools
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Visitor interface for concrete InfoTag classes.
   */
  class NO_VTABLE IInfoTagVisitor : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Visits the given info tag.
     * 
     * @param tag The info tag.
     */
    virtual void Visit(InfoTag_Dataset* tag) = 0;
    
    /*!
     * @brief  Visits the given info tag.
     * 
     * @param tag The info tag.
     */
    virtual void Visit(InfoTag_FileType* tag) = 0;
    
    /*!
     * @brief  Visits the given info tag.
     * 
     * @param tag The info tag.
     */
    virtual void Visit(InfoTag_Image* tag) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IInfoTagVisitor> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x44D5775C;
    
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
