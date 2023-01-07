#pragma once

#include <vector>

namespace Uranium {

	class Scene;
	class Application;

	class SceneManager {
	private:
		friend class Scene;
		friend class Application;

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