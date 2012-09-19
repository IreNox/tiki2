////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_VERTEXFACTORIES_VERTEXFORMATS_IVERTEXFORMAT_H
#define CLODDY_API_VERTEXFACTORIES_VERTEXFORMATS_IVERTEXFORMAT_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IVertexSize.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace VertexData { class IVertexDataCollection; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace VertexData { class Semantic; } } }
namespace CodeX { namespace System { class ByteBuffer; } }

// Declare interface ::Cloddy::API::VertexFactories::VertexFormats::IVertexFormat.

namespace Cloddy { namespace API { namespace VertexFactories { namespace VertexFormats
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::VertexData::IVertexDataCollection;
  using Cloddy::Kernel::IVertexSize;
  
  // Use referenced classes.
  
  using Cloddy::API::VertexData::Semantic;
  using CodeX::System::ByteBuffer;
  
  /*!
   * @brief  Base interface for classes that convert vertex data stored in a one or 
   *         more IVertexData containers to GPU vertex data.
   */
  class NO_VTABLE IVertexFormat : public virtual IVertexSize
  {
    // ---------------------------------------------------------------------------------------------
    // Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Returns a mnemonic string that describes the layout of this vertex format,eg. 
     *         \c P3F  for three 32-bit floating point values representing vertex position 
     *         coordinates.
     * 
     * @return <b>[not-null]</b>  The mnemonic string.
     */
    virtual String GetMnemonic() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Appends the given vertex format to this vertex format.
     * 
     * @param format <b>[not-null]</b>  The vertex format to append.
     * 
     * @return <b>[not-null]</b>  The resulting vertex format.
     */
    virtual Ptr<IVertexFormat> Append(IVertexFormat* format) = 0;
    
    /*!
     * @brief  Sets the vertex data containers from which this vertex converter shall read vertex 
     *         data.
     * 
     * @param vertexDataCollection <b>[not-null]</b>  The vertex data collection.
     */
    virtual void SetVertexData(IVertexDataCollection* vertexDataCollection) = 0;
    
    /*!
     * @brief  Returns if this vertex format uses the given semantic.
     * 
     * @param semantic <b>[not-null]</b>  The vertex data semantic.
     * 
     * @return \c true  if this vertex format uses the given semantic,\c false  if not.
     */
    virtual bool UsesSemantic(Semantic* semantic) = 0;
    
    /*!
     * @brief  Writes vertex data to the given vertex buffer.
     * 
     * @param vertex <b>[>=0]</b>  The vertex index.
     * @param buffer <b>[not-null]</b>  The target vertex buffer region.
     */
    virtual void WriteVertex(int32 vertex, ByteBuffer* buffer) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IVertexFormat> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xAE6FB0C0;
    
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
      if ((ptr = IVertexSize::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
} } } } 

#endif
