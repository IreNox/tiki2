////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_DATASETS_DATASETBUILDER_1_1_RECT_SPARSE_H
#define CLODDY_API_DATASETS_DATASETBUILDER_1_1_RECT_SPARSE_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/DatasetBuilder.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Datafiles { class IDatafile; } } }
namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleFormats { class ISampleFormat; } } } }
namespace Cloddy { namespace API { namespace Util { namespace Progress { class IProgressMonitor; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Datasets { class DatasetBuilder; } } }
namespace Cloddy { namespace API { namespace Imaging { class PatchImage; } } }
namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::API::Datasets::DatasetBuilder_1_1_Rect_Sparse.

namespace Cloddy { namespace API { namespace Datasets
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Datafiles::IDatafile;
  using Cloddy::API::Heightmaps::SampleFormats::ISampleFormat;
  using Cloddy::API::Util::Progress::IProgressMonitor;
  
  // Use referenced classes.
  
  using Cloddy::API::Imaging::PatchImage;
  using CodeX::System::ByteBuffer;
  
  /*!
   * @brief  The DatasetBuilder_1_1_Rect_Sparse class builds a rectangular version 1.0 dataset.
   */
  class DatasetBuilder_1_1_Rect_Sparse : public DatasetBuilder
  {
    // Declare friend classes.
    
    friend class DatasetBuilder;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual void Prepare(IProgressMonitor* progressMonitor);
    
    virtual void Run(IProgressMonitor* argument);
    
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
     * @brief  The output dataset file.
     */
    Ptr<IDatafile> datasetFile;
    
    /*!
     * @brief  Optional sample format for metadata.
     */
    Ptr<ISampleFormat> format;
    
    /*!
     * @brief  The input patch images.
     */
    Array<Ptr<PatchImage> > images;
    
    /*!
     * @brief  Total number of Patches in a input patch images.
     * 
     * This value is initialized in #Prepare.
     */
    int32 patchCount;
    
    /*!
     * @brief  A dataset sample that represents void,ie. no data exists at the given coordinates.
     */
    Ptr<ByteBuffer> voidSample;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of DatasetBuilder_1_0_Rect.
     * 
     * @param images The input images for the dataset.
     * @param format Optional input sample format.
     * @param voidSample A dataset sample that represents void.
     * @param datasetFile The output dataset file.
     */
    DatasetBuilder_1_1_Rect_Sparse(Array<Ptr<PatchImage> > images, ISampleFormat* format, ByteBuffer* voidSample, IDatafile* datasetFile);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<DatasetBuilder_1_1_Rect_Sparse> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x62610BD6;
    
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
      if ((ptr = DatasetBuilder::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
