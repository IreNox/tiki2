#include "Game/OcTree.h"
#include "Game/Utils.h"
#include "Core/LibraryManager.h"
#include "Core/IGraphics.h"

namespace TikiEngine
{
	namespace AI
	{
		OcTree::OcTree()
			: foundTriangles()
		{
			//this->octreeTable = 0;
			//this->triangleIdxTable = 0;
			this->drawIdx = 0;

#if _DEBUG
			this->showTree = false;
#endif
		}

		OcTree::~OcTree()
		{
			if (octreeTable != 0)
			for (int i = 0; i < octreeCount; i++)
				octreeTable[i].Dispose();

			SafeDelete(&octreeTable);
			SafeDelete(&triangleIdxTable);

			foundTriangles.Clear();
		}

		void OcTree::Dispose()
		{
			//if (octreeTable != 0)
			//for (int i = 0; i < octreeCount; i++)
			//	octreeTable[i].Dispose();
			//	SafeRelease(&octreeTable[i].BBox);

			//SafeDelete(&octreeTable);
			//SafeDelete(&triangleIdxTable);


			//foundTriangles->Clear();
		}


		int OcTree::GetOppositeIdx(int idx)
		{
			if (idx % 2 == 0)
				return (idx + 1);
			else
				return (idx - 1);
		}


		void OcTree::FindNeighbor(OctNode** octTable, OctNode* node, BoxSide* side, int idx, int* found, float* foundSize)
		{
			if (node && node->ChildIdx[0] != NULL_NODE)
			{
				// loop all childs
				for (int i = 0; i < NUM_CHILDREN; i++)
				{
					// get the current one
					OctNode* child = octTable[node->ChildIdx[i]];

					// Find the side of the test box facing the opposite direction of the current side
					BoxSide testSide;
					int testIdx = GetOppositeIdx(idx);
					testSide.SetFromBox(child->BBox, testIdx);
					
					//  If it's the same size or greater, test to see if planes are neighbors
					if (side->GetSize() <= testSide.GetSize())
					{
						if (side->Neighbors(testSide))
							if (testSide.GetSize() < *foundSize)
							{
								*found = node->ChildIdx[i];
								*foundSize = testSide.GetSize();
							} // if

					// keep searching if we haven't found a prefect fit
					if (*foundSize != side->GetSize())
						FindNeighbor(octTable, child, side, idx, found, foundSize);


					} // if

				} // for (i)

			} // if
		}



		void OcTree::FindBox(const TRI* tris, int triCount, IBoundingBox* BBox)
		{
			float extend = 0;
			
			for (int i = 0; i < triCount; i++)
			{
				const TRI* Tri = &tris[i];
				for(int j = 0; j < 3; j++)
				{
					if (ABS(Tri->Pt[j].X) > extend)
						extend = ABS(Tri->Pt[j].X);

					if (ABS(Tri->Pt[j].Y) > extend)
						extend = ABS(Tri->Pt[j].Y);

					if (ABS(Tri->Pt[j].Z) > extend)
						extend = ABS(Tri->Pt[j].Z);
				}
			}

			BBox->Set(Vector3(-extend), Vector3(extend));
		}
		
		int OcTree::BuildRootNode(const TRI* tris, int triCount)
		{
			OctNode root;
			int i;

			// start by construction a root node that contains all triangles
			root.BBox = engine->librarys->CreateResource<IBoundingBox>();
			FindBox(tris, triCount, root.BBox);
			
			for(i = 0; i < NUM_CHILDREN; i++)
				root.ChildIdx[i] = NULL_NODE;

			for(i = 0; i < NUM_NEIGHBORS; i++)
				root.NeighborIdx[i] = NULL_NODE;

			root.TriIdxStart = TriIdxList.GetCount();
			root.TriIdxCount = triCount;


			// Fill the start of the TriIdxList with pointers to all triangles
			for (i = 0; i < triCount; i++)
			{
				unsigned int index = (unsigned int) i;
				TriIdxList.Append(&index, sizeof(unsigned int));
			}

			// Add the root node to the table
			OctNodeList.Append(&root, sizeof(OctNode));

			return 1;
		}


		void OcTree::GetBox(IBoundingBox* parentBox, IBoundingBox* newBox, int i)
		{
			Vector3 center = (parentBox->GetMax() + parentBox->GetMin()) / 2;
			Vector3 boxSize = parentBox->GetMax() - parentBox->GetMin();
			
			Vector3 newCenter;
			if(i % 2 == 0)
				newCenter.X = (center.X - (boxSize.X / 4));
			else
				newCenter.X = (center.X + (boxSize.X / 4));

			if(i < 4)
				newCenter.Y = (center.Y - (boxSize.Y / 4));
			else
				newCenter.Y = (center.Y + (boxSize.Y / 4));

			if(i== 2 || i== 3 || i== 6 || i== 7)
				newCenter.Z = (center.Z - (boxSize.Z / 4));
			else
				newCenter.Z = (center.Z + (boxSize.Z / 4));


			newBox->Set(newCenter - boxSize / 4,
						newCenter + boxSize / 4);
		}

		void OcTree::BuildTree(OctNode* node, int trisPerNode, const TRI* tris, int triCount)
		{
			//	if the node has more than threshold number of triangles, create children
			if (node->TriIdxCount > trisPerNode)
			{

				for (int i = 0; i < NUM_CHILDREN; i++)
				{
					OctNode newNode;

					// Set this node's child pointer.
					node->ChildIdx[i] = OctNodeList.GetCount();

					// partition the new box for the child.
					newNode.BBox = engine->librarys->CreateResource<IBoundingBox>();
					GetBox(node->BBox, newNode.BBox, i);

					//	Initialize fields
					for (int j = 0; j < NUM_CHILDREN; j++)
						newNode.ChildIdx[i] = NULL_NODE;

					for (int j = 0; j < NUM_NEIGHBORS; j++)
						newNode.NeighborIdx[i] = NULL_NODE;

					//	See which of the parent's triangles lie within the new node.
					newNode.TriIdxCount = 0;
					newNode.TriIdxStart = TriIdxList.GetCount();
					TriIdxList.PositionAt(node->TriIdxStart);

					for (int j = 0; j < node->TriIdxCount; j++)
					{
						unsigned int* TriIdx = (unsigned int*)TriIdxList.GetCurrent();
						const TRI* Tri = &tris[*TriIdx];

						if (TriBoxIntersect(newNode.BBox, *Tri) == INSIDE)
						{
							TriIdxList.Append(TriIdx, sizeof(unsigned int));
							newNode.TriIdxCount++;
						} // if 

						TriIdxList.Advance();
					} // for (j)

					// Add the new node ad recurse on its children
					OctNodeList.Append(&newNode, sizeof(OctNode));
					BuildTree((OctNode*)OctNodeList.GetLast(), trisPerNode, tris, triCount);

				} // for (i)
			} // if 

		}


		int OcTree::Create(Engine* engine, const TRI* tris, int triCount, int trisPerNode)
		{
			this->engine = engine;

			// Build our root node
			if (!BuildRootNode(tris, triCount))
				return 0;

			// Build tree recursively
			BuildTree((OctNode*)OctNodeList.GetLast(), trisPerNode, tris, triCount);

			// Get the table and find neighbors
			int octCount;
			OctNode** octTable = (OctNode**)OctNodeList.BuildTable(&octCount);

			for (int i = 0; i < octCount; i++)
			{
				OctNode* node = octTable[i];

				for (int j = 0; j < NUM_NEIGHBORS; j++)
				{
					int found = NULL_NODE;
					float foundSize = (float)(unsigned int)(1 << 31); // Max val

					BoxSide side;
					side.SetFromBox(node->BBox, j);

					FindNeighbor(octTable, octTable[0], &side, j, &found, &foundSize);

					node->NeighborIdx[j] = found;

				} // for (j)
			} // for (i)

		
			free(octTable);

			this->triangles = tris;

			// Get the final tables
			GetTables(&octreeTable, &octreeCount, &triangleIdxTable, &triangleIdxCount);



			return 1;
		}

		void OcTree::GetTables(OctNode** octTable, int* octCount, 
							   unsigned int** triIdxTable, int* triIdxCount)
		{
			*octTable = (OctNode*)OctNodeList.BuildLinearTable(octCount);
			*triIdxTable = (unsigned int*)TriIdxList.BuildLinearTable(triIdxCount);
		}

		int OcTree::PositionToIndex(const Vector3& pos)
		{
			int ret; 
			for (int i = 1; i < octreeCount - 1; i++)
				if (octreeTable[i].BBox->Contains(pos))
					ret = i;

			return ret;
		}

		//Vector3
		List<TRI>* OcTree::GetTrianglesAt(const Vector3& pos)
		{
			foundTriangles.Clear();

			int idx = PositionToIndex(pos);
			drawIdx = idx;

			int start = octreeTable[idx].TriIdxStart;
			int end = octreeTable[idx].TriIdxStart + octreeTable[idx].TriIdxCount;
			for (int i = start; i < end; i++)
			{
				unsigned int triIdx = triangleIdxTable[i];
				foundTriangles.Add(triangles[triIdx]);
			}

			return &foundTriangles;
		}


#if _DEBUG
		void OcTree::DrawDebug()
		{
			// draw the whole tree
			if (showTree)
			{
				for (int i = 0; i < octreeCount; i++)
					octreeTable[i].BBox->DrawDebug(Color::White);
			}
			// Draw one node with its neighbors and tris
			else
			{
				// Draw Neighbors
				for (int i = 0; i < NUM_NEIGHBORS; i++)
				{
					if (octreeTable[drawIdx].NeighborIdx[i] != NULL_NODE)
						octreeTable[octreeTable[drawIdx].NeighborIdx[i]].BBox->DrawDebug(Color::Red);
				}

				// Draw current box
				octreeTable[drawIdx].BBox->DrawDebug(Color::White);

			}

			// draw found triangles via GetTrianglesAt
			for(unsigned int i = 0; i < foundTriangles.Count(); i++)
			{
				TRI t = foundTriangles.Get(i);

				for (int j = 0; j < 3; j++)
				{
					Vector3 start = t.Pt[j];
					Vector3 end = t.Pt[(j + 1) % 3];
					engine->graphics->DrawLine(start, end, Color::Blue);
				}
			}

		}
#endif
	}
}