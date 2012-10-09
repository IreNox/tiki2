#pragma once

#include "Core/Plane.h"
#include "Core/Line2D.h"
#include "Game/NavigationHeap.h"

namespace TikiEngine
{
	namespace AI
	{
		
		// a forward declaration for NavigationHeap is required
		class NavigationHeap;


	    /* A NavigationCell represents a single triangle within a NavigationMesh. It contains 
		*  functions for testing a path against the cell, and various ways to resolve collisions
		*  with the cell walls. Portions of the A* path finding algorithm are provided within this
		*  class as well, but the path finding process is managed by the parent Navigation Mesh.
		*/
		class NavigationCell
		{
		public:
			enum CELL_VERT
			{
				VERT_A = 0,
				VERT_B,
				VERT_C
			};

			enum CELL_SIDE
			{
				SIDE_AB = 0,
				SIDE_BC,
				SIDE_CA
			};

			enum PATH_RESULT
			{
				NO_RELATIONSHIP, // the path does not cross this cell
				ENDING_CELL,	 // the path ends in this cell	
				EXITING_CELL	 // the path exits this cell through side X
			};

			// ctor / dtor
			inline NavigationCell() : sessionID(0) { };
			inline NavigationCell(const NavigationCell& src) { *this = src; };
			inline ~NavigationCell() { };

			// operators
			NavigationCell& operator=(const NavigationCell& src);


			// Initialize our Cell object, given it's vertices in clockwise order 
			void Initialize(const Vector3& pointA, const Vector3& pointB, const Vector3& pointC);

			// Compute additional data about the cell used for navigation tests and pathfinding 
			void ComputeCellData();

			// Navigation Mesh is created as a pool of raw cells. The cells are then compared against 
			// each other to find common edges and create links. This routine is called from a 
			// potentially adjacent cell to test if a link should exist between the two. 
			bool RequestLink(const Vector3& PointA, const Vector3& PointB, NavigationCell* Caller);
			
			// Sets a link to the calling cell on the enumerated edge. 
			void SetLink(CELL_SIDE Side, NavigationCell* Caller);

			
			// Classifies a Path in relationship to this cell. A path is represented by a 2D line 
			// where Point A is the start of the path and Point B is the desired position. 
 			// 
			// If the path exits this cell on a side which is linked to another cell, that cell index 
			// is returned in the NextCell parameter and SideHit contains the side number of the wall  
			// exited through. 
			//  
			// If the path collides with a side of the cell which has no link (a solid edge),  
			// SideHit contains the side number (0-2) of the colliding wall. 
 			// 
			// In either case PointOfIntersection will contain the point where the path intersected 
			// with the wall of the cell if it is provided by the caller. 
			PATH_RESULT ClassifyPathToCell(const Line2D& MotionPath, NavigationCell** pNextCell, CELL_SIDE& Side, Vector2* pPointOfIntersection) const;

			// ProjectPathOnCellWall projects a path intersecting the wall with the wall itself. This 
			// can be used to convert a path colliding with a cell wall to a resulting path moving 
			// along the wall. The input parameter MotionPath MUST contain a starting point (EndPointA) 
			// which is the point of intersection with the path and cell wall number [SideNumber] 
			// and an ending point (EndPointB) which resides outside of the cell. 
			void ProjectPathOnCellWall(CELL_SIDE SideNumber, Line2D& MotionPath)const;

			// Uses the X and Z information of the vector to calculate Y on the cell plane 
			void MapVectorHeightToCell(Vector3& MotionPoint)const;

			// Force a 3D point to the interior cell by forcing it to the interior of each wall   
			bool ForcePointToCellCollumn(Vector3& TestPoint) const;
			// Force a 2D point to the interior cell by forcing it to the interior of each wall   
			bool ForcePointToCellCollumn(Vector2& TestPoint) const;

			//  Force a 2D point to the interior side of the specified wall.   
			bool ForcePointToWallInterior(CELL_SIDE SideNumber, Vector2& TestPoint) const;
			// Force a 3D point to the interior side of the specified wall.   
			bool ForcePointToWallInterior(CELL_SIDE SideNumber, Vector3& TestPoint) const;

			// Process this cells neighbors using A*   
			bool ProcessCell(NavigationHeap* pHeap);
			// Process this cell using the A* heuristic   
			bool QueryForPath(NavigationHeap* pHeap, NavigationCell* Caller, float arrivalcost);

			#pragma region Accessors
			bool IsPointInCellCollumn(const Vector3& TestPoint) const;

			// Test to see if a 2D point is within the cell. There are probably better ways to do 
			// this, but this seems plenty fast for the time being. 
			bool IsPointInCellCollumn(const Vector2& TestPoint) const;
			const Vector3& Vertex(int Vert) const;
			const Vector3& CenterPoint() const;
			NavigationCell* Link(int Side) const;

			//const Vector3& LinkPoint() const;

			float ArrivalCost() const;
			float Heuristic() const;
			float PathfindingCost() const;

			int ArrivalWall() const;
			const Vector3 WallMidpoint(int Side) const;
			#pragma endregion

		private:
			// Compute the A* Heuristic for this cell given a Goal point. heuristic is the estimated distance 
			// (using the longest axis delta) between our cell center and the goal location   
			void ComputeHeuristic(const Vector3& goal); 


			Plane cellPlane;		 // A plane containing the cell triangle
			Vector3 vertex[3];		 // pointers to the verticies of this triangle held in the NavigationMesh's vertex pool
			Vector3 centerPoint;	 // The triangle's center
			Line2D side[3];			 // a 2D line representing each cell Side
			NavigationCell* link[3]; // pointers to cells that attach to this cell. A NULL link denotes a solid edge.


			int sessionID;			 // an identifier for the current pathfinding session.
			float arrivalCost;		 // total cost to use this cell as part of a path
			float heuristic;		 // our estimated cost to the goal from here
			bool open;				 // are we currently listed as an Open cell to revisit and test?
			int	arrivalWall;		 // the side we arrived through.
			Vector3 wallMidpoint[3]; // the pre-computed midpoint of each wall.
			float wallDistance[3];	 // the distances between each wall midpoint of sides (0-1, 1-2, 2-0)


		};

	}
}