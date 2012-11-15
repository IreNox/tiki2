#include "Game/Bullet.h"
#include "Game/TikiBot.h"
#include "Core/ITriangleMeshCollider.h"

namespace TikiEngine
{
    namespace AI
    {
        Bullet::Bullet(GameState* gameState, GameObject* gameObject)
            : Projectile(gameState, gameObject)
        {

        }

        Bullet::~Bullet()
        {

        }

        void Bullet::Init(ProjectileDescription desc, const UpdateArgs& args)
        {
            Projectile::Init(desc, args);

            Vector3 vel = Vector3::Normalize(desc.Target - desc.Origin);
            vel = vel* desc.MaxSpeed;
            sphere->GetRigidBody()->SetMass(desc.Mass);
            sphere->GetRigidBody()->SetVelocity(vel);
        }


        void Bullet::Handle(ICollider* sender, const TriggerEnterArgs& args)
        {
            // TODO: faction
            TikiBot* bot = args.otherCollider->GetGameObject()->GetComponent<TikiBot>();
            if (bot != 0)
            {
                if (bot->ID() != shooterID)
                {
                    impacted = true;
                    dead = true;

                    OutputDebugString(L"bot hit, health reduced. \n");
                    bot->ReduceHealth(damage);
                }
            }
            else
            {
                // ITriangleMeshCollider* coll = args.otherCollider->GetGameObject()->GetComponent<ITriangleMeshCollider>();
                ITriangleMeshCollider* coll = dynamic_cast<ITriangleMeshCollider*>(args.otherCollider);
                if (coll != 0)
                {
                    impacted = true;
                    dead = true;
                }
            }
        }


        void Bullet::Update(const UpdateArgs& args)
        {
            // handle lifetime
            Projectile::Update(args);
        }
    }
}