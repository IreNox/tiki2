#pragma once

#include "Core/TypeGlobals.h"

#include "Game/GamePart.h"
#include "Game/NavigationMesh.h"

#include "Core/IPhysicsMaterial.h"

#include "Game/EventUnitSelectionChanged.h"

namespace TikiEngine
{
	namespace Game
	{
		using namespace TikiEngine::AI;
		using namespace TikiEngine::Resources;

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
			void InitLevel();
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

			#pragma region Member - GetPart
			template <typename T>
			T* GetPart(int id)
			{
				UInt32 i = 0;
				while (i < gameParts.Count())
				{
					T* part = dynamic_cast<T*>(gameParts[i]);
					if (part != 0 && part->GetID() == id) return part;

					i++;
				}

				T* nT = new T(this);
				nT->SetID(id);
				gameParts.Add(nT);

				return nT;
			}

			template <typename T>
			void GetParts(List<T*>& list)
			{
				UInt32 i = 0;
				while (i < gameParts.Count())
				{
					T* part = dynamic_cast<T*>(gameParts[i]);

					if (part != 0) list.Add(part);

					i++;
				}
			}
			#pragma endregion
			inline void AddPart(GamePart* part) { gameParts.Add(part); }

			inline IPhysicsMaterial* GetDefaultMaterial() { return defaultMaterial; }

		private:
			
			double resource;

			GameHud* hud;
			SceneLevel* scene;
			List<GamePart*> gameParts;

			NavigationMesh* navMesh;			
			TikiBotFactory* botFactory;
			UnitSelection* unitSelection;
			ProjectileManager* projectiles;

			IPhysicsMaterial* defaultMaterial;

		};
	}
}
