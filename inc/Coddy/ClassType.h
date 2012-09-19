////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_CONFIG_CLASSTYPE_H
#define CLODDY_CORE_CONFIG_CLASSTYPE_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IConfigPropertyType.h"
#include "Cloddy/IFieldContainer.h"

// Include referenced classes.

#include "CodeX/Disposable.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Collections { template<class> class IList; } } }
namespace Cloddy { namespace Core { namespace Config { class IConfigPropertyValue; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace Config { class ConfigProperty; } } }

// Declare class ::Cloddy::Core::Config::ClassType.

namespace Cloddy { namespace Core { namespace Config
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::Collections::IList;
  
  // Use referenced classes.
  
  using CodeX::System::Disposable;
  
  /*!
   * @brief  Config property type:composite class type (supporting simple inheritance).
   */
  class ClassType : public Disposable, public virtual IConfigPropertyType, public virtual IFieldContainer
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual int32 GetFieldCount();
    
    virtual String GetName();
    
    /*!
     * @brief  The super class of this class type.
     * 
     * @return The super class type or \c null .
     */
    Ptr<ClassType> GetSuperClass();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of ClassType.
     * 
     * The created class type will have no fields and no super class.
     * 
     * @param name <b>[not-empty]</b>  The class name.
     */
    ClassType(String name);
    
    /*!
     * @brief  Creates a new instance of ClassType.
     * 
     * @param name <b>[not-empty]</b>  The class name.
     * @param fields The class fields or \c null  if this class has no fields.
     * @param superClass The super class of this class type,or \c null .
     */
    ClassType(String name, Array<Ptr<ConfigProperty> > fields, ClassType* superClass);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual Ptr<IConfigPropertyValue> CreateValue();
    
    virtual Ptr<ConfigProperty> GetField(int32 idx);
    
    virtual bool IsConvertibleTo(IConfigPropertyType* other);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
  protected:
    
    virtual void DisposeManaged();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Cached total number of fields.
     */
    int32 fieldCount;
    
    /*!
     * @brief  The class fields.
     */
    Array<Ptr<ConfigProperty> > fields;
    
    /*!
     * @brief  The class name.
     */
    String name;
    
    /*!
     * @brief  List of direct sub classes.
     */
    Ptr<IList<Ref<ClassType> > > subClasses;
    
    /*!
     * @brief  The super class of this class type.
     */
    Ptr<ClassType> superClass;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    void AddSubClass(ClassType* subClass);
    
    /*!
     * @brief  Retrieves the given class field,looking into superclasses if necessary.
     * 
     * @param idx The field index.
     * 
     * @return The class field or \c null .
     */
    Ptr<ConfigProperty> GetFieldInternal(int32 idx);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<ClassType> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x87536637;
    
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
      if ((ptr = Disposable::TryCast(typeId)) != 0) return ptr;
      if ((ptr = IConfigPropertyType::TryCast(typeId)) != 0) return ptr;
      if ((ptr = IFieldContainer::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
