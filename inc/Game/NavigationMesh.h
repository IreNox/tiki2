#pragma once

#include <vector>

#include "Game/NavigationCell.h"
#include "Game/NavigationHeap.h"
#include "Core/DrawArgs.h"
#include "Core/IModel.h"
#include "Core/LibraryManager.h"
#include "Game/OcTree.h"

namespace TikiEngine
{
	namespace AI
	{
		using namespace TikiEngine::Resources;

		// forward declaration required
		class NavigationPath;

		/* A NavigationMesh is a collecion of NavigationCells used to control object movement while
		*  also providing path finding line-of-sight testing. It serves as a parent to all the
		*  Agent objects which exist upon it.
		*/
		class NavigationMesh
		{
		public:



			typedef	std::vector<NavigationCell*> CELL_ARRAY;

			NavigationMesh(Engine* engine);
			~NavigationMesh();

			// Delete all cells associated with this mesh 
			void Clear();
			// Add a new cell, defined by the three vertices in clockwise order, to this mesh 
			void AddCell(const Vector3& pointA, const Vector3& pointB, const Vector3& pointC);
			void LinkCells();

			void Load(const wstring& name, const Matrix& transform);

			// Force a point to be inside the cell  
			Vector3 SnapPointToCell(NavigationCell* Cell, const Vector3& Point);
			
			// Force a point to be inside the nearest cell on the mesh  
			Vector3 SnapPointToMesh(NavigationCell** CellOut, const Vector3& Point);
			
			// TODO:: Speed this up with cellspace! Find the closest cell on the mesh to the given point  
			NavigationCell* FindClosestCell(const Vector3& Point) const;

			// Test to see if two points on the mesh can view each other  
			bool LineOfSightTest(NavigationCell* StartCell, const Vector3& StartPos, NavigationCell* EndCell, const Vector3& EndPos);

			bool BuildNavigationPath(NavigationPath& NavPath, NavigationCell* StartCell, 
									 const Vector3& StartPos, NavigationCell* EndCell, const Vector3& EndPos);

			// Resolve a movement vector on the mesh  
			void ResolveMotionOnMesh(const Vector3& StartPos, NavigationCell* StartCell, Vector3& EndPos, NavigationCell** EndCell);

			void Draw(const DrawArgs& args);

			int TotalCells() const;
			NavigationCell* Cell(int index);

		private:
			// not implemented
			NavigationMesh( const NavigationMesh& Src);
			NavigationMesh& operator=( const NavigationMesh& Src);

			CELL_ARRAY cellArray;	// the cells that make up this mesh
			int pathSession;
			NavigationHeap navHeap;

			IModel* navModel;
			Engine* engine;

			OcTree* tree;
			List<TRI> tris; // = TotalCells

		};


	}
}