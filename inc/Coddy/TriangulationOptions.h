////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_TRIANGULATIONOPTIONS_H
#define CLODDY_API_TRIANGULATIONOPTIONS_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/Orientation.h"
#include "Cloddy/TriangleStitching.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Kernel { class ITriangulationCallback; } }

// Declare class ::Cloddy::API::TriangulationOptions.

namespace Cloddy { namespace API
{
  // Use referenced namespaces.
  
  using namespace Cloddy::Kernel;
  using namespace CodeX;
  
  /*!
   * @brief  Holds the triangulation options of a Terrain object.
   */
  class TriangulationOptions : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The ITriangulationCallback object to use when triangulation a terrain.
     * 
     * The default value is \c null .
     * 
     * @return The callback to use.
     * 
     * @see Terrain::Triangulate
     */
    Ptr<ITriangulationCallback> GetCallback();
    
    /*!
     * @brief  The ITriangulationCallback object to use when triangulation a terrain.
     * 
     * The default value is \c null .
     * 
     * @param value The callback to use.
     * 
     * @see Terrain::Triangulate
     */
    void SetCallback(ITriangulationCallback* value);
    
    /*!
     * @brief  Fill the last triangle strip chunk to maximum length?
     * 
     * The default value is \c false .
     * 
     * @return \c true  to fill the last chunk,\c false  to leave it as it is.
     */
    bool GetFillLast();
    
    /*!
     * @brief  Fill the last triangle strip chunk to maximum length?
     * 
     * The default value is \c false .
     * 
     * @param value \c true  to fill the last chunk,\c false  to leave it as it is.
     */
    void SetFillLast(bool value);
    
    /*!
     * @brief  The triangle stitching mode to use when triangulation a terrain.
     * 
     * The default value is TriangleStitching::TriangleStitching_Chunked.
     * 
     * @return The stitching mode to use.
     * 
     * @see Terrain::Triangulate
     */
    TriangleStitching GetStitching();
    
    /*!
     * @brief  The triangle stitching mode to use when triangulation a terrain.
     * 
     * The default value is TriangleStitching::TriangleStitching_Chunked.
     * 
     * @param value The stitching mode to use.
     * 
     * @see Terrain::Triangulate
     */
    void SetStitching(TriangleStitching value);
    
    /*!
     * @brief  The triangle orientation to use when triangulation a terrain.
     * 
     * The default value is Orientation::Orientation_CounterClockwise 
     * 
     * @return The triangle orientation.
     */
    Orientation GetTriangleOrientation();
    
    /*!
     * @brief  The triangle orientation to use when triangulation a terrain.
     * 
     * The default value is Orientation::Orientation_CounterClockwise 
     * 
     * @param value The triangle orientation.
     */
    void SetTriangleOrientation(Orientation value);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of TriangulationOptions.
     */
    TriangulationOptions();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The ITriangulationCallback object to use when triangulation a terrain.
     */
    Ptr<ITriangulationCallback> callback;
    
    /*!
     * @brief  Fill the last triangle strip chunk to maximum length?
     */
    bool fillLast;
    
    /*!
     * @brief  The triangle stitching mode to use when triangulation a terrain.
     */
    TriangleStitching stitching;
    
    /*!
     * @brief  The triangle orientation to use when triangulation a terrain.
     */
    Orientation triangleOrientation;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<TriangulationOptions> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xEDD6FF9D;
    
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
  
} } 

#endif
