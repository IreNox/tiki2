
#include "Game/SceneMark.h"

#include "Core/LibraryManager.h"
#include "Core/IPhysicsMaterial.h"
#include "Core/CameraObject.h"

#include "Core/IPhysics.h"
#include "Core/ISpriteBatch.h"
#include <sstream>

#include "Core/IGraphics.h"

#include <ppl.h>
using namespace Concurrency;

namespace TikiEngine
{
	namespace Game
	{
		using namespace TikiEngine::Objects;
		using namespace TikiEngine::Scripts;

		// Geometry
		#pragma region Map
		unsigned long map_totalpoints = 77;  

		Vector3 map_points[] =   
		{  
			Vector3(-41.4328f, 40.0000f, 24.0671f),  
			Vector3(-23.1315f, 40.0000f, 42.3684f),  
			Vector3(-23.1315f, 40.0000f, 92.3684f),  
			Vector3(-16.4328f, 40.0000f, 67.3684f),  
			Vector3(-66.4328f, 40.0000f, 17.3684f),  
			Vector3(-91.4328f, 40.0000f, 24.0671f),  
			Vector3(-109.7341f, 40.0000f, 42.3684f),  
			Vector3(-116.4328f, 40.0000f, 67.3684f),  
			Vector3(-109.7341f, 40.0000f, 92.3684f),  
			Vector3(-91.4328f, 40.0000f, 110.6697f),  
			Vector3(-66.4328f, 40.0000f, 117.3684f),  
			Vector3(-41.4328f, 40.0000f, 110.6697f),  
			Vector3(-40.4520f, 40.0000f, 82.3684f),  
			Vector3(-51.4328f, 40.0000f, 93.3492f),  
			Vector3(-66.4328f, 40.0000f, 97.3684f),  
			Vector3(-81.4328f, 40.0000f, 93.3492f),  
			Vector3(-92.4136f, 40.0000f, 82.3684f),  
			Vector3(-96.4328f, 40.0000f, 67.3684f),  
			Vector3(-92.4136f, 40.0000f, 52.3684f),  
			Vector3(-81.4328f, 40.0000f, 41.3876f),  
			Vector3(-66.4328f, 40.0000f, 37.3684f),  
			Vector3(-51.4328f, 40.0000f, 41.3876f),  
			Vector3(-40.4520f, 40.0000f, 52.3684f),  
			Vector3(-36.4328f, 40.0000f, 67.3684f),  
			Vector3(-56.5907f, 10.0000f, 67.1996f),  
			Vector3(-56.5907f, 10.0000f, 67.1996f),  
			Vector3(-81.4328f, 40.0000f, 93.3492f),  
			Vector3(-67.5715f, 10.0000f, 56.2188f),  
			Vector3(-67.5715f, 10.0000f, 56.2188f),  
			Vector3(-92.4136f, 40.0000f, 82.3684f),  
			Vector3(65.0024f, 5.7630f, -65.5516f),  
			Vector3(35.0030f, 5.7630f, -84.3647f),  
			Vector3(0.4275f, 5.7630f, -91.4832f),  
			Vector3(-33.1311f, 5.7630f, -83.8563f),  
			Vector3(-63.6390f, 5.7630f, -65.0431f),  
			Vector3(-83.9775f, 5.7630f, -36.0606f),  
			Vector3(-93.1299f, 5.7630f, -0.4682f),  
			Vector3(-88.0453f, 5.7630f, 20.3789f),  
			Vector3(-66.1813f, 5.7630f, 14.2773f),  
			Vector3(-52.4528f, 5.7630f, 18.3450f),  
			Vector3(-44.3174f, 5.7630f, 21.3958f),  
			Vector3(-60.0797f, 5.7630f, 41.7344f),  
			Vector3(-63.4004f, 5.7630f, 51.8567f),  
			Vector3(-52.4528f, 5.7630f, 62.7418f),  
			Vector3(-39.2327f, 5.7630f, 55.4629f),  
			Vector3(-19.4026f, 5.7630f, 43.2598f),  
			Vector3(-13.8095f, 5.7630f, 64.6152f),  
			Vector3(-19.4026f, 5.7630f, 89.0215f),  
			Vector3(0.4275f, 5.7630f, 92.0723f),  
			Vector3(36.0200f, 5.7630f, 84.4454f),  
			Vector3(65.5109f, 5.7630f, 66.6491f),  
			Vector3(85.8495f, 5.7630f, 34.6159f),  
			Vector3(93.4764f, 5.7630f, 0.5488f),  
			Vector3(86.3579f, 5.7630f, -35.0437f),  
			Vector3(86.3579f, 5.7630f, -35.0437f),  
			Vector3(63.9855f, 5.7630f, -21.8236f),  
			Vector3(41.1046f, 5.7630f, -18.7729f),  
			Vector3(63.4770f, 5.7630f, 3.0911f),  
			Vector3(49.2400f, 5.7630f, 25.9720f),  
			Vector3(27.3761f, 5.7630f, 36.1413f),  
			Vector3(0.4275f, 5.7630f, 35.6328f),  
			Vector3(-21.9449f, 5.7630f, 22.4127f),  
			Vector3(-33.6396f, 5.7630f, 3.0911f),  
			Vector3(-36.6904f, 5.7630f, -24.3660f),  
			Vector3(-23.4703f, 5.7630f, -45.2130f),  
			Vector3(0.4275f, 5.7630f, -59.9585f),  
			Vector3(26.3592f, 5.7630f, -59.9585f),  
			Vector3(19.2407f, 5.7630f, -37.5860f),  
			Vector3(6.5291f, 5.7630f, -38.0945f),  
			Vector3(-5.1656f, 5.7630f, -30.4675f),  
			Vector3(-11.7756f, 5.7630f, -18.2644f),  
			Vector3(-11.2672f, 5.7630f, -5.0443f),  
			Vector3(-4.1487f, 5.7630f, 7.6673f),  
			Vector3(6.0206f, 5.7630f, 14.2773f),  
			Vector3(20.2576f, 5.7630f, 14.7858f),  
			Vector3(32.4607f, 5.7630f, 7.6673f),  
			Vector3(39.0708f, 5.7630f, -3.0105f),  
		};  



		unsigned short map_polys[][3] =   
		{  
			{ 67, 68, 69},  
			{ 67, 69, 70},  
			{ 67, 70, 71},  
			{ 67, 71, 72},  
			{ 67, 72, 73},  
			{ 67, 73, 74},  
			{ 67, 74, 75},  
			{ 67, 75, 76},  
			{ 67, 76, 56},  
			{ 60, 61, 45},  
			{ 60, 45, 46},  
			{ 36, 37, 38},  
			{ 35, 36, 38},  
			{ 46, 47, 48},  
			{ 46, 48, 49},  
			{ 60, 46, 49},  
			{ 42, 43, 44},  
			{ 60, 49, 50},  
			{ 41, 42, 44},  
			{ 40, 41, 44},  
			{ 40, 44, 45},  
			{ 40, 45, 61},  
			{ 40, 61, 62},  
			{ 39, 40, 62},  
			{ 39, 62, 63},  
			{ 34, 35, 38},  
			{ 38, 39, 63},  
			{ 34, 38, 63},  
			{ 33, 34, 63},  
			{ 32, 33, 63},  
			{ 66, 67, 56},  
			{ 66, 56, 55},  
			{ 59, 60, 50},  
			{ 59, 50, 51},  
			{ 58, 59, 51},  
			{ 57, 58, 51},  
			{ 57, 51, 52},  
			{ 55, 57, 52},  
			{ 55, 52, 53},  
			{ 66, 55, 53},  
			{ 54, 30, 31},  
			{ 54, 31, 32},  
			{ 32, 63, 64},  
			{ 32, 64, 65},  
			{ 32, 65, 66},  
			{ 66, 53, 54},  
			{ 54, 32, 66},  
			{ 28, 24, 43},  
			{ 28, 43, 42},  
			{ 11, 2, 12},  
			{ 12, 2, 3},  
			{ 12, 3, 1},  
			{ 10, 11, 12},  
			{ 1, 0, 4},  
			{ 1, 4, 5},  
			{ 6, 7, 8},  
			{ 6, 8, 9},  
			{ 10, 12, 13},  
			{ 9, 10, 13},  
			{ 23, 12, 1},  
			{ 22, 23, 1},  
			{ 21, 22, 1},  
			{ 21, 1, 5},  
			{ 20, 21, 5},  
			{ 20, 5, 6},  
			{ 19, 20, 6},  
			{ 18, 19, 6},  
			{ 17, 18, 6},  
			{ 17, 6, 9},  
			{ 16, 17, 9},  
			{ 15, 16, 9},  
			{ 9, 13, 14},  
			{ 9, 14, 15},  
			{ 25, 27, 29},  
			{ 25, 29, 26},  
		};  


		unsigned long map_totalpolys = 75;
		#pragma endregion

		SceneMark::SceneMark(Engine* engine)
			: Scene(engine)
		{
			state = new GameState(engine);

			showNaviMesh = true;
			drawCellSpace = false;
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

			cellSpace->EmptyCells();
			delete cellSpace;

			EntityMgr->Dispose();
			
			SafeRelease(&state);
		}

		void SceneMark::Initialize(const InitializationArgs& args)
		{


			GameObject* go = new GameObject(engine);
			//TODO: EntityMgr->RegisterMovingEntity(go); //, desc
			//cellSpace = new CellSpacePartition<TikiBot*>(engine, 50.0f, 50.0f, 8, 8, 50); 
			cellSpace = new CellSpacePartition<TikiBot*>(engine, 256, 256, 10, 10, 10);
			
			// Create a test navigation mesh
			naviMesh.Clear();  
			for (UInt32 i = 0; i < map_totalpolys; ++i)
			{  

				Vector3 vertA = map_points[map_polys[i][0]];  
				Vector3 vertB = map_points[map_polys[i][1]];  
				Vector3 vertC = map_points[map_polys[i][2]];  

				Matrix m = Matrix::CreateTranslation(100, 0, 100);
				vertA = Vector3::TransformCoordinate(vertA, m);
				vertB = Vector3::TransformCoordinate(vertB, m);
				vertC = Vector3::TransformCoordinate(vertC, m);

				// some art programs can create linear polygons which have two or more  
				// identical vertices. This creates a poly with no surface area,  
				// which will wreak havok on our navigation mesh algorithms.  
				// We only except polygons with unique vertices.  
				if ((vertA != vertB) && (vertB != vertC) && (vertC != vertA))  
				{  
					naviMesh.AddCell(vertA, vertB, vertC);  
				}  
			}  
			naviMesh.LinkCells();

			// Create TikiBot, set steering, add to cellspace and entitymgr
			bot = new TikiBot(state, go);
			bot->CreateNav(&naviMesh, 0);

			cellSpace->AddEntity(bot);
			EntityMgr->RegisterEntity(bot);

			this->AddElement(go);
			go->Release();



			//IPhysicsMaterial* material; 
			//material = engine->content->LoadPhysicsMaterial(L"TODO");
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
			staticBox->SetCenter(Vector3(100, 5.2f, 100));
			staticBox->SetSize(Vector3(100, 0.1f, 100));
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
			go->PRS.Position() = Vector3(0, 20, 50);
			//go->PRS.Rotation = Quaternion::CreateFromYawPitchRoll(3.14159f, 0, 0);
			this->AddElement(go);
			go->Release();

			fly = new CameraFly(engine, go);

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
			// Draw Mouse Ray
		    Vector3 forwardCam = fly->GetGameObject()->PRS.Position() + fly->GetGameObject()->PRS.GetForward();
		    engine->graphics->DrawLine(forwardCam, forwardCam + dir * 100.0f, Color::Red);
			engine->graphics->DrawLine(forwardCam, impact, Color::Green);

			// Draw bot Velocity
			Vector3 botPos = Vector3(bot->GetGameObject()->PRS.Position());
			Vector3 heading = Vector3(bot->Heading().X, 0, bot->Heading().Y);
			engine->graphics->DrawLine(botPos + heading, botPos, Color::Green);


			// Draw some debug text
			std::wostringstream s;
			s << "ControllerPos (" << botPos.X << ", " << botPos.Y  << ", " << botPos.Z << ")";
			wstring str = s.str();
			engine->sprites->DrawString(font, str, Vector2(1, 80));

			std::wostringstream s3;
			Vector3 camPos = fly->GetGameObject()->PRS.Position();
			s3 << "Cam Pos" << camPos.X << ", " << camPos.Y << ", " << camPos.Z;
			str = s3.str();
			engine->sprites->DrawString(font, str, Vector2(1, 120));


			if (showNaviMesh)
				naviMesh.Draw(args);

			#if _DEBUG
			engine->physics->DrawDebug();
			if (drawCellSpace)
				cellSpace->RenderCells();
			#endif

			Scene::Draw(args);
		}

		void SceneMark::Update(const UpdateArgs& args)
		{
			cellSpace->CalculateNeighbors(bot->Pos(), 24);
			
			//parallel_invoke(
			//	[=](){ cellSpace->UpdateEntity(bot, Vector2::Zero); },
			//	[=](){ Vector2::Zero; }
			//);

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

		    // F1 - Raycast Test
		    if (args.Input.GetKey(KEY_F1))
		    {
				RaycastHit info;
				Vector2 absMouse = engine->graphics->GetViewPort()->ToPixelCoord(args.Input.MousePosition);
		    
				Ray ray = fly->GetGameObject()->GetComponent<Camera>()->ScreenPointToRay(absMouse);
		    
				orig = ray.Origin;
				dir = ray.Direction;
				

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

					// stop any steering or Navigation
					bot->GetSteering()->ArriveOff();
					bot->GetSteering()->SeekOff();
					bot->pathActive = false;
					bot->pathMovement = Vector3::Zero;
						
					// get the impact point and activate bot movement
					impact = info.Point;
					bot->GetSteering()->SetTarget(Vector2(impact.X, impact.Z));
					bot->GetSteering()->ArriveOn();
				}
		     }

			// F2 - Navigation Test
			if (args.Input.GetKey(KEY_F2))
				bot->GotoRandomLocation();

			// F5/F6 - Cellspace debug drawing
			if (args.Input.GetKey(KEY_F5))
				drawCellSpace = true; 
			else if (args.Input.GetKey(KEY_F6))
				drawCellSpace = false; 


			// Camera Frustum test
			//Camera* cam = fly->GetGameObject()->GetComponent<Camera>();
			//if (cam->GetFrustum()->BoxInFrustum(cellSpace->GetQuerybox()))
			//	OutputDebugString(L"cellSpace QueryBox InFrustum \n");
			//else if (cam->GetFrustum()->SphereInFrustum(bot->Pos3D(), (float)bot->BRadius()))
			//	OutputDebugString(L"Bot Sphere InFrustum \n");
			//else if (cam->GetFrustum()->PointInFrustum(Vector3::Zero) == Frustum::INSIDE)
			//	OutputDebugString(L"Point(0, 0, 0) In Frustum \n");
			//else
			//	OutputDebugString(L"No intersection \n");



			// Update base
			Scene::Update(args);
		}
	}
}
