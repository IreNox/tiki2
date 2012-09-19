////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_DATASETS_DATASETREGION_H
#define CLODDY_API_DATASETS_DATASETREGION_H

#include "CodeX/System.h"

// Include referenced structures.

#include "Cloddy/MapField.h"

// Include referenced classes.

#include "CodeX/Disposable.h"

// Forward declare referenced classes.

namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::API::Datasets::DatasetRegion.

namespace Cloddy { namespace API { namespace Datasets
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced structures.
  
  using Cloddy::API::Util::MapField;
  
  // Use referenced classes.
  
  using CodeX::System::ByteBuffer;
  using CodeX::System::Disposable;
  
  /*!
   * @brief  This class represents the samples of a rectangular region of a dataset.
   */
  class DatasetRegion : public Disposable
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The number of dataset channels.
     * 
     * @return <b>[>0]</b>  The dataset channel count.
     */
    int32 GetChannels();
    
    /*!
     * @brief  The map field that describes the extends of the dataset region.
     */
    MapField Field;
    
    /*!
     * @brief  The height of this region,in dataset samples.
     * 
     * @return <b>[>0]</b>  The height the region,in heightmap samples.
     */
    int32 GetHeight();
    
    /*!
     * @brief  The samples of this dataset region.
     * 
     * The ByteBuffer::GetPosition of the buffer will be set to \c 0  and the ByteBuffer::GetLimit 
     * to its capacity before it is returned.
     * 
     * @return <b>[not-null]</b>  The sample buffer.
     */
    Ptr<ByteBuffer> GetSamples();
    
    /*!
     * @brief  The width of this region,in dataset samples.
     * 
     * @return <b>[>0]</b>  The width of the region,in heightmap samples.
     */
    int32 GetWidth();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of DatasetRegion.
     * 
     * @param width <b>[>0]</b>  Width of the dataset region,in dataset samples.
     * @param height <b>[>0]</b>  Height of the dataset region,in dataset samples.
     * @param channels <b>[>0]</b>  The dataset channel count.
     * 
     * @return <b>[not-null]</b>  The created DatasetRegion object.
     */
    static Ptr<DatasetRegion> Create(int32 width, int32 height, int32 channels);
    
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
     * @brief  The number of dataset channels.
     */
    int32 channels;
    
    /*!
     * @brief  The height of this region,in dataset samples.
     */
    int32 height;
    
    /*!
     * @brief  The samples of this dataset region.
     */
    Ptr<ByteBuffer> samples;
    
    /*!
     * @brief  The width of this region,in dataset samples.
     */
    int32 width;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of DatasetRegion.
     * 
     * @param width Dataset region width.
     * @param height Dataset region height.
     * @param channels Dataset region channel count.
     * @param buffer The byte buffer.
     */
    DatasetRegion(int32 width, int32 height, int32 channels, ByteBuffer* buffer);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<DatasetRegion> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x958E08B3;
    
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
      return (void*) 0;
    }
  };
  
} } } 

#endif
