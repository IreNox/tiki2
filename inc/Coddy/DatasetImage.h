////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_IMAGING_DATASETIMAGE_H
#define CLODDY_API_IMAGING_DATASETIMAGE_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/PixelFormat.h"

// Include referenced classes.

#include "Cloddy/ImageBase.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Datasets { class IDataset; } } }
namespace Cloddy { namespace API { namespace Imaging { class IImage; } } }
namespace Cloddy { namespace API { namespace Imaging { class IImageReader; } } }
namespace Cloddy { namespace API { namespace Imaging { class IImageVisitor; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Imaging { class ImageInfo; } } }
namespace Cloddy { namespace Core { namespace IO { namespace Files { class Path; } } } }

// Declare class ::Cloddy::API::Imaging::DatasetImage.

namespace Cloddy { namespace API { namespace Imaging
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Datasets::IDataset;
  
  // Use referenced classes.
  
  using Cloddy::Core::IO::Files::Path;
  
  /*!
   * @brief  An Imaging Object Model node that reads the samples of a dataset as an image.
   */
  class DatasetImage : public ImageBase
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Index of the first channel to extract from the dataset.
     * 
     * @return Offset of first channel to extract.
     */
    int32 GetChannel();
    
    /*!
     * @brief  Index of the first channel to extract from the dataset.
     * 
     * @param value Offset of first channel to extract.
     */
    void SetChannel(int32 value);
    
    /*!
     * @brief  The cubemap face from which to extract.
     * 
     * The default value is Cubemap::FaceNegZ.
     * 
     * @return The cubemap face,see the constants of the Cubemap class.
     */
    int32 GetFace();
    
    /*!
     * @brief  The cubemap face from which to extract.
     * 
     * The default value is Cubemap::FaceNegZ.
     * 
     * @param value The cubemap face,see the constants of the Cubemap class.
     */
    void SetFace(int32 value);
    
    /*!
     * @brief  X-coordinate of top-left corner of rectangle to extract.
     * 
     * @return X-coordinate of top-left corner of rectangle,in dataset samples.
     */
    int32 GetFaceX();
    
    /*!
     * @brief  X-coordinate of top-left corner of rectangle to extract.
     * 
     * @param value X-coordinate of top-left corner of rectangle,in dataset samples.
     */
    void SetFaceX(int32 value);
    
    /*!
     * @brief  Y-coordinate of top-left corner of rectangle to extract.
     * 
     * @return Y-coordinate of top-left corner of rectangle,in dataset samples.
     */
    int32 GetFaceY();
    
    /*!
     * @brief  Y-coordinate of top-left corner of rectangle to extract.
     * 
     * @param value Y-coordinate of top-left corner of rectangle,in dataset samples.
     */
    void SetFaceY(int32 value);
    
    /*!
     * @brief  Height of rectangle to extract.
     * 
     * @return Height of the rectangle to extract,in dataset samples.
     */
    int32 GetHeight();
    
    /*!
     * @brief  Height of rectangle to extract.
     * 
     * @param value Height of the rectangle to extract,in dataset samples.
     */
    void SetHeight(int32 value);
    
    /*!
     * @brief  The dataset to use.
     * 
     * Either #GetInputDatasetPath or #GetInputDataset may be specified.If both are set,an error is 
     * generated.
     * 
     * @return The dataset.
     */
    Ptr<IDataset> GetInputDataset();
    
    /*!
     * @brief  The dataset to use.
     * 
     * Either #GetInputDatasetPath or #GetInputDataset may be specified.If both are set,an error is 
     * generated.
     * 
     * @param value The dataset.
     */
    void SetInputDataset(IDataset* value);
    
    /*!
     * @brief  Path to the dataset file.
     * 
     * Either #GetInputDatasetPath or #GetInputDataset may be specified.If both are set,an error is 
     * generated.
     * 
     * @return Path to the dataset file.
     */
    Ptr<Path> GetInputDatasetPath();
    
    /*!
     * @brief  Path to the dataset file.
     * 
     * Either #GetInputDatasetPath or #GetInputDataset may be specified.If both are set,an error is 
     * generated.
     * 
     * @param value Path to the dataset file.
     */
    void SetInputDatasetPath(Path* value);
    
    /*!
     * @brief  The pixel format of the image to extract.
     * 
     * @return The pixel format of the extracted image.
     */
    PixelFormat GetPixelFormat();
    
    /*!
     * @brief  The pixel format of the image to extract.
     * 
     * @param value The pixel format of the extracted image.
     */
    void SetPixelFormat(PixelFormat value);
    
    /*!
     * @brief  The dataset sample stride.
     * 
     * Stride values greater than \c 1  can be used to extract images at a lower resolution.
     * 
     * The default value is \c 1 .
     * 
     * @return The dataset sample stride.
     */
    int32 GetStride();
    
    /*!
     * @brief  The dataset sample stride.
     * 
     * Stride values greater than \c 1  can be used to extract images at a lower resolution.
     * 
     * The default value is \c 1 .
     * 
     * @param value The dataset sample stride.
     */
    void SetStride(int32 value);
    
    /*!
     * @brief  Width of rectangle to extract.
     * 
     * @return Width of the rectangle to extract,in dataset samples.
     */
    int32 GetWidth();
    
    /*!
     * @brief  Width of rectangle to extract.
     * 
     * @param value Width of the rectangle to extract,in dataset samples.
     */
    void SetWidth(int32 value);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of DatasetImage.
     */
    DatasetImage();
    
    /*!
     * @brief  Creates a new instance of DatasetImage.
     * 
     * @param inputDatasetPath Path to the dataset file.
     * @param channel Offset of first channel to extract.
     * @param face The cubemap face from which to extract (see constants in Cubemap).
     * @param faceX X-coordinate of top-left corner of rectangle to extract.
     * @param faceY Y-coordinate of top-left corner of rectangle to extract.
     * @param width Width of rectangle to extract.
     * @param height Height of rectangle to extract.
     * @param stride The dataset sample stride.
     * @param pixelFormat The pixel format of the image to extract.
     */
    DatasetImage(Path* inputDatasetPath, int32 channel, int32 face, int32 faceX, int32 faceY, int32 width, int32 height, int32 stride, PixelFormat pixelFormat);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void Accept(IImageVisitor* visitor, Object* userData);
    
    virtual Ptr<IImage> Clip(int32 x, int32 y, int32 width, int32 height);
    
    virtual void Validate();
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
  protected:
    
    virtual Ptr<IImageReader> DoReadImage();
    
    virtual Ptr<ImageInfo> DoReadImageInfo();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Index of the first channel to extract from the dataset.
     */
    int32 channel;
    
    /*!
     * @brief  The cubemap face from which to extract.
     */
    int32 face;
    
    /*!
     * @brief  X-coordinate of top-left corner of rectangle to extract.
     */
    int32 faceX;
    
    /*!
     * @brief  Y-coordinate of top-left corner of rectangle to extract.
     */
    int32 faceY;
    
    /*!
     * @brief  Height of rectangle to extract.
     */
    int32 height;
    
    /*!
     * @brief  The dataset to use.
     */
    Ptr<IDataset> inputDataset;
    
    /*!
     * @brief  Path to the dataset file.
     */
    Ptr<Path> inputDatasetPath;
    
    /*!
     * @brief  The pixel format of the image to extract.
     */
    PixelFormat pixelFormat;
    
    /*!
     * @brief  The dataset sample stride.
     */
    int32 stride;
    
    /*!
     * @brief  Width of rectangle to extract.
     */
    int32 width;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<DatasetImage> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xE4CB5F1B;
    
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
      if ((ptr = ImageBase::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
