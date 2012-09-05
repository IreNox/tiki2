#include "Physics/PhysicsModule.h"
#include "Physics/DllMain.h"

namespace TikiEngine
{
	namespace Modules
	{
		#pragma region Class
		PhysicsModule::PhysicsModule(Engine* engine)
			: IPhysics(engine)
		{
			pause = false;
			tikiEngine = engine;
		}

		PhysicsModule::~PhysicsModule()
		{
		}

		void PhysicsModule::Dispose()
		{
			if (physicsSDK != 0)
			{
				// release scene
				if (scene != 0)
					physicsSDK->releaseScene(*scene);
				scene = 0;

				// release SDK
				NxReleasePhysicsSDK(physicsSDK);
				physicsSDK = 0;
			}
		}
		#pragma endregion

		#pragma region Init
		bool PhysicsModule::Initialize(EngineDescription& desc)
		{
			Console::Write("Initializing");

			// init PhysX SDK
			NxPhysicsSDKDesc sdkDesc;
			//sdkDesc.flags &= ~NX_SDKF_NO_HARDWARE; // enables HardWare support
			NxSDKCreateError errorCode = NXCE_NO_ERROR;

			ErrorStream errorStream;
			physicsSDK = NxCreatePhysicsSDK(NX_PHYSICS_SDK_VERSION, NULL, &errorStream, sdkDesc, &errorCode);
			if (physicsSDK == 0)
			{
				Console::Write("Unable to initialize the PhysX SDK, exiting." + errorStream.GetNxSDKCreateError(errorCode));
				return false;
			}

			// Connect to the Visual Remote Debugger. The settings for the VRD host and port are found in VRDSettings.h
#if USE_VRD
			if (physicsSDK->getFoundationSDK().getRemoteDebugger())
				physicsSDK->getFoundationSDK().getRemoteDebugger()->connect(VRD_HOST, VRD_PORT, VRD_EVENTMASK);
#endif
			// Create the PhysX Scene and set the current one
			NxSceneDesc sceneDesc;
			sceneDesc.gravity = NxVec3(0.0f, -9.81f, 0.0f);
			scene = physicsSDK->createScene(sceneDesc);
			if (scene == NULL)
			{
				Console::Write("Error: Unable to create a PhysX scene, exiting. \n");
				return false;
			}

			// set some Visualization Flags, else debugRendering won't work.
#if _DEBUG
			physicsSDK->setParameter(NX_SKIN_WIDTH, 0.025f);
			physicsSDK->setParameter(NX_VISUALIZATION_SCALE, 1.0f);
			physicsSDK->setParameter(NX_VISUALIZE_COLLISION_SHAPES, 1);
			physicsSDK->setParameter(NX_VISUALIZE_ACTOR_AXES, 1);
			//physicsSDK->setParameter(NX_VISUALIZE_CONTACT_POINT, 1);
			//physicsSDK->setParameter(NX_VISUALIZE_CONTACT_NORMAL, 1);
			//physicsSDK->setParameter(NX_VISUALIZE_CONTACT_FORCE, 1);
			//physicsSDK->setParameter(NX_VISUALIZE_BODY_LIN_VELOCITY, 1);
			//physicsSDK->setParameter(NX_VISUALIZE_BODY_ANG_FORCE, 1);
#endif

			//bool hardware = IsHardwarePresent();
			// assign the scene and physX sdks to dllMain
			DllMain::Scene = scene;
			DllMain::PhysicsSDK = physicsSDK;

			// Create ground plane with material for testing
			NxPlaneShapeDesc planeDesc;
			NxActorDesc actorDesc;
			actorDesc.shapes.pushBack(&planeDesc);
			scene->createActor(actorDesc);

			return true;
		}
		#pragma endregion

		bool PhysicsModule::IsHardwarePresent()
		{
			return physicsSDK->getHWVersion() != NX_HW_VERSION_NONE;
		}

		NxScene* PhysicsModule::GetScene()
		{
			return scene; 
		}

		void PhysicsModule::Begin()
		{


		}

		void PhysicsModule::End()
		{

			if (scene && !pause)
			{
				// the new method to start the SDK
				scene->simulate(1.0f / 60.0f); 
				scene->flushStream();

				// in here we can do computations which depend only on the old state of the scene "actors". 
				// Writing to the scene is not allowed. Write calls in here are skipped.


				// method to sync with the SDK after it has finished.it waits (non)blocking for the end of a given NxSimulationStatus, 
				// if the end is reached it swaps the buffers, fires the callbacks and removes the writelock, 
				// if all simulations of the scene have reached its end. at the moment there is only a NX_RIGID_BODY_FINISHED status.
				scene->fetchResults(NX_RIGID_BODY_FINISHED, true);

				// we could also do this with non blocking calls
				//while(!scene->fetchResults(NX_RIGID_BODY_FINISHED, false))
				//{
				//     compute something till rigid body simulation has finished
				//}

			}

			// then we can use isWritable() to test if we fetched  all simulation results and made the scene writable again.
			// Since there is only one status flag it is obvious that we fetched everything and the scene is writable.
			NX_ASSERT(scene->isWritable());
		}

#pragma region Debug
#if _DEBUG
		void PhysicsModule::FillDebugMesh(Dictionary<PrimitiveTopologies, Mesh*>* list)
		{
			const NxDebugRenderable* debug = scene->getDebugRenderable();

			NxU32 i = 0;
			NxU32 count = debug->getNbPoints();
			if (count > 0)
			{
				Mesh* mesh = debugCheckMesh(list, PT_PointList);
				ColorVertex* vertices = new ColorVertex[count * 1];

				const NxDebugPoint* points = debug->getPoints();

				while (i < count)
				{
					UInt32 index = i * 2;
					const NxDebugPoint* point = points + i;

					debugFillVertex(vertices[index + 0], point->p, point->color);

					i++;
				}

				mesh->SetVertexData(vertices, sizeof(ColorVertex) * count);
				delete(vertices);
			}

			i = 0;
			count = debug->getNbLines();
			if (count > 0)
			{
				Mesh* mesh = debugCheckMesh(list, PT_LineList);
				ColorVertex* vertices = new ColorVertex[count * 2];

				const NxDebugLine* lines = debug->getLines();

				while (i < count)
				{
					UInt32 index = i * 2;
					const NxDebugLine* line = lines + i;

					debugFillVertex(vertices[index + 0], line->p0, line->color);
					debugFillVertex(vertices[index + 1], line->p1, line->color);

					i++;
				}

				mesh->SetVertexData(vertices, sizeof(ColorVertex) * count);
				delete(vertices);
			}

			i = 0;
			count = debug->getNbTriangles();
			if (count > 0)
			{
				Mesh* mesh = debugCheckMesh(list, PT_TriangleList);
				ColorVertex* vertices = new ColorVertex[count * 3];

				const NxDebugTriangle* triangles = debug->getTriangles();

				while (i< count)
				{
					UInt32 index = i * 2;
					const NxDebugTriangle* triangle = triangles + i;

					debugFillVertex(vertices[index + 0], triangle->p0, triangle->color);
					debugFillVertex(vertices[index + 1], triangle->p1, triangle->color);
					debugFillVertex(vertices[index + 2], triangle->p2, triangle->color);

					i++;
				}
			}
		}

		Mesh* PhysicsModule::debugCheckMesh(Dictionary<PrimitiveTopologies, Mesh*>* list, PrimitiveTopologies topology)
		{
			Mesh* mesh = 0;

			if (list->ContainsKey(topology))
			{
				mesh = list->Get(topology);
			}
			else
			{
				mesh = new Mesh(engine);
				mesh->SetVertexDeclaration(ColorVertex::Declaration, 2);
				mesh->SetPrimitiveTopology(topology);

				list->Add(topology, mesh);
			}

			return mesh;
		}

		void PhysicsModule::debugFillVertex(ColorVertex& vertex, const NxVec3& pos, const NxU32& color)
		{
			vertex.Position[0] = pos.x;
			vertex.Position[1] = pos.y;
			vertex.Position[2] = pos.z;
			vertex.Color[0]	= (float)((color>>16)&0xff)/255.0f;
			vertex.Color[1]	= (float)((color>>8)&0xff)/255.0f;
			vertex.Color[2]	= (float)(color&0xff)/255.0f;
			vertex.Color[3]	= 1.0f;
		}
#endif
#pragma endregion

	}
}