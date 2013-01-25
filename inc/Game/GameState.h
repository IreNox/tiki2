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
		class Cheater;
		class GameHud;
		class SceneLevel;
		class UnitSelection;
		class TikiBotFactory;
		class ProjectileManager;

		class GameState : public EngineObject, public ConsoleCommandEventHandler
		{
		public:

			UnitSelectionChangedEvent UnitSelectionChanged;

			#if _DEBUG
			bool DrawNavMesh;
			bool DrawRenderTarget;
			bool DrawPhysX;
			bool DrawHud;
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
			inline UnitSelection* GetUnitSelection() { return unitSelection; }
			inline ProjectileManager* GetProjectiles() { return projectiles; }

			inline double GetResource() { return resource; }
			inline void IncrementResource(double toIncrement) { resource += toIncrement; }
			inline void DecrementResource(double toDecrement) { resource -= toDecrement; if (resource < 0) resource = 0; }

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

				T* nT = TIKI_NEW T(this);
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

			void Handle(const HelperLog* sender, const wstring& args);

		private:
			
			double resource;

			bool followHero;

			GameHud* hud;
			Cheater* cheater;
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
