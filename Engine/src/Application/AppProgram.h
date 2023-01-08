#pragma once

#include <vector>

namespace Uranium {

	class Scene;
	class Application;

	class AppProgram {
	private:
		friend class Scene;
		friend class Application;

		bool hasChangedScene;

		std::vector<Scene*> activeScenes;

		Scene* currentScene;

		void draw();
		void afterDraw();
		void update();

	public:
		virtual void init() = 0;
		virtual void dispose() = 0;
		
		AppProgram();
		virtual ~AppProgram();

		void push_firstNewScene(Scene* _scenePtr);
	};
}