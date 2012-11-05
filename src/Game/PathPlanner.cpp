#include "Game/PathPlanner.h"

#include "Game/TikiBot.h"
#include "Core/IGraphics.h"

namespace TikiEngine
{
    namespace AI
    {
        PathPlanner::PathPlanner(TikiBot* bot)
        {
            this->bot = bot;
            pathActive = false;
            pathMovement = Vector3::Zero;
            pathPos = Vector3::Zero;
            currentCell = 0;
            parent = 0;
			targetSnap = Vector3::Zero;
        }

        PathPlanner::~PathPlanner()
        {

        }

        bool PathPlanner::Create(NavigationMesh* navMesh)
        {
            pathPos = bot->Pos3D();
            parent = navMesh;
            
            // no starting cell is provided, find one by searching the mesh
            if (parent)
            {
                currentCell = parent->FindClosestCell(pathPos);
                // make sure our position is within the current cell
                pathPos = parent->SnapPointToCell(currentCell, pathPos);
                bot->GetController()->SetCenter(pathPos);
                return true;
            }
            else
                return false;
        }


        bool PathPlanner::RequestPathTo(const Vector3& target)
        {
            if (!parent)
                return false;

            // find closest cell to the target position
            NavigationCell* endCell = parent->FindClosestCell(target);

            // don't move if we have a position outisde of navMesh
            if (!endCell)
                return false;

			// snap the point to the cell
			targetSnap = target;
			if (!endCell->IsPointInCellCollumn(target))
				targetSnap = parent->SnapPointToCell(endCell, target);


            // find closest cell to the bot position
            currentCell = parent->FindClosestCell(bot->Pos3D());
            if (!currentCell)
                return false;

            // if we can see the target, just use steering, else use A*
            if (parent->LineOfSightTest(currentCell, bot->Pos3D(), endCell, targetSnap))
            {
                // stop Navigation and seek
                pathActive = false;
                pathMovement = Vector3::Zero;
                return false;
            }
            else
            {
                // stop any steering and begin building the navigationPath
                //bot->GetSteering()->ArriveOff();
                pathPos = bot->Pos3D();
                pathMovement = Vector3::Zero;
                pathActive = parent->BuildNavigationPath(path, currentCell, pathPos, endCell, targetSnap);
                if (pathActive)
                    nextWaypoint = path.WaypointList().begin();

                return pathActive;
            }

        }

		Vector3 PathPlanner::GetTargetSnap() const
		{
			return targetSnap;
		}

		std::list<PathEdge> PathPlanner::GetPath(bool smooth)
		{
			std::list<PathEdge> pathEdges;

			if (smooth)
			{
				Vector2 last = Vector2(nextWaypoint->position.X, nextWaypoint->position.Z);

				while(nextWaypoint != path.WaypointList().end())
				{
					nextWaypoint = path.GetFurthestVisibleWayPoint(nextWaypoint);

					if (nextWaypoint != path.WaypointList().end())
					{
						Vector2 curr = Vector2(nextWaypoint->position.X, nextWaypoint->position.Z);
						pathEdges.push_back(PathEdge(last, curr));
						last = curr;
					}
				}
			}
			else
			{
				NavigationPath::WAYPOINT_LIST::const_iterator iter = path.WaypointList().begin();
				if (iter != path.WaypointList().end())
				{
				    NavigationPath::WAYPOINT LastWaypoint = *iter;
				    ++iter;
				    for ( ; iter != path.WaypointList().end(); ++iter)
				    {
				        const NavigationPath::WAYPOINT& waypoint= *iter;
				 
				 	Vector2 last = Vector2(LastWaypoint.position.X, LastWaypoint.position.Z);
				 	Vector2 curr = Vector2(waypoint.position.X, waypoint.position.Z);
				 	pathEdges.push_back(PathEdge(last, curr));
				 
				        LastWaypoint = waypoint;
				    }
				}
			}


			return pathEdges;
		}

//         void PathPlanner::Update(const UpdateArgs& args)
//         {
//             float distance;
//             float max_distance = (float)(bot->MaxSpeed() * args.Time.ElapsedTime);
// 
//             // if we have no parent mesh, return. We are simply a static object.
//             if (!parent)
//                 return;
// 
//             // Figure out where we are going
//             if (pathActive)
//             {
//                 // Move along the waypoint path
//                 if (nextWaypoint != path.WaypointList().end())
//                 {
//                     // determine our desired movement vector
//                     pathMovement = (*nextWaypoint).position;
//                     pathMovement -= pathPos;
//                 }
//                 else
//                 {
//                     // we have reached the end of the path
//                     pathActive = false;
//                     pathMovement = Vector3::Zero;
//                 }
//             }
//             else
//             {
//                 // apply some friction to our current movement (if any)
//                 pathMovement.X *= 0.75f;
//                 pathMovement.Y *= 0.75f;
//                 pathMovement.Z *= 0.75f;
//             }
// 
//             // scale back movement by our max speed if needed
//             distance = pathMovement.LengthSquared();
//             if (distance > max_distance * max_distance)
//             {
//                 pathMovement = Vector3::Normalize(pathMovement);
//                 pathMovement = pathMovement * max_distance;
//             }
// 
//             // come to a full stop when we go below a certain threshold
//             if (fabs(pathMovement.X) < 0.005f) pathMovement.X = 0.0f;
//             if (fabs(pathMovement.Y) < 0.005f) pathMovement.Y = 0.0f;
//             if (fabs(pathMovement.Z) < 0.005f) pathMovement.Z = 0.0f;
// 
// 
//             // Constrain any remaining Horizontal movement to the parent navigation rink
//             if (pathMovement.X || pathMovement.Z)
//             {
//                 // Constrain any remaining Horizontal movement to the parent navigation rink
//                 if (parent)
//                 {
//                     // compute the next desired location
//                     Vector3 NextPosition = pathPos + pathMovement;
//                     NavigationCell* NextCell;
// 
//                     // test location on the NavigationMesh and resolve collisions
//                     parent->ResolveMotionOnMesh(pathPos, currentCell, NextPosition, &NextCell);
//                     pathPos = NextPosition;
//                     currentCell = NextCell;
//                     //controller->SetCenter(pathPos);	// this is only for height adjustment
//                 }
//             }
//             else if (pathActive)
//             {
//                 // If we have no remaining movement, but the path is active,
//                 // we have arrived at our desired waypoint.
//                 // Snap to it's position and figure out where to go next
//                 pathPos = (*nextWaypoint).position;
//                 pathMovement = Vector3::Zero;
//                 distance = 0.0f;
//                 //lastWaypoint = nextWaypoint;
//                 nextWaypoint = path.GetFurthestVisibleWayPoint(nextWaypoint);
// 
//                 // if we have no more waypoints, Stop seeking and nav
//                 if (nextWaypoint == path.WaypointList().end())
//                 {
//                     pathActive = false;
//                     pathMovement = Vector3::Zero;
//                     bot->GetSteering()->SeekOff();
//                 }
//                 else
//                 {
//                     bot->GetSteering()->SetTarget(Vector2((*nextWaypoint).position.X, (*nextWaypoint).position.Z));
//                     bot->GetSteering()->SeekOn();
//                 }
// 
// 
//             } // else if (pathActive)
//         
//         }

        void PathPlanner::Draw(const DrawArgs& args)
        {
            NavigationPath::WAYPOINT_LIST::const_iterator iter = path.WaypointList().begin();
            if (iter != path.WaypointList().end())
            {
                NavigationPath::WAYPOINT LastWaypoint = *iter;
                ++iter;
                for (;iter != path.WaypointList().end();++iter)
                {
                    const NavigationPath::WAYPOINT& waypoint= *iter;

                    Vector3 last = Vector3(LastWaypoint.position.X, 
                        LastWaypoint.position.Y + 0.1f, 
                        LastWaypoint.position.Z);
                    Vector3 curr = Vector3(waypoint.position.X, 
                        waypoint.position.Y + 0.1f,
                        waypoint.position.Z);

                    args.Graphics->DrawLine(last, curr, Color::Green);

                    LastWaypoint = waypoint;
                }
            }

//             // draw current heading
//             if (pathActive)
//             {
//                // const NavigationPath::WAYPOINT& waypoint = *nextWaypoint;
//                 //Vector3 start(pathPos.X, pathPos.Y + 0.1f, pathPos.Z);
//                 //Vector3 wp(waypoint.position.X, waypoint.position.Y + 0.1f, waypoint.position.Z);
// 
//                 //args.Graphics->DrawLine(start, wp, Color(1, 1, 1, 1));
//             }

        }


    }
}