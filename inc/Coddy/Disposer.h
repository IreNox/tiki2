////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_KERNEL_DISPOSER_H
#define CLODDY_KERNEL_DISPOSER_H

#include "CodeX/System.h"

// Include referenced classes.

#include "CodeX/Disposable.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Collections { template<class> class IList; } } }
namespace CodeX { namespace System { class IDisposable; } }

// Declare class ::Cloddy::Kernel::Disposer.

namespace Cloddy { namespace Kernel
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::Collections::IList;
  using CodeX::System::IDisposable;
  
  // Use referenced classes.
  
  using CodeX::System::Disposable;
  
  /*!
   * @brief  A Disposer is a container that holds zero or more IDisposable objects,which are 
   *         disposed when the Disposer itself is disposed.
   * 
   * The IDisposable objects will be disposed in the same order as they have been added to 
   * the Disposer via #Add.
   */
  class Disposer : public Disposable
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Adds an IDisposable object to this disposer.
     * 
     * The given \e disposable  object will be added to the list of objects to dispose.If the 
     * given \e disposable  object has already been added to this disposer,it will be moved to the 
     * end of the list.
     * 
     * @param disposable <b>[not-null]</b>  The object to add.
     */
    void Add(IDisposable* disposable);
    
    /*!
     * @brief  Removes an IDisposable object from this disposer.
     * 
     * @param disposable <b>[not-null]</b>  The object to add.
     */
    void Remove(IDisposable* disposable);
    
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
     * @brief  The list of IDisposable objects currently in the trashcan.
     */
    Ptr<IList<Ref<IDisposable> > > disposables;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<Disposer> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x89027046;
    
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
      return (void*) 0;
    }
  };
  
} } 

#endif
