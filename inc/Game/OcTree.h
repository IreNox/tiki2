#pragma once

#include "Core/IBoundingBox.h"
#include "Core/TypeGlobals.h"
#include "Game/VoidList.h"
#include "Game/TriBox.h"
#include "Game/BoxSide.h"


namespace TikiEngine
{
	namespace AI
	{
		using namespace TikiEngine::Resources;

		const int NUM_CHILDREN =	8;
		const int NUM_NEIGHBORS	=   6;
		const int NULL_NODE =	   -1;

		struct OctNode
		{
			IBoundingBox* BBox;
			int ChildIdx[NUM_CHILDREN];
			int NeighborIdx[NUM_NEIGHBORS];

			int TriIdxStart;
			int TriIdxCount;

			// todo!
			void Dispose() { SafeRelease(&BBox); }
		};


		class OcTree
		{
		protected:
			//  Given a cube side index, return an index to the side opposite it
			int GetOppositeIdx(int idx);

			// Given the side of a cube face, search through the Octree to find the best fit neighbor
			void FindNeighbor(OctNode** octTable, OctNode* node, BoxSide* side, 
							  int idx, int* found, float* foundSize);

			// Given a list of triangles, finds a cube centered at the origin which fully encloses all points
			void FindBox(const TRI* tris, int triCount, IBoundingBox* BBox);

			// Build the first node in the tree which encloses all the triangles
			int BuildRootNode(const TRI* tris, int triCount);

			// After building the root node, this function recursively subdivides the tree into octants.  
			// Each octants gets a new bounding box and all the polygons in the parent are tested to see
			// which lie within the new box.  Stops once each node contains no more than trisPerNode
			void BuildTree(OctNode* node, int trisPerNode, const TRI* tris, int triCount);

			// Given a parent box, finds a partitioned child box based on the index i.
			// i refers to the octant of the new box 0-7
			void GetBox(IBoundingBox* parentBox, IBoundingBox* newBox, int i);


		public:
			OcTree();
			~OcTree();

			void Dispose();

			// Tris - Array of triangles to construct Octree with
			// TriCount - Number of Triangles in the Tris array
			// TrisPerNode - Max number of triangles in each octree node
			int Create(Engine* engine, const TRI* tris, int triCount, int trisPerNode);

			// OctTable - Gets a pointer to a linear block of oct node data
			// OctCount - Number of node's in OctTable
			// TriIdxTable - Gets a pointer to a linear block of all triangle indices
			// TriIdxCount - Number of indices in TriIdxTable
			void GetTables(OctNode** octTable, int* octCount,
						   unsigned int** triIdxTable, int* triIdxCount);


			// Receive the octIndex from position
			int PositionToIndex(const Vector3& pos);

			// get all intersecting triangles from the box positioned within pos
			List<TRI>* GetTrianglesAt(const Vector3& pos);

			void DrawDebug();

		protected:
			VoidList OctNodeList;
			VoidList TriIdxList;
			Engine* engine;

			OctNode* octreeTable;
			int octreeCount;
			unsigned int* triangleIdxTable;
			int triangleIdxCount;
			int drawIdx;
			bool showTree;
			const TRI* triangles; // = TotalCells

			List<TRI> foundTriangles;

			
		};


	}
}