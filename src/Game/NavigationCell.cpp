#include "Game/NavigationCell.h"
#include "Game/Utils.h"

namespace TikiEngine
{
	namespace AI
	{
		using namespace TikiEngine;
		// operators
		inline NavigationCell& NavigationCell::operator=(const NavigationCell& src)
		{
			if (this != &src)
			{
				cellPlane = src.cellPlane;		
				centerPoint = src.centerPoint;	
				sessionID = src.sessionID;
				arrivalCost = src.arrivalCost;
				heuristic = src.heuristic;
				open = src.open;
				arrivalWall = src.arrivalWall;

				for (int i = 0; i < 3; i++)
				{
					vertex[i] = src.vertex[i];
					side[i] = src.side[i];
					link[i] = src.link[i];
					wallMidpoint[i] = src.wallMidpoint[i];
					wallDistance[i] = src.wallDistance[i];
				}
			}
			return (*this);
		}

		inline void NavigationCell::Initialize(const Vector3& pointA, const Vector3& pointB, const Vector3& pointC)
		{
			vertex[VERT_A] = pointA;
			vertex[VERT_B] = pointB;
			vertex[VERT_C] = pointC;

			// object must be re-linked
			link[SIDE_AB] = 0;
			link[SIDE_BC] = 0;
			link[SIDE_CA] = 0;

			// now that the vertex pointers are set, compute additional data about the Cell
			ComputeCellData();
		}

		inline void NavigationCell::ComputeCellData()
		{
			// create 2D versions of our verticies
			Vector2 Point1(vertex[VERT_A].X, vertex[VERT_A].Z);
			Vector2 Point2(vertex[VERT_B].X, vertex[VERT_B].Z);
			Vector2 Point3(vertex[VERT_C].X, vertex[VERT_C].Z);

			// innitialize our sides
			side[SIDE_AB].SetPoints(Point1, Point2);	// line AB
			side[SIDE_BC].SetPoints(Point2, Point3);	// line BC
			side[SIDE_CA].SetPoints(Point3, Point1);	// line CA

			cellPlane.Set(vertex[VERT_A], vertex[VERT_B], vertex[VERT_C]);

			// compute midpoint as centroid of polygon
			centerPoint.X = ((vertex[VERT_A].X + vertex[VERT_B].X + vertex[VERT_C].X) / 3);
			centerPoint.Y = ((vertex[VERT_A].Y + vertex[VERT_B].Y + vertex[VERT_C].Y) / 3);
			centerPoint.Z = ((vertex[VERT_A].Z + vertex[VERT_B].Z + vertex[VERT_C].Z) / 3);

			// compute the midpoint of each cell wall
			wallMidpoint[0].X = (vertex[VERT_A].X + vertex[VERT_B].X) / 2.0f;
			wallMidpoint[0].Y = (vertex[VERT_A].Y + vertex[VERT_B].Y) / 2.0f;
			wallMidpoint[0].Z = (vertex[VERT_A].Z + vertex[VERT_B].Z) / 2.0f;

			wallMidpoint[1].X = (vertex[VERT_C].X + vertex[VERT_B].X) / 2.0f;
			wallMidpoint[1].Y = (vertex[VERT_C].Y + vertex[VERT_B].Y) / 2.0f;
			wallMidpoint[1].Z = (vertex[VERT_C].Z + vertex[VERT_B].Z) / 2.0f;

			wallMidpoint[2].X = (vertex[VERT_C].X + vertex[VERT_A].X) / 2.0f;
			wallMidpoint[2].Y = (vertex[VERT_C].Y + vertex[VERT_A].Y) / 2.0f;
			wallMidpoint[2].Z = (vertex[VERT_C].Z + vertex[VERT_A].Z) / 2.0f;

			// compute the distances between the wall midpoints
			Vector3 WallVector;
			WallVector = wallMidpoint[0] - wallMidpoint[1];
			wallDistance[0] = WallVector.Length();

			WallVector = wallMidpoint[1] - wallMidpoint[2];
			wallDistance[1] = WallVector.Length();

			WallVector = wallMidpoint[2] - wallMidpoint[0];
			wallDistance[2] = WallVector.Length();
		}

		inline bool NavigationCell::RequestLink(const Vector3& PointA, const Vector3& PointB, NavigationCell* Caller)
		{
			// return true if we share the two provided verticies with the calling cell.
			if (vertex[VERT_A] == PointA)
			{
				if (vertex[VERT_B] == PointB)
				{
					link[SIDE_AB] = Caller;
					return true;
				}
				else if (vertex[VERT_C] == PointB)
				{
					link[SIDE_CA] = Caller;
					return true;
				}
			}
			else if (vertex[VERT_B] == PointA)
			{
				if (vertex[VERT_A] == PointB)
				{
					link[SIDE_AB] = Caller;
					return true;
				}
				else if (vertex[VERT_C] == PointB)
				{
					link[SIDE_BC] = Caller;
					return true;
				}
			}
			else if (vertex[VERT_C] == PointA)
			{
				if (vertex[VERT_A] == PointB)
				{
					link[SIDE_CA] = Caller;
					return true;
				}
				else if (vertex[VERT_B] == PointB)
				{
					link[SIDE_BC] = Caller;
					return true;
				}
			}

			// we are not adjacent to the calling cell
			return false;
		}

		inline void NavigationCell::SetLink(CELL_SIDE Side, NavigationCell* Caller)
		{
			link[Side] = Caller;
		}

		NavigationCell::PATH_RESULT NavigationCell::ClassifyPathToCell(const Line2D& MotionPath, NavigationCell** pNextCell, CELL_SIDE& Side, Vector2* pPointOfIntersection) const  
		{  
			int InteriorCount = 0;  
  
			// Check our MotionPath against each of the three cell walls  
			for (int i = 0; i < 3; ++i)  
			{  
				// Classify the MotionPath endpoints as being either ON_LINE,  
				// or to its LEFT_SIDE or RIGHT_SIDE.   
				// Since our triangle vertices are in clockwise order,   
				// we know that points  to the right of each line are inside the cell.  
				// Points to the left are outside.   
				// We do this test using the ClassifyPoint function of Line2D  
  
				// If the destination endpoint of the MotionPath   
				// is Not on the right side of this wall...  
				if (side[i].ClassifyPoint(MotionPath.EndPointB()) != Line2D::RIGHT_SIDE)  
				{  
					// ..and the starting endpoint of the MotionPath   
					// is Not on the left side of this wall...  
					if (side[i].ClassifyPoint(MotionPath.EndPointA()) != Line2D::LEFT_SIDE)  
					{  
						// Check to see if we intersect the wall   
						// using the Intersection function of Line2D  
						Line2D::LINE_CLASSIFICATION IntersectResult = MotionPath.Intersection(side[i], pPointOfIntersection);  
                  
						if (IntersectResult == Line2D::SEGMENTS_INTERSECT || 
							IntersectResult == Line2D::A_BISECTS_B)  
						{  
							// record the link to the next adjacent cell  
							// (or NULL if no attachement exists)  
							// and the enumerated ID of the side we hit.  
							*pNextCell = link[i];  
							Side = (CELL_SIDE)i;  
							return (EXITING_CELL);  
						}  
					}  
				}  
				else  
				{  
					// The destination endpoint of the MotionPath is on the right side.  
					// Increment our InteriorCount so we'll know how many walls we were  
					// to the right of.  
					InteriorCount++;  
				}  
			}  
  
			// An InteriorCount of 3 means the destination endpoint of the MotionPath   
			// was on the right side of all walls in the cell.   
			// That means it is located within this triangle, and this is our ending cell.  
			if (InteriorCount == 3)  
			{  
				return (ENDING_CELL);  
			}  
  
			// We only reach here is if the MotionPath does not intersect the cell at all.  
			return (NO_RELATIONSHIP);  
		}  

		void NavigationCell::ProjectPathOnCellWall(CELL_SIDE SideNumber, Line2D& MotionPath) const  
		{  
			// compute the normalized vector of the cell wall in question  
			Vector2 WallNormal = side[SideNumber].EndPointB() - side[SideNumber].EndPointA();  
			WallNormal.Normalize();  
  
			// determine the vector of our current movement  
			Vector2 MotionVector = MotionPath.EndPointB() - MotionPath.EndPointA();  
  
			// compute dot product of our MotionVector and the normalized cell wall  
			// this gives us the magnitude of our motion along the wall  
			float DotResult = Vector2::Dot(MotionVector, WallNormal);  
      
			// our projected vector is then the normalized wall vector times our new found magnatude  
			MotionVector = Vector2( (DotResult * WallNormal.X), (DotResult * WallNormal.Y));  
  
			// redirect our motion path along the new reflected direction  
			MotionPath.SetEndPointB(MotionPath.EndPointA() + MotionVector);  
  

			// Make sure starting point of motion path is within the cell  
			Vector2 NewPoint = MotionPath.EndPointA();  
			ForcePointToCellCollumn(NewPoint);  
			MotionPath.SetEndPointA(NewPoint);  
  
			// Make sure destination point does not intersect this wall again  
			NewPoint = MotionPath.EndPointB();  
			ForcePointToWallInterior(SideNumber, NewPoint);  
			MotionPath.SetEndPointB(NewPoint);  
		}  


		inline void NavigationCell::MapVectorHeightToCell(Vector3& MotionPoint) const
		{
			MotionPoint.Y = cellPlane.SolveForY(MotionPoint.X, MotionPoint.Z);
		}

		bool NavigationCell::ForcePointToCellCollumn(Vector3& TestPoint) const  
		{  
			Vector2 TestPoint2D(TestPoint.X, TestPoint.Z);  
			bool PointAltered = ForcePointToCellCollumn(TestPoint2D);  
  
			if (PointAltered)  
			{  
				TestPoint.X = TestPoint2D.X;  
				TestPoint.Z = TestPoint2D.Y;  
			}  
			return (PointAltered);  
		}  

		bool NavigationCell::ForcePointToCellCollumn(Vector2& TestPoint) const  
		{  
			bool PointAltered = false;  
  
			// create a motion path from the center of the cell to our point  
			Line2D TestPath(Vector2(centerPoint.X, centerPoint.Z), TestPoint);  
			Vector2 PointOfIntersection;  
			CELL_SIDE Side;  
			NavigationCell* NextCell;  
  
			PATH_RESULT result = ClassifyPathToCell(TestPath, &NextCell, Side, &PointOfIntersection);  
			// compare this path to the cell.  
  
			if (result == EXITING_CELL)  
			{  
				Vector2 PathDirection(PointOfIntersection.X - centerPoint.X, 
									  PointOfIntersection.Y - centerPoint.Z);  
  
				PathDirection = (PathDirection.X * 0.9f, 
								 PathDirection.Y * 0.9f);  
  
				TestPoint.X = centerPoint.X + PathDirection.X;  
				TestPoint.Y = centerPoint.Z + PathDirection.Y;  
				return (true);  
			}  
			else if (result == NO_RELATIONSHIP)  
			{  
				TestPoint.X = centerPoint.X;  
				TestPoint.Y = centerPoint.Z;  
				return (true);  
			}  
  
			return (false);  
		}  


		bool NavigationCell::ForcePointToWallInterior(CELL_SIDE SideNumber, Vector2& TestPoint) const  
		{  
			float Distance = side[SideNumber].SignedDistance(TestPoint);  
			float Epsilon = 0.001f;  
  
			if (Distance = Epsilon)  
			{  
				if (Distance = 0.0f)  
				{  
					Distance -= Epsilon;  
				}  
  
				Distance = (float) fabs(Distance);  
				Distance = (Epsilon > Distance ? Epsilon : Distance);  
  
				// this point needs adjustment  
				Vector2 Normal = side[SideNumber].Normal();  
				TestPoint += Vector2(Normal.X * Distance, Normal.Y * Distance);  
				return (true);  
			}  
			return (false);  
		}  

		bool NavigationCell::ForcePointToWallInterior(CELL_SIDE SideNumber, Vector3& TestPoint)const  
		{  
			Vector2 TestPoint2D(TestPoint.X, TestPoint.Z);  
			bool PointAltered = ForcePointToWallInterior(SideNumber, TestPoint2D);  
  
			if (PointAltered)  
			{  
				TestPoint.X = TestPoint2D.X;  
				TestPoint.Z = TestPoint2D.Y;  
			}  
  
			return (PointAltered);  
		} 

		bool NavigationCell::ProcessCell(NavigationHeap* pHeap)  
		{  
			if (sessionID==pHeap->SessionID())  
			{  
				// once we have been processed, we are closed  
				open  = false;  
  
				// querry all our neigbors to see if they need to be added to the Open heap  
				for (int i = 0; i < 3; ++i)  
				{  
					if (link[i])  
					{  
						// abs(i-m_ArrivalWall) is a formula to determine which distance measurement to use.  
						// The Distance measurements between the wall midpoints of this cell  
						// are held in the order ABtoBC, BCtoCA and CAtoAB.   
						// We add this distance to our known m_ArrivalCost to compute  
						// the total cost to reach the next adjacent cell.  
						link[i]->QueryForPath(pHeap, this, arrivalCost+wallDistance[abs(i - arrivalWall)]);  
					}  
				}  
				return(true);  
			}  
			return(false);  
		}  

		bool NavigationCell::QueryForPath(NavigationHeap* pHeap, NavigationCell* Caller, float arrivalcost)  
		{  
			if (sessionID != pHeap->SessionID())  
			{  
				// this is a new session, reset our internal data  
				sessionID = pHeap->SessionID();  
  
				if (Caller)  
				{  
					open  = true;  
					ComputeHeuristic(pHeap->Goal());  
					arrivalCost = arrivalcost;  
  
					// remember the side this caller is entering from  
					if (Caller == link[0])  
					{  
						arrivalWall = 0;  
					}  
					else if (Caller == link[1])  
					{  
						arrivalWall = 1;  
					}  
					else if (Caller == link[2])  
					{  
						arrivalWall = 2;  
					}  
				}  
				else  
				{  
					// we are the cell that contains the starting location  
					// of the A* search.  
					open  = false;  
					arrivalCost = 0;  
					heuristic = 0;  
					arrivalWall = 0;  
				}  
				// add this cell to the Open heap  
				pHeap->AddCell(this);  
				return(true);  
			}  
			else if (open)  
			{  
				// Open means we are already in the Open Heap.  
				// If this new caller provides a better path, adjust our data  
				// Then tell the Heap to resort our position in the list.  
				if ((arrivalcost + heuristic) < (arrivalCost + heuristic))  
				{  
						arrivalCost = arrivalcost;  
  
						// remember the side this caller is entering from  
						if (Caller == link[0])  
						{  
							arrivalWall = 0;  
						}  
						else if (Caller == link[1])  
						{  
							arrivalWall = 1;  
						}  
						else if (Caller == link[2])  
						{  
							arrivalWall = 2;  
						}  
						// ask the heap to resort our position in the priority heap  
						pHeap->AdjustCell(this);  
						return(true);  
				}  
			}  
			// this cell is closed  
			return(false);  
		}  


		#pragma region Accessors
		inline bool NavigationCell::IsPointInCellCollumn(const Vector2& TestPoint) const
		{
			// we are "in" the cell if we are on the right hand side of all edge lines of the cell
			int InteriorCount = 0;

			for (int i = 0; i < 3; i++)
			{
				Line2D::POINT_CLASSIFICATION SideResult = side[i].ClassifyPoint(TestPoint);

				if (SideResult != Line2D::LEFT_SIDE)
					InteriorCount++;
			}

			return (InteriorCount == 3);
		}

		inline bool NavigationCell::IsPointInCellCollumn(const Vector3& TestPoint) const
		{
			Vector2 TestPoint2D(TestPoint.X,TestPoint.Z);
			return (IsPointInCellCollumn(TestPoint2D));
		}

		inline const Vector3& NavigationCell::Vertex(int Vert) const
		{
			return(vertex[Vert]);
		}

		inline const Vector3& NavigationCell::CenterPoint() const
		{
			return(centerPoint);
		}

		inline NavigationCell* NavigationCell::Link(int Side) const
		{
			return(link[Side]);
		}

		inline float NavigationCell::ArrivalCost() const
		{
			return(arrivalCost);
		}

		inline float NavigationCell::Heuristic() const
		{
			return(heuristic);
		}

		float NavigationCell::PathfindingCost() const
		{
			return(arrivalCost + heuristic);
		}

		inline int NavigationCell::ArrivalWall() const
		{
			return(arrivalWall);
		}

		inline const Vector3 NavigationCell::WallMidpoint(int Side)const
		{
			return(wallMidpoint[Side]);
		}
		#pragma endregion	

		void NavigationCell::ComputeHeuristic(const Vector3& Goal)  
		{  
			// our heuristic is the estimated distance (using the longest axis delta) between our  
			// cell center and the goal location  
			float XDelta = fabs(Goal.X - centerPoint.X);  
			float YDelta = fabs(Goal.Y - centerPoint.Y);  
			float ZDelta = fabs(Goal.Z - centerPoint.Z);  
  
			heuristic = MaxOf(MaxOf(XDelta,YDelta), ZDelta); //__max(__max(XDelta,YDelta), ZDelta);  
		}  

	}
}