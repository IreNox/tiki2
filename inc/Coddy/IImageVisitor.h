////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_IMAGING_IIMAGEVISITOR_H
#define CLODDY_API_IMAGING_IIMAGEVISITOR_H

#include "CodeX/System.h"

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Imaging { class BlendImage; } } }
namespace Cloddy { namespace API { namespace Imaging { class ClampImage; } } }
namespace Cloddy { namespace API { namespace Imaging { class ClipImage; } } }
namespace Cloddy { namespace API { namespace Imaging { class ConstantImage; } } }
namespace Cloddy { namespace API { namespace Imaging { class ConvertImage; } } }
namespace Cloddy { namespace API { namespace Imaging { class DatasetImage; } } }
namespace Cloddy { namespace API { namespace Imaging { class FileImage; } } }
namespace Cloddy { namespace API { namespace Imaging { class GridImage; } } }
namespace Cloddy { namespace API { namespace Imaging { class MemoryImage; } } }
namespace Cloddy { namespace API { namespace Imaging { class NormalizeImage; } } }
namespace Cloddy { namespace API { namespace Imaging { class PadImage; } } }
namespace Cloddy { namespace API { namespace Imaging { class PatchImage; } } }
namespace Cloddy { namespace API { namespace Imaging { class PixelCoverageImage; } } }
namespace Cloddy { namespace API { namespace Imaging { class RawImage; } } }
namespace Cloddy { namespace API { namespace Imaging { class ScaleImage; } } }
namespace Cloddy { namespace API { namespace Imaging { class SmoothImage; } } }

// Declare interface ::Cloddy::API::Imaging::IImageVisitor.

namespace Cloddy { namespace API { namespace Imaging
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Visitor interface for IImage objects.
   */
  class NO_VTABLE IImageVisitor : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Visits the given IImage object.
     * 
     * @param image <b>[not-null]</b>  The IImage object.
     * @param userData Optional user data.
     */
    virtual void Visit(BlendImage* image, Object* userData) = 0;
    
    /*!
     * @brief  Visits the given IImage object.
     * 
     * @param image <b>[not-null]</b>  The IImage object.
     * @param userData Optional user data.
     */
    virtual void Visit(ClampImage* image, Object* userData) = 0;
    
    /*!
     * @brief  Visits the given IImage object.
     * 
     * @param image <b>[not-null]</b>  The IImage object.
     * @param userData Optional user data.
     */
    virtual void Visit(ClipImage* image, Object* userData) = 0;
    
    /*!
     * @brief  Visits the given IImage object.
     * 
     * @param image <b>[not-null]</b>  The IImage object.
     * @param userData Optional user data.
     */
    virtual void Visit(ConstantImage* image, Object* userData) = 0;
    
    /*!
     * @brief  Visits the given IImage object.
     * 
     * @param image <b>[not-null]</b>  The IImage object.
     * @param userData Optional user data.
     */
    virtual void Visit(ConvertImage* image, Object* userData) = 0;
    
    /*!
     * @brief  Visits the given IImage object.
     * 
     * @param image <b>[not-null]</b>  The IImage object.
     * @param userData Optional user data.
     */
    virtual void Visit(DatasetImage* image, Object* userData) = 0;
    
    /*!
     * @brief  Visits the given IImage object.
     * 
     * @param image <b>[not-null]</b>  The IImage object.
     * @param userData Optional user data.
     */
    virtual void Visit(FileImage* image, Object* userData) = 0;
    
    /*!
     * @brief  Visits the given IImage object.
     * 
     * @param image <b>[not-null]</b>  The IImage object.
     * @param userData Optional user data.
     */
    virtual void Visit(GridImage* image, Object* userData) = 0;
    
    /*!
     * @brief  Visits the given IImage object.
     * 
     * @param image <b>[not-null]</b>  The IImage object.
     * @param userData Optional user data.
     */
    virtual void Visit(MemoryImage* image, Object* userData) = 0;
    
    /*!
     * @brief  Visits the given IImage object.
     * 
     * @param image <b>[not-null]</b>  The IImage object.
     * @param userData Optional user data.
     */
    virtual void Visit(NormalizeImage* image, Object* userData) = 0;
    
    /*!
     * @brief  Visits the given IImage object.
     * 
     * @param image <b>[not-null]</b>  The IImage object.
     * @param userData Optional user data.
     */
    virtual void Visit(PadImage* image, Object* userData) = 0;
    
    /*!
     * @brief  Visits the given IImage object.
     * 
     * @param image <b>[not-null]</b>  The IImage object.
     * @param userData Optional user data.
     */
    virtual void Visit(PatchImage* image, Object* userData) = 0;
    
    /*!
     * @brief  Visits the given IImage object.
     * 
     * @param image <b>[not-null]</b>  The IImage object.
     * @param userData Optional user data.
     */
    virtual void Visit(PixelCoverageImage* image, Object* userData) = 0;
    
    /*!
     * @brief  Visits the given IImage object.
     * 
     * @param image <b>[not-null]</b>  The IImage object.
     * @param userData Optional user data.
     */
    virtual void Visit(RawImage* image, Object* userData) = 0;
    
    /*!
     * @brief  Visits the given IImage object.
     * 
     * @param image <b>[not-null]</b>  The IImage object.
     * @param userData Optional user data.
     */
    virtual void Visit(ScaleImage* image, Object* userData) = 0;
    
    /*!
     * @brief  Visits the given IImage object.
     * 
     * @param image <b>[not-null]</b>  The IImage object.
     * @param userData Optional user data.
     */
    virtual void Visit(SmoothImage* image, Object* userData) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IImageVisitor> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xC8EC9E7E;
    
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
} } } 

#endif
