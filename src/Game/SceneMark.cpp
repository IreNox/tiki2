
#include "Game/SceneMark.h"

#include "Core/LibraryManager.h"
#include "Core/IPhysicsMaterial.h"
#include "Core/CameraObject.h"

#include "Core/IPhysics.h"
#include "Core/ISpriteBatch.h"
#include <sstream>

#include "Core/IGraphics.h"
#include "Core/MeshIndexed.h"
#include "Core/LightObject.h"

#include "Game/Utils.h"



#include <ppl.h>
using namespace Concurrency;

namespace TikiEngine
{
	namespace Game
	{
		using namespace TikiEngine::Objects;
		using namespace TikiEngine::Scripts;
		using namespace TikiEngine::Resources;

		SceneMark::SceneMark(Engine* engine)
			: Scene(engine)
		{
			state = new GameState(engine, 0);

			showNaviMesh = true;
			drawCellSpace = false;

			octTable = 0;
			triIdxTable = 0;
			drawIdx = 0;

			showTree = 0;

		}

		SceneMark::~SceneMark()
		{
			SafeRelease(&kinematicBox);
			SafeRelease(&staticBox);
			SafeRelease(&dynamicBox);
			SafeRelease(&triggerSphere);
			SafeRelease(&controller);
			SafeRelease(&material);
		


			SafeRelease(&bot);

			SafeRelease(&fly);
			SafeRelease(&font);
			

			
			SafeDelete(&naviMesh);
			//SafeDelete(&tree);

			SafeRelease(&state);

		}

		void SceneMark::Initialize(const InitializationArgs& args)
		{
			// Create a test navigation mesh
			naviMesh = new NavigationMesh(engine);

			// make sure we are witin positive X-Z space else Cellspace won't work!
			Matrix m = Matrix::CreateTranslation(128, 0, 128);
			naviMesh->Load(L"NavMesh_Pitch", m);

			// Create TikiBot, set steering, add to cellspace and entitymgr
			GameObject* go = new GameObject(engine);
			bot = new TikiBot(state, go);
			bot->CreateNav(naviMesh, 0);
			//cellSpace->AddEntity(bot);
			// TODO: state->GetEntityMgr()->RegisterEntity(bot);
			this->AddElement(go);
			go->Release();

			// Create static Octree for NavMesh triangles and get the tables
			tree = new OcTree(engine);
			int totalCells = naviMesh->TotalCells();
			
			for (int i = 0; i < totalCells; i++)
			{
				NavigationCell* cell = naviMesh->Cell(i);
				for(int j = 0; j < 3; j++)
				{
					tris[i].Pt[j] = cell->Vertex(j);
					tris[i].UserData = (void*) cell;
				}

			}
			tree->Create(&tris[0], totalCells, 32);
			tree->GetTables(&octTable, &octCount, &triIdxTable, &triIdxCount);

			//IPhysicsMaterial* material; 
			material = engine->librarys->CreateResource<IPhysicsMaterial>();
			material->SetRestitution(0.7f);
			material->SetDynamicFriction(0.7f);
			material->SetStaticFriction(0.5f); // static friction may be higher than 1.

			// Init Colliders
			// by default these can be set to static or dynamic objects
			// every time we change static to dynamic, or center/size, we recreate the Actor.
			// When recreating, the class also keeps track if the Collider was a trigger
			// and raises the flags respectively.
			go = new GameObject(engine);
			dynamicBox = engine->librarys->CreateComponent<IBoxCollider>(go);
			dynamicBox->SetMaterial(material->GetIndex()); // 0 = default material	
			dynamicBox->SetCenter(Vector3(10, 10, 20));
			dynamicBox->SetSize(Vector3(1, 1, 1));
			dynamicBox->SetDynamic(true);
			// assign collision groups after object is created, else it won't work!
			dynamicBox->SetGroup(CG_Collidable_Pushable);
			this->AddElement(go);
			go->Release();

			// init box plane
			go = new GameObject(engine);
			staticBox = engine->librarys->CreateComponent<IBoxCollider>(go);
			staticBox->SetMaterial(material->GetIndex()); // 0 = default material	
			staticBox->SetCenter(Vector3(128, 5, 128));
			staticBox->SetSize(Vector3(128, 1, 128));
			staticBox->SetDynamic(false);
			staticBox->SetGroup(CG_Collidable_Non_Pushable);
			this->AddElement(go);
			go->Release();

			// Init kinematic actor
			go = new GameObject(engine);
			kinematicBox = engine->librarys->CreateComponent<IBoxCollider>(go);
			kinematicBox->SetMaterial(material->GetIndex()); // 0 = default material	
			kinematicBox->SetCenter(Vector3(10, 30, 10));
			kinematicBox->SetSize(Vector3(1, 1.5, 1));
			kinematicBox->SetDynamic(true);
			kinematicBox->GetRigidBody()->SetKinematic(true);
			this->AddElement(go);
			go->Release();

			// init static sphere trigger 
			go = new GameObject(engine);
			triggerSphere = engine->librarys->CreateComponent<ISphereCollider>(go);
			triggerSphere->SetMaterial(material->GetIndex()); // 0 = default material	
			triggerSphere->SetCenter(Vector3(3, 20, 10));
			triggerSphere->SetRadius(1.0f);
			triggerSphere->SetDynamic(false);
			triggerSphere->SetTrigger(true);
			triggerSphere->SetGroup(CG_Collidable_Non_Pushable);
			this->AddElement(go);
			go->Release();

			// init CharacterController
			go = new GameObject(engine);
			controller = engine->librarys->CreateComponent<ICharacterController>(go);
			controller->SetCenter(Vector3(10, 10, 10));
			controller->SetRadius(0.25f);
			controller->SetHeight(1.0f);
			controller->SetSlopeLimit(45.0f);
			controller->SetStepOffset(0.5f);
			controller->SetGroup(CG_Collidable_Pushable);
			this->AddElement(go);
			go->Release();




			go = new CameraObject(engine);
			go->PRS.SPosition() = Vector3(0, 20, 50);
			//go->PRS.Rotation = Quaternion::CreateFromYawPitchRoll(3.14159f, 0, 0);
			
			fly = new CameraFly(engine, go);
			
			this->AddElement(go);
			go->Release();


			font = engine->librarys->CreateResource<IFont>();
			font->Create(L"Arial", 10);



			// Test if the box is dynamic to move it around
			if (dynamicBox->GetDynamic())
			{
				// set some mass, this won't affect kinematic actors.
				dynamicBox->GetRigidBody()->SetMass(5);
				//assert(box->GetRigidBody()->GetMass() == 5);

				// give this tiny box a force pointing upwards
				dynamicBox->GetRigidBody()->SetVelocity(Vector3(0, 11, 0));

				// and set an angular velocity on the Y-Axis
				dynamicBox->GetRigidBody()->SetAngularVelocity(Vector3(0, 5, 0));
			}

			Scene::Initialize(args);
		}

		void SceneMark::Draw(const DrawArgs& args)
		{
			#if _DEBUG
			// Draw Mouse Ray
		    Vector3 forwardCam = fly->GetGameObject()->PRS.GPosition() + fly->GetGameObject()->PRS.GetForward();
		    engine->graphics->DrawLine(forwardCam, forwardCam + dir * 100.0f, Color::Red);
			engine->graphics->DrawLine(forwardCam, impact, Color::Green);

			// Draw bot Velocity
			Vector3 botPos = bot->GetGameObject()->PRS.GPosition();
			Vector3 heading = Vector3(bot->Heading().X, 0, bot->Heading().Y);
			engine->graphics->DrawLine(botPos + heading, botPos, Color::Green);


			// Draw some debug text
			std::wostringstream s;
			s << "ControllerPos (" << botPos.X << ", " << botPos.Y  << ", " << botPos.Z << ")";
			wstring str = s.str();
			engine->sprites->DrawString(font, str, Vector2(1, 80));

			std::wostringstream s3;
			Vector3 camPos = fly->GetGameObject()->PRS.GPosition();
			s3 << "Cam Pos" << camPos.X << ", " << camPos.Y << ", " << camPos.Z;
			str = s3.str();
			engine->sprites->DrawString(font, str, Vector2(1, 120));


			if (showNaviMesh)
				naviMesh->Draw(args);

			tree->DrawDebug();

			int idx = drawIdx;
			// draw the whole tree
			if (showTree)
			{
				for (int i = 0; i < octCount; i++)
					octTable[i].BBox->DrawDebug(Color::White);
			}
			// Draw one node with its neighbors and tris
			else
			{
				// Draw Neighbors
				for (int i = 0; i < NUM_NEIGHBORS; i++)
				{
					if (octTable[idx].NeighborIdx[i] != NULL_NODE)
						octTable[octTable[idx].NeighborIdx[i]].BBox->DrawDebug(Color::Red);
				}

				// Draw Box
				octTable[idx].BBox->DrawDebug(Color::White);

			}

			// Draw triangles
			int start = octTable[idx].TriIdxStart;
			int end = octTable[idx].TriIdxStart + octTable[idx].TriIdxCount;
			for (int i = start; i < end; i++)
			{
				unsigned int triIdx = triIdxTable[i];
				for (int i = 0; i < 3; i++)
				{
					Vector3 start = tris[triIdx].Pt[i];
					Vector3 end = tris[triIdx].Pt[(i + 1) % 3];
					NavigationCell* cell = (NavigationCell*)tris[triIdx].UserData;
					engine->graphics->DrawLine(start, end, Color::Blue);
				}

			}


			engine->physics->DrawDebug();




			#endif




			Scene::Draw(args);
		}

		void SceneMark::Update(const UpdateArgs& args)
		{
			//parallel_invoke(
			//	[=](){ cellSpace->UpdateEntity(bot, Vector2::Zero); },
			//	[=](){ Vector2::Zero; }
			//);

			// TODO: PositionToIndex(Vector3 pos)
			Vector3 testPos = bot->Pos3D();
			for (int idx = 1; idx < octCount - 1; idx++)
			{
				if (octTable[idx].BBox->Contains(testPos))
					drawIdx = idx;
			}
			// = foundIdx;


			if (args.Input.GetKeyPressed(KEY_F5))
			{
				showTree = 0;
				if (drawIdx < octCount - 1)
					drawIdx++;
			}

			if (args.Input.GetKeyPressed(KEY_F6))
			{
				showTree = 0;
				if (drawIdx > 0)
					drawIdx--;
			}

			if (args.Input.GetKeyPressed(KEY_F7))
			{
				showTree = 1;
				drawIdx = 0;
			}

			// Update Controller movement
			Vector3 displacement(0, -9.8f, 0);
			if (args.Input.GetKey(KEY_I))
				displacement -= Vector3(0, 0, 1);
			if (args.Input.GetKey(KEY_K))
				displacement += Vector3(0, 0, 1);
			if (args.Input.GetKey(KEY_J))
				displacement -= Vector3(1, 0, 0);
			if (args.Input.GetKey(KEY_L))
				displacement += Vector3(1, 0, 0);
			if (args.Input.GetKey(KEY_SPACE))
				controller->SetCenter(Vector3(0, 2, 0));

			// we can also determine which parts of the collider collided with another one.
			CollisionFlags cf;
			cf = controller->Move(displacement * (float)args.Time.ElapsedTime);
			bool isGrounded = (cf & CF_Down) != 0;
			bool collidedSides = (cf & CF_Sides) != 0;
			bool collidedAbove = (cf & CF_Up) != 0;

			// if it is dynamic and also kinematic, use following functions to move/rotate:
			// PhysX does its rotations in a right-handed manner. 
			//box->GetRigidBody()->MoveRotation(q3 * q2 * q1); // rotating objects araound the global axes
			//box->GetRigidBody()->MoveRotation(q1 * q2 * q3); // rotating objects around the local axes
			if (kinematicBox->GetDynamic() && 
				kinematicBox->GetRigidBody()->GetKinematic())
			{
				kinematicBox->GetRigidBody()->MoveRotation(Quaternion::CreateFromYawPitchRoll(0, 0, (float)args.Time.ElapsedTime));
			}

		    // Right Mouse - Raycast Test + Movement
			if(args.Input.GetMousePressed(MB_Left))
		    {
				
				Vector2 absMouse = engine->graphics->GetViewPort()->ToPixelCoord(args.Input.MousePosition);
		    
				Ray ray = fly->GetGameObject()->GetComponent<Camera>()->ScreenPointToRay(absMouse);
				orig = ray.Origin;
				dir = ray.Direction;
				RaycastHit info;

				if (engine->physics->RayCast(ray, &info))
				{
					// 
					ICollider* coll = info.Collider;
					if (coll)
					{
						if(coll->GetDynamic())
						{
						   coll->GetRigidBody()->SetVelocity(Vector3(0, 10, 0));
						   coll->GetRigidBody()->SetAngularVelocity(Vector3(5, 10, 0));
						}
					}
						
					// get the impact point and activate bot movement
					impact = info.Point;
					bot->GotoLocation(impact);
				}
		     }

			// F2 - Navigation Test
			if (args.Input.GetKeyPressed(KEY_F2))
				showNaviMesh = !showNaviMesh;

			// F5/F6 - Cellspace debug drawing
			if (args.Input.GetKey(KEY_F5))
				drawCellSpace = true; 
			else if (args.Input.GetKey(KEY_F6))
				drawCellSpace = false; 



			// Update base
			Scene::Update(args);
		}
	}
}
