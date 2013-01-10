#pragma once

#include "Game/BaseGameEntity.h"
#include "Core/IBoxCollider.h"

namespace TikiEngine
{
	namespace AI
	{


		class Trigger : public BaseGameEntity, public TriggerEnterEventHandler, public TriggerExitEventHandler
		{

		public:

			Trigger(GameState* gameState, GameObject* gameObject);
			~Trigger();

			virtual void Draw(const DrawArgs& args) {}
			virtual void Update(const UpdateArgs& args);

		protected:

			virtual void Handle(ICollider* sender, const TriggerEnterArgs& args);
			virtual void Handle(ICollider* sender, const TriggerExitArgs& args);

			IBoxCollider* boxCollider;
			bool needUpdate;
		};


	}
}