////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_UTIL_SPATIAL_IDISCRETESPACE_H
#define CLODDY_API_UTIL_SPATIAL_IDISCRETESPACE_H

#include "CodeX/System.h"

// Forward declare referenced structures.

namespace Cloddy { namespace Core { namespace Math { namespace Vectors { struct Vec3I; } } } }

// Declare interface ::Cloddy::API::Util::Spatial::IDiscreteSpace.

namespace Cloddy { namespace API { namespace Util { namespace Spatial
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced structures.
  
  using Cloddy::Core::Math::Vectors::Vec3I;
  
  /*!
   * @brief  Base interface for classes that perform discrete space partitioning.
   * 
   * A discrete space is divided into cells.Each cell can be solid or empty.
   */
  class NO_VTABLE IDiscreteSpace : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The depth of this discrete space.
     * 
     * @return <b>[>0]</b>  The space depth,in cells.
     */
    virtual int32 GetDepth() = 0;
    
    /*!
     * @brief  The height of this discrete space.
     * 
     * @return <b>[>0]</b>  The space height,in cells.
     */
    virtual int32 GetHeight() = 0;
    
    /*!
     * @brief  The width of this discrete space.
     * 
     * @return <b>[>0]</b>  The space width,in cells.
     */
    virtual int32 GetWidth() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Is the given cell solid?
     * 
     * @param xyz The cell coordinates.
     * 
     * @return \c true  if the cell is solid,\c false  if it is empty.
     */
    virtual bool IsSolid(const Vec3I& xyz) = 0;
    
    /*!
     * @brief  Is the given cell solid?
     * 
     * @param x The cell X-coordinate.
     * @param y The cell Y-coordinate.
     * @param z The cell Z-coordinate.
     * 
     * @return \c true  if the cell is solid,\c false  if it is empty.
     */
    virtual bool IsSolid(int32 x, int32 y, int32 z) = 0;
    
    /*!
     * @brief  Makes the given cell solid or empty.
     * 
     * @param xyz The cell coordinates.
     * @param solid bla
     * 
     * @return bla
     */
    virtual bool SetSolid(const Vec3I& xyz, bool solid) = 0;
    
    virtual bool SetSolid(int32 x, int32 y, int32 z, bool solid) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IDiscreteSpace> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x2788AC9A;
    
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
