#include "Game/NavigationPath.h"

namespace TikiEngine
{
	namespace AI
	{
		// ctor / dtor
		NavigationPath::NavigationPath()
		{
		}

		NavigationPath::~NavigationPath()
		{
		}

		void NavigationPath::Setup(NavigationMesh* Parent, const Vector3& StartPoint, NavigationCell* StartCell, const Vector3& EndPoint, NavigationCell* EndCell)
		{
			this->waypointList.clear();

			this->parent = Parent;
			this->startPoint.position = StartPoint;
			this->startPoint.cell = StartCell;
			this->endPoint.position = EndPoint;
			this->endPoint.cell = EndCell;

			// setup the waypoint list with our start and end points
			this->waypointList.push_back(startPoint);
		}

		void NavigationPath::AddWayPoint(const Vector3& Point, NavigationCell* Cell)
		{
			WAYPOINT NewPoint;

			NewPoint.position = Point;
			NewPoint.cell = Cell;

			this->waypointList.push_back(NewPoint);
		}

		void NavigationPath::EndPath()
		{
			// cap the waypoint path with the last endpoint
			this->waypointList.push_back(endPoint);
		}

		// accessors
		NavigationMesh* NavigationPath::Parent()const
		{
			return(parent);
		}

		const NavigationPath::WAYPOINT& NavigationPath::StartPoint() const
		{
			return(startPoint);
		}

		const NavigationPath::WAYPOINT&	NavigationPath::EndPoint() const
		{
			return(endPoint);
		}

		NavigationPath::WAYPOINT_LIST& NavigationPath::WaypointList()
		{
			return(waypointList);
		}

		NavigationPath::WayPointID NavigationPath::GetFurthestVisibleWayPoint(const WayPointID& VantagePoint) const
		{
			// see if we are already talking about the last waypoint
			if (VantagePoint == waypointList.end())
			{
				return(VantagePoint);
			}

			const WAYPOINT& Vantage = *VantagePoint;
			WayPointID TestWaypoint = VantagePoint;
			++TestWaypoint;

			if (TestWaypoint == waypointList.end())
			{
				return(TestWaypoint);
			}

			WayPointID VisibleWaypoint = TestWaypoint;
			++TestWaypoint;

			while (TestWaypoint != waypointList.end())
			{
				const WAYPOINT& Test = *TestWaypoint;
				if (!parent->LineOfSightTest(Vantage.cell, Vantage.position, Test.cell, Test.position))
				{
					return(VisibleWaypoint);
				}
				VisibleWaypoint = TestWaypoint;
				++TestWaypoint;	
			}
			return(VisibleWaypoint);
		}

	}
}