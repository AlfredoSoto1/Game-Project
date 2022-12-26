#pragma once

#include "AppProgram/Program/AppControl/AppComponent.h"

struct GLFWwindow;

namespace Application {
	class App;
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

	class Window : public Application::AppComponent {
	private:
		friend class Application::App;
		friend class Listener::WindowListener;

		GLFWwindow* winPtr;

		Settings::WindowSettings* settings;
		Listener::WindowListener* listener;

		bool initGLEW();

		void init();
		void initCallback();
		void dispose();

	public:
		Window(Application::App* _appRef, const char* _title, unsigned int _width, unsigned int _height);
		~Window();

		operator GLFWwindow* ();

		void close();
		void focus();
		void requestAttention();

		void setListener(Listener::WindowListener* _listener);

		Settings::WindowSettings& getSettings();
	};
}

