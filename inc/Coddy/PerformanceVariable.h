////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_PROFILING_PERFORMANCEVARIABLE_H
#define CLODDY_CORE_PROFILING_PERFORMANCEVARIABLE_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IPerformanceVariable.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Collections { template<class> class IList; } } }
namespace Cloddy { namespace Core { namespace Profiling { class IPerformanceValueListener; } } }

// Declare class ::Cloddy::Core::Profiling::PerformanceVariable.

namespace Cloddy { namespace Core { namespace Profiling
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::Collections::IList;
  
  class PerformanceVariable : public virtual IPerformanceVariable
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual float64 GetCurrent();
    
    virtual int32 GetTimestamp();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void AddListener(IPerformanceValueListener* listener);
    
    virtual void RemoveListener(IPerformanceValueListener* listener);
    
    virtual void ReportValue(float64 value);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The most recent performance value.
     */
    float64 current;
    
    /*!
     * @brief  The registered performance value listeners.
     */
    Ptr<IList<Ref<IPerformanceValueListener> > > listeners;
    
    /*!
     * @brief  The timestamp when #current has been reported.
     */
    int32 timestamp;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    void FirePerformanceValueChanged(float64 oldValue);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
  public:
    
    PerformanceVariable();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<PerformanceVariable> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xE0EE08DF;
    
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
      if ((ptr = IPerformanceVariable::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
