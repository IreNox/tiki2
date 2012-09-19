////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_DATASETS_DATASETBUILDER_1_0_CUBE_H
#define CLODDY_API_DATASETS_DATASETBUILDER_1_0_CUBE_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/DatasetBuilder.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Datafiles { class IDatafile; } } }
namespace Cloddy { namespace API { namespace Datasets { class IDataset; } } }
namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleFormats { class ISampleFormat; } } } }
namespace Cloddy { namespace API { namespace Imaging { class IImage; } } }
namespace Cloddy { namespace API { namespace Util { namespace Progress { class IProgressMonitor; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Datasets { class DatasetBuilder; } } }

// Declare class ::Cloddy::API::Datasets::DatasetBuilder_1_0_Cube.

namespace Cloddy { namespace API { namespace Datasets
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Datafiles::IDatafile;
  using Cloddy::API::Heightmaps::SampleFormats::ISampleFormat;
  using Cloddy::API::Imaging::IImage;
  using Cloddy::API::Util::Progress::IProgressMonitor;
  
  /*!
   * @brief  The DatasetBuilder_1_0_Cube class builds a cubemap version 1.0 dataset.
   */
  class DatasetBuilder_1_0_Cube : public DatasetBuilder
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
     * @brief  The output dataset.
     */
    Ptr<IDataset> dataset;
    
    /*!
     * @brief  The input images per cubemap face.
     */
    Array<Ptr<IImage> > images;
    
    /*!
     * @brief  Size of the input images (always a power of two plus one).
     */
    int32 inputImageSize;
    
    /*!
     * @brief  The sample stride.
     */
    int32 stride;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of DatasetBuilder_1_0_Cube.
     * 
     * @param images The input images.
     * @param format Optional input sample format.
     * @param stride The sample stride.
     * @param datafile The output datafile.
     */
    DatasetBuilder_1_0_Cube(Array<Ptr<IImage> > images, ISampleFormat* format, int32 stride, IDatafile* datafile);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Processes the given cubemap face.
     * 
     * @param face The face to process,see constants defined in Cubemap.
     * @param progressMonitor The progress monitor to use.
     */
    void ProcessCubemapFace(int32 face, IProgressMonitor* progressMonitor);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<DatasetBuilder_1_0_Cube> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x5E35A109;
    
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
