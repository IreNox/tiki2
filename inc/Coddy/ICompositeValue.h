////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_CONFIG_ICOMPOSITEVALUE_H
#define CLODDY_CORE_CONFIG_ICOMPOSITEVALUE_H

#include "CodeX/System.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Collections { template<class> class ICollectionConst; } } }
namespace Cloddy { namespace Core { namespace Collections { template<class> class ISetConst; } } }
namespace Cloddy { namespace Core { namespace Config { class IConfigPropertyValue; } } }

// Declare interface ::Cloddy::Core::Config::ICompositeValue.

namespace Cloddy { namespace Core { namespace Config
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::Collections::ICollectionConst;
  using Cloddy::Core::Collections::ISetConst;
  
  class NO_VTABLE ICompositeValue : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The number of fields.
     * 
     * @return <b>[>=0]</b>  The number of fields.
     */
    virtual int32 GetCount() = 0;
    
    /*!
     * @brief  Returns a read-only set of all feild names.
     * 
     * @return <b>[not-null]</b>  The set of field names.
     */
    virtual Ptr<ISetConst<Prm<String> > > GetFieldNames() = 0;
    
    /*!
     * @brief  Returns a read-only collection of all field values.
     * 
     * @return <b>[not-null]</b>  The collection of field values.
     */
    virtual Ptr<ICollectionConst<Ref<IConfigPropertyValue> > > GetFieldValues() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Returns the field value for the given name.
     * 
     * @param name <b>[not-empty]</b>  The field name.
     * 
     * @return <b>[not-null]</b>  The field value.
     */
    virtual Ptr<IConfigPropertyValue> GetField(String name) = 0;
    
    /*!
     * @brief  Returns if a field of the given name exists in this composite value.
     * 
     * @param name <b>[not-empty]</b>  The field name.
     * 
     * @return \c true  if the given field is existent,\c false  if not.
     */
    virtual bool HasField(String name) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<ICompositeValue> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x5B334A5A;
    
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
