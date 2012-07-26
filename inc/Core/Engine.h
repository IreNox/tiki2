#pragma once

#include "Core/TypeInc.h"

class Window;

namespace TikiEngine
{
	class Scene;

	struct DrawArgs;
	struct UpdateArgs;

	namespace Modules
	{
		class IAudio;
		class IInput;
		class IPhysics;
		class IGraphics;
		class IContentManager;
	}

	namespace Description
	{
		struct EngineDescription;
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
		
		/*!
		 * @brief Gibt das aktuelle Arbeitsverzeichnis zurück
		 * @return Das aktuelle Arbeitsverzeichnis
		 */
		string GetWorkingDir();

	protected:

		virtual void Draw(const DrawArgs& args);
		virtual void Update(const UpdateArgs& args);

	private:

		string workingDir;

	};
}