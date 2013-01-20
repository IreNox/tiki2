
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
            // assault
			peAssault = new PEShootMG(engine);
			peAssault->AddRef();

			prAssault = engine->librarys->CreateComponent<IParticleRenderer>(this);
			prAssault->SetParticleEffect(peAssault);
			prAssault->SetTexture(engine->content->LoadTexture(L"particle/mg"));
			prAssault->AddRef();


			// Smoke
			peSmoke = new PESmoke(engine);
			peSmoke->SIsAlive(false);
			peSmoke->AddRef();

			prSmoke = engine->librarys->CreateComponent<IParticleRenderer>(this);
			prSmoke->SetTexture(engine->content->LoadTexture(L"particle/smoke"));
			prSmoke->SetParticleEffect(peSmoke);
			prSmoke->AddRef();


			// Fire
			peFire = new PEFire(engine);
			peFire->SIsAlive(false);
			peFire->AddRef();

			prFire = engine->librarys->CreateComponent<IParticleRenderer>(this);
			prFire->SetTexture(engine->content->LoadTexture(L"particle/fire"));
			prFire->SetParticleEffect(peFire);
			prFire->AddRef();


			// Shockwave
			peShockwave = new PEShockWave(engine);
			peShockwave->SIsAlive(false);
			peShockwave->AddRef();

			prShockWave = engine->librarys->CreateComponent<IParticleRenderer>(this);
			prShockWave->SetTexture(engine->content->LoadTexture(L"particle/Shockwave")); 
			prShockWave->SetParticleEffect(peShockwave);
			prShockWave->AddRef();


            // explosion
            peExplosion = new PEExplosion(engine);
            peExplosion->SIsAlive(false);
            peExplosion->AddRef();

            prExplosion = engine->librarys->CreateComponent<IParticleRenderer>(this);
            prExplosion->SetTexture(engine->content->LoadTexture(L"particle/explosion")); 
            prExplosion->SetParticleEffect(peExplosion);
            prExplosion->AddRef();

			// round sparks
			peRoundSparks = new PERoundSparks(engine);
			peRoundSparks->SIsAlive(false);
			peRoundSparks->AddRef();

			prRoundSparks = engine->librarys->CreateComponent<IParticleRenderer>(this);
			prRoundSparks->SetTexture(engine->content->LoadTexture(L"particle/roundsparks")); 
			prRoundSparks->SetParticleEffect(peRoundSparks);
			prRoundSparks->AddRef();


			// Blood
			peBlood = new PEBlood(engine);
			peBlood->SIsAlive(false);
			peBlood->AddRef();

			prBlood = engine->librarys->CreateComponent<IParticleRenderer>(this);
			prBlood->SetTexture(engine->content->LoadTexture(L"particle/blood")); 
			prBlood->SetParticleEffect(peBlood);
			prBlood->AddRef();
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

            SafeRelease(&peSmoke);
            SafeRelease(&prSmoke);

            SafeRelease(&peExplosion);
            SafeRelease(&prExplosion);

			SafeRelease(&peBlood);
			SafeRelease(&prBlood);

			SafeRelease(&peShockwave);
			SafeRelease(&prShockWave);

			SafeRelease(&peRoundSparks);
			SafeRelease(&prRoundSparks);

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

		void ProjectileManager::AddBloodEffect(double elapsedTime, double releasePerSecound, const Vector3& pos)
		{
			peBlood->Trigger(elapsedTime, releasePerSecound, pos);
		}

		#pragma endregion
		
		#pragma region Member - Update
		void ProjectileManager::Update(const UpdateArgs& args)
		{
			UInt32 i = 0;
			while (i < projectiles.Count())
			{
				ProjInfo& pi = projectiles[i];

                //pi.proj->Update(args);
                pi.proj->GetGameObject()->Update(args);

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
                        peExplosion->Trigger(
							1,
                            2000,
                            Matrix::TransformCoordinate(
								Vector3(0, 0, 0),
								Matrix::Transpose(pi.proj->GetGameObject()->PRS.GetWorld())
                            )
                        );

						peShockwave->Trigger(
							1,
							1,
							Matrix::TransformCoordinate(
							Vector3(0, 0, 0),
							Matrix::Transpose(pi.proj->GetGameObject()->PRS.GetWorld())
							)
						);

						peRoundSparks->Trigger(
							1,
							5,
							Matrix::TransformCoordinate(
							Vector3(0, 0, 0),
							Matrix::Transpose(pi.proj->GetGameObject()->PRS.GetWorld())
							)
						);

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
							args.Time.ElapsedTime,
                            200,
                            Matrix::TransformCoordinate( 
								Vector3(0, 0, 0),
								Matrix::Transpose(pi.proj->GetGameObject()->PRS.GetWorld())
                            )
                        );

                        // smoke
                        peSmoke->Trigger(
							args.Time.ElapsedTime,
                            200,
                            Matrix::TransformCoordinate(
								Vector3(0, 0, 0),
								Matrix::Transpose(pi.proj->GetGameObject()->PRS.GetWorld())
                            )
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
