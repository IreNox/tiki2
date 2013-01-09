#include "Game/Rocket.h"
#include "Game/TikiBot.h"
#include "Core/ITriangleMeshCollider.h"
#include "Game/SceneLevel.h"


namespace TikiEngine
{
	namespace AI
	{
		Rocket::Rocket(GameState* gameState, GameObject* gameObject)
			: Projectile(gameState, gameObject)			
		{
			aoeRadius = 20.0f;
			heal = false;
            projectileType = PT_Rocket;
		}

		Rocket::~Rocket()
		{

		}

		void Rocket::Init(ProjectileDescription desc, float radius, bool heal)
		{
			Projectile::Init(desc);
			this->aoeRadius = radius;
			this->heal = heal;

			Vector3 toTarget = Vector3::Normalize(desc.Target - desc.Origin);
			toTarget = toTarget * desc.MaxSpeed;

			sphere->SetCenter(desc.Origin);
			sphere->GetRigidBody()->SetMass(desc.Mass);
			sphere->GetRigidBody()->SetVelocity(toTarget);
		}


		void Rocket::Handle(ICollider* sender, const TriggerEnterArgs& args)
		{
			TikiBot* bot = args.otherCollider->GetGameObject()->GetComponent<TikiBot>();
			if (bot != 0)
			{
				if (bot->ID() != shooterID)
				{
					if (heal)
					{
						if (bot->GetFaction() == shooter->GetFaction())
						{
							impacted = true;
							dead = true;
							InflictAoeHeal();
						}
					}
					else
					{
						if (bot->GetFaction() != shooter->GetFaction())
						{
							impacted = true;
							dead = true;
							InflictAoEDamage();
						}
					}
				}

			}
			else
			{
				ITriangleMeshCollider* coll = dynamic_cast<ITriangleMeshCollider*>(args.otherCollider);
				if (coll != 0)
				{
					impacted = true;
					dead = true;

					if (heal)
						InflictAoeHeal();
					else
						InflictAoEDamage();
				}
			}
		}

		void Rocket::Update(const UpdateArgs& args)
		{
			// handle lifetime
			Projectile::Update(args);
		}


		void Rocket::InflictAoEDamage()
		{
#if TIKI_USE_SCENEGRAPH
			gameState->GetScene()->SceneGraph.DoWithinRange(GetCollider()->GetCenter(), aoeRadius, [&](GameObject* go)
			{
				TikiBot* bot = go->GetComponent<TikiBot>();
				if(bot != 0 && bot->GetFaction() != shooter->GetFaction())
				{
					bot->ReduceHealth(damage);
					if(bot->IsDead())
						shooter->KilledBot(bot);
				}
			});
#else
			// loop all bots and make distance check
			for (UInt32 i = 0; i < gameState->GetScene()->GetElements().Count(); i++)
			{
				GameObject* current = gameState->GetScene()->GetElements().Get(i);
				TikiBot* curBot = current->GetComponent<TikiBot>();
				if (curBot != 0 && curBot->GetFaction() != shooter->GetFaction())
				{
					float rad = aoeRadius + (float)curBot->BRadius();
					Vector2 projPos = Vector2(GetCollider()->GetCenter().X, GetCollider()->GetCenter().Z);
					float dist = Vector2::Distance(projPos, curBot->Pos());
					if (dist < rad)
					{
						curBot->ReduceHealth(damage);
						if (curBot->IsDead()) shooter->KilledBot(curBot);
					}
				}
			}
#endif
		}

		void Rocket::InflictAoeHeal()
		{
#if TIKI_USE_SCENEGRAPH
			gameState->GetScene()->SceneGraph.DoWithinRange(GetCollider()->GetCenter(), aoeRadius, [&](GameObject* go)
			{
				TikiBot* bot = go->GetComponent<TikiBot>();
				if(bot != 0 && bot->GetFaction() != shooter->GetFaction())
				{
					bot->IncreaseHealth(damage);
				}
			});
#else

			// loop all bots and make distance check
			for (UInt32 i = 0; i < gameState->GetScene()->GetElements().Count(); i++)
			{
				GameObject* current = gameState->GetScene()->GetElements().Get(i);
				TikiBot* curBot = current->GetComponent<TikiBot>();
				if (curBot != 0 && curBot->GetFaction() == shooter->GetFaction())
				{
					float rad = aoeRadius + (float)curBot->BRadius();
					Vector2 projPos = Vector2(GetCollider()->GetCenter().X, GetCollider()->GetCenter().Z);
					float dist = Vector2::Distance(projPos, curBot->Pos());
					if (dist < rad)
					{
						curBot->IncreaseHealth(damage);
					}
				}
			}
#endif
		}
	}
}