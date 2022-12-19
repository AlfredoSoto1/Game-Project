#pragma once

#include <vector>

namespace Display {
	class Window;
}

namespace Settings {
	class MouseSettings;
	class WindowSettings;
}

namespace SceneUtils {

	class Scene;

	class SceneManager {
	public:
		SceneManager();
		~SceneManager();

		Settings::MouseSettings& getMouseSettings();
		Settings::WindowSettings& getWindowSettings();

		void addScene(Scene* _scene);

	private:
		friend class Display::Window;

		double lastTime;
		double lastRefresh;
		double timeDifference;
		double lastTimeDifference;

		unsigned short frames;

		bool hasChangedScene;

		Scene* currentScene;

		std::vector<Scene*> scenes;

		Settings::MouseSettings* mouseSettings;
		Settings::WindowSettings* windowSettings;

		void loadMouseSettings(Settings::MouseSettings* _mouseSettings);
		void loadWindowSettings(Settings::WindowSettings* _windowSettings);
		
		void init();
		void draw();
		void afterDraw();
		void update();
		void dispose();

		void limitFramerate();
		void calcFramerate();

	};
}