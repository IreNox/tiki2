#pragma once

#include "Core/TypeInc.h"
#include "Core/EngineDescription.h"

#include "Core/List.h"

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

		class IAudio;
		class IInput;
		class IPhysics;
		class IGraphics;
		class IContentManager;
	}

	using namespace TikiEngine::Modules;
	using namespace TikiEngine::Description;

	class Engine
	{
	public:

		IAudio* audio;
		IInput* input;
		IPhysics* physics;
		IGraphics* graphics;
		IContentManager* content;

		Window* window;
		LibraryManager* librarys;
	
		Scene* scene;

		/*!
		 * @brief Erstellt eine neue instanz von Engine.
		 */
		Engine();
		
		/*!
		 * @brief Zerstört die Engine
		 */
		~Engine();

		/*!
		 * @brief Iniziert die Engine.
		 *
		 * @param desc Inizierungs Variable
		 *
		 * @return Erfolgreich
		 */
		bool Initialize(EngineDescription& desc);

		/*!
		 * @brief Startet die Anwendungsschleife
		 */
		void Run();

	protected:

		virtual void Draw(const DrawArgs& args);
		virtual void Update(const UpdateArgs& args);

	private:

		EngineDescription desc;

		List<IModule*> loadedModules;

		bool initModule(IModule* module);

	};
}