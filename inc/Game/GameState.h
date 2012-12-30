#pragma once

#include "Core/TypeGlobals.h"

#include "Game/GamePart.h"
#include "Game/NavigationMesh.h"

#include "Game/EventUnitSelectionChanged.h"

namespace TikiEngine
{
	namespace Game
	{
		using namespace TikiEngine::AI;

		class Level;
		class GameHud;
		class SceneLevel;
		class UnitSelection;
		class TikiBotFactory;
		class ProjectileManager;

		class GameState : public EngineObject
		{
		public:

			UnitSelectionChangedEvent UnitSelectionChanged;

			#if _DEBUG
			bool DrawNavMesh;
			bool DrawRenderTarget;
			bool DrawPhysX;
			#endif

			GameState(Engine* engine, SceneLevel* scene);
			~GameState();

			void LoadLevel(Level* level);
			void DisposeLevel();

			inline Engine* GetEngine() { return engine; }
			inline SceneLevel* GetScene() { return scene; }
			inline NavigationMesh* GetNavMesh() { return navMesh; }
			inline List<GamePart*>& GetGameParts() { return gameParts; }
			inline TikiBotFactory* GetBotFactory() { return botFactory; }
			inline ProjectileManager* GetProjectiles() { return projectiles; }

			inline double GetResource() { return resource; }
			inline void IncrementResource(double toIncrement) { resource += toIncrement; }
			inline void DecrementResource(double toDecrement) { resource -= toDecrement; }

			void Draw(const DrawArgs& args);
			void Update(const UpdateArgs& args);

			template <typename T>
			T* GetPart(int id)
			{
				UInt32 i = 0;
				while (i < gameParts.Count())
				{
					T* part = dynamic_cast<T*>(gameParts[i]);
					if (part != 0 && part->GetID()) return part;

					i++;
				}

				T* nT = new T(this);
				gameParts.Add(nT);

				return nT;
			}
			inline void AddPart(GamePart* part) { gameParts.Add(part); }

		private:
			
			double resource;

			GameHud* hud;
			SceneLevel* scene;
			List<GamePart*> gameParts;

			NavigationMesh* navMesh;			
			TikiBotFactory* botFactory;
			UnitSelection* unitSelection;
			ProjectileManager* projectiles;

		};
	}
}
