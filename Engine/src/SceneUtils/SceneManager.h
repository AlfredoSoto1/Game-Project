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
		friend class Scene;
		friend class Display::Window;
		friend class Application::App;
		friend class Application::AppComponent;

		volatile double lastTime;
		volatile double lastRefresh;
		volatile double timeDifference;
		volatile double lastTimeDifference;

		volatile unsigned short frames;

		short targetFrames;

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

		short getTargetFPS();

		void setTargetFPS(short _FPS);

		void addScene(Scene* _scene);

	};
}