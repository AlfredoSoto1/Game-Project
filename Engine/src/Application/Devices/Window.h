#pragma once

struct GLFWwindow;

namespace Uranium {

	class Application;
	class WindowSettings;
	class WindowListener;

	class Window {
	private:
		friend class Application;
		friend class WindowListener;

		GLFWwindow* winPtr;

		WindowSettings* settings;
		WindowListener* listener;

		bool initGLEW();

		void init();
		void initCallback();
		void dispose();

	public:
		Window(const char* _title, unsigned int _width, unsigned int _height);
		~Window();

		operator GLFWwindow* ();

		void close();
		void focus();
		void requestAttention();

		void setListener(WindowListener* _listener);

		WindowSettings& getSettings();
	};
}

