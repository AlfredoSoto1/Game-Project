#pragma once

#include <vector>

#include "Framework/AppManager/AppComponent.h"

namespace FrameworkEngine {
	class Application;
	class AppComponent;
}

namespace SceneControl {

	class Scene;

	class SceneManager : public FrameworkEngine::AppComponent {
	private:
		friend class Scene;
		friend class FrameworkEngine::Application;
		friend class FrameworkEngine::AppComponent;

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
		SceneManager(FrameworkEngine::Application* _reference);
		~SceneManager();

		short getTargetFPS();

		void setTargetFPS(short _FPS);

		void addScene(Scene* _scene);

	};
}