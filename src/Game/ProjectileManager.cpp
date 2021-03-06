
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
			peAssault = TIKI_NEW PEShootMG(engine);
			peAssault->AddRef();

			prAssault = engine->librarys->CreateComponent<IParticleRenderer>(this);
			prAssault->SetParticleEffect(peAssault);
			prAssault->SetTexture(engine->content->LoadTexture(L"particle/mg"));
			prAssault->AddRef();


			// Smoke
			peSmoke = TIKI_NEW PESmoke(engine);
			peSmoke->SIsAlive(false);
			peSmoke->AddRef();

			prSmoke = engine->librarys->CreateComponent<IParticleRenderer>(this);
			prSmoke->SetTexture(engine->content->LoadTexture(L"particle/smoke"));
			prSmoke->SetParticleEffect(peSmoke);
			prSmoke->AddRef();


			// Fire
			peFire = TIKI_NEW PEFire(engine);
			peFire->SIsAlive(false);
			peFire->AddRef();

			prFire = engine->librarys->CreateComponent<IParticleRenderer>(this);
			prFire->SetTexture(engine->content->LoadTexture(L"particle/fire"));
			prFire->SetParticleEffect(peFire);
			prFire->AddRef();


			// Shockwave
			peShockwave = TIKI_NEW PEShockWave(engine);
			peShockwave->SIsAlive(false);
			peShockwave->AddRef();

			prShockWave = engine->librarys->CreateComponent<IParticleRenderer>(this);
			prShockWave->SetTexture(engine->content->LoadTexture(L"particle/Shockwave")); 
			prShockWave->SetParticleEffect(peShockwave);
			prShockWave->AddRef();


			// debris
			peDebris = TIKI_NEW PEDebris(engine);
			peDebris->SIsAlive(false);
			peDebris->AddRef();

			prDebris = engine->librarys->CreateComponent<IParticleRenderer>(this);
			prDebris->SetTexture(engine->content->LoadTexture(L"particle/debris")); 
			prDebris->SetParticleEffect(peDebris);
			prDebris->AddRef();

            // explosion
            peExplosion = TIKI_NEW PEExplosion(engine);
            peExplosion->SIsAlive(false);
            peExplosion->AddRef();

            prExplosion = engine->librarys->CreateComponent<IParticleRenderer>(this);
            prExplosion->SetTexture(engine->content->LoadTexture(L"particle/explosion")); 
            prExplosion->SetParticleEffect(peExplosion);
            prExplosion->AddRef();

			// round sparks
			peRoundSparks = TIKI_NEW PERoundSparks(engine);
			peRoundSparks->SIsAlive(false);
			peRoundSparks->AddRef();

			prRoundSparks = engine->librarys->CreateComponent<IParticleRenderer>(this);
			prRoundSparks->SetTexture(engine->content->LoadTexture(L"particle/roundsparks")); 
			prRoundSparks->SetParticleEffect(peRoundSparks);
			prRoundSparks->AddRef();


			// Blood
			peBlood = TIKI_NEW PEBlood(engine);
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

			SafeRelease(&peDebris);
			SafeRelease(&prDebris);

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
			peBlood->setNewRandom(Random(0, 1));
			peBlood->Trigger(elapsedTime, releasePerSecound, pos);
		}

		void ProjectileManager::AddExplosionEffect(const Vector3& pos, bool addDebrisEffect)
		{
			peExplosion->Trigger(1, 2000, pos);
			peShockwave->Trigger(1, 1, pos);
			peRoundSparks->Trigger(1, 5, pos);

			if (addDebrisEffect)
				peDebris->Trigger(1, 20, pos);

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
						AddExplosionEffect(Matrix::TransformCoordinate(
							Vector3(0, 0, 0),
							Matrix::Transpose(pi.proj->GetGameObject()->PRS.GetWorld())
							),
							false
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
