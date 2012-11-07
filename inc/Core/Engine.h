#pragma once

#include "Core/TypeDef.h"
#include "Core/List.h"

#include "Core/HelperPath.h"
#include "Core/BufferState.h"
#include "Core/EngineDescription.h"

namespace TikiEngine
{
	class Scene;
	
	class Mutex;
	template <typename T>
	class Thread;

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

		const HelperPath HPath;
	
		/*!
		 * @brief Create new instance of Engine.
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
		/*! @brief Set and initialize a new Scene */
		void SetScene(Scene* scene);

		/*! @brief Destroy Engine-Object and unload all Modules */
		void Dispose();

		/*! @brief Get the BufferState for multi threading. */
		inline BufferState& GetState()
		{
			return state;
		}

		/*! @brief Get the Description of this Engine instance. */
		inline EngineDescription& GetEngineDescription()
		{
			return desc;
		}

	protected:

		void Draw(void*);
		void Update(void*);

	private:

		Scene* scene;

		//Thread<Engine>* threadDraw;
		//Thread<Engine>* threadUpdate;
		//Mutex* csDraw;
		//Mutex* csUpdate;
		//Mutex* csEngine;

#if _DEBUG
		UInt32 fpsIndex;
		double fpsMin;
		double fpsAve;
		double fpsMax;
		double fpsCache[5];
#endif

		BufferState state;
		EngineDescription desc;

		List<IModule*> loadedModules;

		bool initModule(IModule* module);

	};
}