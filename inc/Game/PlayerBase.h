#pragma once

#include "Game/GamePart.h"
#include "Game/LevelPoint.h"

#include "Core/TikiTimer.h"
#include "Core/GameObject.h"
#include "Core/ISphereCollider.h"

#include "Game/EventBotDead.h"
#include "Game/TikiAttModifier.h"

namespace TikiEngine
{
	namespace Game
	{
		class PlayerBase : public GamePart, public BotDeadEventHandler, public TriggerEnterEventHandler, public TriggerExitEventHandler
		{
		public:

			LevelPoint* SpawnPoint;

			GameObject* Hero;

			// Buildings
			GameObject* HeroPlatform;
			GameObject* MainBuilding;
			List<GameObject*> UnitSpawnBuildings;

			PlayerBase(GameState* state);
			~PlayerBase();
			
			void Init();

			void Update(const UpdateArgs& args);
			void Draw(const DrawArgs& args);

			void Handle(TikiBot* sender, const BotDeadArgs& args);
			void Handle(ICollider* sender, const TriggerEnterArgs& args);
			void Handle(ICollider* sender, const TriggerExitArgs& args);
			
			bool IsHeroDead() { return heroDead; }

		private:

			bool heroDead;
			TikiTimer heroDeadTimer;

			Vector3 heroStartPos;

			TikiAttModifier attmodHealthReg;

		};
	}
}