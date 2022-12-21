#pragma once

#include <string>
#include "Application/AppComponent.h"

struct GLFWwindow;

namespace Application {
	class App;
	class AppComponent;
}

namespace Settings {
	class WindowSettings;
}

namespace Callback {
	class WindowCallback;
}

namespace SceneUtils {
	class SceneManager;
}

namespace Display {

	/* 
		Main Application Components
	*/

	class Window : public Application::AppComponent {
	private:
		friend class Application::App;
		friend class SceneUtils::SceneManager;
		friend class Callback::WindowCallback;

		GLFWwindow* winPtr;

		Settings::WindowSettings* windowSettings;
		Callback::WindowCallback* windowCallback;

		bool initGLEW();
		bool initGLFW();

		void init();
		void runLoop();
		void dispose();

		void pollEvents(int _isOnCallback);

	public:
		Window(const Settings::WindowSettings& _settings);
		Window(const std::string& _title, unsigned int _width, unsigned int _height);
		~Window();

		operator GLFWwindow* ();

		void close();
		void focus();

		Settings::WindowSettings& getWindowSettings();
		Callback::WindowCallback& getWindowCallback();
	};
}

