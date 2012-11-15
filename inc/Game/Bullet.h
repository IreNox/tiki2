#pragma once

#include "Game/Projectile.h"

namespace TikiEngine
{
    namespace AI
    {
        class Bullet : public Projectile
        {
        public:
            Bullet(GameState* gameState, GameObject* gameObject);
            ~Bullet();

            void Init(ProjectileDescription desc, const UpdateArgs& args);

            void Handle(ICollider* sender, const TriggerEnterArgs& args);

            void Update(const UpdateArgs& args);


        };


    }
}