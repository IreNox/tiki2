////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_IO_FILES_PATHFORMAT_H
#define CLODDY_CORE_IO_FILES_PATHFORMAT_H

#include "CodeX/System_Native.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Collections { template<class> class ISetConst; } } }

// Declare class ::Cloddy::Core::IO::Files::PathFormat.

namespace Cloddy { namespace Core { namespace IO { namespace Files
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::Collections::ISetConst;
  
  /*!
   * @brief  Describes the path format of a platform.
   */
  class PathFormat : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The path format on Linux platforms.
     */
    static const StaticPtr<PathFormat> Linux;
    
    /*!
     * @brief  THe path format on Macintosh platforms.
     */
    static const StaticPtr<PathFormat> Macintosh;
    
    static Ptr<PathFormat> GetPlatform();
    
    /*!
     * @brief  The path format on Windows platforms.
     */
    static const StaticPtr<PathFormat> Windows;
    
    /*!
     * @brief  The token that refers to the current directory.
     */
    String CurrentDirectory;
    
    /*!
     * @brief  The set of invalid directory and file name characters.
     */
    Ptr<ISetConst<Prm<wchar_t> > > InvalidCharacters;
    
    /*!
     * @brief  The token that refers to the parent directory.
     */
    String ParentDirectory;
    
    /*!
     * @brief  The separator for directory and files.
     */
    String PathSeparator;
    
    /*!
     * @brief  The separator for root selectors.
     */
    String RootSeparator;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of PathFormat.
     * 
     * @param rootSeparator The separator for root selectors or \c null .
     * @param pathSeparator <b>[not-empty]</b>  The separator for directory and files.
     * @param currentDirectory <b>[not-empty]</b>  The token that refers to the current directory.
     * @param parentDirectory <b>[not-empty]</b>  The token that refers to the parent directory.
     * @param invalidCharacters <b>[not-empty]</b>  The set of invalid directory and file name 
     * characters.
     */
    PathFormat(String rootSeparator, String pathSeparator, String currentDirectory, String parentDirectory, String invalidCharacters);
    
    // ---------------------------------------------------------------------------------------------
    // Static Initializer Functions
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief Static initializer function for field Linux.
     */
    static Object* StaticInitializer_Linux();
    
    /*!
     * @brief Static initializer function for field Macintosh.
     */
    static Object* StaticInitializer_Macintosh();
    
    /*!
     * @brief Static initializer function for field Windows.
     */
    static Object* StaticInitializer_Windows();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<PathFormat> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xCD8314F2;
    
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
  
} } } } 

#endif
