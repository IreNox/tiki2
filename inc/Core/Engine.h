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
	
		Scene* scene;

		/*!
		 * @brief Erstellt eine neue instanz von Engine.
		 */
		Engine();
		
		/*!
		 * @brief Zerst�rt die Engine
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

		EngineDescription* GetEngineDescription(); 

	protected:

		virtual void Draw(const DrawArgs& args);
		virtual void Update(const UpdateArgs& args);

	private:

		EngineDescription desc;

		List<IModule*> loadedModules;

		bool initModule(IModule* module);

	};
}