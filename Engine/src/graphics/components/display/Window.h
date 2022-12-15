#pragma once

#include <string>

struct GLFWwindow;

namespace Listener {
	class WindowListener;
}

namespace Display {
	class WindowSettings;

	class Window {
	public:
		Window(const WindowSettings& settings);
		Window(const std::string& title, unsigned int width, unsigned int height);
		~Window();

		//operator overload
		operator GLFWwindow* ();

		void close();
		void focus();

		//temp
		void processFrames();
		void renderDisplay();
		void render(int);

		WindowSettings& getSettings();
		Listener::WindowListener& getWindowListener();

	//private:
		GLFWwindow* winPtr;
		WindowSettings* settings;

		Listener::WindowListener* windowListener;

		bool initGLEW();
		bool initGLFW();
		void initWindow();
	};
}