#pragma once

#include <vector>
#include "Scene.h"

namespace Settings {
	class WindowSettings;
}

namespace StageUtils {
	class Stage {
	public:
		Stage();
		~Stage();

		void init(Settings::WindowSettings* _windowSettings);
		void render();
		void postRender();
		void update();
		void dispose();

		void addScene(const Scene& _scene);
		
	private:
		double lastTime;
		double lastRefresh;
		double timeDifference;
		double lastTimeDifference;

		unsigned short frames;

		std::vector<Scene> scenes;

		Settings::WindowSettings* windowSettings;

		void calcFramerate();
		void limitFramerate();

	};
}