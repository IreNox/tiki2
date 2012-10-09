#pragma once

#include <list>
#include "Game/NavigationCell.h"
#include "Game/NavigationMesh.h"

namespace TikiEngine
{
	namespace AI
	{
		/* NavigationPath is a collection of waypoints that define a movement path for an Actor.
		*  This object is ownded by an Agent and filled by NavigationMesh::BuildNavigationPath().
		*/
		class NavigationPath
		{
		public:
			struct WAYPOINT
			{
				Vector3 position;		// 3D position of waypoint
				NavigationCell* cell;	// The cell which owns the waypoint
			};

			typedef std::list <WAYPOINT> WAYPOINT_LIST;
			typedef WAYPOINT_LIST::const_iterator WayPointID;

			NavigationPath();
			~NavigationPath();

			// Sets up a new path from StartPoint to EndPoint. It adds the StartPoint as the first 
			// waypoint in the list and waits for further calls to AddWayPoint and EndPath to 
			// complete the list 
			void Setup(NavigationMesh* Parent, const Vector3& StartPoint, NavigationCell* StartCell, const Vector3& EndPoint, NavigationCell* EndCell);
			
			// Adds a new waypoint to the end of the list 
			void AddWayPoint(const Vector3& Point, NavigationCell* Cell);

			// Caps the end of the waypoint list by adding our final destination point 
			void EndPath();

			// accessors
			NavigationMesh*	Parent() const;
			const WAYPOINT&	StartPoint() const;
			const WAYPOINT&	EndPoint() const;
			WAYPOINT_LIST& WaypointList();

			//	Find the furthest visible waypoint from the VantagePoint provided. This is used to smooth out irregular paths. 
			WayPointID GetFurthestVisibleWayPoint(const WayPointID& VantagePoint)const;


		private:
			// not impl.
			NavigationPath( const NavigationPath& Src);
			NavigationPath& operator=( const NavigationPath& Src);

			NavigationMesh*		parent;
			WAYPOINT			startPoint;
			WAYPOINT			endPoint;
			WayPointID			endID;
			WAYPOINT_LIST		waypointList;



		};


	}
}