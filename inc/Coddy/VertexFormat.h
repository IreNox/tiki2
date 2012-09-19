////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_VERTEXFACTORIES_VERTEXFORMATS_VERTEXFORMAT_H
#define CLODDY_API_VERTEXFACTORIES_VERTEXFORMATS_VERTEXFORMAT_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/ColorFormat.h"

// Include referenced interfaces.

#include "Cloddy/IVertexFormat.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace VertexData { class IVertexDataCollection; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace VertexData { class Semantic; } } }
namespace Cloddy { namespace API { namespace VertexFactories { namespace VertexFormats { class FixedRange; } } } }
namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::API::VertexFactories::VertexFormats::VertexFormat.

namespace Cloddy { namespace API { namespace VertexFactories { namespace VertexFormats
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::VertexData::IVertexDataCollection;
  
  // Use referenced classes.
  
  using Cloddy::API::VertexData::Semantic;
  using CodeX::System::ByteBuffer;
  
  /*!
   * @brief  Abstract base class for IVertexFormat implementations.
   */
  class VertexFormat : public virtual IVertexFormat
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual String GetMnemonic();
    
    virtual int32 GetVertexSize();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  A vertex format that contains vertex diffuse colors.
     * 
     * This vertex format has the following structure:
     *   - diffuse :int
     * 
     * @param colorFormat The color format to use.
     * 
     * @return <b>[not-null]</b>  The vertex format.
     */
    static Ptr<IVertexFormat> C1I(ColorFormat colorFormat);
    
    /*!
     * @brief  A vertex format that contains vertex tangent vectors.
     * 
     * This vertex format has the following structure:
     *   - tangent :float3
     * 
     * @param maxHeightmapCoord The maximum heightmap coordinate.
     * 
     * @return <b>[not-null]</b>  The vertex format.
     */
    static Ptr<IVertexFormat> G3F(int32 maxHeightmapCoord);
    
    /*!
     * @brief  A vertex format that contains vertex normal vectors.
     * 
     * This vertex format has the following structure:
     *   - normal :float3
     * 
     * @return <b>[not-null]</b>  The vertex format.
     */
    static Ptr<IVertexFormat> N3F();
    
    /*!
     * @brief  A vertex format that contains vertex positions.
     * 
     * This vertex format has the following structure:
     *   - position :float3
     * 
     * @return <b>[not-null]</b>  The vertex format.
     */
    static Ptr<IVertexFormat> P3F();
    
    /*!
     * @brief  A vertex format that contains vertex position.
     * 
     * This vertex format has the following structure:
     *   - position :int3
     * 
     * @param range <b>[not-null]</b>  The fixed coordinate range.
     * 
     * @return <b>[not-null]</b>  The vertex format.
     */
    static Ptr<IVertexFormat> P3I(FixedRange* range);
    
    /*!
     * @brief  A vertex format that contains point sprite sizes.
     * 
     * Point sizes are read from Semantic::Radius.
     * 
     * This vertex format has the following structure:
     *   - pointSize :float
     * 
     * @return <b>[not-null]</b>  The vertex format.
     */
    static Ptr<IVertexFormat> S1F();
    
    /*!
     * @brief  A vertex format that contains point sprite sizes.
     * 
     * This vertex format has the following structure:
     *   - pointSize :float
     * 
     * @param semantic <b>[not-null]</b>  The semantic of the vertex data container that stores 
     * point sizes.
     * 
     * @return <b>[not-null]</b>  The vertex format.
     */
    static Ptr<IVertexFormat> S1F(Semantic* semantic);
    
    /*!
     * @brief  A vertex format that contains one texture coordinate set.
     * 
     * This vertex format has the following structure:
     *   - texcoord :float2
     * 
     * @param scaleX Scale factor for texture X-coordinate.
     * @param scaleY Scale factor for texture Y-coordinate.
     * 
     * @return <b>[not-null]</b>  The vertex format.
     */
    static Ptr<IVertexFormat> T2F(float32 scaleX, float32 scaleY);
    
    /*!
     * @brief  A vertex format that contains one texture coordinate set.
     * 
     * This vertex format has the following structure:
     *   - texcoord :float3
     * 
     * @param scaleX Scale factor for texture X-coordinate.
     * @param scaleY Scale factor for texture Y-coordinate.
     * @param scaleZ Scale factor for texture Z-coordinate.
     * 
     * @return <b>[not-null]</b>  The vertex format.
     */
    static Ptr<IVertexFormat> T3F(float32 scaleX, float32 scaleY, float32 scaleZ);
    
    /*!
     * @brief  A vertex format that contains twelve 8-bit detail channel values.
     * 
     * This vertex format has the following structure:
     *   - detail_0_to_2 :float
     *   - detail_3_to_5 :float
     *   - detail_6_to_8 :float
     *   - detail_9_to_11 :float
     * Each float value stores three detail channel values (see TODO:Not found Maths.Pack(int,int,
     * int)???Maths::Pack(int32,int32,int32,int32) and Maths::Unpack3 for detail on how to pack and 
     * unpack detail channel values to and from float values).
     * 
     * @return <b>[not-null]</b>  The vertex format.
     */
    static Ptr<IVertexFormat> X4F_12();
    
    /*!
     * @brief  A vertex format that contains sixteen 8-bit detail channel values.
     * 
     * This vertex format has the following structure:
     *   - detail_0_to_3 :float
     *   - detail_4_to_7 :float
     *   - detail_8_to_11 :float
     *   - detail_12_to_15 :float
     * Each float value stores four detail channel values (see Maths::Pack(int32,int32,int32,int32) 
     * and Maths::Unpack4 for detail on how to pack and unpack detail channel values to and from 
     * float values).
     * 
     * @return <b>[not-null]</b>  The vertex format.
     */
    static Ptr<IVertexFormat> X4F_16();
    
    virtual Ptr<IVertexFormat> Append(IVertexFormat* format);
    
    virtual void SetVertexData(IVertexDataCollection* vertexDataCollection) = 0;
    
    virtual bool UsesSemantic(Semantic* semantic) = 0;
    
    virtual void WriteVertex(int32 vertex, ByteBuffer* buffer) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Constructors
    // ---------------------------------------------------------------------------------------------
  protected:
    
    /*!
     * @brief  Creates a new instance of VertexFormat.
     * 
     * @param vertexSize <b>[>=0]</b>  Amount of data this vertex converter generates,in bytes.
     * @param mnemonic <b>[not-empty]</b>  The mnemonic of this vertex converter.
     */
    VertexFormat(int32 vertexSize, String mnemonic);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The mnemonic of this vertex converter.
     */
    String mnemonic;
    
    /*!
     * @brief  Amount of data this vertex converter generates,in bytes.
     */
    int32 vertexSize;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<VertexFormat> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xC043ACEF;
    
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
      if ((ptr = IVertexFormat::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } 

#endif
