////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_HEIGHTMAP_CONCAT_H
#define CLODDY_API_HEIGHTMAPS_HEIGHTMAP_CONCAT_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/HeightmapLayer.h"

// Include referenced classes.

#include "Cloddy/CompositeHeightmapTwo.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Heightmaps { class IHeightmap; } } }
namespace Cloddy { namespace Core { namespace Collections { template<class> class IPredicate; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Heightmaps { class Heightmap; } } }
namespace Cloddy { namespace API { namespace Heightmaps { class HeightmapSample; } } }

// Declare class ::Cloddy::API::Heightmaps::Heightmap_Concat.

namespace Cloddy { namespace API { namespace Heightmaps
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::Collections::IPredicate;
  
  class Heightmap_Concat : public CompositeHeightmapTwo
  {
    // Declare friend classes.
    
    friend class Heightmap;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual void Get(int32 x, int32 y, HeightmapSample* sample);
    
    virtual void Get(int32 x, int32 y, int32 z, HeightmapSample* sample);
    
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
     * @brief  The layers of the second heightmap.
     */
    HeightmapLayer layers;
    
    /*!
     * @brief  Optional heightmap sample predicate.
     */
    Ptr<IPredicate<Ref<HeightmapSample> > > predicate;
    
    /*!
     * @brief  Helper heightmap sample object.
     */
    Ptr<HeightmapSample> sample;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of Heightmap_Concat.
     * 
     * @param first The first heightmap.
     * @param second The second heightmap.
     * @param predicate Optional heightmap sample predicate.
     */
    Heightmap_Concat(IHeightmap* first, IHeightmap* second, IPredicate<Ref<HeightmapSample> >* predicate);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<Heightmap_Concat> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xC5D13246;
    
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
      if ((ptr = CompositeHeightmapTwo::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
