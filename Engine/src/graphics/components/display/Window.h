#pragma once

#include <string>

struct GLFWwindow;

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
	//private:
		GLFWwindow* winPtr;
		WindowSettings* settings;

		bool initGLEW();
		bool initGLFW();
		void initWindow();
	};
}