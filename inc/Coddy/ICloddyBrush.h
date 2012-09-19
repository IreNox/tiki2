////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_EXTENSIONS_ICLODDYBRUSH_H
#define CLODDY_EXTENSIONS_ICLODDYBRUSH_H

// Definitions

#define CODEX_PREFIX
#define CODEX_SYSTEM_PREFIX
#define CLODDY_CORE_PREFIX
#define CLODDY_KERNEL_PREFIX
#define CLODDY_API_PREFIX
#define CLODDY_GRAPHICS_PREFIX

// Include referenced classes.

#include <CodeX/CodeX.h>
#include <CodeX/System.h>
#include <Cloddy/Cloddy_Core.h>
#include <Cloddy/Cloddy_API.h>

// Declare interface ::Cloddy::Extensions::ICloddyBrush.

namespace Cloddy { namespace Extensions { 

  /*!
  * @brief  Base interface for classes that represent brushes.
  */
  class NO_VTABLE ICloddyBrush : public virtual codex_IDisposable
  {
    // ---------------------------------------------------------------------------------------------
    // Public
    // ---------------------------------------------------------------------------------------------

  public:

    /*!
     * @brief Gets the mask.
     *
     * @returns The mask.
     */
    virtual codex_Ptr<cloddy_IBrushMask> GetMask() = 0;

    /*!
     * @brief Sets a mask.
     *
     * @param A mask.
     */
    virtual void SetMask(cloddy_IBrushMask* mask) = 0;

    /*!
     * @brief Gets the internal brush.
     *
     * @returns The internal brush.
     */
    virtual codex_Ptr<cloddy_IBrush> GetBrush() = 0;

    /*!
     * @brief Gets the width.
     *
     * @returns The width.
     */
    virtual codex_int32 GetWidth() = 0;

    /*!
     * @brief Gets the height.
     *
     * @returns The height.
     */
    virtual codex_int32 GetHeight() = 0;

    /*!
     * @brief The unique ID of this type.
     */
    static const codex_int32 TypeId = 0x237CDFA8;

    // ---------------------------------------------------------------------------------------------
    // Protected
    // ---------------------------------------------------------------------------------------------

  protected:
    
    /*!
     * @brief Tries to cast this object to the given type.
     *
     * @param typeId The ID of the type to cast to.
     *
     * @return The result of the type cast. Can be \c 0 if the requested cast is an invalid 
     *         downcast.
     */
    virtual void* TryCast(int id)
    {
      void* ptr;

      if (id == TypeId) return (void*) this;
      if ((ptr = codex_IDisposable::TryCast(id)) != 0) return ptr;

      return Object::TryCast(id);
    }
  };

} }

#endif