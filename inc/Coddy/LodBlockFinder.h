////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_DATASETS_LODBLOCKFINDER_H
#define CLODDY_API_DATASETS_LODBLOCKFINDER_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IMapRegionCallback.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Util { class IMapRegion; } } }
namespace Cloddy { namespace Core { namespace Collections { template<class> class ISet; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Datasets { class LodBlockPartitioning2D; } } }

// Declare class ::Cloddy::API::Datasets::LodBlockFinder.

namespace Cloddy { namespace API { namespace Datasets
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Util::IMapRegion;
  using Cloddy::API::Util::IMapRegionCallback;
  using Cloddy::Core::Collections::ISet;
  
  class LodBlockFinder : public virtual IMapRegionCallback
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Creates a new instance of LodBlockFinder.
     * 
     * @param partitioning <b>[not-null]</b>  The LOD block partitioning to use.
     * @param isCube Will be used for a cubemap?
     */
    LodBlockFinder(LodBlockPartitioning2D* partitioning, bool isCube);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void ConsumeMapRegion(int32 face, int32 faceX, int32 faceY, int32 width, int32 height);
    
    /*!
     * @brief  Finds all LOD blocks that intersect with the given map region.
     * 
     * @param mapRegion <b>[not-null]</b>  The map region.
     * 
     * @return <b>[not-null]</b>  The set of found LOD blocks.
     */
    Ptr<ISet<Prm<int32> > > FindLodBlocks(IMapRegion* mapRegion);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    Ptr<ISet<Prm<int32> > > blockIndices;
    
    bool isCube;
    
    Ptr<LodBlockPartitioning2D> partitioning;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<LodBlockFinder> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x14602A4D;
    
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
      if ((ptr = IMapRegionCallback::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
