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

namespace Callback {
	class WindowCallback;
}

namespace Display {

	/* 
		Main Application Components
	*/

	class Window : public Application::AppComponent {
	private:
		friend class Application::App;
		friend class Callback::WindowCallback;

		GLFWwindow* winPtr;

		Settings::WindowSettings* windowSettings;
		Callback::WindowCallback* windowCallback;

		bool initGLEW();

		void init();
		void dispose();

	public:
		Window(Application::App* _appRef, const char* _title, unsigned int _width, unsigned int _height);
		~Window();

		operator GLFWwindow* ();

		void close();
		void focus();
		void requestAttention();

		Settings::WindowSettings& getSettings();
		Callback::WindowCallback& getCallback();
	};
}

