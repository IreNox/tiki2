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


			virtual bool HandleMessage(const Telegram& msg){ return false; }

			//entities should be able to read/write their data to a stream
			virtual void Write(std::ostream& os) const { }
			virtual void Read(std::ifstream& is) { }

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