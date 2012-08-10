
#include "Core/DebugPhysicsRenderer.h"

#include "Core/IPhysics.h"
#include "Core/IContentManager.h"
#include "Core/LibraryManager.h"

namespace TikiEngine
{
	namespace Objects
	{
		DebugPhysicRenderer::DebugPhysicRenderer(Engine* engine)
			: GameObject(engine), renderer()
		{
			renderer.Add(PT_LineList, engine->librarys->CreateComponent<IMeshRenderer>(this));
			renderer.Add(PT_PointList, engine->librarys->CreateComponent<IMeshRenderer>(this));
			renderer.Add(PT_TriangleList, engine->librarys->CreateComponent<IMeshRenderer>(this));

			Material* mat = engine->content->LoadMaterial(L"Data\\Effects\\os_color.fx");

			List<IMeshRenderer*> values = renderer.GetValues();

			UInt32 i = 0;
			while (i < values.Count())
			{
				values[i]->SetMaterial(mat);

				i++;
			}
		}

		DebugPhysicRenderer::~DebugPhysicRenderer()
		{
		}

		void DebugPhysicRenderer::Draw(const DrawArgs& args)
		{
			List<IMeshRenderer*> values = renderer.GetValues();
		
			UInt32 i = 0;
			while (i < values.Count())
			{
				values[i]->Draw(args);

				i++;
			}
		}

		void DebugPhysicRenderer::Update(const UpdateArgs& args)
		{
			engine->physics->FillDebugMesh(&meshes);
			
			List<PrimitiveTopologies> keys = meshes.GetKeys();

			UInt32 i = 0;
			while (i < keys.Count())
			{
				IMeshRenderer* render = renderer.Get(keys[i]);

				render->SetMesh(meshes.Get(keys[i]));
				render->Update(args);

				i++;
			}
		}
	}
}