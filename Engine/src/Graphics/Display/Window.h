#pragma once

#include "Framework/AppManager/AppComponent.h"

struct GLFWwindow;

namespace FrameworkEngine {
	class Application;
	class AppComponent;
}

namespace Settings {
	class WindowSettings;
}

namespace Listener {
	class WindowListener;
}

namespace Display {

	/* 
		Main Application Components
	*/

	class Window : public FrameworkEngine::AppComponent {
	private:
		friend class FrameworkEngine::Application;
		friend class Listener::WindowListener;

		GLFWwindow* winPtr;

		Settings::WindowSettings* settings;
		Listener::WindowListener* listener;

		bool initGLEW();

		void init();
		void initCallback();
		void dispose();

	public:
		Window(FrameworkEngine::Application* _reference, const char* _title, unsigned int _width, unsigned int _height);
		~Window();

		operator GLFWwindow* ();

		void close();
		void focus();
		void requestAttention();

		void setListener(Listener::WindowListener* _listener);

		Settings::WindowSettings& getSettings();
	};
}

