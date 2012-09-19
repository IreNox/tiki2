////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_UTIL_SPATIAL_CELLSPACE_H
#define CLODDY_API_UTIL_SPATIAL_CELLSPACE_H

#include "CodeX/System.h"

// Forward declare referenced structures.

namespace Cloddy { namespace Core { namespace Math { namespace Vectors { struct Vec3I; } } } }

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Collections { template<class> class ISet; } } }

// Declare class ::Cloddy::API::Util::Spatial::CellSpace.

namespace Cloddy { namespace API { namespace Util { namespace Spatial
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced structures.
  
  using Cloddy::Core::Math::Vectors::Vec3I;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::Collections::ISet;
  
  /*!
   * @brief  The CellSpace class defines a finite three-dimensional space that consist of equally 
   *         size cubes.
   */
  class CellSpace : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Constants
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The maximum valid coordinate value.
     */
    static const int32 Max = 2097151;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of CellSpace.
     */
    CellSpace();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Returns the state of the given cell.
     * 
     * @param v The cell coordinates.
     * 
     * @return \c true  if the cell is solid,\c false  if it is empty.
     */
    bool GetCell(const Vec3I& v);
    
    /*!
     * @brief  Returns the state of the given cell.
     * 
     * @param x <b>[0..#Max]</b>  The cell X-coordinate.
     * @param y <b>[0..#Max]</b>  The cell Y-coordinate.
     * @param z <b>[0..#Max]</b>  The cell Z-coordinate.
     * 
     * @return \c true  if the cell is solid,\c false  if it is empty.
     */
    bool GetCell(int32 x, int32 y, int32 z);
    
    /*!
     * @brief  Sets the state of the given cell.
     * 
     * @param v The cell coordinates.
     * @param solid \c true  to make the cell solid,\c false  to make it empty.
     */
    void SetCell(const Vec3I& v, bool solid);
    
    /*!
     * @brief  Sets the state of the given cell.
     * 
     * @param x <b>[0..#Max]</b>  The cell X-coordinate.
     * @param y <b>[0..#Max]</b>  The cell Y-coordinate.
     * @param z <b>[0..#Max]</b>  The cell Z-coordinate.
     * @param solid \c true  to make the cell solid,\c false  to make it empty.
     */
    void SetCell(int32 x, int32 y, int32 z, bool solid);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The set of solid cells.
     */
    Ptr<ISet<Prm<int64> > > cells;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Computes the cell ID for the given coordinates.
     * 
     * @param x X-coordinate of cell.
     * @param y Y-coordiante of cell.
     * @param z Z-coordinate of cell.
     * 
     * @return The cell ID.
     */
    static int64 ToCellId(int32 x, int32 y, int32 z);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<CellSpace> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x3064B16E;
    
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
  
} } } } 

#endif
