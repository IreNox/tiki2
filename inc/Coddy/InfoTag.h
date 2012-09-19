////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_TOOLS_INFOTAG_H
#define CLODDY_API_TOOLS_INFOTAG_H

#include "CodeX/System.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Tools { class IInfoTagVisitor; } } }

// Declare class ::Cloddy::API::Tools::InfoTag.

namespace Cloddy { namespace API { namespace Tools
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Abstract base class for information tags that are read from a file by the InfoTool 
   *         command.
   */
  class InfoTag : public virtual IComparable<Ref<InfoTag> >
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Name of this info tag.
     * 
     * @return <b>[not-null]</b>  The unique info tag name.
     */
    String GetName();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Accepts the given info tag visitor.
     * 
     * @param visitor <b>[not-null]</b>  The visitor.
     */
    virtual void Accept(IInfoTagVisitor* visitor) = 0;
    
    virtual int32 CompareTo(InfoTag* other);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Constructors
    // ---------------------------------------------------------------------------------------------
  protected:
    
    /*!
     * @brief  Creates a new instance of InfoTag.
     * 
     * @param name <b>[not-empty]</b>  The unique info tag name.
     */
    InfoTag(String name);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The info tag name.
     */
    String name;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<InfoTag> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x2371D17F;
    
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
