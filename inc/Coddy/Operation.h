////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_UTIL_PROGRESS_OPERATION_H
#define CLODDY_API_UTIL_PROGRESS_OPERATION_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IOperation.h"

// Include referenced classes.

#include "CodeX/Disposable.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Util { namespace Progress { class IProgressMonitor; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Util { namespace Progress { class RunningOperation; } } } }

// Declare class ::Cloddy::API::Util::Progress::Operation.

namespace Cloddy { namespace API { namespace Util { namespace Progress
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced classes.
  
  using CodeX::System::Disposable;
  
  /*!
   * @brief  Abstract base class for IOperation implementations.
   * 
   * Subclasses must implement the #Prepare and RunningOperation methods and the #GetName property.
   * They may use the #ShallCancel property to terminate gracefully when another thread has 
   * cancelled the background operation.
   */
  class Operation : public Disposable, public virtual IOperation
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual String GetName() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual Ptr<IOperation> Append(IOperation* operation);
    
    virtual Ptr<RunningOperation> Background();
    
    virtual void Cancel();
    
    virtual void Prepare(IProgressMonitor* progressMonitor) = 0;
    
    virtual void Run(IProgressMonitor* argument) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Attributes
    // ---------------------------------------------------------------------------------------------
  protected:
    
    /*!
     * @brief  Shall the background operation cancel?
     * 
     * @return \c true  if the operation shall cancel,\c false  if not.
     */
    bool ShallCancel();
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Runs the given IOperation as a child of this operation.
     * 
     * The given \e operation  will be disposed after it has finished.
     * 
     * @param operation <b>[not-null]</b>  The sub-operation to run.
     * @param progressMonitor <b>[not-null]</b>  The progress monitor to use.
     */
    void RunSubOperation(IOperation* operation, IProgressMonitor* progressMonitor);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Shall the background operation cancel?
     */
    bool shallCancel;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
  public:
    
    Operation();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<Operation> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xCC7E96E;
    
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
      if ((ptr = IOperation::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } 

#endif
