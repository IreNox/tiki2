////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_IMAGING_WRITERS_BMPWRITER_H
#define CLODDY_API_IMAGING_WRITERS_BMPWRITER_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IImageWriter.h"

// Include referenced classes.

#include "CodeX/Disposable.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Imaging { class IImage; } } }
namespace Cloddy { namespace API { namespace Imaging { class IImageReader; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace IO { namespace Files { class Path; } } } }

// Declare class ::Cloddy::API::Imaging::Writers::BmpWriter.

namespace Cloddy { namespace API { namespace Imaging { namespace Writers
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Imaging::IImage;
  using Cloddy::API::Imaging::IImageReader;
  using Cloddy::API::Imaging::IImageWriter;
  
  // Use referenced classes.
  
  using Cloddy::Core::IO::Files::Path;
  using CodeX::System::Disposable;
  
  /*!
   * @brief  Utility class for writing 24-bit truecolor BMP images.
   */
  class BmpWriter : public Disposable, public virtual IImageWriter
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The output file path.
     * 
     * @return <b>[not-null]</b>  The output file path.
     */
    Ptr<Path> GetOutputFilePath();
    
    /*!
     * @brief  The output file path.
     * 
     * @param value <b>[not-null]</b>  The output file path.
     */
    void SetOutputFilePath(Path* value);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of BmpWriter.
     */
    BmpWriter();
    
    /*!
     * @brief  Creates a new instance of BmpWriter.
     * 
     * @param outputFilePath <b>[not-null]</b>  The output file path.
     */
    BmpWriter(Path* outputFilePath);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Writes a PixelFormat::PixelFormat_Truecolor24 BMP file.
     * 
     * @param filePath <b>[not-empty]</b>  Path to the BMP file to write.
     * @param image <b>[not-null]</b>  The IImage object.
     */
    static void WriteImage(String filePath, IImage* image);
    
    /*!
     * @brief  Writes a PixelFormat::PixelFormat_Truecolor24 BMP file.
     * 
     * @param filePath <b>[not-empty]</b>  Path to the BMP file to write.
     * @param imageReader <b>[not-null]</b>  The IImageReader object.
     */
    static void WriteImage(String filePath, IImageReader* imageReader);
    
    /*!
     * @brief  Writes a PixelFormat::PixelFormat_Truecolor24 BMP file.
     * 
     * @param filePath <b>[not-null]</b>  Path to the BMP file to write.
     * @param image <b>[not-null]</b>  The IImage object.
     */
    static void WriteImage(Path* filePath, IImage* image);
    
    /*!
     * @brief  Writes a PixelFormat::PixelFormat_Truecolor24 BMP file.
     * 
     * @param filePath <b>[not-null]</b>  Path to the BMP file to write.
     * @param imageReader <b>[not-null]</b>  The IImageReader object.
     */
    static void WriteImage(Path* filePath, IImageReader* imageReader);
    
    virtual void WriteImage(IImageReader* imageReader);
    
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
     * @brief  The output file path.
     */
    Ptr<Path> outputFilePath;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Asserts that the #GetOutputFilePath property has been set.
     */
    void AssertHasOutputPath();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<BmpWriter> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x139F01A2;
    
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
      if ((ptr = IImageWriter::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } 

#endif
