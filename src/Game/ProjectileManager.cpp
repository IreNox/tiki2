
#include "Game/ProjectileManager.h"
#include "Game/GameState.h"

#include "Core/IContentManager.h"

namespace TikiEngine
{
	namespace Game
	{
		#pragma region Class
		ProjectileManager::ProjectileManager(GameState* state)
			: GameObject(state->GetEngine()), gameState(state)
		{
			peAssault = new PEShootMG(engine);
			peAssault->AddRef();

			prAssault = engine->librarys->CreateComponent<IParticleRenderer>(this);
			prAssault->SetParticleEffect(peAssault);
			prAssault->SetTexture(engine->content->LoadTexture(L"particle/mg"));
			prAssault->AddRef();
		}

		ProjectileManager::~ProjectileManager()
		{
			UInt32 i = 0;
			while (i < projectiles.Count())
			{
				projectiles[i].proj->GetGameObject()->Release();
				i++;
			}

			SafeRelease(&peAssault);
			SafeRelease(&prAssault);
		}
		#pragma endregion

		#pragma region Member
		void ProjectileManager::AddProjectile(Projectile* proj)
		{
			ProjInfo i;
			i.proj = proj;
			peAssault->Allocate(&i.p1, &i.p2);

			projectiles.Add(i);
		}
		#pragma endregion
		
		#pragma region Member - Update
		void ProjectileManager::Update(const UpdateArgs& args)
		{
			UInt32 i = 0;
			while (i < projectiles.Count())
			{
				ProjInfo& pi = projectiles[i];

				pi.proj->Update(args);

				if (pi.proj->IsDead())
				{
					pi.p1->Position = Vector3::Zero;
					pi.p2->Position = Vector3::Zero;
					pi.proj->GetGameObject()->Release();
					projectiles.RemoveAt(i);
				}
				else
				{
					Vector3 pos = pi.proj->GetCollider()->GetCenter();
					Vector3 velo = Vector3::Normalize(pi.proj->GetCollider()->GetRigidBody()->GetVelocity()) * 1.75f;
					pi.p1->Position = pos - velo;
					pi.p2->Position = pos + velo;

					i++;
				}

				//GameObject* go = projectiles[i];

				//if (go != 0)
				//{
				//	go->Update(args);

				//	Projectile* p = go->GetComponent<Projectile>();
				//	if (p != 0 && p->IsDead())
				//	{
				//		projectiles.Remove(go);
				//		SafeRelease(&go);
				//	}
				//}
			}

			GameObject::Update(args);
		}
		#pragma endregion
	}
}