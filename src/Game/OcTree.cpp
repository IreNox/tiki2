#include "Game/OcTree.h"
#include "Game/Utils.h"
#include "Core/LibraryManager.h"

namespace TikiEngine
{
	namespace AI
	{
		OcTree::OcTree(Engine* engine)
		{
			this->engine = engine;
		}

		OcTree::~OcTree()
		{
		}

		void OcTree::FindBox(TRI* tris, int triCount, IBoundingBox* BBox)
		{
			float extend = 0;
			
			for (int i = 0; i < triCount; i++)
			{
				TRI* Tri = &tris[i];
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
		
		int OcTree::BuildRootNode(TRI* tris, int triCount)
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
			Vector3 center =  (parentBox->GetMax() + parentBox->GetMin()) / 2;
			Vector3 boxSize =  parentBox->GetMax() - parentBox->GetMin();
			
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

		void OcTree::BuildTree(OctNode* node, int trisPerNode, TRI* tris, int triCount)
		{

		}


		int OcTree::Create(TRI* tris, int triCount, int trisPerNode)
		{

			
			if (!BuildRootNode(tris, triCount))
				return 0;

			BuildTree((OctNode*)OctNodeList.GetLast(), trisPerNode, tris, triCount);


			//OctNode** octTable;
			//int octCount;


			return 1;

		}



		void OcTree::DrawDebug()
		{
			//root.BBox->DrawDebug(Color::White);
		}

	}
}