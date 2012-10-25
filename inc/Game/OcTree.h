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

			OctNode() {}
			~OctNode() { SafeRelease(&BBox); }
		};


		class OcTree
		{
		protected:
			// Given a list of triangles, finds a cube centered at the origin which fully encloses all points
			void FindBox(TRI* tris, int triCount, IBoundingBox* BBox);

			// Build the first node in the tree which encloses all the triangles
			int BuildRootNode(TRI* tris, int triCount);

			// TODO:
			// After building the root node, this function recursively subdivides the tree into octants.  
			// Each octants gets a new bounding box and all the polygons in the parent are tested to see
			// which lie within the new box.  Stops once each node contains no more than trisPerNode
			void BuildTree(OctNode* node, int trisPerNode, TRI* tris, int triCount);

			// Given a parent box, finds a partitioned child box based on the index i.
			// i refers to the octant of the new box 0-7
			void GetBox(IBoundingBox* parentBox, IBoundingBox* newBox, int i);

		public:
			OcTree(Engine* engine);
			~OcTree();

			// Tris - Array of triangles to construct Octree with
			// TriCount - Number of Triangles in the Tris array
			// TrisPerNode - Max number of triangles in each octree node
			int Create(TRI* tris, int triCount, int trisPerNode);


			void DrawDebug();

		protected:
			VoidList OctNodeList;
			VoidList TriIdxList;
			Engine* engine;

			
			
		};


	}
}