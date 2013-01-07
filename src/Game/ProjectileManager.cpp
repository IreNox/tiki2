
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

            // Fire
            peFire = new PEFire(engine);
            peFire->SIsAlive(false);
            peFire->AddRef();

            prFire = engine->librarys->CreateComponent<IParticleRenderer>(this);
            prFire->SetTexture(engine->content->LoadTexture(L"particle/fire"));
            prFire->SetParticleEffect(peFire);
            prFire->AddRef();

            // Smoke
//             smokeEmitter = new GameObject(engine);
//             smokeEmitter->PRS.SPosition() = Vector3(0, 0, 0);
//             smokeEmitter->PRS.SScale() = Vector3(0.01f);
// 
//             smokeEffect = new PESmoke(engine);
//             smokeEffect->SIsAlive(false);

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

            SafeRelease(&peFire);
            SafeRelease(&prFire);
		}
		#pragma endregion

		#pragma region Member
		void ProjectileManager::AddProjectile(Projectile* proj)
		{
			ProjInfo i;
			i.proj = proj;

            if (proj->GetProjectileType() == PT_Bullet)
            {
                peAssault->Allocate(&i.p1, &i.p2);
            }
            else if (proj->GetProjectileType() == PT_Rocket)
            {
                i.p1 = 0;
                i.p2 = 0;
            }

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
                    if (pi.proj->GetProjectileType() == PT_Bullet)
                    {
                        pi.p1->Position = Vector3::Zero;
                        pi.p2->Position = Vector3::Zero;
                    }
                    else if (pi.proj->GetProjectileType() == PT_Rocket)
                    {
                        // explosion
                    }

					pi.proj->GetGameObject()->Release();
					projectiles.RemoveAt(i);
				}
				else
				{
                    if (pi.proj->GetProjectileType() == PT_Bullet)
                    {
                        Vector3 pos = pi.proj->GetCollider()->GetCenter();
                        Vector3 velo = Vector3::Normalize(pi.proj->GetCollider()->GetRigidBody()->GetVelocity()) * 1.75f;
                        pi.p1->Position = pos - velo;
                        pi.p2->Position = pos + velo;
                    }
                    else if (pi.proj->GetProjectileType() == PT_Rocket)
                    {
                        // Fire
						peFire->Trigger(
							(UInt32)(200.0 * args.Time.ElapsedTime),
							Vector3::TransformCoordinate( 
							Vector3(0.8f, 0, 0),
							Matrix::Transpose(pi.proj->GetGameObject()->PRS.GetWorld())
							) * 100.0f
						);
                    }

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