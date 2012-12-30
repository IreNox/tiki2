#include "Game/NavigationMesh.h"

#include "Game/NavigationPath.h"
#include "Core/Color.h"
#include "Core/List.h"
#include "Core/IGraphics.h"
#include "Core/IcontentManager.h"
#include "Core/Mesh.h"

namespace TikiEngine
{
	namespace AI
	{
		// ctor / dtor
		NavigationMesh::NavigationMesh(Engine* engine)
			: pathSession(0)
		{
			this->engine = engine;
			cellArray.clear();
			tree = 0;
		}

		NavigationMesh::~NavigationMesh()
		{

			Clear();

			
			//SafeRelease(&navModel);

			SafeDelete(&tree);
		}

		void NavigationMesh::Clear()
		{
			CELL_ARRAY::iterator CellIter = cellArray.begin();
			for(;CellIter != cellArray.end(); ++CellIter)
			{
				NavigationCell* Cell = *CellIter;
				delete Cell;
			}

			cellArray.clear();
		}

		void NavigationMesh::AddCell(const Vector3& pointA, const Vector3& pointB, const Vector3& pointC)
		{
			NavigationCell* NewCell = new NavigationCell;
			NewCell->Initialize(pointA, pointB, pointC);
			cellArray.push_back(NewCell);
		}

		void NavigationMesh::LinkCells()  
		{  
			// Link all cells
			CELL_ARRAY::iterator IterA = cellArray.begin();  

			while (IterA != cellArray.end())  
			{  
				NavigationCell* pCellA = *IterA;  
				CELL_ARRAY::iterator IterB = cellArray.begin();  

				while (IterB != cellArray.end())  
				{  
					NavigationCell* pCellB = *IterB;  

					if (IterA != IterB)  
					{  
						if (!pCellA->Link(NavigationCell::SIDE_AB) && pCellB->RequestLink(pCellA->Vertex(0), pCellA->Vertex(1), pCellA))  
						{  
							pCellA->SetLink(NavigationCell::SIDE_AB, pCellB);  
						}  
						else if (!pCellA->Link(NavigationCell::SIDE_BC) && pCellB->RequestLink(pCellA->Vertex(1), pCellA->Vertex(2), pCellA))  
						{  
							pCellA->SetLink(NavigationCell::SIDE_BC, pCellB);  
						}  
						else if (!pCellA->Link(NavigationCell::SIDE_CA) && pCellB->RequestLink(pCellA->Vertex(2), pCellA->Vertex(0), pCellA))  
						{  
							pCellA->SetLink(NavigationCell::SIDE_CA, pCellB);  
						}  
					}  

					++IterB;  
				}  

				++IterA;  
			}  
		}  

		void NavigationMesh::Load(const wstring& name, const Matrix& transform)
		{
			Mesh* mesh = engine->content->LoadMesh(name);

			UInt32 indexCount;
			UInt32* indexData;
			mesh->GetIndexData(&indexData, &indexCount);

			UInt32 vertexLength;
			DefaultVertex* vertexData;
			mesh->GetVertexData((void**)&vertexData, &vertexLength);

			float minX = -3.4E+38f;
			float minZ = -3.4E+38f;
			float maxX = -3.4E+38f;
			float maxZ = -3.4E+38f;

			Clear();
			for(UInt32 i = 0; i < indexCount; i+=3)
			{
				Vector3 vertC = vertexData[indexData[i]].Position;
				Vector3 vertB = vertexData[indexData[i+1]].Position;
				Vector3 vertA = vertexData[indexData[i+2]].Position;
				
				vertA = Vector3::TransformCoordinate(vertA, transform);
				vertB = Vector3::TransformCoordinate(vertB, transform);
				vertC = Vector3::TransformCoordinate(vertC, transform);

				// compute level dimensions
				if (vertA.X < minX) minX = vertA.X;
				if (vertB.X < minX) minX = vertB.X;
				if (vertC.X < minX) minX = vertC.X;

				if (vertA.Z < minZ) minZ = vertA.Z;
				if (vertB.Z < minZ) minZ = vertB.Z;
				if (vertC.Z < minZ) minZ = vertC.Z;

				if (vertA.X > maxX) maxX = vertA.X;
				if (vertB.X > maxX) maxX = vertB.X;
				if (vertC.X > maxX) maxX = vertC.X;

				if (vertA.Z > maxZ) maxZ = vertA.Z;
				if (vertB.Z > maxZ) maxZ = vertB.Z;
				if (vertC.Z > maxZ) maxZ = vertC.Z;


				if ((vertA != vertB) && (vertB != vertC) && (vertC != vertA))
					AddCell(vertA, vertB, vertC);
			}
			LinkCells();


			tree = new OcTree();
			int totalCells = TotalCells();

			for (int i = 0; i < totalCells; i++)
			{
				TRI t;

				NavigationCell* cell = Cell(i);
				t.UserData = (void*) cell;

				for(int j = 0; j < 3; j++)
				{
					t.Pt[j] = cell->Vertex(j);
				}

				tris.Add(t);
			}
			tree->Create(engine, tris.GetInternalData(), totalCells, 64);

			//if (minX < 0) maxX += abs(minX);
			//if (minZ < 0) maxZ += abs(minZ);

			SafeRelease(&mesh);
		}

		Vector3 NavigationMesh::SnapPointToCell(NavigationCell* Cell, const Vector3& Point)  
		{  
			Vector3 PointOut = Point;  

			if (!Cell->IsPointInCellCollumn(PointOut))  
			{  
				Cell->ForcePointToCellCollumn(PointOut);  
			}  

			Cell->MapVectorHeightToCell(PointOut);  
			return (PointOut);  
		}  


		Vector3 NavigationMesh::SnapPointToMesh(NavigationCell** CellOut, const Vector3& Point)  
		{  
			Vector3 PointOut = Point;  

			*CellOut = FindClosestCell(PointOut);  

			return (SnapPointToCell(*CellOut, PointOut));  
		}  

		inline NavigationCell* NavigationMesh::FindClosestCell(const Vector3& Point) const  
		{  
			float ClosestDistance = 3.4E+38f;  
			float ClosestHeight = 3.4E+38f;  
			bool FoundHomeCell = false;  
			float ThisDistance;  
			NavigationCell* ClosestCell = 0;  

			List<TRI>* triangles = tree->GetTrianglesAt(Point);

			for(UInt32 i = 0; i < triangles->Count(); i++)
			{
				NavigationCell* pCell = (NavigationCell*)triangles->Get(i).UserData;

				if (pCell->IsPointInCellCollumn(Point))  
				{  
					Vector3 NewPosition(Point);  
					pCell->MapVectorHeightToCell(NewPosition);  

					ThisDistance = fabs(NewPosition.Y - Point.Y);  

					if (FoundHomeCell)  
					{  
						if (ThisDistance < ClosestHeight)  
						{  
							ClosestCell = pCell;  
							ClosestHeight = ThisDistance;  
						}  
					}  
					else  
					{  
						ClosestCell = pCell;  
						ClosestHeight = ThisDistance;  
						FoundHomeCell = true;  
					}  
				}  

				if (!FoundHomeCell)  
				{  
					Vector2 Start(pCell->CenterPoint().X, pCell->CenterPoint().Z);  
					Vector2 End(Point.X, Point.Z);  
					Line2D MotionPath(Start, End);  
					NavigationCell* NextCell;  
					NavigationCell::CELL_SIDE WallHit;  
					Vector2 PointOfIntersection;  

					NavigationCell::PATH_RESULT Result = pCell->ClassifyPathToCell(MotionPath, &NextCell, WallHit, &PointOfIntersection);  

					if (Result == NavigationCell::EXITING_CELL)  
					{  
						Vector3 ClosestPoint3D(PointOfIntersection.X, 0.0f, PointOfIntersection.Y);  
						pCell->MapVectorHeightToCell(ClosestPoint3D);  

						ClosestPoint3D -= Point;  

						ThisDistance = ClosestPoint3D.LengthSquared();  

						if (ThisDistance < ClosestDistance)  
						{  
							ClosestDistance=ThisDistance;  
							ClosestCell = pCell;  
						}  
					}  
				}  
			}

			if (!ClosestCell)
				engine->HLog.Write("No closeset cell found in FindClosestCell() (navigationMesh.cpp) \n");
			return ClosestCell;
		}  

		NavigationCell* NavigationMesh::FindClosestCellSlow(const Vector3& Point) const  
		{  
			float ClosestDistance = 3.4E+38f;  
			float ClosestHeight = 3.4E+38f;  
			bool FoundHomeCell = false;  
			float ThisDistance;  
			NavigationCell* ClosestCell = 0;  

			CELL_ARRAY::const_iterator  CellIter = cellArray.begin();  
			for(;CellIter != cellArray.end(); ++CellIter)  
			{  
				NavigationCell* pCell = *CellIter;

				if (pCell->IsPointInCellCollumn(Point))  
				{  
					Vector3 NewPosition(Point);  
					pCell->MapVectorHeightToCell(NewPosition);  

					ThisDistance = fabs(NewPosition.Y - Point.Y);  

					if (FoundHomeCell)  
					{  
						if (ThisDistance < ClosestHeight)  
						{  
							ClosestCell = pCell;  
							ClosestHeight = ThisDistance;  
						}  
					}  
					else  
					{  
						ClosestCell = pCell;  
						ClosestHeight = ThisDistance;  
						FoundHomeCell = true;  
					}  
				}  

				if (!FoundHomeCell)  
				{  
					Vector2 Start(pCell->CenterPoint().X, pCell->CenterPoint().Z);  
					Vector2 End(Point.X, Point.Z);  
					Line2D MotionPath(Start, End);  
					NavigationCell* NextCell;  
					NavigationCell::CELL_SIDE WallHit;  
					Vector2 PointOfIntersection;  

					NavigationCell::PATH_RESULT Result = pCell->ClassifyPathToCell(MotionPath, &NextCell, WallHit, &PointOfIntersection);  

					if (Result == NavigationCell::EXITING_CELL)  
					{  
						Vector3 ClosestPoint3D(PointOfIntersection.X, 0.0f, PointOfIntersection.Y);  
						pCell->MapVectorHeightToCell(ClosestPoint3D);  

						ClosestPoint3D -= Point;  

						ThisDistance = ClosestPoint3D.LengthSquared();  

						if (ThisDistance < ClosestDistance)  
						{  
							ClosestDistance=ThisDistance;  
							ClosestCell = pCell;  
						}  
					}  
				}  
			}

			if (!ClosestCell)
				engine->HLog.Write("No closeset cell found in FindClosestCell() (navigationMesh.cpp) \n");
			return ClosestCell;
		}  


		bool NavigationMesh::LineOfSightTest(NavigationCell* StartCell, const Vector3& StartPos, NavigationCell* EndCell, const Vector3& EndPos)  
		{  
			Line2D MotionPath(Vector2(StartPos.X, StartPos.Z), Vector2(EndPos.X, EndPos.Z));  
			NavigationCell* NextCell = StartCell;  
			NavigationCell::CELL_SIDE WallNumber;  
			NavigationCell::PATH_RESULT Result;  

			int i = 0;
			while((Result = NextCell->ClassifyPathToCell(MotionPath, &NextCell, WallNumber, 0)) == NavigationCell::EXITING_CELL)  
			{  
				i++;
				if (!NextCell || i >= 500) 
					return (false);
			}

			return (Result == NavigationCell::ENDING_CELL);  
		}  

		bool NavigationMesh::BuildNavigationPath(NavigationPath& NavPath, NavigationCell* StartCell,
												 const Vector3& StartPos, NavigationCell* EndCell, const Vector3& EndPos)  
		{  
			bool FoundPath = false;  

			// Increment our path finding session ID  
			// This Identifies each pathfinding session  
			// so we do not need to clear out old data  
			// in the cells from previous sessions.  
			++pathSession;  

			// load our data into the NavigationHeap object  
			// to prepare it for use.  
			navHeap.Setup(pathSession, StartPos);  

			// We are doing a reverse search, from EndCell to StartCell.  
			// Push our EndCell onto the Heap at the first cell to be processed  
			EndCell->QueryForPath(&navHeap, 0, 0);  

			// process the heap until empty, or a path is found  
			while(navHeap.NotEmpty() && !FoundPath)  
			{  
				NavigationNode ThisNode;  

				// pop the top cell (the open cell with the lowest cost) off the Heap  
				navHeap.GetTop(ThisNode);  

				// if this cell is our StartCell, we are done  
				if(ThisNode.cell == StartCell)  
				{  
					FoundPath = true;  
				}  
				else  
				{  
					// Process the Cell, Adding it's neighbors to the Heap as needed  
					ThisNode.cell->ProcessCell(&navHeap);  
				}  
			}  

			// if we found a path, build a waypoint list  
			// out of the cells on the path  
			if (FoundPath)  
			{  
				NavigationCell* TestCell = StartCell;  
				Vector3 NewWayPoint;  

				// Setup the Path object, clearing out any old data  
				NavPath.Setup(this, StartPos, StartCell, EndPos, EndCell);  

				int escapeCtr = 0;
				// Step through each cell linked by our A* algorythm   
				// from StartCell to EndCell  
				while (TestCell && TestCell != EndCell)  
				{  
					// escape out of while loop it something went wrong.
					escapeCtr++;
					if (escapeCtr > 512)
					{
						engine->HLog.Write("Escaped out of while loop in BuildNavigationPath() NavigationMesh.cpp \n");
						return false;
					}

					// add the link point of the cell as a way point (the exit wall's center)  
					int LinkWall = TestCell->ArrivalWall();  

					NewWayPoint = TestCell->WallMidpoint(LinkWall);  
					NewWayPoint = SnapPointToCell(TestCell, NewWayPoint); // just to be sure  

					NavPath.AddWayPoint(NewWayPoint, TestCell);  

					// and on to the next cell  
					TestCell = TestCell->Link(LinkWall);  
				}  

				// cap the end of the path.  
				NavPath.EndPath();  
				return(true);  
			}  
			return(false);  
		}  

		void NavigationMesh::ResolveMotionOnMesh(const Vector3& StartPos, NavigationCell* StartCell, Vector3& EndPos, NavigationCell** EndCell)  
		{  
			// create a 2D motion path from our Start and End positions, tossing out their Y values to project them   
			// down to the XZ plane.  
			Line2D MotionPath(Vector2(StartPos.X, StartPos.Z), 
							  Vector2(EndPos.X, EndPos.Z));  

			// these three will hold the results of our tests against the cell walls  
			NavigationCell::PATH_RESULT Result = NavigationCell::NO_RELATIONSHIP;  
			NavigationCell::CELL_SIDE WallNumber;  
			Vector2 PointOfIntersection;  
			NavigationCell* NextCell;  

			// TestCell is the cell we are currently examining.  
			NavigationCell* TestCell = StartCell;  

			// Keep testing until we find our ending cell or stop moving due to friction  
			while ((Result != NavigationCell::ENDING_CELL) && (MotionPath.EndPointA() != MotionPath.EndPointB()))  
			{  
				// use NavigationCell to determine how our path and cell interact  
				Result = TestCell->ClassifyPathToCell(MotionPath, &NextCell, WallNumber, &PointOfIntersection);  

				// if exiting the cell...  
				if (Result == NavigationCell::EXITING_CELL)  
				{  
					// Set if we are moving to an adjacent cell or we have hit a solid (unlinked) edge  
					if(NextCell)  
					{  
						// moving on. Set our motion origin to the point of intersection with this cell  
						// and continue, using the new cell as our test cell.  
						MotionPath.SetEndPointA(PointOfIntersection);  
						TestCell = NextCell;  
					}  
					else  
					{  
						// we have hit a solid wall. Resolve the collision and correct our path.  
						MotionPath.SetEndPointA(PointOfIntersection);  
						TestCell->ProjectPathOnCellWall(WallNumber, MotionPath);  

						// add some friction to the new MotionPath since we are scraping against a wall.  
						// we do this by reducing the magnatude of our motion by 10%  
						Vector2 Direction = MotionPath.EndPointB() - MotionPath.EndPointA();  
						Direction = Direction * 0.9f;
						MotionPath.SetEndPointB(MotionPath.EndPointA() + Direction);  
					}  
				}  
				else if (Result == NavigationCell::NO_RELATIONSHIP)  
				{  
					// Although theoretically we should never encounter this case,  
					// we do sometimes find ourselves standing directly on a vertex of the cell.  
					// This can be viewed by some routines as being outside the cell.  
					// To accomodate this rare case, we can force our starting point to be within  
					// the current cell by nudging it back so we may continue.  
					Vector2 NewOrigin = MotionPath.EndPointA();  
					TestCell->ForcePointToCellCollumn(NewOrigin);  
					MotionPath.SetEndPointA(NewOrigin);  
				}  
			}  

			// we now have our new host cell  
			*EndCell = TestCell;  

			// Update the new control point position,   
			// solving for Y using the Plane member of the NavigationCell  
			EndPos.X = MotionPath.EndPointB().X;  
			EndPos.Z = MotionPath.EndPointB().Y;  
			TestCell->MapVectorHeightToCell(EndPos);  
		}  

		void NavigationMesh::Draw(const DrawArgs& args)
		{
#if _DEBUG
			// render each cell triangle
			List<Vector3> triangles;
			CELL_ARRAY::const_iterator iter = cellArray.begin();
			for (; iter != cellArray.end(); ++iter)
			{
				const NavigationCell* cell = *iter;

				args.Graphics->DrawLine(cell->Vertex(0),cell->Vertex(1), Color::Red);
				args.Graphics->DrawLine(cell->Vertex(1),cell->Vertex(2), Color::Red);
				args.Graphics->DrawLine(cell->Vertex(2),cell->Vertex(0), Color::Red);
			}

			// Draw Octree
			tree->DrawDebug();
#endif
		}

		int NavigationMesh::TotalCells() const
		{
			return((int)cellArray.size());
		}

		NavigationCell* NavigationMesh::Cell(int index)
		{
			return(cellArray.at(index));
		}

	}
}