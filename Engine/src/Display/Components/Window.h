#pragma once

#include <string>

struct GLFWwindow;

namespace Settings {
	class MouseSettings;
	class WindowSettings;
}

namespace Callback {
	class MouseCallback;
	class WindowCallback;
}

namespace SceneUtils {
	class SceneManager;
}

namespace Display {
	class Window {
	public:
		Window(const Settings::WindowSettings&& _settings);
		Window(const std::string& _title, unsigned int _width, unsigned int _height);
		~Window();

		operator GLFWwindow* ();

		void start();
		void close();
		void focus();

		SceneUtils::SceneManager& getSceneManager();

		Settings::MouseSettings& getMouseSettings();
		Settings::WindowSettings& getWindowSettings();

		Callback::MouseCallback& getMouseCallback();
		Callback::WindowCallback& getWindowCallback();

	private:
		friend class Callback::WindowCallback;

		GLFWwindow* winPtr;

		Settings::MouseSettings* mouseSettings;
		Settings::WindowSettings* windowSettings;

		Callback::MouseCallback* mouseCallback;
		Callback::WindowCallback* windowCallback;

		SceneUtils::SceneManager* sceneManager;

		bool initGLEW();
		bool initGLFW();

		void pollEvents(int _isOnCallback);

		void runLoop();
		void finish();
	};
}