#include "Game/TikiBot.h"

#include "Core/LibraryManager.h"
#include "Core/TypeGlobals.h"
#include "Core/IGraphics.h"

namespace TikiEngine
{
	namespace AI
	{
		using namespace TikiEngine::Components;

		TikiBot::TikiBot(GameState* gameState, GameObject* gameObject) 
			: MovingEntity(gameState, gameObject)
		{

			// Init MovingEntity stats
			Init();

			// Init bot attributes
			maxHealth = 100;
			health = maxHealth;

			numUpdatesHitPersistant = 12; //(int) (60 * 0.2);
			hit = false;
			score = 0;
			status = spawning;
			possessed = false;
			fieldOfView = DegsToRads(180);

			// TODO: game types
			//SetEntityType(type_bot);

			// a bot starts off facing in the direction it is heading
			facing = heading;

			steering = new TikiSteering(this);

			// init CharacterController
			controller = engine->librarys->CreateComponent<ICharacterController>(gameObject);
			controller->SetCenter(Pos3D());
			controller->SetRadius((float)boundingRadius);
			controller->SetHeight(1.0f);
			controller->SetSlopeLimit(45.0f);
			controller->SetStepOffset(0.5f);
			controller->SetGroup(CG_Collidable_Pushable);

			// Navigation
			pathActive = false;
			currentCell = 0;
			pathMovement = Vector3::Zero;
			pathPos = Vector3::Zero;
		}

		TikiBot::~TikiBot()
		{
			SafeRelease(&controller);
			delete steering;
		}

		void TikiBot::CreateNav(NavigationMesh* par, NavigationCell* currCell)
		{
			parent = par;
			pathPos = Pos3D();
			currentCell = currCell;

			pathMovement = Vector3::Zero;
			//geometry.clear();

			if (parent)
			{

				// if no starting cell is provided, find one by searching the mesh
				if (!currentCell)
				{
					currentCell = parent->FindClosestCell(pathPos);
				}

				// make sure our position is within the current cell
				pathPos = parent->SnapPointToCell(currentCell, pathPos);
				controller->SetCenter(pathPos);
			}
		}




		inline void TikiBot::GotoLocation(const Vector3& p, NavigationCell* cell)
		{
			if (parent)
			{
				pathMovement = Vector3::Zero;
				pathPos = Pos3D();
				pathActive = parent->BuildNavigationPath(path, currentCell, pathPos, cell, p);

				if(pathActive)
				{
					nextWaypoint = path.WaypointList().begin();
				}
			}
		}
		void TikiBot::GotoRandomLocation()
		{
			if (parent)
			{
				// pick a random cell and go there
				int index = rand() % parent->TotalCells();
				NavigationCell* pCell = parent->Cell(index);

				GotoLocation(pCell->CenterPoint(), pCell);
			}
		}


		void TikiBot::Draw(const DrawArgs& args)
		{
			// connect the waypoins to draw lines in green
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
					engine->graphics->DrawLine(last, curr, Color::Green);

					LastWaypoint = waypoint;
				}
			}

			// draw current heading
			if (pathActive)
			{
				const NavigationPath::WAYPOINT& waypoint = *nextWaypoint;


				Vector3 start(pathPos.X, pathPos.Y + 0.1f, pathPos.Z);
				Vector3 wp(waypoint.position.X, waypoint.position.Y + 0.1f, waypoint.position.Z);
				engine->graphics->DrawLine(start, wp, Color(1, 1, 1, 1));
			}
		}

		void TikiBot::Update(const UpdateArgs& args)
		{

			
			UpdateNavigation(args);

			//Calculate the steering force and update the bot's velocity and position
			UpdateMovement(args);


			
		}


		void TikiBot::UpdateMovement(const UpdateArgs& args)
		{
			// calculate the combined steering force
			Vector2 force = steering->Calculate();

			// if no steering force is produced decelerate the player by applying a braking force
			if (steering->Force().IsZero())
			{
				const float BrakingRate = 0.8f;
				velocity = velocity * BrakingRate;
			}

			//calculate the acceleration
			Vector2 accel = force / (float)mass;

			//update the velocity
			velocity += accel;

			//make sure vehicle does not exceed maximum velocity
			velocity.Truncate((float)maxSpeed);

			// Move the controller and set some gravity
			Vector3 displacement(velocity.X,
								 0,	// -9.81f 
								 velocity.Y); 
			controller->Move(displacement * (float)args.Time.ElapsedTime);

			//if the vehicle has a non zero velocity the heading and side vectors must be updated
			if (!velocity.IsZero())
			{    
				heading = Vector2::Normalize(velocity);

				side = heading.Cross();
			}

		}

		void TikiBot::UpdateNavigation(const UpdateArgs& args)
		{
			float distance;
			float max_distance = (float)(maxSpeed * args.Time.ElapsedTime);

			// if we have no parent mesh, return. We are simply a static object.
			if (!parent)
				return;

			// Figure out where we are going
			if (pathActive)
			{
				// Move along the waypoint path
				if (nextWaypoint != path.WaypointList().end())
				{
					// determine our desired movement vector
					pathMovement = (*nextWaypoint).position;
					pathMovement -= pathPos;
				}
				else
				{
					// we have reached the end of the path
					pathActive = false;
					pathMovement = Vector3::Zero;
				}
			}

			// Adjust Movement

			// scale back movement by our max speed if needed
			distance = pathMovement.LengthSquared();
			if (distance > max_distance * max_distance)
			{
				pathMovement = Vector3::Normalize(pathMovement);
				pathMovement = pathMovement * max_distance;
			}

			// come to a full stop when we go below a certain threshold
		    if (fabs(pathMovement.X) < 0.005f) pathMovement.X = 0.0f;
			if (fabs(pathMovement.Y) < 0.005f) pathMovement.Y = 0.0f;
			if (fabs(pathMovement.Z) < 0.005f) pathMovement.Z = 0.0f;


			// Constrain any remaining Horizontal movement to the parent navigation rink
			if (pathMovement.X || pathMovement.Z)
			{
				// Constrain any remaining Horizontal movement to the parent navigation rink
				if (parent)
				{
					// compute the next desired location
					Vector3 NextPosition = pathPos + pathMovement;
					NavigationCell* NextCell;

					// test location on the NavigationMesh and resolve collisions
					parent->ResolveMotionOnMesh(pathPos, currentCell, NextPosition, &NextCell);
					pathPos = NextPosition;
					currentCell = NextCell;
					controller->SetCenter(pathPos);	// this is only for height adjustment
				}
			}
			else if (pathActive)
			{
				// If we have no remaining movement, but the path is active,
				// we have arrived at our desired waypoint.
				// Snap to it's position and figure out where to go next
				pathPos = (*nextWaypoint).position;
				//controller->SetCenter(pathPos);
				pathMovement = Vector3::Zero;
				distance = 0.0f;
				lastWaypoint = nextWaypoint;
				nextWaypoint = path.GetFurthestVisibleWayPoint(nextWaypoint);
				

				// if we have no more waypoints, Stop arriving
				if (nextWaypoint == path.WaypointList().end())
				{
					steering->SeekOff();
					pathActive = false;
					pathMovement = Vector3::Zero;
				}
				else
				{
					// only set some target if the nextWaypoint changed
					if (nextWaypoint != lastWaypoint)
					{
						steering->SetTarget(Vector2((*nextWaypoint).position.X, (*nextWaypoint).position.Z));
						if (!steering->SeekIsOn()) steering->SeekOn();	
					}

					// Override seek with arrive
					//if (nextWaypoint == --path.WaypointList().end())
					//{
					//	if (steering->SeekIsOn()) steering->SeekOff();	
					//	steering->SetTarget(Vector2((*nextWaypoint).position.X, (*nextWaypoint).position.Z));
					//	steering->ArriveOn();
					//}

				} // else
				 
			} // else if (pathActive)
		}

	}
}