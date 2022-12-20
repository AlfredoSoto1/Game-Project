#pragma once

#include <vector>

#include "Application/AppComponent.h"

namespace Application {
	class App;
	class AppComponent;
}

namespace Display {
	class Window;
}

namespace SceneUtils {

	class Scene;

	class SceneManager : public Application::AppComponent {
	private:
		friend class Application::App;
		friend class Display::Window;

		double lastTime;
		double lastRefresh;
		double timeDifference;
		double lastTimeDifference;

		unsigned short frames;

		bool hasChangedScene;

		Scene* currentScene;

		std::vector<Scene*> scenes;

		void init();
		void draw();
		void afterDraw();
		void update();
		void dispose();

		void limitFramerate();
		void calcFramerate();

	public:
		SceneManager();
		~SceneManager();

		void addScene(Scene* _scene);

	};
}