#pragma once

#include "Core/TypeDef.h"
#include "Core/List.h"

#include "Core/EngineDescription.h"

namespace TikiEngine
{
	class Scene;
	
	struct DrawArgs;
	struct UpdateArgs;

	namespace Modules
	{
		class IModule;

		class Window;
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

		Window* window;
		LibraryManager* librarys;
	
		/*!
		 * @brief Create new instance of Engine.
		 */
		Engine();
		~Engine();

		/*!
		 * @brief Initialize the Engine.
		 *
		 * @param desc Variable
		 *
		 * @return Successful
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

		EngineDescription* GetEngineDescription(); 

	protected:

		virtual void Draw(const DrawArgs& args);
		virtual void Update(const UpdateArgs& args);

	private:

		Scene* scene;

		EngineDescription desc;

		List<IModule*> loadedModules;

		bool initModule(IModule* module);

	};
}