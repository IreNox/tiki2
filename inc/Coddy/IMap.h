////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_UTIL_IMAP_H
#define CLODDY_API_UTIL_IMAP_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/MapType.h"

// Include referenced interfaces.

#include "Cloddy/IBeginEnd.h"
#include "CodeX/IDisposable.h"
#include "Cloddy/IFlushable.h"

// Declare interface ::Cloddy::API::Util::IMap.

namespace Cloddy { namespace API { namespace Util
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::IO::IFlushable;
  using CodeX::System::IDisposable;
  
  /*!
   * @brief  Base interface for maps.
   * 
   * Maps can be rectangular or cubemaps.A rectangular map is like a 2D texture,where each texel 
   * represents a map sample.A cubemap is like a cubemap texture.
   * <pre>
   *      .   Rectangular:
   *      .   ------------
   *      .   
   *      .       (0|0)            (w|0) (s|0)
   *      .         +----------------+-----+               Y-
   *      .         |                |     |               |
   *      .         |                |     |               |
   *      .         |                |     |         X- ---O--- X+
   *      .         |                |     |               |
   *      .         |                |     |               |
   *      .   (0|h) +----------------+     |               Y+
   *      .         |              (w|h)   |
   *      .         |                      |      +-----------------+
   *      .         |                      |      | w := Width - 1  |
   *      .         |                      |      | h := Height - 1 |
   *      .         |                      |      | s := Size  - 1  |
   *      .         +----------------------+      +-----------------+
   *      .       (0|s)                  (s|s)
   * </pre>
   * Rectangular maps can have arbitrary dimensions (regarding \c w  and \c h ).The internal size 
   * \c s  however is always a power of two plus one and is greater than or equal to both \c w  and 
   * \c h .
   * <pre>
   *      .   Cubemap:
   *      .   --------
   *      .   
   *      .       (0|0|s)               (s|0|s)
   *      .             +---------------+               Y- |  / Z+
   *      .            /|              /|                  | /
   *      .           / |             / |                  |/
   *      .   (0|0|0)/  |     (s|0|0)/  |           X- ----O---- X+
   *      .         +---------------+   |                 /|
   *      .         |   |           |   |                / |
   *      .         |   +-----------|---+            Z- /  | Y+
   *      .         |  /(0|s|s)     |  /(s|s|s)
   *      .         | /             | /           +-----------------+
   *      .         |/              |/            | s := Size  - 1  |
   *      .         +---------------+             +-----------------+
   *      .   (0|s|0)               (s|s|0)
   * </pre>
   * The size \c s  of a cubemap is always a power of two plus one.For cubemaps,the \c w  and \c h  
   * values are equal to \c s .
   */
  class NO_VTABLE IMap : public virtual IDisposable, public virtual IBeginEnd, public virtual IFlushable
  {
    // ---------------------------------------------------------------------------------------------
    // Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Returns the height of this map.
     * 
     * @return <b>[>0]</b>  The height of the map,in samples.
     */
    virtual int32 GetHeight() = 0;
    
    /*!
     * @brief  Is this map mutable,ie. can the application modify its samples?
     * 
     * @return \c true  if the map is mutable,\c false  if not.
     */
    virtual bool IsMutable() = 0;
    
    /*!
     * @brief  The type of this map (rectangular or cube).
     * 
     * @return The MapType of this map.
     */
    virtual MapType GetMapType() = 0;
    
    /*!
     * @brief  Returns the internal size of this map (is always a power of two plus one).
     * 
     * @return <b>[pow2+1]</b>  The internal size of the map.
     */
    virtual int32 GetSize() = 0;
    
    /*!
     * @brief  Returns the width of this map.
     * 
     * @return <b>[>0]</b>  The width of the map,in samples.
     */
    virtual int32 GetWidth() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IMap> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xF4A3F0A9;
    
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
      if ((ptr = IDisposable::TryCast(typeId)) != 0) return ptr;
      if ((ptr = IBeginEnd::TryCast(typeId)) != 0) return ptr;
      if ((ptr = IFlushable::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
} } } 

#endif
