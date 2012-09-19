////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_BRUSHES_BRUSHMASK_BUFFER_H
#define CLODDY_API_HEIGHTMAPS_BRUSHES_BRUSHMASK_BUFFER_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/BrushMask.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Brushes { class IBrushMask; } } } }
namespace Cloddy { namespace API { namespace Imaging { class IImageReader; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Brushes { class BrushMask; } } } }

// Declare class ::Cloddy::API::Heightmaps::Brushes::BrushMask_Buffer.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Brushes
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Imaging::IImageReader;
  
  /*!
   * @brief  An implementation of the IBrushMask interface that provides mask values that have been 
   *         read from a 16-bit greyscale image or specified explicitly in a mask value buffer.
   */
  class BrushMask_Buffer : public BrushMask
  {
    // Declare friend classes.
    
    friend class BrushMask;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual Ptr<IBrushMask> Buffer();
    
    virtual int32 GetMaskValue(int32 x, int32 y);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
  protected:
    
    virtual Ptr<IBrushMask> DoScale(int32 width, int32 height);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Stride of value buffer.
     */
    int32 stride;
    
    /*!
     * @brief  The value buffer.
     */
    Array<int16> values;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    BrushMask_Buffer(int32 width, int32 height, Array<int16> values);
    
    /*!
     * @brief  Creates a new instance of BrushMask_Buffer.
     * 
     * @param reader The 16-bit greyscale image to read.
     */
    BrushMask_Buffer(IImageReader* reader);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<BrushMask_Buffer> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xD964629F;
    
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
      if ((ptr = BrushMask::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } 

#endif
