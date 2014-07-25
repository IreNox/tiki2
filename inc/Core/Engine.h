#pragma once

#include "Core/TypeDef.h"
#include "Core/List.h"

#include "Core/HelperLog.h"
#include "Core/HelperPath.h"

#include "Core/EngineDescription.h"

#include "Core/CriticalSection.h"
#include "Core/Thread.h"

#include "extern/sqlite3.h"

namespace TikiEngine
{
	class Scene;
	
	struct DrawArgs;
	struct UpdateArgs;

	namespace Modules
	{
		class IModule;

		class WindowModule;
		class LibraryManager;

		class IInput;
		class IPhysics;
		class IGraphics;
		class ISoundSystem;
		class ISpriteBatch;
		class IContentManager;
	}

	using namespace TikiEngine::Modules;
	using namespace TikiEngine::Description;

	class Engine
	{
	public:

		IInput* input;
		IPhysics* physics;
		IGraphics* graphics;
		ISoundSystem* sound;
		ISpriteBatch* sprites;
		IContentManager* content;

		WindowModule* window;
		LibraryManager* librarys;

		HelperPath HPath;
		HelperLog HLog;
	
		/*!
		 * @brief Create TIKI_NEW instance of Engine.
		 */
		Engine();
		~Engine();

		/*! @brief Initialize the Engine.
		 *  @param desc Description for Engine initialization
		 *  @return Successful
		 */
		bool Initialize(EngineDescription& desc);

		/*! @brief Start Render loop */
		void Run();
		/*! @brief Exit Render loop */
		void Exit();

		/*! @brief Get current Scene */
		Scene* GetScene() const;
		/*! @brief go back to main menu */
		void SetSceneMenu();
		/*! @brief Set and initialize a new Scene */
		void SetScene(Scene* scene);


		/*! @brief Get the Scene there was showing at loading */
		Scene* GetLoadingScene() const;
		/*! @brief Set and initialize a new Scene */
		void SetLoadingScene(Scene* scene);


		/*! @brief Destroy Engine-Object and unload all Modules */
		void Dispose();

		/*! @brief Get the Description of this Engine instance. */
		inline EngineDescription& GetEngineDescription()
		{
			return desc;
		}

		/* @brief Get Database-Connection object. */
		inline sqlite3* GetDB()
		{
			return dataBase;
		}

		inline bool GetShadowsEnabled() { return useShadows; }
		inline void SetShadowsEnabled(bool use) { useShadows = use; }

	protected:

		void Draw(UpdateArgs& args);
		void Update(UpdateArgs& args);

	private:

		Scene* scene;
		Scene* sceneMenu;

		bool isLoading;
		bool isLoadingFinish;
		Scene* loadingScene;
		CriticalSection critLoading;
		Thread<Engine, Scene>* loadingThread;

		sqlite3* dataBase;

		bool useShadows;

#if _DEBUG
		UInt32 fpsIndex;
		double fpsAve;
		double fpsCache[5];
#endif
		UInt64 frameCount;

		EngineDescription desc;

		List<IModule*> loadedModules;

		void initScene(Scene* scene);
		bool initModule(IModule* module);

	};
}