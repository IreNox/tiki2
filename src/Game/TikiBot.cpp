#include "Game/TikiBot.h"

#include "Core/LibraryManager.h"
#include "Core/TypeGlobals.h"
#include "Core/IGraphics.h"

#include "Game/GoalThink.h"

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
			status = alive; //spawning;
			possessed = false;
			fieldOfView = DegsToRads(180);

			// TODO: game types
			//SetEntityType(type_bot);

			// a bot starts off facing in the direction it is heading
			facing = heading;

			// Create steering behavior
			steering = new TikiSteering(this);

			// init CharacterController
			controller = engine->librarys->CreateComponent<ICharacterController>(gameObject);
			controller->SetCenter(Pos3D());
			controller->SetRadius((float)boundingRadius);
			controller->SetHeight(1.0f);
			controller->SetSlopeLimit(45.0f);
			controller->SetStepOffset(0.5f);
			controller->SetGroup(CG_Collidable_Pushable);
			controller->AddRef();

			// Create the goal queue
			brain = new GoalThink(this);
			brain->RemoveAllSubgoals();
			// we must always have a goal in our brain
			brain->AddGoalWander();
			brain->AddGoalSeek(Vector2(50, 50));


			// Navigation
			pathActive = false;
			currentCell = 0;
			pathMovement = Vector3::Zero;
			pathPos = Vector3::Zero;
		}

		TikiBot::~TikiBot()
		{

			SafeDelete(&brain);

			SafeRelease(&controller);
			
			SafeDelete(&steering);
		}

		bool TikiBot::IsAtPosition(Vector2 pos)
		{
			const static float tolerance = 2.0f;
			return Vector2::DistanceSquared(Pos(), pos) < tolerance;
		}

		void TikiBot::CreateNav(NavigationMesh* par, NavigationCell* currCell)
		{
			parent = par;
			pathPos = Pos3D();
			currentCell = currCell;
			pathMovement = Vector3::Zero;

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

		void TikiBot::GotoLocation(const Vector3& p)
		{
			if (parent)
			{
				// find the closest target cell we will move to
				NavigationCell* endCell = parent->FindClosestCell(p);

				// if we have no closest cell found at the given targetPosition,
				// we didn't click on any or near a navigation Cell, so just return
				if (!endCell)
					return;

				// don't move if we have a position which is not in navMesh
				if(!endCell->IsPointInCellCollumn(p))
					return;

				// snap point to cell so we don't freak out! no need checked point?
				Vector3 targetPos = parent->SnapPointToCell(endCell, p);

				// Check if needed!
				currentCell = parent->FindClosestCell(Pos3D());

				// if we can see the target, just use steering, else use A*
				if (parent->LineOfSightTest(currentCell, Pos3D(), endCell, p))
				{
					// stop Navigation and seek
					pathActive = false;
					pathMovement = Vector3::Zero;
					steering->SeekOff();
					steering->SetTarget(Vector2(p.X, p.Z));
					steering->ArriveOn();
				}
				else
				{
					steering->ArriveOff();
					GotoLocation(p, endCell);
				}
			}
		}


		void TikiBot::Draw(const DrawArgs& args)
		{
			// connect the waypoins to draw lines in green
			#if _DEBUG
			if (!gameState->DrawNavMesh) return;

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

			brain->Draw(args);


			#endif
		}

		void TikiBot::Update(const UpdateArgs& args)
		{
			// process the currently active goal. Note this is required even if the bot
			// is under user control. This is because a goal is created whenever a user 
			// clicks on an area of the map that necessitates a path planning request.
			//brain->AddGoalWander();
			brain->Process();
			//brain->AddGoalWander();

			// Update navigation
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

			if (velocity != Vector2::Zero)
			{
				gameObject->PRS.SRotation() = Quaternion::CreateFromYawPitchRoll(
					(3.14159f - atan2(velocity.Y, velocity.X)) - (3.14159f / 2), 0, 0
				);

				if (gameObject->GModel()) gameObject->GModel()->SetAnimationSpeed(Vector2::Normalize(velocity).Length());
			}
			else
			{
				if (gameObject->GModel()) gameObject->GModel()->SetAnimationSpeed(0);
			}

			//calculate the acceleration
			Vector2 accel = force / (float)mass;

			//update the velocity
			velocity += accel;

			//make sure vehicle does not exceed maximum velocity
			velocity.Truncate((float)maxSpeed);

			// Move the controller and set some gravity
			Vector3 displacement(velocity.X,
								 0, //-9.81f, 
								 velocity.Y); 
			controller->Move(displacement * (float)args.Time.ElapsedTime);

			//if the vehicle has a non zero velocity the heading and side vectors must be updated
			if (!velocity.IsZero())
			{    
				heading = Vector2::Normalize(velocity);
				side = heading.Cross();
			}

			// Update the current cell if collider moved and the path is not active
			if (!pathActive)
			{
				NavigationCell* NextCell;
				Vector3 endPos = Pos3D() + Vector3(force.X, 0, force.Y);
				parent->ResolveMotionOnMesh(Pos3D(), currentCell, endPos, &NextCell);
				currentCell = NextCell;
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
			else
			{
				// apply some friction to our current movement (if any)
				pathMovement.X *= 0.75f;
				pathMovement.Y *= 0.75f;
				pathMovement.Z *= 0.75f;
			}

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
				pathMovement = Vector3::Zero;
				distance = 0.0f;
				lastWaypoint = nextWaypoint;
				nextWaypoint = path.GetFurthestVisibleWayPoint(nextWaypoint);

				// if we have no more waypoints, Stop seeking and nav
				if (nextWaypoint == path.WaypointList().end())
				{
					pathActive = false;
					pathMovement = Vector3::Zero;
					steering->SeekOff();
				}
				else
				{
					steering->SetTarget(Vector2((*nextWaypoint).position.X, (*nextWaypoint).position.Z));
					steering->SeekOn();
				}


			} // else if (pathActive)
		}

	}
}
