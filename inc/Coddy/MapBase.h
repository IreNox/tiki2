////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_UTIL_MAPBASE_H
#define CLODDY_API_UTIL_MAPBASE_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/MapType.h"

// Include referenced interfaces.

#include "Cloddy/IMap.h"

// Include referenced classes.

#include "CodeX/Disposable.h"

// Declare class ::Cloddy::API::Util::MapBase.

namespace Cloddy { namespace API { namespace Util
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced classes.
  
  using CodeX::System::Disposable;
  
  /*!
   * @brief  Abstract base class for IMap implementations.
   * 
   * The MapBase class stores the values of the #GetHeight,MapType,#GetSize and #GetWidth 
   * properties.These can be initialized from within the constructor of a subclass by calling one 
   * of the following methods:#Initialize,#InitializeCube and #InitializeRect.
   * 
   * The following interface implementations are provided by this class:
   *   - #GetHeight:fixed
   *   - #IsMutable:default
   *   - MapType:fixed
   *   - #GetSize:fixed
   *   - #GetWidth:fixed
   *   - #Begin:empty
   *   - #End:empty
   *   - #Flush:empty
   */
  class MapBase : public Disposable, public virtual IMap
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual int32 GetHeight();
    
    virtual bool IsMutable();
    
    virtual MapType GetMapType();
    
    virtual int32 GetSize();
    
    virtual int32 GetWidth();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Computes the internal map size for the given map width and height.
     * 
     * @param width <b>[>0]</b>  The map width.
     * @param height <b>[>0]</b>  The map height.
     * 
     * @return <b>[pow2+1]</b>  The internal map size.
     */
    static int32 ComputeInternalSize(int32 width, int32 height);
    
    /*!
     * @brief  Computes the number of refinement levels the given map has.
     * 
     * @param map <b>[not-null]</b>  The map.
     * 
     * @return <b>[>=0]</b>  The number of refinement levels.
     */
    static int32 ComputeMeshRefinementLevels(IMap* map);
    
    virtual void Begin();
    
    virtual void End();
    
    virtual void Flush();
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Attributes
    // ---------------------------------------------------------------------------------------------
  protected:
    
    /*!
     * @brief  The height of the heightmap.
     */
    int32 height;
    
    /*!
     * @brief  The internal size of the heightmap,minus one.
     */
    int32 sizeMinusOne;
    
    /*!
     * @brief  The width of the heightmap.
     */
    int32 width;
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Initializes the map to the size and type of the given IMap object.
     * 
     * @param map <b>[not-null]</b>  The IMap object.
     */
    void Initialize(IMap* map);
    
    /*!
     * @brief  Initializes the map to type MapType::MapType_Cube.
     * 
     * @param size <b>[pow2+1]</b>  Size of the map.
     */
    void InitializeCube(int32 size);
    
    /*!
     * @brief  Initializes the map to type MapType::MapType_Rect.
     * 
     * @param width <b>[>0]</b>  Width of the map.
     * @param height <b>[>0]</b>  Height of the map.
     */
    void InitializeRect(int32 width, int32 height);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The type of the heightmap (rectangular or cube).
     */
    MapType mapType;
    
    /*!
     * @brief  The internal size of the heightmap.
     */
    int32 size;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
  public:
    
    MapBase();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<MapBase> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x654FD169;
    
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
      if ((ptr = IMap::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
